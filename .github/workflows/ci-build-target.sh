#! /bin/bash

BUILD=$1
shift
TARGETS="$@"
RUN_TARGETS=""
SKIP_TARGETS=""

for TARGET in $TARGETS; do
    if [[ -n $(cmake --build ${BUILD} --target help | grep "${TARGET}") ]]; then
        RUN_TARGETS="${RUN_TARGETS} ${TARGET}"
    else
        SKIP_TARGETS="${SKIP_TARGETS} ${TARGET}"
    fi
done
if [[ -n "${RUN_TARGETS}" ]]; then
    cmake --build ${BUILD} --target ${RUN_TARGETS} --verbose
fi

if [[ -n "${SKIP_TARGETS}" ]]; then
    echo "Target(s): ${SKIP_TARGETS} not found in ${BUILD}"
    echo "------------------------------"
    cmake --build ${BUILD} --target help
    echo "------------------------------"
fi
