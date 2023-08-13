cmake_minimum_required(VERSION 3.22)

# set target name
set(TARGET_NAME "ds-algo")

# set executable source files
set(DS_ALGO_SRCS
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# set include directory
set(DS_ALGO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

# add executable for the project
add_executable(${TARGET_NAME}
    ${DS_ALGO_SRCS}
)

# add target include directory
target_include_directories(${TARGET_NAME} PRIVATE
    ${DS_ALGO_INCLUDE_DIR}
)