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
#include <grpc/support/port_platform.h>

#include "gtest/gtest.h"

#include <grpc/grpc.h>
#include <grpc/support/log.h>

#include "test/core/util/test_config.h"

#if defined(GRPC_ENABLE_FORK_SUPPORT) && \
    defined(GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK)

#include "src/core/lib/iomgr/exec_ctx.h"

TEST(IomgrForkTest, GrpcCanFork) {
  int pid = fork();
  ASSERT_NE(pid, -1);
  if (pid == 0) {
    gpr_log(GPR_DEBUG, "post-fork child ran");
  }
  if (pid > 0) {
    gpr_log(GPR_DEBUG, "post-fork parent ran");
    int status;
    ASSERT_NE(waitpid(pid, &status, 0), -1);
    gpr_log(GPR_DEBUG, "child process finished");
  }
}

#endif  // GRPC_ENABLE_FORK_SUPPORT

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int retval = RUN_ALL_TESTS();
  grpc_shutdown();
  return retval;
}
