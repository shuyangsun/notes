#!/bin/bash
set -e

# Collect all files passed by lint-staged
FILES="$@"

# Find unique directories
# We use a loop to handle paths correctly
DIRS=$(for file in $FILES; do dirname "$file"; done | sort -u)

for DIR in $DIRS; do
  # Check if directory contains .tf files
  if ls "$DIR"/*.tf 1> /dev/null 2>&1; then
    # Only init if .terraform doesn't exist
    if [ ! -d "$DIR/.terraform" ]; then
      echo "Initializing $DIR"
      terraform -chdir="$DIR" init -backend=false -input=false
    fi

    echo "Linting $DIR"
    tflint --chdir="$DIR"
  fi
done
