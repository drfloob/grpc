/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/config/bootstrap/v3/bootstrap.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/bootstrap/v3/bootstrap.upb.h"
#include "envoy/config/accesslog/v3/accesslog.upb.h"
#include "envoy/config/cluster/v3/cluster.upb.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/config/core/v3/config_source.upb.h"
#include "envoy/config/core/v3/event_service_config.upb.h"
#include "envoy/config/core/v3/extension.upb.h"
#include "envoy/config/core/v3/resolver.upb.h"
#include "envoy/config/core/v3/socket_option.upb.h"
#include "envoy/config/listener/v3/listener.upb.h"
#include "envoy/config/metrics/v3/stats.upb.h"
#include "envoy/config/overload/v3/overload.upb.h"
#include "envoy/config/trace/v3/http_tracer.upb.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb.h"
#include "envoy/type/v3/percent.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/struct.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "envoy/annotations/deprecation.upb.h"
#include "udpa/annotations/migrate.upb.h"
#include "udpa/annotations/security.upb.h"
#include "udpa/annotations/status.upb.h"
#include "udpa/annotations/versioning.upb.h"
#include "validate/validate.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub envoy_config_bootstrap_v3_Bootstrap_submsgs[27] = {
  {.submsg = &envoy_config_core_v3_Node_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Bootstrap_StaticResources_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Bootstrap_DynamicResources_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_ClusterManager_msg_init},
  {.submsg = &envoy_config_metrics_v3_StatsSink_msg_init},
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Watchdog_msg_init},
  {.submsg = &envoy_config_trace_v3_Tracing_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Admin_msg_init},
  {.submsg = &envoy_config_metrics_v3_StatsConfig_msg_init},
  {.submsg = &envoy_config_core_v3_ApiConfigSource_msg_init},
  {.submsg = &envoy_config_overload_v3_OverloadManager_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_LayeredRuntime_msg_init},
  {.submsg = &google_protobuf_UInt64Value_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
  {.submsg = &envoy_config_core_v3_ConfigSource_msg_init},
  {.submsg = &envoy_config_core_v3_ConfigSource_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Watchdogs_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_FatalAction_msg_init},
  {.submsg = &envoy_config_core_v3_DnsResolutionConfig_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_CustomInlineHeader_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap__fields[35] = {
  {1, UPB_SIZE(4, 16), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 40), 4, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(128, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 64), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 72), 5, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(28, 80), 6, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 88), 7, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(36, 96), 8, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(40, 104), 9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(44, 112), 10, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(48, 120), 11, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(52, 4), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(56, 128), 12, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, 136, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(60, 152), 13, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(64, 5), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(68, 160), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(72, 168), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(76, 176), 14, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(144, 184), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {25, UPB_SIZE(80, 200), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {26, UPB_SIZE(84, 208), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {27, UPB_SIZE(88, 216), 15, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {28, UPB_SIZE(92, 224), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {29, 3, UPB_SIZE(-97, -9), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {30, UPB_SIZE(100, 232), 16, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {31, UPB_SIZE(104, 240), 17, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {32, UPB_SIZE(108, 248), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {33, UPB_SIZE(152, 256), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(112, 272), 18, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {35, UPB_SIZE(116, 280), 19, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {36, UPB_SIZE(120, 288), 20, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {37, UPB_SIZE(124, 296), 21, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Bootstrap_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap__fields[0],
  UPB_SIZE(160, 304), 35, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(248), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000000100000a, &upb_psm_1bt_maxmaxb},
    {0x0018000002010012, &upb_psm_1bt_max64b},
    {0x002000000302001a, &upb_psm_1bt_max128b},
    {0x0028000004030022, &upb_psm_1bt_max64b},
    {0x003000003f00002a, &upb_pss_1bt},
    {0x004000003f040032, &upb_prm_1bt_maxmaxb},
    {0x004800000505003a, &upb_psm_1bt_maxmaxb},
    {0x0050000006060042, &upb_psm_1bt_max128b},
    {0x005800000707004a, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0060000008080062, &upb_psm_1bt_max128b},
    {0x006800000909006a, &upb_psm_1bt_maxmaxb},
    {0x007000000a0a0072, &upb_psm_1bt_maxmaxb},
    {0x007800000b0b007a, &upb_psm_1bt_maxmaxb},
    {0x000400003f000180, &upb_psb1_2bt},
    {0x008000000c0c018a, &upb_psm_2bt_max64b},
    {0x008800003f000192, &upb_pss_2bt},
    {0x009800000d0d019a, &upb_psm_2bt_maxmaxb},
    {0x000500003f0001a0, &upb_psb1_2bt},
    {0x00a000003f0e01aa, &upb_prm_2bt_maxmaxb},
    {0x00a800003f0f01b2, &upb_prm_2bt_maxmaxb},
    {0x00b000000e1001ba, &upb_psm_2bt_maxmaxb},
    {0x00b800003f0001c2, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00d000003f0001d2, &upb_prs_2bt},
    {0x00d800000f1201da, &upb_psm_2bt_max64b},
    {0x00e000003f1301e2, &upb_prm_2bt_max64b},
    {0x000300081d0001e8, &upb_pob1_2bt},
    {0x00e80000101401f2, &upb_psm_2bt_maxmaxb},
    {0x00f00000111501fa, &upb_psm_2bt_maxmaxb},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Bootstrap_StaticResources_submsgs[3] = {
  {.submsg = &envoy_config_listener_v3_Listener_msg_init},
  {.submsg = &envoy_config_cluster_v3_Cluster_msg_init},
  {.submsg = &envoy_extensions_transport_sockets_tls_v3_Secret_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_StaticResources__fields[3] = {
  {1, 0, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 8), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 16), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Bootstrap_StaticResources_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_StaticResources_submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_StaticResources__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f00000a, &upb_prm_1bt_maxmaxb},
    {0x000800003f010012, &upb_prm_1bt_maxmaxb},
    {0x001000003f02001a, &upb_prm_1bt_maxmaxb},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Bootstrap_DynamicResources_submsgs[3] = {
  {.submsg = &envoy_config_core_v3_ConfigSource_msg_init},
  {.submsg = &envoy_config_core_v3_ConfigSource_msg_init},
  {.submsg = &envoy_config_core_v3_ApiConfigSource_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_DynamicResources__fields[5] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 24), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Bootstrap_DynamicResources_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_DynamicResources_submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_DynamicResources__fields[0],
  UPB_SIZE(32, 64), 5, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x001800000302001a, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00002a, &upb_pss_1bt},
    {0x003000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_submsgs[1] = {
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000001000012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Admin_submsgs[3] = {
  {.submsg = &envoy_config_core_v3_Address_msg_init},
  {.submsg = &envoy_config_core_v3_SocketOption_msg_init},
  {.submsg = &envoy_config_accesslog_v3_AccessLog_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Admin__fields[6] = {
  {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 40), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 1), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Admin_msg_init = {
  &envoy_config_bootstrap_v3_Admin_submsgs[0],
  &envoy_config_bootstrap_v3_Admin__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800000100001a, &upb_psm_1bt_maxmaxb},
    {0x003000003f010022, &upb_prm_1bt_maxmaxb},
    {0x003800003f02002a, &upb_prm_1bt_maxmaxb},
    {0x000100003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_ClusterManager_submsgs[3] = {
  {.submsg = &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_msg_init},
  {.submsg = &envoy_config_core_v3_BindConfig_msg_init},
  {.submsg = &envoy_config_core_v3_ApiConfigSource_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_ClusterManager__fields[4] = {
  {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 40), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_ClusterManager_msg_init = {
  &envoy_config_bootstrap_v3_ClusterManager_submsgs[0],
  &envoy_config_bootstrap_v3_ClusterManager__fields[0],
  UPB_SIZE(24, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000001000012, &upb_psm_1bt_max64b},
    {0x002000000201001a, &upb_psm_1bt_maxmaxb},
    {0x0028000003020022, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_submsgs[1] = {
  {.submsg = &envoy_config_core_v3_EventServiceConfig_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_msg_init = {
  &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_submsgs[0],
  &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__fields[0],
  UPB_SIZE(16, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000001000012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Watchdogs_submsgs[2] = {
  {.submsg = &envoy_config_bootstrap_v3_Watchdog_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Watchdog_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdogs__fields[2] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Watchdogs_msg_init = {
  &envoy_config_bootstrap_v3_Watchdogs_submsgs[0],
  &envoy_config_bootstrap_v3_Watchdogs__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_max128b},
    {0x0010000002010012, &upb_psm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Watchdog_submsgs[7] = {
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &envoy_type_v3_Percent_msg_init},
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_Watchdog_WatchdogAction_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdog__fields[7] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 24), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 32), 4, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 40), 5, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 48), 6, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(28, 56), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Watchdog_msg_init = {
  &envoy_config_bootstrap_v3_Watchdog_submsgs[0],
  &envoy_config_bootstrap_v3_Watchdog__fields[0],
  UPB_SIZE(32, 64), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x001800000302001a, &upb_psm_1bt_maxmaxb},
    {0x0020000004030022, &upb_psm_1bt_maxmaxb},
    {0x002800000504002a, &upb_psm_1bt_maxmaxb},
    {0x0030000006050032, &upb_psm_1bt_maxmaxb},
    {0x003800003f06003a, &upb_prm_1bt_max64b},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Watchdog_WatchdogAction_submsgs[1] = {
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdog_WatchdogAction__fields[2] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 4), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Watchdog_WatchdogAction_msg_init = {
  &envoy_config_bootstrap_v3_Watchdog_WatchdogAction_submsgs[0],
  &envoy_config_bootstrap_v3_Watchdog_WatchdogAction__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x000400003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_FatalAction_submsgs[1] = {
  {.submsg = &envoy_config_core_v3_TypedExtensionConfig_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_FatalAction__fields[1] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_FatalAction_msg_init = {
  &envoy_config_bootstrap_v3_FatalAction_submsgs[0],
  &envoy_config_bootstrap_v3_FatalAction__fields[0],
  UPB_SIZE(8, 16), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_Runtime_submsgs[1] = {
  {.submsg = &google_protobuf_Struct_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Runtime__fields[4] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(4, 56), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_Runtime_msg_init = {
  &envoy_config_bootstrap_v3_Runtime_submsgs[0],
  &envoy_config_bootstrap_v3_Runtime__fields[0],
  UPB_SIZE(32, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800003f00001a, &upb_pss_1bt},
    {0x0038000001000022, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_RuntimeLayer_submsgs[4] = {
  {.submsg = &google_protobuf_Struct_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_msg_init},
  {.submsg = &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer__fields[5] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), -1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 24), -1, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(4, 24), -1, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(4, 24), -1, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_RuntimeLayer_msg_init = {
  &envoy_config_bootstrap_v3_RuntimeLayer_submsgs[0],
  &envoy_config_bootstrap_v3_RuntimeLayer__fields[0],
  UPB_SIZE(16, 32), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000002000012, &upb_pom_1bt_maxmaxb},
    {0x001800000301001a, &upb_pom_1bt_max64b},
    {0x0018000004020022, &upb_pom_1bt_max64b},
    {0x001800000503002a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer__fields[3] = {
  {1, UPB_SIZE(4, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_msg_init = {
  NULL,
  &envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x000000003f000010, &upb_psb1_1bt},
    {0x001800003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_msg_init = {
  NULL,
  NULL,
  0, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_submsgs[1] = {
  {.submsg = &envoy_config_core_v3_ConfigSource_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_msg_init = {
  &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_submsgs[0],
  &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__fields[0],
  UPB_SIZE(16, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000001000012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_bootstrap_v3_LayeredRuntime_submsgs[1] = {
  {.submsg = &envoy_config_bootstrap_v3_RuntimeLayer_msg_init},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_LayeredRuntime__fields[1] = {
  {1, 0, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_LayeredRuntime_msg_init = {
  &envoy_config_bootstrap_v3_LayeredRuntime_submsgs[0],
  &envoy_config_bootstrap_v3_LayeredRuntime__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f00000a, &upb_prm_1bt_max64b},
  })
};

static const upb_MiniTableField envoy_config_bootstrap_v3_CustomInlineHeader__fields[2] = {
  {1, UPB_SIZE(4, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 0, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_config_bootstrap_v3_CustomInlineHeader_msg_init = {
  NULL,
  &envoy_config_bootstrap_v3_CustomInlineHeader__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x000000003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[18] = {
  &envoy_config_bootstrap_v3_Bootstrap_msg_init,
  &envoy_config_bootstrap_v3_Bootstrap_StaticResources_msg_init,
  &envoy_config_bootstrap_v3_Bootstrap_DynamicResources_msg_init,
  &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_msg_init,
  &envoy_config_bootstrap_v3_Admin_msg_init,
  &envoy_config_bootstrap_v3_ClusterManager_msg_init,
  &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_msg_init,
  &envoy_config_bootstrap_v3_Watchdogs_msg_init,
  &envoy_config_bootstrap_v3_Watchdog_msg_init,
  &envoy_config_bootstrap_v3_Watchdog_WatchdogAction_msg_init,
  &envoy_config_bootstrap_v3_FatalAction_msg_init,
  &envoy_config_bootstrap_v3_Runtime_msg_init,
  &envoy_config_bootstrap_v3_RuntimeLayer_msg_init,
  &envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_msg_init,
  &envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_msg_init,
  &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_msg_init,
  &envoy_config_bootstrap_v3_LayeredRuntime_msg_init,
  &envoy_config_bootstrap_v3_CustomInlineHeader_msg_init,
};

const upb_MiniTableFile envoy_config_bootstrap_v3_bootstrap_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  18,
  0,
  0,
};

#include "upb/port/undef.inc"

