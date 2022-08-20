#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

"$SCRIPT_DIR/build.sh" -DTESTS=ON && \
"$SCRIPT_DIR/build/unit_test"