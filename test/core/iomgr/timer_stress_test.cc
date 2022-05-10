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

#include <random>
#include <thread>

#include <gtest/gtest.h>

#include "absl/functional/bind_front.h"
#include "absl/time/time.h"

#include <grpc/grpc.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/log.h>

#include "src/core/lib/gprpp/sync.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/timer.h"
#include "test/core/util/test_config.h"

class TimerTest : public testing::Test {
 public:
  static void ScheduleCheckCB(void* arg, grpc_error_handle error);

 protected:
  grpc_core::Mutex mu_;
  grpc_core::CondVar cv_;
  bool signaled_ ABSL_GUARDED_BY(mu_) = false;
  std::atomic<int> call_count{0};
  std::atomic<int> failed_call_count{0};
};

struct TimerData {
  grpc_timer timer;
  TimerTest* test;
  grpc_core::Timestamp when;
  int total_expected;
};

void TimerTest::ScheduleCheckCB(void* arg, grpc_error_handle /*error*/) {
  TimerData* td = reinterpret_cast<TimerData*>(arg);
  auto now = grpc_core::ExecCtx::Get()->Now();
  EXPECT_LE(td->when, now);
  if (td->when > now) ++(td->test->failed_call_count);
  if (++(td->test->call_count) == td->total_expected) {
    grpc_core::MutexLock lock(&td->test->mu_);
    td->test->signaled_ = true;
    td->test->cv_.Signal();
  }
  delete td;
};

TEST_F(TimerTest, StressTestTimersNotCalledBeforeScheduled) {
  constexpr int thread_count = 100;
  constexpr int call_count_per_thread = 500;
  constexpr float timeout_min_millis = 50;
  constexpr float timeout_max_millis = 10 * 1000;
  std::vector<std::thread> threads;
  threads.reserve(thread_count);
  for (int thread_n = 0; thread_n < thread_count; ++thread_n) {
    threads.emplace_back([&]() {
      grpc_core::ExecCtx ctx;
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(timeout_min_millis,
                                           timeout_max_millis);
      for (int call_n = 0; call_n < call_count_per_thread; ++call_n) {
        grpc_core::Timestamp when = grpc_core::ExecCtx::Get()->Now() +
                                    grpc_core::Duration::Milliseconds(dis(gen));
        auto* td = new TimerData;
        td->test = this;
        td->when = when;
        td->total_expected = thread_count * call_count_per_thread;
        grpc_timer_init(&td->timer, when,
                        GRPC_CLOSURE_CREATE(ScheduleCheckCB, td, nullptr));
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  grpc_core::MutexLock lock(&mu_);
  // to protect against spurious wakeups.
  while (!signaled_) {
    cv_.Wait(&mu_);
  }
  gpr_log(GPR_DEBUG, "failed timer count: %d of %d", failed_call_count.load(),
          thread_count * call_count);
  ASSERT_EQ(0, failed_call_count.load());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
