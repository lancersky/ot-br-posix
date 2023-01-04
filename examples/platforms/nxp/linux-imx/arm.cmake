#  Copyright (c) 2022, The OpenThread Authors.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the copyright holder nor the
#     names of its contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-poky-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-poky-linux-gnueabi-g++)
set(CMAKE_C_COMPILER_LAUNCHER)
set(CMAKE_CXX_COMPILER_LAUNCHER)
set(CMAKE_ASM_COMPILER arm-poky-linux-gnueabi-gcc)
find_program(CMAKE_AR arm-poky-linux-gnueabi-gcc-ar DOC "Archiver" REQUIRED)
set(CMAKE_C_FLAGS " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong  -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=$ENV{SDKTARGETSYSROOT} -O2 -pipe -g -feliminate-unused-debug-types " CACHE STRING "CFLAGS")
set(CMAKE_CXX_FLAGS " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong --sysroot=$ENV{SDKTARGETSYSROOT} -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -fvisibility-inlines-hidden" CACHE STRING "CXXFLAGS")
set(CMAKE_ASM_FLAGS " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong --sysroot=$ENV{SDKTARGETSYSROOT} -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security " CACHE STRING "ASM FLAGS")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CFLAGS for release")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CXXFLAGS for release")
set(CMAKE_ASM_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional ASM FLAGS for release")
set(CMAKE_C_LINK_FLAGS " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong --sysroot=$ENV{SDKTARGETSYSROOT} -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -Wl,-z,relro,-z,now" CACHE STRING "LDFLAGS")
set(CMAKE_CXX_LINK_FLAGS " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong --sysroot=$ENV{SDKTARGETSYSROOT} -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -fvisibility-inlines-hidden -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -Wl,-z,relro,-z,now -L$ENV{SDKTARGETSYSROOT}/usr/lib " CACHE STRING "LDFLAGS")
set(CMAKE_FIND_ROOT_PATH $ENV{OECORE_NATIVE_SYSROOT} $ENV{SDKTARGETSYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_PROGRAM_PATH "/")
set(CMAKE_INSTALL_RPATH)
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
list(APPEND CMAKE_MODULE_PATH "$ENV{SDKTARGETSYSROOT}/usr/share/cmake/Modules/")
set(CMAKE_LIBRARY_PATH /usr/lib /lib)
list(APPEND CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES /usr/include)
list(APPEND CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES /usr/include)
set(READLINE "$ENV{SDKTARGETSYSROOT}/usr/lib/libreadline.so")
