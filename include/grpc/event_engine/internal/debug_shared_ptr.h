// Copyright 2023 The gRPC Authors
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
#include <unordered_map>

#include "test/core/util/stack_tracer.h"

namespace std {
template <>
class shared_ptr<grpc_event_engine::experimental::EventEngine>
    : public _Ptr_base<grpc_event_engine::experimental::EventEngine> {
 private:
  using _Ty = grpc_event_engine::experimental::EventEngine;
  using _Mybase = _Ptr_base<_Ty>;

 public:
  using typename _Mybase::element_type;

#if _HAS_CXX17
  using weak_type = weak_ptr<_Ty>;
#endif  // _HAS_CXX17

  shared_ptr() noexcept : id_(GetId("empty")) {}
  shared_ptr(nullptr_t) noexcept : id_(GetId("nullptr")) {}
  template <class _Ux,
            enable_if_t<conjunction_v<conditional_t<is_array_v<_Ty>,
                                                    _Can_array_delete<_Ux>,
                                                    _Can_scalar_delete<_Ux>>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  explicit shared_ptr(_Ux* _Px) : id_(GetId(_Px)) {
    // construct shared_ptr object that owns _Px
    if constexpr (is_array_v<_Ty>) {
      _Setpd(_Px, default_delete<_Ux[]>{});
    } else {
      _Temporary_owner<_Ux> _Owner(_Px);
      _Set_ptr_rep_and_enable_shared(_Owner._Ptr,
                                     new _Ref_count<_Ux>(_Owner._Ptr));
      _Owner._Ptr = nullptr;
    }
  }

  template <class _Ux, class _Dx,
            enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                      _Can_call_function_object<_Dx&, _Ux*&>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  shared_ptr(_Ux* _Px, _Dx _Dt) : id_(GetId(_Px)) {
    // construct with _Px, deleter
    _Setpd(_Px, _STD move(_Dt));
  }

  template <class _Ux, class _Dx, class _Alloc,
            enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                      _Can_call_function_object<_Dx&, _Ux*&>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  shared_ptr(_Ux* _Px, _Dx _Dt, _Alloc _Ax) : id_(GetId(_Px)) {
    // construct with _Px, deleter, allocator
    _Setpda(_Px, _STD move(_Dt), _Ax);
  }

  template <
      class _Dx,
      enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                _Can_call_function_object<_Dx&, nullptr_t&>>,
                  int> = 0>
  shared_ptr(nullptr_t, _Dx _Dt) : id_(GetId("nullptr")) {
    // construct with nullptr, deleter
    _Setpd(nullptr, _STD move(_Dt));
  }

  template <
      class _Dx, class _Alloc,
      enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                _Can_call_function_object<_Dx&, nullptr_t&>>,
                  int> = 0>
  shared_ptr(nullptr_t, _Dx _Dt, _Alloc _Ax) : id_(GetId("nullptr")) {
    // construct with nullptr, deleter, allocator
    _Setpda(nullptr, _STD move(_Dt), _Ax);
  }

  template <class _Ty2>
  shared_ptr(const shared_ptr<_Ty2>& _Right, element_type* _Px) noexcept
      : id_(GetId(_Right.get())) {
    // construct shared_ptr object that aliases _Right
    this->_Alias_construct_from(_Right, _Px);
  }

  template <class _Ty2>
  shared_ptr(shared_ptr<_Ty2>&& _Right, element_type* _Px) noexcept {
    // move construct shared_ptr object that aliases _Right
    GPR_ASSERT(false &&
               "DO NOT SUBMIT: move construct shared_ptr object that "
               "aliases _Right shared_ptr<EventEngine>");
    this->_Alias_move_construct_from(_STD move(_Right), _Px);
  }

  shared_ptr(const shared_ptr& _Other) noexcept
      : id_(GetId(_Other.get())) {  // construct shared_ptr object that
                                    // owns same resource as _Other
    this->_Copy_construct_from(_Other);
  }

  template <class _Ty2,
            enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
  shared_ptr(const shared_ptr<_Ty2>& _Other) noexcept
      : id_(GetId(_Other.get())) {
    // construct shared_ptr object that owns same resource as _Other
    this->_Copy_construct_from(_Other);
  }

  shared_ptr(shared_ptr&& _Right) noexcept {
    // construct shared_ptr object that takes resource from _Right
    this->_Move_construct_from(_STD move(_Right));
    id_ = _Right.id_;
    _Right.id_ = 0;
  }

  template <class _Ty2,
            enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
  shared_ptr(
      shared_ptr<_Ty2>&& _Right) noexcept {  // construct shared_ptr object that
                                             // takes resource from _Right
    GPR_ASSERT(false && "DO NOT SUBMIT: converted to shared_ptr<EventEngine>");
    this->_Move_construct_from(_STD move(_Right));
  }

  //   template <class _Ty2,
  //             enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
  //   explicit shared_ptr(
  //       const weak_ptr<_Ty2>&
  //           _Other) {  // construct shared_ptr object that owns resource
  //           *_Other
  //     gpr_log(GPR_DEBUG, "DO NOT SUBMIT: creating shared_ptr from
  //     weak_ptr<%s>",
  //             typeid(_Ty2).name());
  //     GPR_ASSERT(false && "DO NOT SUBMIT: weak_ptr");
  //     if (!this->_Construct_from_weak(_Other)) {
  //       _Throw_bad_weak_ptr();
  //     }
  //   }

  explicit shared_ptr(
      const weak_ptr<_Ty>&
          _Other) {  // construct shared_ptr object that owns resource *_Other
    if (!this->_Construct_from_weak(_Other)) {
      _Throw_bad_weak_ptr();
    }
  }

#if _HAS_AUTO_PTR_ETC
  template <class _Ty2, enable_if_t<is_convertible_v<_Ty2*, _Ty*>, int> = 0>
  shared_ptr(auto_ptr<_Ty2>&& _Other) {  // construct shared_ptr object that
                                         // owns *_Other.get()
    _Ty2* _Px = _Other.get();
    _Set_ptr_rep_and_enable_shared(_Px, new _Ref_count<_Ty2>(_Px));
    _Other.release();
  }
#endif  // _HAS_AUTO_PTR_ETC

  template <
      class _Ux, class _Dx,
      enable_if_t<
          conjunction_v<_SP_pointer_compatible<_Ux, _Ty>,
                        is_convertible<typename unique_ptr<_Ux, _Dx>::pointer,
                                       element_type*>>,
          int> = 0>
  shared_ptr(unique_ptr<_Ux, _Dx>&& _Other) : id_(GetId(_Other.get())) {
    using _Fancy_t = typename unique_ptr<_Ux, _Dx>::pointer;
    using _Raw_t = typename unique_ptr<_Ux, _Dx>::element_type*;
    using _Deleter_t =
        conditional_t<is_reference_v<_Dx>,
                      decltype(_STD ref(_Other.get_deleter())), _Dx>;

    const _Fancy_t _Fancy = _Other.get();

    if (_Fancy) {
      const _Raw_t _Raw = _Fancy;
      const auto _Rx = new _Ref_count_resource<_Fancy_t, _Deleter_t>(
          _Fancy, _STD forward<_Dx>(_Other.get_deleter()));
      _Set_ptr_rep_and_enable_shared(_Raw, _Rx);
      _Other.release();
    }
  }

  ~shared_ptr() noexcept {  // release resource
    gpr_log(GPR_ERROR, "Destroying: shared_ptr<EventEngine>::%d", id_);
    living_engines_.erase(id_);
    this->_Decref();
  }

  shared_ptr& operator=(const shared_ptr& _Right) noexcept {
    shared_ptr(_Right).swap(*this);
    return *this;
  }

  template <class _Ty2,
            enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
  shared_ptr& operator=(const shared_ptr<_Ty2>& _Right) noexcept {
    shared_ptr(_Right).swap(*this);
    return *this;
  }

  shared_ptr& operator=(
      shared_ptr&& _Right) noexcept {  // take resource from _Right
    shared_ptr(_STD move(_Right)).swap(*this);
    return *this;
  }

  template <class _Ty2,
            enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
  shared_ptr& operator=(
      shared_ptr<_Ty2>&& _Right) noexcept {  // take resource from _Right
    shared_ptr(_STD move(_Right)).swap(*this);
    return *this;
  }

#if _HAS_AUTO_PTR_ETC
  template <class _Ty2, enable_if_t<is_convertible_v<_Ty2*, _Ty*>, int> = 0>
  shared_ptr& operator=(auto_ptr<_Ty2>&& _Right) {
    shared_ptr(_STD move(_Right)).swap(*this);
    return *this;
  }
#endif  // _HAS_AUTO_PTR_ETC

  template <
      class _Ux, class _Dx,
      enable_if_t<
          conjunction_v<_SP_pointer_compatible<_Ux, _Ty>,
                        is_convertible<typename unique_ptr<_Ux, _Dx>::pointer,
                                       element_type*>>,
          int> = 0>
  shared_ptr& operator=(
      unique_ptr<_Ux, _Dx>&& _Right) {  // move from unique_ptr
    shared_ptr(_STD move(_Right)).swap(*this);
    return *this;
  }

  void swap(shared_ptr& _Other) noexcept {
    this->_Swap(_Other);
    _STD swap(id_, _Other.id_);
  }

  void
  reset() noexcept {  // release resource and convert to empty shared_ptr object
    shared_ptr().swap(*this);
  }

  template <class _Ux,
            enable_if_t<conjunction_v<conditional_t<is_array_v<_Ty>,
                                                    _Can_array_delete<_Ux>,
                                                    _Can_scalar_delete<_Ux>>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  void reset(_Ux* _Px) {  // release, take ownership of _Px
    shared_ptr(_Px).swap(*this);
  }

  template <class _Ux, class _Dx,
            enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                      _Can_call_function_object<_Dx&, _Ux*&>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  void reset(_Ux* _Px,
             _Dx _Dt) {  // release, take ownership of _Px, with deleter _Dt
    shared_ptr(_Px, _Dt).swap(*this);
  }

  template <class _Ux, class _Dx, class _Alloc,
            enable_if_t<conjunction_v<is_move_constructible<_Dx>,
                                      _Can_call_function_object<_Dx&, _Ux*&>,
                                      _SP_convertible<_Ux, _Ty>>,
                        int> = 0>
  void reset(_Ux* _Px, _Dx _Dt,
             _Alloc _Ax) {  // release, take ownership of _Px, with deleter _Dt,
                            // allocator _Ax
    shared_ptr(_Px, _Dt, _Ax).swap(*this);
  }

  using _Mybase::get;

  template <class _Ty2 = _Ty,
            enable_if_t<!disjunction_v<is_array<_Ty2>, is_void<_Ty2>>, int> = 0>
  _NODISCARD _Ty2& operator*() const noexcept {
    return *get();
  }

  template <class _Ty2 = _Ty, enable_if_t<!is_array_v<_Ty2>, int> = 0>
  _NODISCARD _Ty2* operator->() const noexcept {
    return get();
  }

  template <class _Ty2 = _Ty, class _Elem = element_type,
            enable_if_t<is_array_v<_Ty2>, int> = 0>
  _NODISCARD _Elem& operator[](ptrdiff_t _Idx) const noexcept
  /* strengthened */ {
    return get()[_Idx];
  }

#if _HAS_DEPRECATED_SHARED_PTR_UNIQUE
  _CXX17_DEPRECATE_SHARED_PTR_UNIQUE _NODISCARD bool unique() const noexcept {
    // return true if no other shared_ptr object owns this resource
    return this->use_count() == 1;
  }
#endif  // _HAS_DEPRECATED_SHARED_PTR_UNIQUE

  explicit operator bool() const noexcept { return get() != nullptr; }

  void PrintLivingEngines() {
    for (const std::pair<int, std::string>& n : living_engines_) {
      gpr_log(GPR_ERROR, "Living engine %d. stack: %s", n.first,
              n.second.c_str());
    }
  }

 private:
  template <class _UxptrOrNullptr, class _Dx>
  void _Setpd(const _UxptrOrNullptr _Px,
              _Dx _Dt) {  // take ownership of _Px, deleter _Dt
    _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
    _Set_ptr_rep_and_enable_shared(
        _Owner._Ptr, new _Ref_count_resource<_UxptrOrNullptr, _Dx>(
                         _Owner._Ptr, _STD move(_Dt)));
    _Owner._Call_deleter = false;
  }

  template <class _UxptrOrNullptr, class _Dx, class _Alloc>
  void _Setpda(
      const _UxptrOrNullptr _Px, _Dx _Dt,
      _Alloc _Ax) {  // take ownership of _Px, deleter _Dt, allocator _Ax
    using _Alref_alloc = _Rebind_alloc_t<
        _Alloc, _Ref_count_resource_alloc<_UxptrOrNullptr, _Dx, _Alloc>>;

    _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
    _Alref_alloc _Alref(_Ax);
    _Alloc_construct_ptr<_Alref_alloc> _Constructor(_Alref);
    _Constructor._Allocate();
    _Construct_in_place(*_Constructor._Ptr, _Owner._Ptr, _STD move(_Dt), _Ax);
    _Set_ptr_rep_and_enable_shared(_Owner._Ptr, _Unfancy(_Constructor._Ptr));
    _Constructor._Ptr = nullptr;
    _Owner._Call_deleter = false;
  }

#if _HAS_CXX20
  template <class _Ty0, class... _Types>
  friend enable_if_t<!is_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(
      _Types&&... _Args);

  template <class _Ty0, class _Alloc, class... _Types>
  friend enable_if_t<!is_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(
      const _Alloc& _Al_arg, _Types&&... _Args);

  template <class _Ty0>
  friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared();

  template <class _Ty0, class _Alloc>
  friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>>
  allocate_shared(const _Alloc& _Al_arg);

  template <class _Ty0>
  friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(
      const remove_extent_t<_Ty0>& _Val);

  template <class _Ty0, class _Alloc>
  friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>>
  allocate_shared(const _Alloc& _Al_arg, const remove_extent_t<_Ty0>& _Val);

  template <class _Ty0>
  friend enable_if_t<!is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>>
  make_shared_for_overwrite();

  template <class _Ty0, class _Alloc>
  friend enable_if_t<!is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>>
  allocate_shared_for_overwrite(const _Alloc& _Al_arg);

  template <class _Ty0, class... _ArgTypes>
  friend shared_ptr<_Ty0> _Make_shared_unbounded_array(
      size_t _Count, const _ArgTypes&... _Args);

  template <class _Ty0, class _Alloc, class... _ArgTypes>
  friend shared_ptr<_Ty0> _Allocate_shared_unbounded_array(
      const _Alloc& _Al, size_t _Count, const _ArgTypes&... _Args);
#else   // ^^^ _HAS_CXX20 / !_HAS_CXX20 vvv
  template <class _Ty0, class... _Types>
  friend shared_ptr<_Ty0> make_shared(_Types&&... _Args);

  template <class _Ty0, class _Alloc, class... _Types>
  friend shared_ptr<_Ty0> allocate_shared(const _Alloc& _Al_arg,
                                          _Types&&... _Args);
#endif  // !_HAS_CXX20

  template <class _Ux>
  void _Set_ptr_rep_and_enable_shared(
      _Ux* const _Px,
      _Ref_count_base* const _Rx) noexcept {  // take ownership of _Px
    this->_Ptr = _Px;
    this->_Rep = _Rx;
    if (conjunction_v<negation<is_array<_Ty>>, negation<is_volatile<_Ux>>,
                      _Can_enable_shared<_Ux>>) {
      if (_Px && _Px->_Wptr.expired()) {
        _Px->_Wptr = shared_ptr<remove_cv_t<_Ux>>(
            *this, const_cast<remove_cv_t<_Ux>*>(_Px));
      }
    }
  }

  void _Set_ptr_rep_and_enable_shared(
      nullptr_t,
      _Ref_count_base* const _Rx) noexcept {  // take ownership of nullptr
    this->_Ptr = nullptr;
    this->_Rep = _Rx;
  }

  static int GetId(void* _Px) {
    auto id = counter_.fetch_add(1);
    gpr_log(GPR_ERROR, "Creating:   shared_ptr<EventEngine>::%d %p", id, _Px);
    living_engines_[id] = grpc_core::testing::GetCurrentStackTrace();
    return id;
  }

  static int GetId(const char* ctx = "") {
    auto id = counter_.fetch_add(1);
    gpr_log(GPR_ERROR, "Creating:   shared_ptr<EventEngine>::%d %s", id, ctx);
    living_engines_[id] = grpc_core::testing::GetCurrentStackTrace();
    return id;
  }

  int id_;
  static atomic<int> counter_;
  static unordered_map<int, string> living_engines_;
};

}  // namespace std
#endif  // GRPC_EVENT_ENGINE_INTERNAL_DEBUG_SHARED_PTR_H
