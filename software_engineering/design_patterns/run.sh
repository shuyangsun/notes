#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd "$SCRIPT_DIR"/build
for FILE in *; do
    [[ "$FILE" =~ ^p[0-9]+_[a-z_]+$ ]] && "./$FILE"
done
