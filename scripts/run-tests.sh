#!/bin/bash

# Function to run an executable
run_executable() {
    echo "Running: $1"
    ./"$1"
}

# Directory to start the search
start_directory="build/test"

# Recursive function to search and run executables
search_and_run_executables() {
    local current_dir="$1"
    for file in "$current_dir"/*; do
        if [ -f "$file" ] && [ -x "$file" ]; then
            run_executable "$file"
        elif [ -d "$file" ]; then
            search_and_run_executables "$file"
        fi
    done
}

# Start the search from the specified directory
search_and_run_executables "$start_directory"
