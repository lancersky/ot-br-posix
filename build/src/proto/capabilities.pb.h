// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: capabilities.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_capabilities_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_capabilities_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_capabilities_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_capabilities_2eproto {
  static const uint32_t offsets[];
};
namespace otbr {
class Capabilities;
struct CapabilitiesDefaultTypeInternal;
extern CapabilitiesDefaultTypeInternal _Capabilities_default_instance_;
}  // namespace otbr
PROTOBUF_NAMESPACE_OPEN
template<> ::otbr::Capabilities* Arena::CreateMaybeMessage<::otbr::Capabilities>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace otbr {

// ===================================================================

class Capabilities final :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:otbr.Capabilities) */ {
 public:
  inline Capabilities() : Capabilities(nullptr) {}
  ~Capabilities() override;
  explicit PROTOBUF_CONSTEXPR Capabilities(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Capabilities(const Capabilities& from);
  Capabilities(Capabilities&& from) noexcept
    : Capabilities() {
    *this = ::std::move(from);
  }

  inline Capabilities& operator=(const Capabilities& from) {
    CopyFrom(from);
    return *this;
  }
  inline Capabilities& operator=(Capabilities&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString);
  }
  inline std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<std::string>();
  }

  static const Capabilities& default_instance() {
    return *internal_default_instance();
  }
  static inline const Capabilities* internal_default_instance() {
    return reinterpret_cast<const Capabilities*>(
               &_Capabilities_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Capabilities& a, Capabilities& b) {
    a.Swap(&b);
  }
  inline void Swap(Capabilities* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Capabilities* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Capabilities* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Capabilities>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)  final;
  void CopyFrom(const Capabilities& from);
  void MergeFrom(const Capabilities& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Capabilities* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "otbr.Capabilities";
  }
  protected:
  explicit Capabilities(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNat64FieldNumber = 1,
    kDhcp6PdFieldNumber = 2,
  };
  // optional bool nat64 = 1;
  bool has_nat64() const;
  private:
  bool _internal_has_nat64() const;
  public:
  void clear_nat64();
  bool nat64() const;
  void set_nat64(bool value);
  private:
  bool _internal_nat64() const;
  void _internal_set_nat64(bool value);
  public:

  // optional bool dhcp6_pd = 2;
  bool has_dhcp6_pd() const;
  private:
  bool _internal_has_dhcp6_pd() const;
  public:
  void clear_dhcp6_pd();
  bool dhcp6_pd() const;
  void set_dhcp6_pd(bool value);
  private:
  bool _internal_dhcp6_pd() const;
  void _internal_set_dhcp6_pd(bool value);
  public:

  // @@protoc_insertion_point(class_scope:otbr.Capabilities)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    bool nat64_;
    bool dhcp6_pd_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_capabilities_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Capabilities

// optional bool nat64 = 1;
inline bool Capabilities::_internal_has_nat64() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Capabilities::has_nat64() const {
  return _internal_has_nat64();
}
inline void Capabilities::clear_nat64() {
  _impl_.nat64_ = false;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline bool Capabilities::_internal_nat64() const {
  return _impl_.nat64_;
}
inline bool Capabilities::nat64() const {
  // @@protoc_insertion_point(field_get:otbr.Capabilities.nat64)
  return _internal_nat64();
}
inline void Capabilities::_internal_set_nat64(bool value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.nat64_ = value;
}
inline void Capabilities::set_nat64(bool value) {
  _internal_set_nat64(value);
  // @@protoc_insertion_point(field_set:otbr.Capabilities.nat64)
}

// optional bool dhcp6_pd = 2;
inline bool Capabilities::_internal_has_dhcp6_pd() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Capabilities::has_dhcp6_pd() const {
  return _internal_has_dhcp6_pd();
}
inline void Capabilities::clear_dhcp6_pd() {
  _impl_.dhcp6_pd_ = false;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline bool Capabilities::_internal_dhcp6_pd() const {
  return _impl_.dhcp6_pd_;
}
inline bool Capabilities::dhcp6_pd() const {
  // @@protoc_insertion_point(field_get:otbr.Capabilities.dhcp6_pd)
  return _internal_dhcp6_pd();
}
inline void Capabilities::_internal_set_dhcp6_pd(bool value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.dhcp6_pd_ = value;
}
inline void Capabilities::set_dhcp6_pd(bool value) {
  _internal_set_dhcp6_pd(value);
  // @@protoc_insertion_point(field_set:otbr.Capabilities.dhcp6_pd)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace otbr

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_capabilities_2eproto
