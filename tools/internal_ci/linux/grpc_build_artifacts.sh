#!/bin/bash
# Copyright 2017 gRPC authors.
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

echo "The grpc_build_artifacts -> grpc_build_packages -> grpc_distribtests build flow has been deprecated."
echo "To build the packages for a grpc release, use the grpc_build_all_packages job."
echo "(which relies on the per-language distribtests jobs to build and test the packages)."
