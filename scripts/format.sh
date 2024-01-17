#!/bin/bash

# Run clang-format
# according to the rules specified at: .cmake-format.yaml
find include test -type f \( -regex ".*\.[ch]?.pp" -o -name "*.h" \) -exec clang-format -i {} \;

# Run cmake-format
# according to the rules specified at: .clang-format
find . -name CMakeLists.txt -exec cmake-format -i {} \;
