#!/bin/bash
set -e

# Collect all files passed by lint-staged
FILES="$@"

# Track linted directories to avoid duplicates
LINTED_DIRS=""

# Run tflint on each unique directory containing terraform files
for FILE in $FILES; do
  if [ -f "$FILE" ]; then
    DIR=$(dirname "$FILE")
    
    # Skip if this directory has already been linted
    if ! echo "$LINTED_DIRS" | grep -q "^$DIR$"; then
      echo "Linting $DIR"
      tflint --chdir "$DIR" --filter "$(basename "$FILE")"
      LINTED_DIRS="$LINTED_DIRS
$DIR"
    fi
  fi
done
