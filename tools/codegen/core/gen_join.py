#!/usr/bin/env python3

# Copyright 2023 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys

from mako.template import Template

join_state = Template(
    """
template <class Traits, ${",".join(f"typename P{i}" for i in range(0,n))}>
struct JoinState<Traits, ${",".join(f"P{i}" for i in range(0,n))}> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
% for i in range(0,n):
  using Promise${i} = PromiseLike<P${i}>;
  using Result${i} = UnwrappedType<typename Promise${i}::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise${i} promise${i};
    GPR_NO_UNIQUE_ADDRESS Result${i} result${i};
  };
% endfor
  GPR_NO_UNIQUE_ADDRESS BitSet<${n}> ready;
  JoinState(${",".join(f"P{i}&& p{i}" for i in range(0,n))}) {
% for i in range(0,n):
    Construct(&promise${i}, std::forward<P${i}>(p${i}));
% endfor
  }
  JoinState(const JoinState& other) {
    CHECK(other.ready.none());
% for i in range(0,n):
    Construct(&promise${i}, other.promise${i});
% endfor
  }
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  JoinState(JoinState&& other) noexcept : ready(other.ready) {
% for i in range(0,n):
    if (ready.is_set(${i})) {
      Construct(&result${i}, std::move(other.result${i}));
    } else {
      Construct(&promise${i}, std::move(other.promise${i}));
    }
% endfor
  }
  ~JoinState() {
% for i in range(0,n):
    if (ready.is_set(${i})) {
      Destruct(&result${i});
    } else {
      Destruct(&promise${i});
    }
% endfor
  }
  using Result = typename Traits::template ResultType<std::tuple<
      ${",".join(f"Result{i}" for i in range(0,n))}>>;
  Poll<Result> PollOnce() {
% for i in range(0,n):
    if (!ready.is_set(${i})) {
      if (grpc_trace_promise_primitives.enabled()) {
        VLOG(2) << "join[" << this << "]: begin poll joint ${i+1}/${n}";
      }
      auto poll = promise${i}();
      if (grpc_trace_promise_primitives.enabled()) {
        auto* p = poll.value_if_ready();
        VLOG(2) << "join[" << this << "]: joint ${i+1}/${n} "
                << (p != nullptr ? (Traits::IsOk(*p)? "ready" : "early-error") : "pending");
      }
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(${i});
          Destruct(&promise${i});
          Construct(&result${i}, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else if (grpc_trace_promise_primitives.enabled()) {
      VLOG(2) << "join[" << this << "]: joint ${i+1}/${n} already ready";
    }
% endfor
    if (ready.all()) {
      return Traits::FinalReturn(${",".join(f"std::move(result{i})" for i in range(0,n))});
    }
    return Pending{};
  }
};
"""
)

front_matter = """
#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_JOIN_STATE_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_JOIN_STATE_H

// This file is generated by tools/codegen/core/gen_seq.py

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"

#include "src/core/lib/gprpp/construct_destruct.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/gprpp/bitset.h"
#include <tuple>
#include <type_traits>
#include <utility>

namespace grpc_core {
namespace promise_detail {
template <class Traits, typename... Ps>
struct JoinState;
"""

end_matter = """
}  // namespace promise_detail
}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_DETAIL_JOIN_STATE_H
"""


# utility: print a big comment block into a set of files
def put_banner(files, banner):
    for f in files:
        for line in banner:
            print("// %s" % line, file=f)
        print("", file=f)


with open(sys.argv[0]) as my_source:
    copyright = []
    for line in my_source:
        if line[0] != "#":
            break
    for line in my_source:
        if line[0] == "#":
            copyright.append(line)
            break
    for line in my_source:
        if line[0] != "#":
            break
        copyright.append(line)

copyright = [line[2:].rstrip() for line in copyright]

with open("src/core/lib/promise/detail/join_state.h", "w") as f:
    put_banner([f], copyright)
    print(front_matter, file=f)
    for n in range(2, 10):
        print(join_state.render(n=n), file=f)
    print(end_matter, file=f)
