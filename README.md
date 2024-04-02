# Mastering-Data-Structures-and-Algorithms-Course

## Description

This project includes my solution for all classes I've done so far in this DSA course: <https://www.udemy.com/course/datastructurescncpp/>

The code is written in C++20, I am using CMake for configuration, and GTest for testing my solutions

In addition, I am experimenting with automation to make things easier and more robust

## Build

* ### For a Clean build

  ``` $ scripts/build.sh clean ```

## Testing

* ### To run all tests (Including sanitized ones)

  ``` $ scripts/run-tests.sh ```

* ### If you faced a problem when running thread sanitized issue

  For me, it had to do with ASLR and having a higher entropy. For more information check this link:

  <https://stackoverflow.com/questions/77850769/fatal-threadsanitizer-unexpected-memory-mapping-when-running-on-linux-kernels>

  And the limit that fixed it on my machine, was this:

  ``` $ sudo sysctl vm.mmap_rnd_bits=28 ```

## Linting and Formatting

* ### Clang Tidy

  ``` $ scripts/run-clang-tidy.sh ```

* ### Formatting

  ```bash
  # Currently runs clang-format and cmake-format
  $ scripts/format.sh
  ```

* ### CppCheck

  ``` $ scripts/run-cppcheck.sh ```
