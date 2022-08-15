#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

rm -rf "$SCRIPT_DIR"/build
rm -rf "$SCRIPT_DIR"/cmake-build-*
