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

#include <grpc/support/log.h>

#include "src/core/lib/gprpp/crash.h"
#include "src/proto/grpc/testing/control.pb.h"
#include "test/core/util/test_config.h"
#include "test/cpp/qps/benchmark_config.h"
#include "test/cpp/qps/driver.h"
#include "test/cpp/util/test_config.h"
#include "test/cpp/util/test_credentials_provider.h"

namespace grpc {
namespace testing {

static const int WARMUP = 1;
static const int BENCHMARK = 3;

static void RunSynchronousUnaryPingPong() {
  const char* json_str = R"json({
      "scenarios": {
        "name": "cpp_protobuf_async_streaming_qps_unconstrained_secure",
        "num_servers": 1,
        "num_clients": 0,
        "client_config": {
          "client_type": "ASYNC_CLIENT",
          "security_params": {
            "use_test_ca": true,
            "server_host_override": "foo.test.google.fr"
          },
          "outstanding_rpcs_per_channel": 100,
          "client_channels": 64,
          "async_client_threads": 0,
          "client_processes": 0,
          "threads_per_cq": 2,
          "rpc_type": "STREAMING",
          "histogram_params": {
            "resolution": 0.01,
            "max_possible": 60000000000.0
          },
          "channel_args": [
            {
              "name": "grpc.optimization_target",
              "str_value": "throughput"
            }
          ],
          "payload_config": {
            "simple_params": {
              "req_size": 0,
              "resp_size": 0
            }
          },
          "load_params": {
            "closed_loop": {}
          }
        },
        "server_config": {
          "server_type": "ASYNC_SERVER",
          "security_params": {
            "use_test_ca": true,
            "server_host_override": "foo.test.google.fr"
          },
          "async_server_threads": 0,
          "server_processes": 0,
          "threads_per_cq": 2,
          "channel_args": [
            {
              "name": "grpc.optimization_target",
              "str_value": "throughput"
            }
          ]
        },
        "warmup_seconds": 30,
        "benchmark_seconds": 30
      }
    })json";
  grpc::protobuf::json::JsonParseOptions options;
  options.case_insensitive_enum_parsing = true;
  // ClientConfig client_config;
  // auto proto_result = grpc::protobuf::json::JsonStringToMessage(
  //     json_str, &client_config, options);
  Scenarios scenarios;
  auto proto_result =
      grpc::protobuf::json::JsonStringToMessage(json_str, &scenarios, options);
  if (!proto_result.ok()) {
    grpc_core::Crash(proto_result.message());
  }
  gpr_log(GPR_INFO, "arstarst Running %s", scenarios.scenarios(0).name().c_str());

  // ServerConfig server_config;
  // server_config.set_server_type(SYNC_SERVER);

  // Set up security params
  // SecurityParams security;
  // security.set_use_test_ca(true);
  // security.set_server_host_override("foo.test.google.fr");
  // scena client_config.mutable_security_params()->CopyFrom(security);
  // server_config.mutable_security_params()->CopyFrom(security);

  const auto result =
      RunScenario(scenarios.scenarios(0).client_config(), 1,
                  scenarios.scenarios(0).server_config(), 1, WARMUP, BENCHMARK,
                  -2, "", kInsecureCredentialsType, {}, false, 0);

  GetReporter()->ReportQPS(*result);
  GetReporter()->ReportLatency(*result);
}

}  // namespace testing
}  // namespace grpc

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);

  grpc::testing::RunSynchronousUnaryPingPong();
  return 0;
}
