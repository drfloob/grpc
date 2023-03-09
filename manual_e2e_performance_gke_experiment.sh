#!/usr/bin/env bash
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
set -ex

# -----------------------------------------------------
# A custom hack of the tools/internal_ci/linux/grpc_e2e_performance_gke_experiment.sh
# This is a C++-only script that generates and runs loadtest config files
#
# REQUIREMENTS
# * this file must be in the root of gRPC
# * `../test-infra` must exist, and already have run `make all-tools`
# * you must have already prebuilt images, and uploaded to: (change me)
PREBUILT_IMAGE_PREFIX="gcr.io/grpc-testing/e2etest/prebuilt/hork"
PREBUILT_IMAGE_TAG="latest"
# * specify the benchmark you want to run
BENCHMARK="cpp_generic_async_streaming_ping_pong_secure"
# * Define the env mapping you want to use in the execution
declare -A CLIENT_ENV=(["GRPC_EXPERIMENTS"]="event_engine_client,event_engine_listener")
declare -A SERVER_ENV=(["GRPC_EXPERIMENTS"]="event_engine_client,event_engine_listener")
# * current limitation of the test runner: this can only be 1
RUNS_PER_TEST=1
# -----------------------------------------------------


# # This is to ensure we can push and pull images from gcr.io. We do not
# # necessarily need it to run load tests, but will need it when we employ
# # pre-built images in the optimization.
# gcloud auth configure-docker

# # Connect to benchmarks-prod2 cluster.
# gcloud config set project grpc-testing
# gcloud container clusters get-credentials benchmarks-prod2 \
#     --zone us-central1-b --project grpc-testing

# Set up environment variables.
LOAD_TEST_PREFIX="${USER}"
BIGQUERY_TABLE_8CORE="e2e_benchmarks.${USER}_experimental_results"
# BIGQUERY_TABLE_32CORE="e2e_benchmarks.${USER}_experimental_results_32core"
# END differentiate experimental configuration from master configuration.
UNIQUE_IDENTIFIER="$(date +%Y%m%d%H%M%S)"
ROOT_DIRECTORY_OF_DOCKERFILES="../test-infra/containers/pre_built_workers/"
# Head of the workspace checked out by Kokoro.
GRPC_GITREF="$(git show --format="%H" --no-patch)"
# Prebuilt workers for core languages are always built from grpc/grpc.
GRPC_CORE_GITREF="$(git ls-remote -h https://github.com/grpc/grpc.git master | cut -f1)"
# Kokoro jobs run on dedicated pools.
DRIVER_POOL=drivers
WORKER_POOL_8CORE=workers-c2-8core
# c2-standard-30 is the closest machine spec to 32 core there is
# WORKER_POOL_32CORE=workers-c2-30core

# Prefix for log URLs in cnsviewer.
# LOG_URL_PREFIX="http://cnsviewer/placer/prod/home/kokoro-dedicated/build_artifacts/${KOKORO_BUILD_ARTIFACTS_SUBDIR}/github/grpc/"

getConfigName() {
    echo "${LOAD_TEST_PREFIX}.${BENCHMARK}.$1.${UNIQUE_IDENTIFIER}.yaml"
}

CLIENT_ENV_STR=""
if [ "$CLIENT_ENV" ]; then
    echo "TODO: client env"
fi

SERVER_ENV_STR=""
if [ "$SERVER_ENV" ]; then
    echo "TODO: server env"
fi

# Build test configurations.
buildConfigs() {
    local -r pool="$1"
    local -r table="$2"
    local -r config_name="$(getConfigName ${pool})"
    shift 2
    tools/run_tests/performance/loadtest_config.py "$@" \
        -t manual_e2e_performance_gke_experiment_template.yaml \
        -s driver_pool="${DRIVER_POOL}" -s driver_image= \
        -s client_pool="${pool}" -s server_pool="${pool}" \
        -s big_query_table="${table}" -s timeout_seconds=900 \
        -s prebuilt_image_prefix="${PREBUILT_IMAGE_PREFIX}" \
        -s prebuilt_image_tag="${PREBUILT_IMAGE_TAG}" \
        -s client_env="${CLIENT_ENV_STR}" \
        -s server_env="${SERVER_ENV_STR}" \
        -a ci_gitCommit="${GRPC_GITREF}" \
        -a ci_gitActualCommit="${KOKORO_GIT_COMMIT}" \
        --prefix="${LOAD_TEST_PREFIX}" -u "${UNIQUE_IDENTIFIER}" -u "${pool}" \
        -a pool="${pool}" -r "${BENCHMARK}" \
        --allow_client_language=c++ --allow_server_language=c++ \
        --runs_per_test=${RUNS_PER_TEST} \
        -o ${config_name}
}

buildConfigs "${WORKER_POOL_8CORE}" "${BIGQUERY_TABLE_8CORE}" -l c++
# buildConfigs "${WORKER_POOL_32CORE}" "${BIGQUERY_TABLE_32CORE}" -l c++

# Run tests.
time ../test-infra/bin/runner \
    -i "$(getConfigName ${WORKER_POOL_8CORE})" \
    -polling-interval 5s \
    -delete-successful-tests \
    -c "${WORKER_POOL_8CORE}:2" \
    -o "runner/sponge_log.xml"
#    -log-url-prefix "${LOG_URL_PREFIX}" \
#    -i "loadtest_with_prebuilt_workers_${WORKER_POOL_32CORE}.yaml" \
#    -c "${WORKER_POOL_32CORE}:2" \


LOGFILE=$(cat runner/${WORKER_POOL_8CORE}/${WORKER_POOL_8CORE}_sponge_log.xml | grep driver-0-main | sed 's/.*value="\([^"]*\)".*/\1/')
echo "Results are in the main driver log: ${LOGFILE}"
echo "Snippet:"
tail -25 "$LOGFILE" | head -12
