/*
 *    Copyright (c) 2019, The OpenThread Authors.
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    3. Neither the name of the copyright holder nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *    POSSIBILITY OF SUCH DAMAGE.
 */

#define OTBR_LOG_TAG "NCP"

#include "ncp/ncp_openthread.hpp"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <openthread/backbone_router_ftd.h>
#include <openthread/dataset.h>
#include <openthread/dnssd_server.h>
#include <openthread/logging.h>
#include <openthread/nat64.h>
#include <openthread/srp_server.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/trel.h>
#include <openthread/platform/logging.h>
#include <openthread/platform/misc.h>
#include <openthread/platform/radio.h>
#include <openthread/platform/settings.h>

#include "common/code_utils.hpp"
#include "common/logging.hpp"
#include "common/types.hpp"
#if OTBR_ENABLE_FEATURE_FLAGS
#include "proto/feature_flag.pb.h"
#endif

namespace otbr {
namespace Ncp {

static const uint16_t kThreadVersion11 = 2; ///< Thread Version 1.1
static const uint16_t kThreadVersion12 = 3; ///< Thread Version 1.2
static const uint16_t kThreadVersion13 = 4; ///< Thread Version 1.3

ControllerOpenThread::ControllerOpenThread(const char                      *aInterfaceName,
                                           const std::vector<const char *> &aRadioUrls,
                                           const char                      *aBackboneInterfaceName,
                                           bool                             aDryRun,
                                           bool                             aEnableAutoAttach)
    : mInstance(nullptr)
    , mEnableAutoAttach(aEnableAutoAttach)
{
    VerifyOrDie(aRadioUrls.size() <= OT_PLATFORM_CONFIG_MAX_RADIO_URLS, "Too many Radio URLs!");

    memset(&mConfig, 0, sizeof(mConfig));

    mConfig.mInterfaceName         = aInterfaceName;
    mConfig.mBackboneInterfaceName = aBackboneInterfaceName;
    mConfig.mDryRun                = aDryRun;

    for (const char *url : aRadioUrls)
    {
        mConfig.mRadioUrls[mConfig.mRadioUrlNum++] = url;
    }
    mConfig.mSpeedUpFactor = 1;
}

ControllerOpenThread::~ControllerOpenThread(void)
{
    // Make sure OpenThread Instance was gracefully de-initialized.
    assert(mInstance == nullptr);
}

otbrLogLevel ControllerOpenThread::ConvertToOtbrLogLevel(otLogLevel aLogLevel)
{
    otbrLogLevel otbrLogLevel;

    switch (aLogLevel)
    {
    case OT_LOG_LEVEL_NONE:
        otbrLogLevel = OTBR_LOG_EMERG;
        break;
    case OT_LOG_LEVEL_CRIT:
        otbrLogLevel = OTBR_LOG_CRIT;
        break;
    case OT_LOG_LEVEL_WARN:
        otbrLogLevel = OTBR_LOG_WARNING;
        break;
    case OT_LOG_LEVEL_NOTE:
        otbrLogLevel = OTBR_LOG_NOTICE;
        break;
    case OT_LOG_LEVEL_INFO:
        otbrLogLevel = OTBR_LOG_INFO;
        break;
    case OT_LOG_LEVEL_DEBG:
    default:
        otbrLogLevel = OTBR_LOG_DEBUG;
        break;
    }

    return otbrLogLevel;
}

#if OTBR_ENABLE_FEATURE_FLAGS
/* Converts ProtoLogLevel to otbrLogLevel */
otbrLogLevel ConvertProtoToOtbrLogLevel(ProtoLogLevel aProtoLogLevel)
{
    otbrLogLevel otbrLogLevel;

    switch (aProtoLogLevel)
    {
    case PROTO_LOG_EMERG:
        otbrLogLevel = OTBR_LOG_EMERG;
        break;
    case PROTO_LOG_ALERT:
        otbrLogLevel = OTBR_LOG_ALERT;
        break;
    case PROTO_LOG_CRIT:
        otbrLogLevel = OTBR_LOG_CRIT;
        break;
    case PROTO_LOG_ERR:
        otbrLogLevel = OTBR_LOG_ERR;
        break;
    case PROTO_LOG_WARNING:
        otbrLogLevel = OTBR_LOG_WARNING;
        break;
    case PROTO_LOG_NOTICE:
        otbrLogLevel = OTBR_LOG_NOTICE;
        break;
    case PROTO_LOG_INFO:
        otbrLogLevel = OTBR_LOG_INFO;
        break;
    case PROTO_LOG_DEBUG:
    default:
        otbrLogLevel = OTBR_LOG_DEBUG;
        break;
    }

    return otbrLogLevel;
}
#endif

otLogLevel ControllerOpenThread::ConvertToOtLogLevel(otbrLogLevel aLevel)
{
    otLogLevel level;

    switch (aLevel)
    {
    case OTBR_LOG_EMERG:
    case OTBR_LOG_ALERT:
    case OTBR_LOG_CRIT:
        level = OT_LOG_LEVEL_CRIT;
        break;
    case OTBR_LOG_ERR:
    case OTBR_LOG_WARNING:
        level = OT_LOG_LEVEL_WARN;
        break;
    case OTBR_LOG_NOTICE:
        level = OT_LOG_LEVEL_NOTE;
        break;
    case OTBR_LOG_INFO:
        level = OT_LOG_LEVEL_INFO;
        break;
    case OTBR_LOG_DEBUG:
    default:
        level = OT_LOG_LEVEL_DEBG;
        break;
    }

    return level;
}

otError ControllerOpenThread::SetOtbrAndOtLogLevel(otbrLogLevel aLevel)
{
    otError error = OT_ERROR_NONE;
    otbrLogSetLevel(aLevel);
    error = otLoggingSetLevel(ConvertToOtLogLevel(aLevel));
    return error;
}

void ControllerOpenThread::Init(void)
{
    otbrError  error = OTBR_ERROR_NONE;
    otLogLevel level = ConvertToOtLogLevel(otbrLogGetLevel());

#if OTBR_ENABLE_FEATURE_FLAGS && OTBR_ENABLE_TREL
    FeatureFlagList featureFlagList;
#endif

    VerifyOrExit(otLoggingSetLevel(level) == OT_ERROR_NONE, error = OTBR_ERROR_OPENTHREAD);

    mInstance = otSysInit(&mConfig);
    assert(mInstance != nullptr);

    {
        otError result = otSetStateChangedCallback(mInstance, &ControllerOpenThread::HandleStateChanged, this);

        agent::ThreadHelper::LogOpenThreadResult("Set state callback", result);
        VerifyOrExit(result == OT_ERROR_NONE, error = OTBR_ERROR_OPENTHREAD);
    }

#if OTBR_ENABLE_FEATURE_FLAGS && OTBR_ENABLE_TREL
    // Enable/Disable trel according to feature flag default value.
    otTrelSetEnabled(mInstance, featureFlagList.enable_trel());
#endif

#if OTBR_ENABLE_SRP_ADVERTISING_PROXY
#if OTBR_ENABLE_SRP_SERVER_AUTO_ENABLE_MODE
    // Let SRP server use auto-enable mode. The auto-enable mode delegates the control of SRP server to the Border
    // Routing Manager. SRP server automatically starts when bi-directional connectivity is ready.
    otSrpServerSetAutoEnableMode(mInstance, /* aEnabled */ true);
#else
    otSrpServerSetEnabled(mInstance, /* aEnabled */ true);
#endif
#endif

#if !OTBR_ENABLE_FEATURE_FLAGS
    // Bring up all features when feature flags is not supported.
#if OTBR_ENABLE_NAT64
    otNat64SetEnabled(mInstance, /* aEnabled */ true);
#endif
#if OTBR_ENABLE_DNS_UPSTREAM_QUERY
    otDnssdUpstreamQuerySetEnabled(mInstance, /* aEnabled */ true);
#endif
#endif // OTBR_ENABLE_FEATURE_FLAGS

    mThreadHelper = std::unique_ptr<otbr::agent::ThreadHelper>(new otbr::agent::ThreadHelper(mInstance, this));

exit:
    SuccessOrDie(error, "Failed to initialize NCP!");
}

#if OTBR_ENABLE_FEATURE_FLAGS
otError ControllerOpenThread::ApplyFeatureFlagList(const FeatureFlagList &aFeatureFlagList)
{
    otError error = OT_ERROR_NONE;
    // Save a cached copy of feature flags for debugging purpose.
    mAppliedFeatureFlagListBytes = aFeatureFlagList.SerializeAsString();

#if OTBR_ENABLE_NAT64
    otNat64SetEnabled(mInstance, aFeatureFlagList.enable_nat64());
#endif

    if (aFeatureFlagList.enable_detailed_logging())
    {
        error = SetOtbrAndOtLogLevel(ConvertProtoToOtbrLogLevel(aFeatureFlagList.detailed_logging_level()));
    }
    else
    {
        error = SetOtbrAndOtLogLevel(otbrLogGetDefaultLevel());
    }

#if OTBR_ENABLE_TREL
    otTrelSetEnabled(mInstance, aFeatureFlagList.enable_trel());
#endif
#if OTBR_ENABLE_DNS_UPSTREAM_QUERY
    otDnssdUpstreamQuerySetEnabled(mInstance, aFeatureFlagList.enable_dns_upstream_query());
#endif

    return error;
}
#endif

void ControllerOpenThread::Deinit(void)
{
    assert(mInstance != nullptr);

    otSysDeinit();
    mInstance = nullptr;
}

void ControllerOpenThread::HandleStateChanged(otChangedFlags aFlags)
{
    for (auto &stateCallback : mThreadStateChangedCallbacks)
    {
        stateCallback(aFlags);
    }

    mThreadHelper->StateChangedCallback(aFlags);
}

void ControllerOpenThread::Update(MainloopContext &aMainloop)
{
    if (otTaskletsArePending(mInstance))
    {
        aMainloop.mTimeout = ToTimeval(Microseconds::zero());
    }

    otSysMainloopUpdate(mInstance, &aMainloop);
}

void ControllerOpenThread::Process(const MainloopContext &aMainloop)
{
    otTaskletsProcess(mInstance);

    otSysMainloopProcess(mInstance, &aMainloop);

    if (IsAutoAttachEnabled() && mThreadHelper->TryResumeNetwork() == OT_ERROR_NONE)
    {
        DisableAutoAttach();
    }
}

bool ControllerOpenThread::IsAutoAttachEnabled(void)
{
    return mEnableAutoAttach;
}

void ControllerOpenThread::DisableAutoAttach(void)
{
    mEnableAutoAttach = false;
}

void ControllerOpenThread::PostTimerTask(Milliseconds aDelay, TaskRunner::Task<void> aTask)
{
    mTaskRunner.Post(std::move(aDelay), std::move(aTask));
}

void ControllerOpenThread::RegisterResetHandler(std::function<void(void)> aHandler)
{
    mResetHandlers.emplace_back(std::move(aHandler));
}

void ControllerOpenThread::AddThreadStateChangedCallback(ThreadStateChangedCallback aCallback)
{
    mThreadStateChangedCallbacks.emplace_back(std::move(aCallback));
}

void ControllerOpenThread::Reset(void)
{
    gPlatResetReason = OT_PLAT_RESET_REASON_SOFTWARE;

    otSysDeinit();
    mInstance = nullptr;

    Init();
    for (auto &handler : mResetHandlers)
    {
        handler();
    }
    mEnableAutoAttach = true;
}

const char *ControllerOpenThread::GetThreadVersion(void)
{
    const char *version;

    switch (otThreadGetVersion())
    {
    case kThreadVersion11:
        version = "1.1.1";
        break;
    case kThreadVersion12:
        version = "1.2.0";
        break;
    case kThreadVersion13:
        version = "1.3.0";
        break;
    default:
        otbrLogEmerg("Unexpected thread version %hu", otThreadGetVersion());
        exit(-1);
    }
    return version;
}

/*
 * Provide, if required an "otPlatLog()" function
 */
extern "C" void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    OT_UNUSED_VARIABLE(aLogRegion);

    otbrLogLevel otbrLogLevel = ControllerOpenThread::ConvertToOtbrLogLevel(aLogLevel);

    va_list ap;
    va_start(ap, aFormat);
    otbrLogvNoFilter(otbrLogLevel, aFormat, ap);
    va_end(ap);
}

extern "C" void otPlatLogHandleLevelChanged(otLogLevel aLogLevel)
{
    otbrLogSetLevel(ControllerOpenThread::ConvertToOtbrLogLevel(aLogLevel));
    otbrLogInfo("OpenThread log level changed to %d", aLogLevel);
}

} // namespace Ncp
} // namespace otbr
