/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/core/v3/resource.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/core/v3/resource.upb.h"
#include "google/protobuf/any.upb.h"
#include "xds/annotations/v3/status.upb.h"
#include "xds/core/v3/resource_name.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub xds_core_v3_Resource_submsgs[2] = {
  {.submsg = &xds_core_v3_ResourceName_msg_init},
  {.submsg = &google_protobuf_Any_msg_init},
};

static const upb_MiniTableField xds_core_v3_Resource__fields[3] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_core_v3_Resource_msg_init = {
  &xds_core_v3_Resource_submsgs[0],
  &xds_core_v3_Resource__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x001000003f000012, &upb_pss_1bt},
    {0x002000000201001a, &upb_psm_1bt_maxmaxb},
  })
};

static const upb_MiniTable *messages_layout[1] = {
  &xds_core_v3_Resource_msg_init,
};

const upb_MiniTableFile xds_core_v3_resource_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"

