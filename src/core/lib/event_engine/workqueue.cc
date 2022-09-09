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
#include <grpc/support/port_platform.h>

#include "workqueue.h"

#include "common_closures.h"

#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/workqueue.h"
#include "src/core/lib/iomgr/exec_ctx.h"

namespace grpc_event_engine {
namespace experimental {

// ------ WorkQueue::Storage --------------------------------------------------

WorkQueue::Storage::Storage(EventEngine::Closure* closure) noexcept
    : closure_(closure),
      enqueued_(
          grpc_core::ExecCtx::Get()->Now().milliseconds_after_process_epoch()) {
}

WorkQueue::Storage::Storage(absl::AnyInvocable<void()> callback) noexcept
    : closure_(SelfDeletingClosure::Create(std::move(callback))),
      enqueued_(
          grpc_core::ExecCtx::Get()->Now().milliseconds_after_process_epoch()) {
}

WorkQueue::Storage::Storage(Storage&& other) noexcept
    : closure_(other.closure_),
      enqueued_(other.enqueued_) {}

WorkQueue::Storage& WorkQueue::Storage::operator=(Storage&& other) noexcept {
  std::swap(closure_, other.closure_);
  std::swap(enqueued_, other.enqueued_);
  return *this;
}

EventEngine::Closure* WorkQueue::Storage::closure() {
  return closure_;
//   if (closure_ != nullptr) return closure_;
//   return reinterpret_cast<EventEngine::Closure*>(&invocable_closure_);
}

// ------ WorkQueue -----------------------------------------------------------

// Returns whether the queue is empty
bool WorkQueue::Empty() const {
  return (most_recent_element_enqueue_timestamp_.load(
              std::memory_order_relaxed) == kInvalidTimestamp &&
          oldest_enqueued_timestamp_.load(std::memory_order_relaxed) ==
              kInvalidTimestamp);
}

size_t WorkQueue::Size() {
  grpc_core::MutexLock lock(&mu_);
  return elements_.size() + (most_recent_element_enqueue_timestamp_.load(
                                 std::memory_order_relaxed) == kInvalidTimestamp
                                 ? 0
                                 : 1);
}

grpc_core::Timestamp WorkQueue::OldestEnqueuedTimestamp() const {
  int64_t front_of_queue_timestamp =
      oldest_enqueued_timestamp_.load(std::memory_order_relaxed);
  if (front_of_queue_timestamp != kInvalidTimestamp) {
    return grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
        front_of_queue_timestamp);
  }
  int64_t most_recent_millis =
      most_recent_element_enqueue_timestamp_.load(std::memory_order_relaxed);
  if (most_recent_millis == kInvalidTimestamp) {
    return grpc_core::Timestamp::InfPast();
  }
  return grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
      most_recent_millis);
}

absl::optional<EventEngine::Closure*> WorkQueue::PopFront()
    ABSL_LOCKS_EXCLUDED(mu_) {
  if (oldest_enqueued_timestamp_.load(std::memory_order_relaxed) !=
      kInvalidTimestamp) {
    absl::optional<EventEngine::Closure*> t = TryLockAndPop(/*front=*/true);
    if (t.has_value()) return t;
  }
  if (most_recent_element_enqueue_timestamp_.load(std::memory_order_relaxed) !=
      kInvalidTimestamp) {
    return TryPopMostRecentElement();
  }
  return absl::nullopt;
}

absl::optional<EventEngine::Closure*> WorkQueue::PopBack() {
  if (most_recent_element_enqueue_timestamp_.load(std::memory_order_relaxed) !=
      kInvalidTimestamp) {
    return TryPopMostRecentElement();
  }
  if (oldest_enqueued_timestamp_.load(std::memory_order_relaxed) !=
      kInvalidTimestamp) {
    absl::optional<EventEngine::Closure*> t = TryLockAndPop(/*front=*/false);
    if (t.has_value()) return *t;
  }
  return absl::nullopt;
}

void WorkQueue::Add(EventEngine::Closure* closure) {
  grpc_core::ExecCtx exec_ctx;
  AddInternal(Storage(closure));
}

void WorkQueue::Add(absl::AnyInvocable<void()> invocable) {
  grpc_core::ExecCtx exec_ctx;
  AddInternal(Storage(std::move(invocable)));
}

void WorkQueue::AddInternal(Storage&& storage) {
  Storage previous_most_recent;
  int64_t previous_ts;
  {
    absl::optional<Storage> tmp_element;
    {
      grpc_core::MutexLock lock(&most_recent_element_lock_);
      previous_ts = most_recent_element_enqueue_timestamp_.exchange(
          storage.enqueued(), std::memory_order_relaxed);
      tmp_element = std::exchange(most_recent_element_, std::move(storage));
    }
    if (!tmp_element.has_value() || previous_ts == kInvalidTimestamp) return;
    previous_most_recent = std::move(*tmp_element);
  }
  grpc_core::MutexLock lock(&mu_);
  if (elements_.empty()) {
    oldest_enqueued_timestamp_.store(previous_ts, std::memory_order_relaxed);
  }
  elements_.push_back(std::move(previous_most_recent));
}

absl::optional<EventEngine::Closure*> WorkQueue::TryLockAndPop(bool front)
    ABSL_LOCKS_EXCLUDED(mu_) {
  // Do not block the worker if there are other workers trying to pop
  // tasks from this queue.
  if (!mu_.TryLock()) return absl::nullopt;
  auto ret = PopLocked(front);
  mu_.Unlock();
  return ret;
}

absl::optional<EventEngine::Closure*> WorkQueue::PopLocked(bool front)
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
  if (GPR_UNLIKELY(elements_.empty())) {
    if (most_recent_element_enqueue_timestamp_.load(
            std::memory_order_relaxed) == kInvalidTimestamp) {
      return absl::nullopt;
    }
    if (!most_recent_element_lock_.TryLock()) return absl::nullopt;
    absl::optional<Storage> ret;
    if (GPR_LIKELY(most_recent_element_.has_value())) {
      most_recent_element_enqueue_timestamp_.store(kInvalidTimestamp,
                                                   std::memory_order_relaxed);
      ret = std::exchange(most_recent_element_, absl::nullopt);
    }
    most_recent_element_lock_.Unlock();
    return ret->closure();
  }
  // the queue has elements, let's pop one and update timestamps
  Storage ret_s;
  if (front) {
    ret_s = std::move(elements_.front());
    elements_.pop_front();
  } else {
    ret_s = std::move(elements_.back());
    elements_.pop_back();
  }
  if (elements_.empty()) {
    oldest_enqueued_timestamp_.store(kInvalidTimestamp,
                                     std::memory_order_relaxed);
  } else if (front) {
    oldest_enqueued_timestamp_.store(elements_.front().enqueued(),
                                     std::memory_order_relaxed);
  }
  return ret_s.closure();
}

absl::optional<EventEngine::Closure*> WorkQueue::TryPopMostRecentElement() {
  if (!most_recent_element_lock_.TryLock()) return absl::nullopt;
  if (GPR_UNLIKELY(!most_recent_element_.has_value())) {
    most_recent_element_lock_.Unlock();
    return absl::nullopt;
  }
  most_recent_element_enqueue_timestamp_.store(kInvalidTimestamp,
                                               std::memory_order_relaxed);
  absl::optional<Storage> tmp =
      std::exchange(most_recent_element_, absl::nullopt);
  most_recent_element_lock_.Unlock();
  return tmp->closure();
}

}  // namespace experimental
}  // namespace grpc_event_engine
