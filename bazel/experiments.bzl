# Copyright 2022 gRPC authors.
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

# Automatically generated by tools/codegen/core/gen_experiments.py

"""Dictionary of tags to experiments so we know when to test different experiments."""

EXPERIMENTS = {
    "dbg": {
    },
    "off": {
        "core_end2end_test": [
            "promise_based_client_call",
        ],
        "endpoint_test": [
            "tcp_frame_size_tuning",
            "tcp_rcv_lowat",
        ],
        "event_engine_client_test": [
            "event_engine_client",
        ],
        "flow_control_test": [
            "peer_state_based_framing",
            "tcp_frame_size_tuning",
            "tcp_rcv_lowat",
        ],
        "lame_client_test": [
            "promise_based_client_call",
        ],
        "resource_quota_test": [
            "free_large_allocator",
            "memory_pressure_controller",
            "unconstrained_max_quota_buffer_size",
        ],
    },
    "on": {
        "core_end2end_tests": [
            "new_hpack_huffman_decoder",
        ],
        "flow_control_test": [
            "flow_control_fixes",
        ],
        "hpack_test": [
            "new_hpack_huffman_decoder",
        ],
    },
    "opt": {
    },
}
