#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

UNIT_TEST_FILE="unit_test";

$SCRIPT_DIR/build.sh && $SCRIPT_DIR/build/$UNIT_TEST_FILE
