#!/bin/bash

BUILD=$1
TARGET=$2
MIN_VER=0
if [[ $# -gt 2 ]]; then
    MIN_VER=$3
fi

if [[ "$(printf '%s\n' "${MIN_VER}" "$(${EZTEST_TIDY} --version | tr -s " " "\012"))" | sort -V | head -n1)" != "${MIN_VER}" ]]; then
    echo "clang-tidy version insufficient"
else
    ./$(dirname $0)/ci-build-target.sh ${BUILD} ${TARGET}
fi
