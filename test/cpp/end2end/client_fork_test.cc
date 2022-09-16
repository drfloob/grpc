/*
 * Copyright 2022 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <pthread.h>
#include <signal.h>

#include <gtest/gtest.h>

#include "absl/strings/str_cat.h"

#include <grpc/fork.h>
#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "src/core/lib/gprpp/fork.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/util/port.h"
#include "test/core/util/test_config.h"
#include "test/cpp/util/subprocess.h"

namespace grpc {
namespace testing {
namespace {

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;
using grpc::testing::EchoTestService;

class ServiceImpl final : public EchoTestService::Service {
  Status BidiStream(
      ServerContext* /*context*/,
      ServerReaderWriter<EchoResponse, EchoRequest>* stream) override {
    EchoRequest request;
    EchoResponse response;
    while (stream->Read(&request)) {
      gpr_log(GPR_INFO, "recv msg %s", request.message().c_str());
      response.set_message(request.message());
      stream->Write(response);
    }
    return Status::OK;
  }
};

// These unfortunately need to live outside of the test body, because
// they're referenced in functions passed by pointer to pthread_atfork.
std::string addr;
std::unique_ptr<EchoTestService::Stub> stub;

std::unique_ptr<EchoTestService::Stub> MakeStub() {
  return EchoTestService::NewStub(
      grpc::CreateChannel(addr, InsecureChannelCredentials()));
}

void ResetStub() {
  stub.reset();
  stub = MakeStub();
}

TEST(ClientForkTest, ClientCallsBeforeAndAfterForkSucceed) {
  grpc_core::Fork::Enable(true);

  int port = grpc_pick_unused_port_or_die();
  addr = absl::StrCat("localhost:", port);

  pid_t server_pid = fork();
  switch (server_pid) {
    case -1:  // fork failed
      GTEST_FAIL() << "failure forking";
    case 0:  // post-fork child
    {
      ServiceImpl impl;
      grpc::ServerBuilder builder;
      builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
      builder.RegisterService(&impl);
      std::unique_ptr<Server> server(builder.BuildAndStart());
      server->Wait();
      return;
    }
    default:  // post-fork parent
      break;
  }

  // Equivalent to grpc_fork_handlers_auto_register, without the need for
  // GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK.
  pthread_atfork(grpc_prefork, grpc_postfork_parent, grpc_postfork_child);

  // Register another atfork handler so that clients are reset in post-fork
  // parent and child.
  pthread_atfork(nullptr, ResetStub, ResetStub);

  stub = MakeStub();

  // Do a round trip before we fork.
  {
    EchoRequest request;
    EchoResponse response;
    ClientContext context;
    context.set_wait_for_ready(true);

    auto stream = stub->BidiStream(&context);

    request.set_message("Hello");
    EXPECT_TRUE(stream->Write(request));
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message());
  }

  // Fork and do round trips in the post-fork parent and child.
  pid_t child_client_pid = fork();
  switch (child_client_pid) {
    case -1:  // fork failed
      GTEST_FAIL() << "fork failed";
    case 0:  // post-fork child
    {
      EchoRequest request;
      EchoResponse response;
      ClientContext context;
      context.set_wait_for_ready(true);

      auto stream = stub->BidiStream(&context);

      request.set_message("Hello");
      ASSERT_TRUE(stream->Write(request));
      ASSERT_TRUE(stream->Read(&response));
      ASSERT_EQ(response.message(), request.message());
      exit(0);
    }
    default:  // post-fork parent
    {
      EchoRequest request;
      EchoResponse response;
      ClientContext context;
      context.set_wait_for_ready(true);

      auto stream = stub->BidiStream(&context);

      request.set_message("Hello");
      ASSERT_TRUE(stream->Write(request));
      ASSERT_TRUE(stream->Read(&response));
      ASSERT_EQ(response.message(), request.message());

      // Wait for the post-fork child to exit; ensure it exited cleanly.
      int child_status;
      ASSERT_EQ(waitpid(child_client_pid, &child_status, 0), child_client_pid)
          << "failed to get status of child client";
      ASSERT_EQ(WEXITSTATUS(child_status), 0) << "child did not exit cleanly";
      break;
    }
  }

  stub.reset();
  kill(server_pid, SIGINT);
}

}  // namespace
}  // namespace testing
}  // namespace grpc

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
