#!/bin/bash

# Specify the directories to analyze
DIRECTORIES=(
    'include'
    'test'
)

# Run Cppcheck on each directory's source files
# TODO: parse build configuration for --std=c++20 instead of hardcoded or any similar approach.
for DIR in "${DIRECTORIES[@]}"; do
    cppcheck --enable=all --suppressions-list='cppcheck-suppress-list.txt' --std=c++20 $(find "$DIR" -type f \( -regex ".*\.[ch]?.pp" -o -name "*.h" \))
done
