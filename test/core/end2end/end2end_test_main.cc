// Copyright 2022 gRPC authors.
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

#include <string>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/strings/str_cat.h"
#include "absl/types/optional.h"
#include "gtest/gtest.h"

#include "src/core/lib/config/config_vars.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/end2end/fixtures/h2_tls_common.h"
#include "test/core/util/test_config.h"

namespace grpc_core {
extern void EnsureSuitesLinked();
}

// DO NOT SUBMIT(hork): delete
void (*prev_handler)(int);
void sigabrt_handler(int i) {
#ifdef GPR_WINDOWS
  // Caught SIGABRT C++ signal
  HMODULE base_address;
  if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT |
                                   GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                               NULL,
                               &base_address) {
    base_address = NULL;
  }
  fprintf(stderr, "\r\nModule base address: 0x%llX\r\n", static_cast<unsigned long long>(
                            reinterpret_cast<uintptr_t>(base_address)));
  // Call prev handler and Terminate program
  prev_handler(i);
  exit(42);
#else
  prev_handler(i);
#endif
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_core::EnsureSuitesLinked();
  ::testing::InitGoogleTest(&argc, argv);
  // TODO(ctiller): make this per fixture?
  grpc_core::ConfigVars::Overrides overrides;
  overrides.default_ssl_roots_file_path = CA_CERT_PATH;
  // DO NOT SUBMIT(hork): remove
  overrides.trace =
      "event_engine,event_engine_endpoint,event_engine_endpoint_data,"
      "event_engine_poller";
  prev_handler = signal(SIGABRT, sigabrt_handler);
  // DO NOT SUBMIT(hork): remove above
  grpc_core::ConfigVars::SetOverrides(overrides);
  const auto all_tests = grpc_core::CoreEnd2endTestRegistry::Get().AllTests();
  for (const auto& test : all_tests) {
    ::testing::RegisterTest(
        absl::StrCat(test.suite).c_str(),
        absl::StrCat(test.name, "/", test.config->name).c_str(), nullptr,
        nullptr, __FILE__, __LINE__,
        [test = &test]() -> grpc_core::CoreEnd2endTest* {
          return test->make_test(test->config);
        });
  }
  return RUN_ALL_TESTS();
}
