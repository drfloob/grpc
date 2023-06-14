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
#include <grpc/support/port_platform.h>

#include "test/core/util/test_config.h"

#include <inttypes.h>
#include <stdlib.h>

#include <initializer_list>
#include <string>

#include "absl/debugging/failure_signal_handler.h"
#include "absl/status/status.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"

#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>

#include "src/core/lib/gprpp/crash.h"
#include "src/core/lib/gprpp/env.h"
#include "src/core/lib/surface/init.h"
#include "test/core/event_engine/test_init.h"
#include "test/core/util/build.h"
#include "test/core/util/stack_tracer.h"

int64_t g_fixture_slowdown_factor = 1;
int64_t g_poller_slowdown_factor = 1;

#if GPR_GETPID_IN_UNISTD_H
#include <unistd.h>

static unsigned seed(void) { return static_cast<unsigned>(getpid()); }
#endif

#if GPR_GETPID_IN_PROCESS_H
#include <process.h>

static unsigned seed(void) { return (unsigned)_getpid(); }
#endif

#ifdef GPR_WINDOWS
#include <windows.h>

#include <iostream>

#include "dbghelp.h"

#include "src/core/lib/gprpp/examine_stack.h"

void print_stack_22467604(CONTEXT* ctx) {
  BOOL result;
  HANDLE process;
  HANDLE thread;
  HMODULE hModule;

  STACKFRAME64 stack;
  ULONG frame;
  DWORD64 displacement;

  DWORD disp;
  IMAGEHLP_LINE64* line;

  char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
  const int MaxNameLen = 256;
  char name[MaxNameLen];
  char module[MaxNameLen];
  PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

  // On x64, StackWalk64 modifies the context record, that could
  // cause crashes, so we create a copy to prevent it
  CONTEXT ctxCopy;
  memcpy(&ctxCopy, ctx, sizeof(CONTEXT));
  memset(&stack, 0, sizeof(STACKFRAME64));

  process = GetCurrentProcess();
  thread = GetCurrentThread();
  displacement = 0;
#if !defined(_M_AMD64)
  stack.AddrPC.Offset = (*ctx).Eip;
  stack.AddrPC.Mode = AddrModeFlat;
  stack.AddrStack.Offset = (*ctx).Esp;
  stack.AddrStack.Mode = AddrModeFlat;
  stack.AddrFrame.Offset = (*ctx).Ebp;
  stack.AddrFrame.Mode = AddrModeFlat;
#endif

  for (frame = 0;; frame++) {
    // get next call from stack
    result = StackWalk64(
#if defined(_M_AMD64)
        IMAGE_FILE_MACHINE_AMD64
#else
        IMAGE_FILE_MACHINE_I386
#endif
        ,
        process, thread, &stack, &ctxCopy, NULL, SymFunctionTableAccess64,
        SymGetModuleBase64, NULL);

    if (!result) break;

    // get symbol name for address
    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen = MAX_SYM_NAME;
    SymFromAddr(process, (ULONG64)stack.AddrPC.Offset, &displacement, pSymbol);

    line = (IMAGEHLP_LINE64*)malloc(sizeof(IMAGEHLP_LINE64));
    line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    // try to get line
    if (SymGetLineFromAddr64(process, stack.AddrPC.Offset, &disp, line)) {
      fprintf(stderr, "\tat %s in %s: line: %lu: address: 0x%llX\n", pSymbol->Name,
             line->FileName, line->LineNumber, pSymbol->Address);
    } else {
      // failed to get line
      fprintf(stderr, "\tat %s, address 0x%llX.\n", pSymbol->Name, pSymbol->Address);
      hModule = NULL;
      lstrcpyA(module, "");
      GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                        (LPCTSTR)(stack.AddrPC.Offset), &hModule);

      // at least print module name
      if (hModule != NULL) GetModuleFileNameA(hModule, module, MaxNameLen);

      fprintf(stderr, "in %s\n", module);
    }

    free(line);
    line = NULL;
  }
}

void print_stack_mehrdad(CONTEXT* ctx) {
  void* trace[63 /* "must be less than 64" according to MSDN */];
  unsigned int const skip = 0;
  size_t const nbacktrace =
      CaptureStackBackTrace(skip, (std::size(trace) - skip), trace, NULL);
  TCHAR line[2 << 10];
  size_t i = 0;
  while (i < nbacktrace && trace[i] != reinterpret_cast<void*>(ctx->
#if defined(_M_IX86)
                                                               Eip
#else
                                                               Rip
#endif
                                                               )) {
    ++i;
  }
  if (i == nbacktrace) {
    i = 0;
  }
  for (; i < nbacktrace; ++i) {
    // if (n >= static_cast<int>(std::size(line)) - 1) {
    //   break;
    // }
    HMODULE base_address = NULL;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT |
                               GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           reinterpret_cast<TCHAR const*>(trace[i]),
                           &base_address)) {
      base_address = NULL;
    }
    unsigned int relative_address = static_cast<unsigned int>(
        static_cast<unsigned char const*>(trace[i]) -
        reinterpret_cast<unsigned char const*>(base_address));
    int m = fprintf(stderr, "\r\n0x%llX+0x%X",
                    static_cast<unsigned long long>(
                        reinterpret_cast<uintptr_t>(base_address)),
                    relative_address);
    if (m < 0) {
      m = 0;
    }
    WCHAR module_name[MAX_PATH];
    size_t module_name_length =
        GetModuleFileNameW(base_address, module_name, std::size(module_name));
    // module_name now contains the DLL name
    fprintf(stderr, "  module: %ls", module_name);
  }
  // buf now contains all the base addresses + offsets
}

long exception_handler(PEXCEPTION_POINTERS p) {
  long r = EXCEPTION_CONTINUE_SEARCH;
  if (p->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION) {
    r = EXCEPTION_EXECUTE_HANDLER;
    auto trace = grpc_core::GetCurrentStackTrace();
    fprintf(stderr,
            "gRPC Exception Handler caught STATUS_ACCESS_VIOLATION. %s\n",
            trace.has_value() ? trace->c_str() : "Could not get stack trace.");
    fprintf(stderr, "---- mehrdad ----\n");
    print_stack_mehrdad(p->ContextRecord);
    fprintf(stderr, "\n---- 22467604 ----\n");
    print_stack_22467604(p->ContextRecord);
  } else {
    fprintf(stderr,
            "DO NOT SUBMIT: gRPC ignoring exception with status: 0x%08x\n",
            p->ExceptionRecord->ExceptionCode);
  }
  return r;
}
#endif

int64_t grpc_test_sanitizer_slowdown_factor() {
  int64_t sanitizer_multiplier = 1;
  if (BuiltUnderValgrind()) {
    sanitizer_multiplier = 20;
  } else if (BuiltUnderTsan()) {
    sanitizer_multiplier = 5;
  } else if (BuiltUnderAsan()) {
    sanitizer_multiplier = 3;
  } else if (BuiltUnderMsan()) {
    sanitizer_multiplier = 4;
  } else if (BuiltUnderUbsan()) {
    sanitizer_multiplier = 5;
  }
  return sanitizer_multiplier;
}

int64_t grpc_test_slowdown_factor() {
  return grpc_test_sanitizer_slowdown_factor() * g_fixture_slowdown_factor *
         g_poller_slowdown_factor;
}

gpr_timespec grpc_timeout_seconds_to_deadline(int64_t time_s) {
  return gpr_time_add(
      gpr_now(GPR_CLOCK_MONOTONIC),
      gpr_time_from_millis(
          grpc_test_slowdown_factor() * static_cast<int64_t>(1e3) * time_s,
          GPR_TIMESPAN));
}

gpr_timespec grpc_timeout_milliseconds_to_deadline(int64_t time_ms) {
  return gpr_time_add(
      gpr_now(GPR_CLOCK_MONOTONIC),
      gpr_time_from_micros(
          grpc_test_slowdown_factor() * static_cast<int64_t>(1e3) * time_ms,
          GPR_TIMESPAN));
}

namespace {
void RmArg(int i, int* argc, char** argv) {
  --(*argc);
  while (i < *argc) {
    argv[i] = argv[i + 1];
    ++i;
  }
}

void ParseTestArgs(int* argc, char** argv) {
  if (argc == nullptr || *argc <= 1) return;
  // flags to look for and consume
  const absl::string_view engine_flag{"--engine="};
  int i = 1;
  while (i < *argc) {
    if (absl::StartsWith(argv[i], engine_flag)) {
      absl::Status engine_set =
          grpc_event_engine::experimental::InitializeTestingEventEngineFactory(
              argv[i] + engine_flag.length());
      if (!engine_set.ok()) {
        grpc_core::Crash(absl::StrFormat("%s", engine_set.ToString().c_str()));
      }
      // remove the spent argv
      RmArg(i, argc, argv);
      continue;
    }
    ++i;
  }
}
}  // namespace

void grpc_test_init(int* argc, char** argv) {
  gpr_log_verbosity_init();
  ParseTestArgs(argc, argv);
  grpc_core::testing::InitializeStackTracer(argv[0]);
  absl::FailureSignalHandlerOptions options;
#ifdef GPR_WINDOWS
  options.call_previous_handler = true;
  AddVectoredExceptionHandler(1, exception_handler);
#endif
  absl::InstallFailureSignalHandler(options);
  gpr_log(GPR_DEBUG,
          "test slowdown factor: sanitizer=%" PRId64 ", fixture=%" PRId64
          ", poller=%" PRId64 ", total=%" PRId64,
          grpc_test_sanitizer_slowdown_factor(), g_fixture_slowdown_factor,
          g_poller_slowdown_factor, grpc_test_slowdown_factor());
  // seed rng with pid, so we don't end up with the same random numbers as a
  // concurrently running test binary
  srand(seed());
}

bool grpc_wait_until_shutdown(int64_t time_s) {
  gpr_timespec deadline = grpc_timeout_seconds_to_deadline(time_s);
  while (grpc_is_initialized()) {
    grpc_maybe_wait_for_async_shutdown();
    gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_millis(1, GPR_TIMESPAN)));
    if (gpr_time_cmp(gpr_now(GPR_CLOCK_MONOTONIC), deadline) > 0) {
      return false;
    }
  }
  return true;
}

namespace grpc {
namespace testing {

int CurrentGtestShard() {
  auto env = grpc_core::GetEnv("GTEST_SHARD_INDEX");
  if (!env.has_value()) return 0;
  int shard;
  if (!absl::SimpleAtoi(*env, &shard)) return 0;
  GPR_ASSERT(shard >= 0);
  GPR_ASSERT(shard < kMaxGtestShard);
  return shard + 1;
}

TestEnvironment::TestEnvironment(int* argc, char** argv) {
  grpc_test_init(argc, argv);
}

TestEnvironment::~TestEnvironment() {
  // This will wait until gRPC shutdown has actually happened to make sure
  // no gRPC resources (such as thread) are active. (timeout = 10s)
  if (!grpc_wait_until_shutdown(10)) {
    gpr_log(GPR_ERROR, "Timeout in waiting for gRPC shutdown");
  }
  if (BuiltUnderMsan()) {
    // This is a workaround for MSAN. MSAN doesn't like having shutdown thread
    // running. Although the code above waits until shutdown is done, chances
    // are that thread itself is still alive. To workaround this problem, this
    // is going to wait for 0.5 sec to give a chance to the shutdown thread to
    // exit. https://github.com/grpc/grpc/issues/23695
    gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_millis(500, GPR_TIMESPAN)));
  }
  gpr_log(GPR_INFO, "TestEnvironment ends");
}

TestGrpcScope::TestGrpcScope() { grpc_init(); }

TestGrpcScope::~TestGrpcScope() {
  grpc_shutdown();
  if (!grpc_wait_until_shutdown(10)) {
    gpr_log(GPR_ERROR, "Timeout in waiting for gRPC shutdown");
  }
}

}  // namespace testing
}  // namespace grpc
