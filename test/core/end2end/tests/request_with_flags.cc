//
//
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#include <stdint.h>
#include <string.h>

#include <functional>
#include <memory>
#include <string>

#include "absl/strings/str_cat.h"

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/gpr/useful.h"
#include "src/core/lib/transport/transport.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/util/test_config.h"

static std::unique_ptr<CoreTestFixture> begin_test(
    const CoreTestConfiguration& config, const char* test_name,
    grpc_channel_args* client_args, grpc_channel_args* server_args) {
  gpr_log(GPR_INFO, "Running test: %s/%s", test_name, config.name);
  auto f = config.create_fixture(grpc_core::ChannelArgs::FromC(client_args),
                                 grpc_core::ChannelArgs::FromC(server_args));
  f->InitServer(grpc_core::ChannelArgs::FromC(server_args));
  f->InitClient(grpc_core::ChannelArgs::FromC(client_args));
  return f;
}

static gpr_timespec one_second_from_now(void) {
  return grpc_timeout_seconds_to_deadline(1);
}

static void test_invoke_request_with_flags(
    const CoreTestConfiguration& config, uint32_t* flags_for_op,
    grpc_call_error call_start_batch_expected_result) {
  grpc_call* c;
  grpc_slice request_payload_slice =
      grpc_slice_from_copied_string("hello world");
  grpc_byte_buffer* request_payload =
      grpc_raw_byte_buffer_create(&request_payload_slice, 1);
  auto f = begin_test(
      config,
      absl::StrCat("test_invoke_request_with_flags[",
                   absl::Hex(flags_for_op[GRPC_OP_SEND_INITIAL_METADATA]), ",",
                   absl::Hex(flags_for_op[GRPC_OP_SEND_MESSAGE]), ",",
                   absl::Hex(flags_for_op[GRPC_OP_SEND_CLOSE_FROM_CLIENT]), ",",
                   absl::Hex(flags_for_op[GRPC_OP_RECV_INITIAL_METADATA]), ",",
                   absl::Hex(flags_for_op[GRPC_OP_RECV_STATUS_ON_CLIENT]),
                   "]=>",
                   grpc_call_error_to_string(call_start_batch_expected_result))
          .c_str(),
      nullptr, nullptr);
  grpc_core::CqVerifier cqv(f->cq());
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_byte_buffer* request_payload_recv = nullptr;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;
  grpc_call_error expectation;

  gpr_timespec deadline = one_second_from_now();
  c = grpc_channel_create_call(f->client(), nullptr, GRPC_PROPAGATE_DEFAULTS,
                               f->cq(), grpc_slice_from_static_string("/foo"),
                               nullptr, deadline, nullptr);
  GPR_ASSERT(c);

  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = flags_for_op[op->op];
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = request_payload;
  op->flags = flags_for_op[op->op];
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op->flags = flags_for_op[op->op];
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = flags_for_op[op->op];
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = flags_for_op[op->op];
  op->reserved = nullptr;
  op++;
  expectation = call_start_batch_expected_result;
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(1), nullptr);
  GPR_ASSERT(expectation == error);

  if (expectation == GRPC_CALL_OK) {
    if (config.feature_mask & FEATURE_MASK_DOES_NOT_SUPPORT_DEADLINES) {
      GPR_ASSERT(GRPC_CALL_OK == grpc_call_cancel(c, nullptr));
    }
    cqv.Expect(grpc_core::CqVerifier::tag(1), true);
    cqv.Verify();
    grpc_slice_unref(details);
  }

  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);

  grpc_call_unref(c);

  grpc_byte_buffer_destroy(request_payload);
  grpc_byte_buffer_destroy(request_payload_recv);
}

void request_with_flags(const CoreTestConfiguration& config) {
  size_t i;
  uint32_t flags_for_op[GRPC_OP_RECV_CLOSE_ON_SERVER + 1];

  {
    // check that all grpc_op_types fail when their flag value is set to an
    // invalid value
    int indices[] = {GRPC_OP_SEND_INITIAL_METADATA, GRPC_OP_SEND_MESSAGE,
                     GRPC_OP_SEND_CLOSE_FROM_CLIENT,
                     GRPC_OP_RECV_INITIAL_METADATA,
                     GRPC_OP_RECV_STATUS_ON_CLIENT};
    for (i = 0; i < GPR_ARRAY_SIZE(indices); ++i) {
      memset(flags_for_op, 0, sizeof(flags_for_op));
      flags_for_op[indices[i]] = 0xDEADBEEF;
      test_invoke_request_with_flags(config, flags_for_op,
                                     GRPC_CALL_ERROR_INVALID_FLAGS);
    }
  }
  {
    // check valid operation with allowed flags for GRPC_OP_SEND_BUFFER
    uint32_t flags[] = {GRPC_WRITE_BUFFER_HINT, GRPC_WRITE_NO_COMPRESS,
                        GRPC_WRITE_INTERNAL_COMPRESS};
    for (i = 0; i < GPR_ARRAY_SIZE(flags); ++i) {
      memset(flags_for_op, 0, sizeof(flags_for_op));
      flags_for_op[GRPC_OP_SEND_MESSAGE] = flags[i];
      test_invoke_request_with_flags(config, flags_for_op, GRPC_CALL_OK);
    }
  }
}

void request_with_flags_pre_init(void) {}
