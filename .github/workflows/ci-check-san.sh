#! /bin/bash

BUILD=$1
LANG=""
if [[ $# -gt 1 ]]; then
    LANG=$2
fi
if [[ -n $($EZTEST_CC --version | grep 'gcc' | grep -oE '[^ ]+$' | grep -E '7\.[0-9]+\.[0-9]+') ]]; then
    # GCC7 need to skip leak sanitizer
    # https://github.com/llvm/llvm-project/issues/55785
    echo 'Running GCC7 Version';
    ./$(dirname $0)/ci-build-target.sh $BUILD check-all${LANG}-usan check-all${LANG}-tsan check-all${LANG}-asan;
elif [[ -n $($EZTEST_CC --version | grep 'gcc' | grep -oE '[^ ]+$' | grep -E '8\.[0-9]+\.[0-9]+') ]]; then
    # GCC7 need to skip leak sanitizer / thread sanitizer
    # https://github.com/llvm/llvm-project/issues/55785
    echo 'Running GCC8 Version';
    ./$(dirname $0)/ci-build-target.sh $BUILD check-all${LANG}-usan check-all${LANG}-asan;
elif [[ -n $($EZTEST_CC --version | grep 'clang' | grep -oE '[^ ]+$' | grep -E '11\.[0-9]+\.[0-9]+') ]]; then
    # Clang11 need to skip
    # https://github.com/llvm/llvm-project/issues/55785
    echo 'Skipping sanitizers clang 11';
else
    echo 'Running General Version';
    ./$(dirname $0)/ci-build-target.sh $BUILD check-all${LANG}-san;
fi;
