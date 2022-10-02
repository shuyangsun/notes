#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

mkdir -p "$SCRIPT_DIR"/build
cd "$SCRIPT_DIR"/build
cmake -DCMAKE_BUILD_TYPE=Release "$SCRIPT_DIR"
make
