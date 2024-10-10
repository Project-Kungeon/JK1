// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameRound.proto

#include "GameRound.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace game {
namespace round {
PROTOBUF_CONSTEXPR S_Round_StartInfo::S_Round_StartInfo(
    ::_pbi::ConstantInitialized){}
struct S_Round_StartInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_Round_StartInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_Round_StartInfoDefaultTypeInternal() {}
  union {
    S_Round_StartInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_Round_StartInfoDefaultTypeInternal _S_Round_StartInfo_default_instance_;
PROTOBUF_CONSTEXPR S_Round_TimeInfo::S_Round_TimeInfo(
    ::_pbi::ConstantInitialized)
  : type_(0)

  , remaining_seconds_(0){}
struct S_Round_TimeInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_Round_TimeInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_Round_TimeInfoDefaultTypeInternal() {}
  union {
    S_Round_TimeInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_Round_TimeInfoDefaultTypeInternal _S_Round_TimeInfo_default_instance_;
PROTOBUF_CONSTEXPR S_Round_EndInfo::S_Round_EndInfo(
    ::_pbi::ConstantInitialized)
  : type_(0)
{}
struct S_Round_EndInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_Round_EndInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_Round_EndInfoDefaultTypeInternal() {}
  union {
    S_Round_EndInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_Round_EndInfoDefaultTypeInternal _S_Round_EndInfo_default_instance_;
PROTOBUF_CONSTEXPR S_Round_GameOver_Countdown::S_Round_GameOver_Countdown(
    ::_pbi::ConstantInitialized)
  : count_(0){}
struct S_Round_GameOver_CountdownDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_Round_GameOver_CountdownDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_Round_GameOver_CountdownDefaultTypeInternal() {}
  union {
    S_Round_GameOver_Countdown _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_Round_GameOver_CountdownDefaultTypeInternal _S_Round_GameOver_Countdown_default_instance_;
}  // namespace round
}  // namespace game
static ::_pb::Metadata file_level_metadata_GameRound_2eproto[4];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_GameRound_2eproto[2];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_GameRound_2eproto = nullptr;

const uint32_t TableStruct_GameRound_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_StartInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_TimeInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_TimeInfo, type_),
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_TimeInfo, remaining_seconds_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_EndInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_EndInfo, type_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_GameOver_Countdown, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::game::round::S_Round_GameOver_Countdown, count_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::game::round::S_Round_StartInfo)},
  { 6, -1, -1, sizeof(::game::round::S_Round_TimeInfo)},
  { 14, -1, -1, sizeof(::game::round::S_Round_EndInfo)},
  { 21, -1, -1, sizeof(::game::round::S_Round_GameOver_Countdown)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::game::round::_S_Round_StartInfo_default_instance_._instance,
  &::game::round::_S_Round_TimeInfo_default_instance_._instance,
  &::game::round::_S_Round_EndInfo_default_instance_._instance,
  &::game::round::_S_Round_GameOver_Countdown_default_instance_._instance,
};

const char descriptor_table_protodef_GameRound_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017GameRound.proto\022\ngame.round\"\023\n\021S_Round"
  "_StartInfo\"\250\001\n\020S_Round_TimeInfo\0227\n\004type\030"
  "\001 \001(\0162).game.round.S_Round_TimeInfo.Time"
  "InfoType\022\031\n\021remaining_seconds\030\002 \001(\005\"@\n\014T"
  "imeInfoType\022\016\n\nROUND_WAIT\020\000\022\017\n\013ROUND_STA"
  "RT\020\001\022\017\n\013TIME_UPDATE\020\002\"\226\001\n\017S_Round_EndInf"
  "o\0227\n\004type\030\001 \001(\0162).game.round.S_Round_End"
  "Info.EndReasonType\"J\n\rEndReasonType\022\023\n\017P"
  "LAYER_ALL_DEAD\020\000\022\017\n\013ROUND_CLEAR\020\001\022\023\n\017ROU"
  "ND_TIME_OVER\020\002\"+\n\032S_Round_GameOver_Count"
  "down\022\r\n\005count\030\001 \001(\005b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_GameRound_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_GameRound_2eproto = {
    false, false, 427, descriptor_table_protodef_GameRound_2eproto,
    "GameRound.proto",
    &descriptor_table_GameRound_2eproto_once, nullptr, 0, 4,
    schemas, file_default_instances, TableStruct_GameRound_2eproto::offsets,
    file_level_metadata_GameRound_2eproto, file_level_enum_descriptors_GameRound_2eproto,
    file_level_service_descriptors_GameRound_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_GameRound_2eproto_getter() {
  return &descriptor_table_GameRound_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_GameRound_2eproto(&descriptor_table_GameRound_2eproto);
namespace game {
namespace round {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* S_Round_TimeInfo_TimeInfoType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_GameRound_2eproto);
  return file_level_enum_descriptors_GameRound_2eproto[0];
}
bool S_Round_TimeInfo_TimeInfoType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr S_Round_TimeInfo_TimeInfoType S_Round_TimeInfo::ROUND_WAIT;
constexpr S_Round_TimeInfo_TimeInfoType S_Round_TimeInfo::ROUND_START;
constexpr S_Round_TimeInfo_TimeInfoType S_Round_TimeInfo::TIME_UPDATE;
constexpr S_Round_TimeInfo_TimeInfoType S_Round_TimeInfo::TimeInfoType_MIN;
constexpr S_Round_TimeInfo_TimeInfoType S_Round_TimeInfo::TimeInfoType_MAX;
constexpr int S_Round_TimeInfo::TimeInfoType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* S_Round_EndInfo_EndReasonType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_GameRound_2eproto);
  return file_level_enum_descriptors_GameRound_2eproto[1];
}
bool S_Round_EndInfo_EndReasonType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr S_Round_EndInfo_EndReasonType S_Round_EndInfo::PLAYER_ALL_DEAD;
constexpr S_Round_EndInfo_EndReasonType S_Round_EndInfo::ROUND_CLEAR;
constexpr S_Round_EndInfo_EndReasonType S_Round_EndInfo::ROUND_TIME_OVER;
constexpr S_Round_EndInfo_EndReasonType S_Round_EndInfo::EndReasonType_MIN;
constexpr S_Round_EndInfo_EndReasonType S_Round_EndInfo::EndReasonType_MAX;
constexpr int S_Round_EndInfo::EndReasonType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

// ===================================================================

class S_Round_StartInfo::_Internal {
 public:
};

S_Round_StartInfo::S_Round_StartInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena, is_message_owned) {
  // @@protoc_insertion_point(arena_constructor:game.round.S_Round_StartInfo)
}
S_Round_StartInfo::S_Round_StartInfo(const S_Round_StartInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:game.round.S_Round_StartInfo)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_Round_StartInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_Round_StartInfo::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata S_Round_StartInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_GameRound_2eproto_getter, &descriptor_table_GameRound_2eproto_once,
      file_level_metadata_GameRound_2eproto[0]);
}

// ===================================================================

class S_Round_TimeInfo::_Internal {
 public:
};

S_Round_TimeInfo::S_Round_TimeInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:game.round.S_Round_TimeInfo)
}
S_Round_TimeInfo::S_Round_TimeInfo(const S_Round_TimeInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&type_, &from.type_,
    static_cast<size_t>(reinterpret_cast<char*>(&remaining_seconds_) -
    reinterpret_cast<char*>(&type_)) + sizeof(remaining_seconds_));
  // @@protoc_insertion_point(copy_constructor:game.round.S_Round_TimeInfo)
}

inline void S_Round_TimeInfo::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&type_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&remaining_seconds_) -
    reinterpret_cast<char*>(&type_)) + sizeof(remaining_seconds_));
}

S_Round_TimeInfo::~S_Round_TimeInfo() {
  // @@protoc_insertion_point(destructor:game.round.S_Round_TimeInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void S_Round_TimeInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void S_Round_TimeInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void S_Round_TimeInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:game.round.S_Round_TimeInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&remaining_seconds_) -
      reinterpret_cast<char*>(&type_)) + sizeof(remaining_seconds_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_Round_TimeInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .game.round.S_Round_TimeInfo.TimeInfoType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::game::round::S_Round_TimeInfo_TimeInfoType>(val));
        } else
          goto handle_unusual;
        continue;
      // int32 remaining_seconds = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          remaining_seconds_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* S_Round_TimeInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:game.round.S_Round_TimeInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .game.round.S_Round_TimeInfo.TimeInfoType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // int32 remaining_seconds = 2;
  if (this->_internal_remaining_seconds() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_remaining_seconds(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:game.round.S_Round_TimeInfo)
  return target;
}

size_t S_Round_TimeInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:game.round.S_Round_TimeInfo)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .game.round.S_Round_TimeInfo.TimeInfoType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_type());
  }

  // int32 remaining_seconds = 2;
  if (this->_internal_remaining_seconds() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_remaining_seconds());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_Round_TimeInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    S_Round_TimeInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_Round_TimeInfo::GetClassData() const { return &_class_data_; }

void S_Round_TimeInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<S_Round_TimeInfo *>(to)->MergeFrom(
      static_cast<const S_Round_TimeInfo &>(from));
}


void S_Round_TimeInfo::MergeFrom(const S_Round_TimeInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:game.round.S_Round_TimeInfo)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  if (from._internal_remaining_seconds() != 0) {
    _internal_set_remaining_seconds(from._internal_remaining_seconds());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void S_Round_TimeInfo::CopyFrom(const S_Round_TimeInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:game.round.S_Round_TimeInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_Round_TimeInfo::IsInitialized() const {
  return true;
}

void S_Round_TimeInfo::InternalSwap(S_Round_TimeInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(S_Round_TimeInfo, remaining_seconds_)
      + sizeof(S_Round_TimeInfo::remaining_seconds_)
      - PROTOBUF_FIELD_OFFSET(S_Round_TimeInfo, type_)>(
          reinterpret_cast<char*>(&type_),
          reinterpret_cast<char*>(&other->type_));
}

::PROTOBUF_NAMESPACE_ID::Metadata S_Round_TimeInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_GameRound_2eproto_getter, &descriptor_table_GameRound_2eproto_once,
      file_level_metadata_GameRound_2eproto[1]);
}

// ===================================================================

class S_Round_EndInfo::_Internal {
 public:
};

S_Round_EndInfo::S_Round_EndInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:game.round.S_Round_EndInfo)
}
S_Round_EndInfo::S_Round_EndInfo(const S_Round_EndInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:game.round.S_Round_EndInfo)
}

inline void S_Round_EndInfo::SharedCtor() {
type_ = 0;
}

S_Round_EndInfo::~S_Round_EndInfo() {
  // @@protoc_insertion_point(destructor:game.round.S_Round_EndInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void S_Round_EndInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void S_Round_EndInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void S_Round_EndInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:game.round.S_Round_EndInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_Round_EndInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .game.round.S_Round_EndInfo.EndReasonType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::game::round::S_Round_EndInfo_EndReasonType>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* S_Round_EndInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:game.round.S_Round_EndInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .game.round.S_Round_EndInfo.EndReasonType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:game.round.S_Round_EndInfo)
  return target;
}

size_t S_Round_EndInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:game.round.S_Round_EndInfo)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .game.round.S_Round_EndInfo.EndReasonType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_Round_EndInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    S_Round_EndInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_Round_EndInfo::GetClassData() const { return &_class_data_; }

void S_Round_EndInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<S_Round_EndInfo *>(to)->MergeFrom(
      static_cast<const S_Round_EndInfo &>(from));
}


void S_Round_EndInfo::MergeFrom(const S_Round_EndInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:game.round.S_Round_EndInfo)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void S_Round_EndInfo::CopyFrom(const S_Round_EndInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:game.round.S_Round_EndInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_Round_EndInfo::IsInitialized() const {
  return true;
}

void S_Round_EndInfo::InternalSwap(S_Round_EndInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata S_Round_EndInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_GameRound_2eproto_getter, &descriptor_table_GameRound_2eproto_once,
      file_level_metadata_GameRound_2eproto[2]);
}

// ===================================================================

class S_Round_GameOver_Countdown::_Internal {
 public:
};

S_Round_GameOver_Countdown::S_Round_GameOver_Countdown(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:game.round.S_Round_GameOver_Countdown)
}
S_Round_GameOver_Countdown::S_Round_GameOver_Countdown(const S_Round_GameOver_Countdown& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  count_ = from.count_;
  // @@protoc_insertion_point(copy_constructor:game.round.S_Round_GameOver_Countdown)
}

inline void S_Round_GameOver_Countdown::SharedCtor() {
count_ = 0;
}

S_Round_GameOver_Countdown::~S_Round_GameOver_Countdown() {
  // @@protoc_insertion_point(destructor:game.round.S_Round_GameOver_Countdown)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void S_Round_GameOver_Countdown::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void S_Round_GameOver_Countdown::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void S_Round_GameOver_Countdown::Clear() {
// @@protoc_insertion_point(message_clear_start:game.round.S_Round_GameOver_Countdown)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  count_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_Round_GameOver_Countdown::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 count = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          count_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* S_Round_GameOver_Countdown::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:game.round.S_Round_GameOver_Countdown)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 count = 1;
  if (this->_internal_count() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_count(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:game.round.S_Round_GameOver_Countdown)
  return target;
}

size_t S_Round_GameOver_Countdown::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:game.round.S_Round_GameOver_Countdown)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 count = 1;
  if (this->_internal_count() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_count());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_Round_GameOver_Countdown::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    S_Round_GameOver_Countdown::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_Round_GameOver_Countdown::GetClassData() const { return &_class_data_; }

void S_Round_GameOver_Countdown::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<S_Round_GameOver_Countdown *>(to)->MergeFrom(
      static_cast<const S_Round_GameOver_Countdown &>(from));
}


void S_Round_GameOver_Countdown::MergeFrom(const S_Round_GameOver_Countdown& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:game.round.S_Round_GameOver_Countdown)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_count() != 0) {
    _internal_set_count(from._internal_count());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void S_Round_GameOver_Countdown::CopyFrom(const S_Round_GameOver_Countdown& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:game.round.S_Round_GameOver_Countdown)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_Round_GameOver_Countdown::IsInitialized() const {
  return true;
}

void S_Round_GameOver_Countdown::InternalSwap(S_Round_GameOver_Countdown* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(count_, other->count_);
}

::PROTOBUF_NAMESPACE_ID::Metadata S_Round_GameOver_Countdown::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_GameRound_2eproto_getter, &descriptor_table_GameRound_2eproto_once,
      file_level_metadata_GameRound_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace round
}  // namespace game
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::game::round::S_Round_StartInfo*
Arena::CreateMaybeMessage< ::game::round::S_Round_StartInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::game::round::S_Round_StartInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::game::round::S_Round_TimeInfo*
Arena::CreateMaybeMessage< ::game::round::S_Round_TimeInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::game::round::S_Round_TimeInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::game::round::S_Round_EndInfo*
Arena::CreateMaybeMessage< ::game::round::S_Round_EndInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::game::round::S_Round_EndInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::game::round::S_Round_GameOver_Countdown*
Arena::CreateMaybeMessage< ::game::round::S_Round_GameOver_Countdown >(Arena* arena) {
  return Arena::CreateMessageInternal< ::game::round::S_Round_GameOver_Countdown >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
