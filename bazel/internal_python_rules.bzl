# Copyright 2021 The gRPC Authors
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
"""Python-related rules intended only for use internal to the repo."""

load("//bazel:gevent_test.bzl", "py_grpc_gevent_test")
load("//bazel:python_rules.bzl", "py2and3_test")

def py_grpc_test(name, **kwargs):
    """Runs a test under all supported environments."""
    py2and3_test(name, **kwargs)
    py_grpc_gevent_test(name, **kwargs)

    suite_kwargs = {}
    if "visibility" in kwargs:
        suite_kwargs["visibility"] = kwargs["visibility"]

    native.test_suite(
        name = name,
        tests = [
            name + ".both_pythons",
            name + ".gevent",
        ],
        **suite_kwargs
    )
