#!/bin/bash

SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd "$SCRIPT_DIR"/build
for FILE in *; do
    [[ "$FILE" =~ ^item_[0-9]+(_[0-9]+)*$ ]] && "./$FILE"
done
