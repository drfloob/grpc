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

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <stdint.h>
#include <string.h>

#include <cstdint>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/util/http_client/parser.h"

void RequestTest(std::vector<uint8_t> buffer) {
  grpc_http_parser parser;
  grpc_http_request request;
  grpc_init();
  memset(&request, 0, sizeof(request));
  grpc_http_parser_init(&parser, GRPC_HTTP_REQUEST, &request);
  grpc_slice slice =
      grpc_slice_from_copied_buffer((const char*)buffer.data(), buffer.size());
  (void)grpc_http_parser_parse(&parser, slice, nullptr);
  (void)grpc_http_parser_eof(&parser);
  grpc_slice_unref(slice);
  grpc_http_parser_destroy(&parser);
  grpc_http_request_destroy(&request);
  grpc_shutdown();
}
FUZZ_TEST(HttpClient, RequestTest);

void ResponseTest(std::vector<uint8_t> buffer) {
  grpc_http_parser parser;
  grpc_http_response response;
  grpc_init();
  response = {};
  grpc_http_parser_init(&parser, GRPC_HTTP_RESPONSE, &response);
  grpc_slice slice =
      grpc_slice_from_copied_buffer((const char*)buffer.data(), buffer.size());
  (void)grpc_http_parser_parse(&parser, slice, nullptr);
  (void)grpc_http_parser_eof(&parser);
  grpc_slice_unref(slice);
  grpc_http_parser_destroy(&parser);
  grpc_http_response_destroy(&response);
  grpc_shutdown();
}
FUZZ_TEST(HttpClient, ResponseTest);
