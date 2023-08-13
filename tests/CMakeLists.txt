cmake_minimum_required(VERSION 3.22)

# set target name
set(TARGET_NAME "ds-algo-tests")

include(FetchContent)
FetchContent_Declare(GTest
    QUIET
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

# set executable source files
set(DS_ALGO_TEST_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# set include directory
set(DS_ALGO_TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

# add tests executable for the project
add_executable(${TARGET_NAME}
    ${DS_ALGO_TEST_SRCS}
)

# add target include directory
target_include_directories(${TARGET_NAME} PRIVATE
    ${DS_ALGO_TEST_INCLUDE_DIR}
)

# add target link libraries
target_link_libraries(${TARGET_NAME} PRIVATE
    gtest
    gmock
)