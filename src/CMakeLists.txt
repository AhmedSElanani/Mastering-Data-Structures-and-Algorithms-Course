cmake_minimum_required(VERSION 3.22)

# set target name
set(TARGET_NAME "ds-algo")

# set executable source files
set(DS_ALGO_SRCS ${CMAKE_SOURCE_DIR}/src/main.cpp)

# add executable for the project
add_executable(${TARGET_NAME} ${DS_ALGO_SRCS})

# add additional compile options for the target
target_compile_options(${TARGET_NAME} PRIVATE ${ADDITIONAL_COMPILE_OPTIONS})
