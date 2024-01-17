#!/bin/bash

# This script runs clang-tidy on .cpp, .hpp, and .h files,
# in the include and tests directories according to the rules
# specified at: .clang-tidy
find include -type f \( -regex ".*\.[ch]?.pp" -o -name "*.h" \) -exec clang-tidy -extra-arg=-Wno-unknown-warning-option --fix-errors -p build/compile_commands.json {} \;
