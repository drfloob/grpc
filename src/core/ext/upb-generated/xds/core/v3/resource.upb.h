/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/core/v3/resource.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#ifndef XDS_CORE_V3_RESOURCE_PROTO_UPB_H_
#define XDS_CORE_V3_RESOURCE_PROTO_UPB_H_

#include "upb/generated_code_support.h"
// Must be last. 
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_core_v3_Resource xds_core_v3_Resource;
extern const upb_MiniTable xds_core_v3_Resource_msg_init;
struct google_protobuf_Any;
struct xds_core_v3_ResourceName;
extern const upb_MiniTable google_protobuf_Any_msg_init;
extern const upb_MiniTable xds_core_v3_ResourceName_msg_init;



/* xds.core.v3.Resource */

UPB_INLINE xds_core_v3_Resource* xds_core_v3_Resource_new(upb_Arena* arena) {
  return (xds_core_v3_Resource*)_upb_Message_New(&xds_core_v3_Resource_msg_init, arena);
}
UPB_INLINE xds_core_v3_Resource* xds_core_v3_Resource_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_Resource* ret = xds_core_v3_Resource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &xds_core_v3_Resource_msg_init, NULL, 0, arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_Resource* xds_core_v3_Resource_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_Resource* ret = xds_core_v3_Resource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, ret, &xds_core_v3_Resource_msg_init, extreg, options, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_Resource_serialize(const xds_core_v3_Resource* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &xds_core_v3_Resource_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_Resource_serialize_ex(const xds_core_v3_Resource* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(msg, &xds_core_v3_Resource_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_core_v3_Resource_clear_name(xds_core_v3_Resource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_ClearNonExtensionField(msg, &field);
}
UPB_INLINE const struct xds_core_v3_ResourceName* xds_core_v3_Resource_name(const xds_core_v3_Resource* msg) {
  const struct xds_core_v3_ResourceName* default_val = NULL;
  const struct xds_core_v3_ResourceName* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(msg, &field, &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_Resource_has_name(const xds_core_v3_Resource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return _upb_Message_HasNonExtensionField(msg, &field);
}
UPB_INLINE void xds_core_v3_Resource_clear_version(xds_core_v3_Resource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_ClearNonExtensionField(msg, &field);
}
UPB_INLINE upb_StringView xds_core_v3_Resource_version(const xds_core_v3_Resource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(msg, &field, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_Resource_clear_resource(xds_core_v3_Resource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_ClearNonExtensionField(msg, &field);
}
UPB_INLINE const struct google_protobuf_Any* xds_core_v3_Resource_resource(const xds_core_v3_Resource* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(msg, &field, &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_Resource_has_resource(const xds_core_v3_Resource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return _upb_Message_HasNonExtensionField(msg, &field);
}

UPB_INLINE void xds_core_v3_Resource_set_name(xds_core_v3_Resource *msg, struct xds_core_v3_ResourceName* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_SetNonExtensionField(msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_ResourceName* xds_core_v3_Resource_mutable_name(xds_core_v3_Resource* msg, upb_Arena* arena) {
  struct xds_core_v3_ResourceName* sub = (struct xds_core_v3_ResourceName*)xds_core_v3_Resource_name(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_ResourceName*)_upb_Message_New(&xds_core_v3_ResourceName_msg_init, arena);
    if (sub) xds_core_v3_Resource_set_name(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_core_v3_Resource_set_version(xds_core_v3_Resource *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_SetNonExtensionField(msg, &field, &value);
}
UPB_INLINE void xds_core_v3_Resource_set_resource(xds_core_v3_Resource *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_SetNonExtensionField(msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* xds_core_v3_Resource_mutable_resource(xds_core_v3_Resource* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)xds_core_v3_Resource_resource(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google_protobuf_Any_msg_init, arena);
    if (sub) xds_core_v3_Resource_set_resource(msg, sub);
  }
  return sub;
}

extern const upb_MiniTableFile xds_core_v3_resource_proto_upb_file_layout;

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port/undef.inc"

#endif  /* XDS_CORE_V3_RESOURCE_PROTO_UPB_H_ */
