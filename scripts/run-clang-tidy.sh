#!/bin/bash

# remove unrecognized arguments to clang-tidy from compile_commands.json before execution
compile_command_path="build/compile_commands.json"
sed -i 's/-fconcepts-diagnostics-depth=3//g' $compile_command_path


# This script runs clang-tidy on .cpp, .hpp, and .h files,
# in the include and tests directories according to the rules
# specified at: .clang-tidy
find include -type f \( -regex ".*\.[ch]?.pp" -o -name "*.h" \) -exec clang-tidy -extra-arg=-Wno-unknown-warning-option --fix-errors -p $compile_command_path {} \;
