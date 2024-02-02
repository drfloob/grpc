// Copyright 2024 The gRPC Authors
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

#include <grpc/support/port_platform.h>

#include "src/core/lib/http/parser.h"
#include "src/core/lib/uri/uri_parser.h"
#include "src/libfuzzer/libfuzzer_macro.h"
#include "test/core/http/httpcli_fuzzer.pb.h"
#include "test/core/util/fuzzing_channel_args.h"

bool squelch = true;
static void dont_log(gpr_log_func_args* /*args*/) {}

namespace {
// DO NOT SUBMIT(hork): implement
}  // namespace

void MakeGetRequest(const httpcli_fuzzer::Msg& msg) {}

void MakePostRequest(const httpcli_fuzzer::Msg& msg) {}

void MakePutRequest(const httpcli_fuzzer::Msg& msg) {}

DEFINE_PROTO_FUZZER(const httpcli_fuzzer::Msg& msg) {
  if (squelch) gpr_set_log_function(dont_log);
  grpc_core::ExecCtx exec_ctx;
  grpc_http_request req;
  memset(&req, 0, sizeof(req));
  switch (msg.request_type()) {
    case httpcli_fuzzer::RequestType::REQUEST_TYPE_GET:
      MakeGetRequest(msg);
      break;
    case httpcli_fuzzer::RequestType::REQUEST_TYPE_POST:
      MakePostRequest(msg);
      break;
    case httpcli_fuzzer::RequestType::REQUEST_TYPE_PUT:
      MakePutRequest(msg);
      break;
    default:
      // unknown request type. Exiting
      return;
  }
  auto uri = grpc_core::URI::Create("http", msg.host(), "/get",
                                    {} /* query params */, "" /* fragment */);
}
