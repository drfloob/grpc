# Copyright 2018 gRPC authors.
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
# distutils: language=c++

from libc cimport string
from cython.operator cimport dereference

from cpython cimport Py_INCREF, Py_DECREF

import atexit
import errno
import sys

gevent_hub = None
g_gevent_pool = None
g_gevent_threadpool = None
g_gevent_activated = False


cdef queue[void*] g_greenlets_to_run
cdef condition_variable g_greenlets_cv
cdef mutex g_greenlets_mu
cdef bint g_shutdown_greenlets_to_run_queue = False


cdef _submit_to_greenlet_queue(object cb, tuple args):
  cdef tuple to_call = (cb,) + args
  cdef unique_lock[mutex]* lk
  Py_INCREF(to_call)
  with nogil:
    lk = new unique_lock[mutex](g_greenlets_mu)
    g_greenlets_to_run.push(<void*>(to_call))
    del lk
    g_greenlets_cv.notify_all()


cdef object await_next_greenlet():
  cdef unique_lock[mutex]* lk
  with nogil:
    # Cython doesn't allow us to do proper stack allocations, so we can't take
    # advantage of RAII.
    lk = new unique_lock[mutex](g_greenlets_mu)
    while not g_shutdown_greenlets_to_run_queue:
      if not g_greenlets_to_run.empty():
        break
      g_greenlets_cv.wait(dereference(lk))
  cdef object to_call = <object>g_greenlets_to_run.front()
  Py_DECREF(to_call)
  g_greenlets_to_run.pop()
  del lk
  return to_call

def spawn_greenlets():
  while True:
    to_call = g_gevent_threadpool.apply(await_next_greenlet, ())
    fn = to_call[0]
    args = to_call[1:]
    fn(*args)

def shutdown_await_next_greenlet():
  global g_shutdown_greenlets_to_run_queue
  cdef unique_lock[mutex]* lk
  with nogil:
    lk = new unique_lock[mutex](g_greenlets_mu)
    g_shutdown_greenlets_to_run_queue = True
  del lk
  g_greenlets_cv.notify_all()

def init_grpc_gevent():
  # Lazily import gevent
  global gevent_hub
  global g_gevent_threadpool
  global g_gevent_activated
  global g_interrupt_check_period_ms
  global g_gevent_pool

  import gevent
  import gevent.pool

  gevent_hub = gevent.hub
  g_gevent_threadpool = gevent_hub.get_hub().threadpool

  g_gevent_activated = True
  g_interrupt_check_period_ms = 2000

  # TODO: Move this to test runner.
  g_gevent_threadpool.maxsize = 1024
  g_gevent_threadpool.size = 32

  g_gevent_pool = gevent.pool.Group()

  g_gevent_pool.spawn(spawn_greenlets)

  set_async_callback_func(_submit_to_greenlet_queue)

  # TODO: Document how this all works.
  atexit.register(shutdown_await_next_greenlet)
