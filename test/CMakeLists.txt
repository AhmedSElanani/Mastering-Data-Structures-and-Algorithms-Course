cmake_minimum_required(VERSION 3.22)

# set target name
set(TARGET_NAME "ds-algo-tests")

include(FetchContent)
FetchContent_Declare(
  GTest
  QUIET
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)

# configure build of googletest
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
set(BUILD_GMOCK
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

# set executable source files
set(DS_ALGO_TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# set include directory
set(DS_ALGO_TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

# set link libraries
set(DS_ALGO_TEST_LINK_LIBRARIES gtest gmock)

# add tests executable for the project
add_executable(${TARGET_NAME} ${DS_ALGO_TEST_SRCS})

# add target include directory
target_include_directories(${TARGET_NAME} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})

# add target link libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# add another tests target with -fsanitize=address option
set(TARGET_NAME_ADDRESS_SANITIZED ${TARGET_NAME}-address-sanitized)
add_executable(${TARGET_NAME_ADDRESS_SANITIZED} ${DS_ALGO_TEST_SRCS})

target_compile_options(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)

target_link_options(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE -fsanitize=address)

set_target_properties(${TARGET_NAME_ADDRESS_SANITIZED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                                  "${CMAKE_CURRENT_BINARY_DIR}/address-sanitized")

target_include_directories(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})

target_link_libraries(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# TODO: similarly for other sanitizers
