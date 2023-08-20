#!/bin/bash

# This script runs clang-tidy on .cpp, .hpp, and .h files,
# in the src and tests directories according to the rules
# specified at: .clang-tidy
find src test -type f \( -regex ".*\.[ch]?.pp" -o -name "*.h" \) -exec clang-tidy --fix-errors -p build/compile_commands.json {} \;
