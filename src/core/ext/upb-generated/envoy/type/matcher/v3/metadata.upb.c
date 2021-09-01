/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/type/matcher/v3/metadata.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/msg_internal.h"
#include "envoy/type/matcher/v3/metadata.upb.h"
#include "envoy/type/matcher/v3/value.upb.h"
#include "udpa/annotations/status.upb.h"
#include "udpa/annotations/versioning.upb.h"
#include "validate/validate.upb.h"

#include "upb/port_def.inc"

static const upb_msglayout *const envoy_type_matcher_v3_MetadataMatcher_submsgs[2] = {
  &envoy_type_matcher_v3_MetadataMatcher_PathSegment_msginit,
  &envoy_type_matcher_v3_ValueMatcher_msginit,
};

static const upb_msglayout_field envoy_type_matcher_v3_MetadataMatcher__fields[3] = {
  {1, UPB_SIZE(4, 8), 0, 0, 9, _UPB_MODE_SCALAR},
  {2, UPB_SIZE(16, 32), 0, 0, 11, _UPB_MODE_ARRAY},
  {3, UPB_SIZE(12, 24), 1, 1, 11, _UPB_MODE_SCALAR},
};

const upb_msglayout envoy_type_matcher_v3_MetadataMatcher_msginit = {
  &envoy_type_matcher_v3_MetadataMatcher_submsgs[0],
  &envoy_type_matcher_v3_MetadataMatcher__fields[0],
  UPB_SIZE(24, 48), 3, false, 3, 255,
};

static const upb_msglayout_field envoy_type_matcher_v3_MetadataMatcher_PathSegment__fields[1] = {
  {1, UPB_SIZE(0, 0), UPB_SIZE(-9, -17), 0, 9, _UPB_MODE_SCALAR},
};

const upb_msglayout envoy_type_matcher_v3_MetadataMatcher_PathSegment_msginit = {
  NULL,
  &envoy_type_matcher_v3_MetadataMatcher_PathSegment__fields[0],
  UPB_SIZE(16, 32), 1, false, 1, 255,
};

#include "upb/port_undef.inc"

