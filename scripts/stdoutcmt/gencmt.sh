#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

CLEAN_FILE="clean.sh"
BUILD_FILE="build.sh"
RUN_FILE="run.sh"

build_and_run () {
    # if [ -f "$1/$CLEAN_FILE" ]; then
    #     "$1/$CLEAN_FILE"
    # fi

    "$1/$BUILD_FILE"
    "$1/$RUN_FILE"

    # if [ -f "$1/$CLEAN_FILE" ]; then
    #     "$1/$CLEAN_FILE"
    # fi
}

recursive_walk () {
    shopt -s nullglob dotglob

    for pathname in "$1"/*; do
        if [ -d "$pathname" ]; then
            recursive_walk "$pathname"
        elif [ "$(basename "$pathname")" == "$BUILD_FILE" ] && [ -f "$(dirname "$pathname")/$RUN_FILE" ]; then
            build_and_run "$(dirname "$pathname")"
        fi
    done
}

if [ -z "$1" ]; then
    echo "No source code directory specified."
    exit 1
fi

"$SCRIPT_DIR/$BUILD_FILE" -DTESTS=OFF && \
TMP_SRC_DIR=$("$SCRIPT_DIR/build/stdoutcmt" --copy "$1") && \
PROGRAM_OUTPUT=$(recursive_walk "$TMP_SRC_DIR") && \
"$SCRIPT_DIR/build/stdoutcmt" --gencmt "$1" "$TMP_SRC_DIR" "$PROGRAM_OUTPUT"

rm -rf "$TMP_SRC_DIR"
