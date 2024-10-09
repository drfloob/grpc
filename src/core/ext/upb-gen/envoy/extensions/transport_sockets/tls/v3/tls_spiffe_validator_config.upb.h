/* This file was generated by upb_generator from the input file:
 *
 *     envoy/extensions/transport_sockets/tls/v3/tls_spiffe_validator_config.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_SPIFFE_VALIDATOR_CONFIG_PROTO_UPB_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_SPIFFE_VALIDATOR_CONFIG_PROTO_UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/transport_sockets/tls/v3/tls_spiffe_validator_config.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig;
typedef struct envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain;
struct envoy_config_core_v3_DataSource;



/* envoy.extensions.transport_sockets.tls.v3.SPIFFECertValidatorConfig */

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* ret = envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* ret = envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_serialize(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_clear_trust_domains(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* const* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_trust_domains(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_trust_domains_upb_array(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_trust_domains_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain** envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_mutable_trust_domains(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain** envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_resize_trust_domains(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_add_trust_domains(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* sub = (struct envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

/* envoy.extensions.transport_sockets.tls.v3.SPIFFECertValidatorConfig.TrustDomain */

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* ret = envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* ret = envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_serialize(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_clear_name(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_name(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_clear_trust_bundle(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_trust_bundle(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_has_trust_bundle(const envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_set_name(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_set_trust_bundle(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_mutable_trust_bundle(envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_trust_bundle(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain_set_trust_bundle(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port/undef.inc"

#endif  /* ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_SPIFFE_VALIDATOR_CONFIG_PROTO_UPB_H_ */
