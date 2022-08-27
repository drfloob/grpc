// Copyright 2022 The gRPC Authors
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

#include <atomic>
#include <cmath>
#include <memory>

#include <benchmark/benchmark.h>

#include <grpc/event_engine/event_engine.h>
#include <grpcpp/impl/grpc_library.h>

#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/promise.h"
#include "test/core/util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

namespace {

using ::grpc_event_engine::experimental::AnyInvocableClosure;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::GetDefaultEventEngine;
using ::grpc_event_engine::experimental::Promise;
using ::grpc_event_engine::experimental::ResetDefaultEventEngine;

void BM_EventEngine_RunLambda(benchmark::State& state) {
  int cb_count = state.range(0);
  std::atomic_int cnt{0};
  Promise<bool> p{false};
  auto cb = [&cnt, &p, cb_count]() {
    if (++cnt == cb_count) p.Set(true);
  };
  auto engine = GetDefaultEventEngine();
  for (auto _ : state) {
    for (int i = 0; i < cb_count; i++) {
      engine->Run(cb);
    }
    GPR_ASSERT(p.Get());
    state.PauseTiming();
    p.Reset();
    cnt.store(0);
    state.ResumeTiming();
  }
  ResetDefaultEventEngine();
  state.SetItemsProcessed(cb_count * state.iterations());
}
BENCHMARK(BM_EventEngine_RunLambda)->Range(100, 10 * 1000);
;

void BM_EventEngine_RunClosure(benchmark::State& state) {
  int cb_count = state.range(0);
  Promise<bool> p{false};
  std::atomic_int cnt{0};
  AnyInvocableClosure closure([&cnt, &p, cb_count]() {
    if (++cnt == cb_count) {
      p.Set(true);
    }
  });
  auto engine = GetDefaultEventEngine();
  for (auto _ : state) {
    for (int i = 0; i < cb_count; i++) {
      engine->Run(&closure);
    }
    GPR_ASSERT(p.Get());
    state.PauseTiming();
    p.Reset();
    cnt.store(0);
    state.ResumeTiming();
  }
  ResetDefaultEventEngine();
  state.SetItemsProcessed(cb_count * state.iterations());
}
BENCHMARK(BM_EventEngine_RunClosure)->Range(100, 10 * 1000);

void FanOutCallback(EventEngine* engine, std::atomic_int& cnt, int fanout,
                    int depth, int limit, Promise<bool>& promise) {
  auto local_cnt = ++cnt;
  if (local_cnt % 1000 == 0) {
    gpr_log(GPR_DEBUG, "DO NOT SUBMIT: fanout=%d, depth=%d, cnt=%d, limit=%d",
            fanout, depth, local_cnt, limit);
  }
  if (local_cnt == limit) {
    promise.Set(true);
    return;
  }
  if (depth == 0) return;
  for (int i = 0; i < fanout; i++) {
    engine->Run([engine, &cnt, fanout, depth, limit, &promise]() {
      FanOutCallback(engine, cnt, fanout, depth - 1, limit, promise);
    });
  }
}

void BM_EventEngine_FanOut(benchmark::State& state) {
  int depth = state.range(0);
  int fanout = state.range(1);
  // sum of geometric series
  int limit = (1 - std::pow(fanout, depth + 1)) / (1 - fanout);
  auto engine = GetDefaultEventEngine();
  for (auto _ : state) {
    Promise<bool> promise{false};
    std::atomic_int cnt{0};
    // gpr_log(GPR_DEBUG, "DO NOT SUBMIT: fanout=%d depth=%d limit=%d", fanout,
    // depth, limit);
    FanOutCallback(engine, cnt, fanout, depth, limit, promise);
    GPR_ASSERT(promise.Get());
  }
  ResetDefaultEventEngine();
  state.SetItemsProcessed(limit * state.iterations());
}
BENCHMARK(BM_EventEngine_FanOut)->Ranges({{1, 6}, {2, 5}});
}  // namespace

// Some distros have RunSpecifiedBenchmarks under the benchmark namespace,
// and others do not. This allows us to support both modes.
namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}  // namespace benchmark

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  LibraryInitializer libInit;
  benchmark::Initialize(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, false);

  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
