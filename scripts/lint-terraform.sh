#!/bin/bash
set -e

# Collect all files passed by lint-staged
FILES="$@"

# Run tflint directly on each file (no terraform init needed)
# tflint can lint individual files without initialization
for FILE in $FILES; do
  if [ -f "$FILE" ]; then
    echo "Linting $FILE"
    tflint "$FILE"
  fi
done
