// Copyright 2024 The gRPC Authors
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
#ifndef GRPC_EVENT_ENGINE_INTERNAL_DEBUG_SHARED_PTR_H
#define GRPC_EVENT_ENGINE_INTERNAL_DEBUG_SHARED_PTR_H

// event_engine.h must have been included already
// DO NOT SUBMIT - needs to be flag-guarded

#include <string>
#include <type_traits>
#include <unordered_map>

#include "absl/log/log.h"

#include <grpc/event_engine/event_engine.h>

#include "src/core/lib/gprpp/examine_stack.h"`

namespace std {
template <>
class shared_ptr<grpc_event_engine::experimental::EventEngine>
    : public __shared_ptr<grpc_event_engine::experimental::EventEngine> {
 private:
  using EE_ = grpc_event_engine::experimental::EventEngine;
  using element_type = typename __shared_ptr<EE_>::element_type;

 public:
  shared_ptr() noexcept : id_(GetId("empty")) {
    LOG(ERROR) << "[DO NOT SUBMIT] empty";
  }

  // NOLINTNEXTLINE(google-explicit-constructor)
  shared_ptr(nullptr_t) noexcept : id_(GetId("nullptr")) {
    LOG(ERROR) << "[DO NOT SUBMIT] nullptr EE";
  }

  template <class convertible_cls,
            enable_if_t<is_convertible<convertible_cls, EE_>::value, int> = 0>
  explicit shared_ptr(convertible_cls* ee) : id_(GetId(ee)) {
    LOG(ERROR) << "[DO NOT SUBMIT] convertible ptr";
    ee_ = ee;
    if (refcounts_.find(ee) == refcounts_.end()) {
      // DO NOT SUBMIT(hork): is this necessary?
      refcounts_[ee] = 1;
    } else {
      refcounts_[ee]++;
    }
  }

  template <class convertible_cls, class _Dx,
            enable_if<is_convertible<convertible_cls, EE_>::value, int> = 0>
  shared_ptr(convertible_cls* ee, _Dx _Dt) : shared_ptr(ee) {
    LOG(ERROR) << "Ignoring custom deleter for EE::" << ee;
  }

  // TODO(hork): No need for a constructor with a custom allocator
  // TODO(hork): No need for a constructor with a custom allocator

  // Aliasing
  template <typename cls>
  shared_ptr(const shared_ptr<cls>& right, element_type* ee) noexcept
      : id_(GetId(ee)), ee_(ee) {
    LOG(ERROR) << "[DO NOT SUBMIT] aliasing1";
    refcounts_[ee_]++;
  }

  // Aliasing
  template <typename cls>
  shared_ptr(shared_ptr<cls>&& right, element_type* ee) noexcept
      : id_(GetId(ee)), ee_(ee) {
    LOG(FATAL) << "Trying to call aliasing move constructor of "
                  "shared_ptr<EE>";
    refcounts_[ee_]++;
  }

  EE_* get() const { return ee_; }

  template <class convertible_cls,
            enable_if<is_convertible<convertible_cls, EE_>::value, int> = 0>
  explicit shared_ptr(const shared_ptr<convertible_cls>& _Other) noexcept
      : id_(GetId(_Other.get())) {
    // construct shared_ptr object that owns same resource as _Other
    ee_ = _Other.get();
    refcounts_[ee_]++;
  }

  template <class convertible_cls, class _Dx,
            enable_if<is_convertible<convertible_cls, EE_>::value, int> = 0>
  shared_ptr(const shared_ptr<convertible_cls>& _Other, _Dx _Dt) noexcept
      : shared_ptr(_Other) {
    LOG(ERROR) << "Ignoring custom deleter for EE::" << _Other.get();
  }

  template <class convertible_cls,
            enable_if<is_convertible<convertible_cls, EE_>::value, int> = 0>
  explicit shared_ptr(shared_ptr<convertible_cls>&& _Other) noexcept {
    // construct shared_ptr object that takes resource from _Right
    id_ = _Other.id_;
    _Other.id_ = 0;
    ee_ = _Other.ee_;
    _Other.ee_ = nullptr;
    refcounts_[ee_]--;
  }

  void swap(shared_ptr& _Other) noexcept {
    std::swap(id_, _Other.id_);
    std::swap(ee_, _Other.ee_);
  }

  void reset() noexcept {
    // release resource and convert to empty shared_ptr object
    shared_ptr().swap(*this);
    // DO NOT SUBMIT(hork): does this need refcount changes?
  }

  // template <class convertible_cls,
  //           enable_if<is_convertible<convertible_cls, EE_>::type, int> = 0>
  template <class convertible_cls>
  explicit shared_ptr(const weak_ptr<convertible_cls>& _Other) {
    LOG(ERROR) << "[DO NOT SUBMIT] weakptr1";
    std::shared_ptr<EE_> eesp = _Other.lock();
    assert(eesp != nullptr);
    eesp.swap(*this);
    // DO NOT SUBMIT(hork): this should be done automatically on construction
    // refcounts_[ee_]++;
  }

  // template <class convertible_cls, class _Dx,
  //           enable_if<is_convertible<convertible_cls, EE_>::value, int> = 0>
  template <class convertible_cls, class _Dx>
  explicit shared_ptr(const weak_ptr<convertible_cls>& _Other, _Dx _Dt)
      : shared_ptr(_Other) {
    LOG(ERROR) << "Converting from weak_ptr, ignoring custom deleter for "
                  "shared_ptr<EventEngine>";
  }

  template <class convertible_cls, class _Dx,
            enable_if_t<is_convertible<
                            typename unique_ptr<convertible_cls, _Dx>::pointer,
                            EE_*>::value,
                        int> = 0>
  explicit shared_ptr(unique_ptr<convertible_cls, _Dx>&& _Other)
      : id_(GetId(_Other.get())) {
    LOG(ERROR) << "Converting from unique_ptr, ignoring custom deleter for "
                  "shared_ptr<EventEngine>::"
               << _Other.get();
    ee_ = _Other.release();
  }

  ~shared_ptr() noexcept {  // release resource
    LOG(ERROR) << "Destroying: shared_ptr<EventEngine>::" << this
               << " id::" << id_;
    living_engines_.erase(id_);
    refcounts_[ee_]--;
  }

  // shared_ptr& operator=(const shared_ptr& _Right) noexcept {
  //   shared_ptr(_Right).swap(*this);
  //   return *this;
  // }

  template <class convertible_cls,
            enable_if_t<is_convertible<convertible_cls, EE_>::value, int> = 0>
  shared_ptr& operator=(const shared_ptr<convertible_cls>& _Right) noexcept {
    shared_ptr(_Right).swap(*this);
    return *this;
  }

  // shared_ptr& operator=(shared_ptr&& _Right) noexcept {
  //   shared_ptr(std::move(_Right)).swap(*this);
  //   return *this;
  // }

  template <class convertible_cls,
            enable_if_t<is_convertible<convertible_cls, EE_>::value, int> = 0>
  shared_ptr& operator=(shared_ptr<convertible_cls>&& _Right) noexcept {
    shared_ptr(std::move(_Right)).swap(*this);
    return *this;
  }

  template <class convertible_cls, class _Dx,
            enable_if_t<is_convertible<convertible_cls, EE_>::value, int> = 0>
  shared_ptr& operator=(unique_ptr<convertible_cls, _Dx>&& _Right) {
    // move from unique_ptr
    shared_ptr(std::move(_Right)).swap(*this);
    return *this;
  }

  // DO NOT SUBMIT(hork): reset with custom destructor is not supported

  // template <class _Ux, class _Dx,
  //           enable_if_t<conjunction_v<is_move_constructible<_Dx>,
  //                                     _Can_call_function_object<_Dx&, _Ux*&>,
  //                                     _SP_convertible<_Ux, _Ty>>,
  //                       int> = 0>
  // void reset(_Ux* _Px,
  //            _Dx _Dt) {  // release, take ownership of _Px, with deleter _Dt
  //   shared_ptr(_Px, _Dt).swap(*this);
  // }

  // template <class _Ux, class _Dx, class _Alloc,
  //           enable_if_t<conjunction_v<is_move_constructible<_Dx>,
  //                                     _Can_call_function_object<_Dx&, _Ux*&>,
  //                                     _SP_convertible<_Ux, _Ty>>,
  //                       int> = 0>
  // void reset(_Ux* _Px, _Dx _Dt,
  //            _Alloc _Ax) {  // release, take ownership of _Px, with deleter
  //            _Dt,
  //                           // allocator _Ax
  //   shared_ptr(_Px, _Dt, _Ax).swap(*this);
  // }

  template <
      class _Ty2 = EE_,
      enable_if_t<!absl::disjunction<is_array<_Ty2>, is_void<_Ty2>>::value,
                  int> = 0>
  ABSL_MUST_USE_RESULT _Ty2& operator*() const noexcept {
    return *get();
  }

  template <class _Ty2 = EE_, enable_if_t<!is_array<_Ty2>::value, int> = 0>
  ABSL_MUST_USE_RESULT _Ty2* operator->() const noexcept {
    return get();
  }

  explicit operator bool() const noexcept { return get() != nullptr; }

  void PrintLivingEngines() {
    for (const auto& n : living_engines_) {
      LOG(ERROR) << "Living engine ID::" << n.first
                 << " metadata: " << n.second;
    }
  }

 private:
  template <class... _Types>
  friend shared_ptr<EE_> make_shared(_Types&&... _Args);

  template <class _Alloc, class... _Types>
  friend shared_ptr<EE_> allocate_shared(const _Alloc& _Al_arg,
                                         _Types&&... _Args);

  static int GetId(void* _Px) {
    auto id = counter_.fetch_add(1);
    gpr_log(GPR_ERROR, "Creating:   shared_ptr<EventEngine>::%d %p", id, _Px);
    living_engines_[id] = grpc_core::GetCurrentStackTrace().value();
    return id;
  }

  static int GetId(const char* ctx = "") {
    auto id = counter_.fetch_add(1);
    gpr_log(GPR_ERROR, "Creating:   shared_ptr<EventEngine>::%d %s", id, ctx);
    living_engines_[id] = grpc_core::GetCurrentStackTrace().value();
    return id;
  }

  int id_;
  EE_* ee_;
  static unordered_map<EE_*, atomic_int> refcounts_;
  static atomic<int> counter_;
  static unordered_map<int, string> living_engines_;
};

}  // namespace std
#endif  // GRPC_EVENT_ENGINE_INTERNAL_DEBUG_SHARED_PTR_H
