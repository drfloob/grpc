/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/config/core/v3/socket_option.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#ifndef ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_
#define ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_

#include "upb/msg_internal.h"
#include "upb/decode.h"
#include "upb/decode_fast.h"
#include "upb/encode.h"

#include "upb/port_def.inc"

#ifdef __cplusplus
extern "C" {
#endif

struct envoy_config_core_v3_SocketOption;
struct envoy_config_core_v3_SocketOptionsOverride;
typedef struct envoy_config_core_v3_SocketOption envoy_config_core_v3_SocketOption;
typedef struct envoy_config_core_v3_SocketOptionsOverride envoy_config_core_v3_SocketOptionsOverride;
extern const upb_MiniTable envoy_config_core_v3_SocketOption_msginit;
extern const upb_MiniTable envoy_config_core_v3_SocketOptionsOverride_msginit;

typedef enum {
  envoy_config_core_v3_SocketOption_STATE_PREBIND = 0,
  envoy_config_core_v3_SocketOption_STATE_BOUND = 1,
  envoy_config_core_v3_SocketOption_STATE_LISTENING = 2
} envoy_config_core_v3_SocketOption_SocketState;



/* envoy.config.core.v3.SocketOption */

UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy_config_core_v3_SocketOption_msginit, arena);
}
UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SocketOption* ret = envoy_config_core_v3_SocketOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &envoy_config_core_v3_SocketOption_msginit, NULL, 0, arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SocketOption* ret = envoy_config_core_v3_SocketOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &envoy_config_core_v3_SocketOption_msginit, extreg, options, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SocketOption_serialize(const envoy_config_core_v3_SocketOption* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &envoy_config_core_v3_SocketOption_msginit, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SocketOption_serialize_ex(const envoy_config_core_v3_SocketOption* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &envoy_config_core_v3_SocketOption_msginit, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_SocketOption_value_int_value = 4,
  envoy_config_core_v3_SocketOption_value_buf_value = 5,
  envoy_config_core_v3_SocketOption_value_NOT_SET = 0
} envoy_config_core_v3_SocketOption_value_oneofcases;
UPB_INLINE envoy_config_core_v3_SocketOption_value_oneofcases envoy_config_core_v3_SocketOption_value_case(const envoy_config_core_v3_SocketOption* msg) {
  return (envoy_config_core_v3_SocketOption_value_oneofcases)*UPB_PTR_AT(msg, UPB_SIZE(0, 0), int32_t);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_description(const envoy_config_core_v3_SocketOption* msg) {
  *UPB_PTR_AT(msg, UPB_SIZE(8, 24), upb_StringView) = upb_StringView_FromDataAndSize(NULL, 0);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SocketOption_description(const envoy_config_core_v3_SocketOption* msg) {
  return *UPB_PTR_AT(msg, UPB_SIZE(8, 24), upb_StringView);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_level(const envoy_config_core_v3_SocketOption* msg) {
  *UPB_PTR_AT(msg, UPB_SIZE(24, 40), int64_t) = 0;
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_level(const envoy_config_core_v3_SocketOption* msg) {
  return *UPB_PTR_AT(msg, UPB_SIZE(24, 40), int64_t);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_name(const envoy_config_core_v3_SocketOption* msg) {
  *UPB_PTR_AT(msg, UPB_SIZE(32, 48), int64_t) = 0;
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_name(const envoy_config_core_v3_SocketOption* msg) {
  return *UPB_PTR_AT(msg, UPB_SIZE(32, 48), int64_t);
}
UPB_INLINE bool envoy_config_core_v3_SocketOption_has_int_value(const envoy_config_core_v3_SocketOption* msg) {
  return _upb_getoneofcase(msg, UPB_SIZE(0, 0)) == 4;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_int_value(const envoy_config_core_v3_SocketOption* msg) {
  UPB_WRITE_ONEOF(msg, int64_t, UPB_SIZE(16, 8), 0, UPB_SIZE(0, 0), envoy_config_core_v3_SocketOption_value_NOT_SET);
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_int_value(const envoy_config_core_v3_SocketOption* msg) {
  return UPB_READ_ONEOF(msg, int64_t, UPB_SIZE(16, 8), UPB_SIZE(0, 0), 4, _upb_Int64_FromLL(0ll));
}
UPB_INLINE bool envoy_config_core_v3_SocketOption_has_buf_value(const envoy_config_core_v3_SocketOption* msg) {
  return _upb_getoneofcase(msg, UPB_SIZE(0, 0)) == 5;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_buf_value(const envoy_config_core_v3_SocketOption* msg) {
  UPB_WRITE_ONEOF(msg, upb_StringView, UPB_SIZE(16, 8), upb_StringView_FromDataAndSize(NULL, 0), UPB_SIZE(0, 0), envoy_config_core_v3_SocketOption_value_NOT_SET);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SocketOption_buf_value(const envoy_config_core_v3_SocketOption* msg) {
  return UPB_READ_ONEOF(msg, upb_StringView, UPB_SIZE(16, 8), UPB_SIZE(0, 0), 5, upb_StringView_FromString(""));
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_state(const envoy_config_core_v3_SocketOption* msg) {
  *UPB_PTR_AT(msg, UPB_SIZE(4, 4), int32_t) = 0;
}
UPB_INLINE int32_t envoy_config_core_v3_SocketOption_state(const envoy_config_core_v3_SocketOption* msg) {
  return *UPB_PTR_AT(msg, UPB_SIZE(4, 4), int32_t);
}

UPB_INLINE void envoy_config_core_v3_SocketOption_set_description(envoy_config_core_v3_SocketOption *msg, upb_StringView value) {
  *UPB_PTR_AT(msg, UPB_SIZE(8, 24), upb_StringView) = value;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_level(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  *UPB_PTR_AT(msg, UPB_SIZE(24, 40), int64_t) = value;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_name(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  *UPB_PTR_AT(msg, UPB_SIZE(32, 48), int64_t) = value;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_int_value(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  UPB_WRITE_ONEOF(msg, int64_t, UPB_SIZE(16, 8), value, UPB_SIZE(0, 0), 4);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_buf_value(envoy_config_core_v3_SocketOption *msg, upb_StringView value) {
  UPB_WRITE_ONEOF(msg, upb_StringView, UPB_SIZE(16, 8), value, UPB_SIZE(0, 0), 5);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_state(envoy_config_core_v3_SocketOption *msg, int32_t value) {
  *UPB_PTR_AT(msg, UPB_SIZE(4, 4), int32_t) = value;
}

/* envoy.config.core.v3.SocketOptionsOverride */

UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SocketOptionsOverride*)_upb_Message_New(&envoy_config_core_v3_SocketOptionsOverride_msginit, arena);
}
UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SocketOptionsOverride* ret = envoy_config_core_v3_SocketOptionsOverride_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &envoy_config_core_v3_SocketOptionsOverride_msginit, NULL, 0, arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SocketOptionsOverride* ret = envoy_config_core_v3_SocketOptionsOverride_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &envoy_config_core_v3_SocketOptionsOverride_msginit, extreg, options, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SocketOptionsOverride_serialize(const envoy_config_core_v3_SocketOptionsOverride* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &envoy_config_core_v3_SocketOptionsOverride_msginit, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SocketOptionsOverride_serialize_ex(const envoy_config_core_v3_SocketOptionsOverride* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &envoy_config_core_v3_SocketOptionsOverride_msginit, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE bool envoy_config_core_v3_SocketOptionsOverride_has_socket_options(const envoy_config_core_v3_SocketOptionsOverride* msg) {
  return _upb_has_submsg_nohasbit(msg, UPB_SIZE(0, 0));
}
UPB_INLINE void envoy_config_core_v3_SocketOptionsOverride_clear_socket_options(const envoy_config_core_v3_SocketOptionsOverride* msg) {
  _upb_array_detach(msg, UPB_SIZE(0, 0));
}
UPB_INLINE const envoy_config_core_v3_SocketOption* const* envoy_config_core_v3_SocketOptionsOverride_socket_options(const envoy_config_core_v3_SocketOptionsOverride* msg, size_t* len) {
  return (const envoy_config_core_v3_SocketOption* const*)_upb_array_accessor(msg, UPB_SIZE(0, 0), len);
}

UPB_INLINE envoy_config_core_v3_SocketOption** envoy_config_core_v3_SocketOptionsOverride_mutable_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, size_t* len) {
  return (envoy_config_core_v3_SocketOption**)_upb_array_mutable_accessor(msg, UPB_SIZE(0, 0), len);
}
UPB_INLINE envoy_config_core_v3_SocketOption** envoy_config_core_v3_SocketOptionsOverride_resize_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, size_t len, upb_Arena* arena) {
  return (envoy_config_core_v3_SocketOption**)_upb_Array_Resize_accessor2(msg, UPB_SIZE(0, 0), len, UPB_SIZE(2, 3), arena);
}
UPB_INLINE struct envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOptionsOverride_add_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SocketOption* sub = (struct envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy_config_core_v3_SocketOption_msginit, arena);
  bool ok = _upb_Array_Append_accessor2(msg, UPB_SIZE(0, 0), UPB_SIZE(2, 3), &sub, arena);
  if (!ok) return NULL;
  return sub;
}

extern const upb_MiniTable_File envoy_config_core_v3_socket_option_proto_upb_file_layout;

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port_undef.inc"

#endif  /* ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_ */
