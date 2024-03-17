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
set(DS_ALGO_TEST_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Recursion_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArrayAdt_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NormalMatrix_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DiagonalMatrix_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MatrixAdt_test.cpp)

# set link libraries
set(DS_ALGO_TEST_LINK_LIBRARIES gtest gmock)

# set include directories
set(DS_ALGO_TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# add tests executable for the project
add_executable(${TARGET_NAME} ${DS_ALGO_TEST_SRCS})
target_compile_options(${TARGET_NAME} PRIVATE ${ADDITIONAL_COMPILE_OPTIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# set additional compile flags for sanitized targets
set(SANITIZED_TARGETS_ADDITIONAL_COMPILE_OPTIONS -fno-omit-frame-pointer -g)

# TODO: use a function or something for setting the sanitized targets

# add another tests target with AddressSanitizer
set(TARGET_NAME_ADDRESS_SANITIZED ${TARGET_NAME}-address-sanitized)
add_executable(${TARGET_NAME_ADDRESS_SANITIZED} ${DS_ALGO_TEST_SRCS})
target_compile_options(
  ${TARGET_NAME_ADDRESS_SANITIZED}
  PRIVATE ${ADDITIONAL_COMPILE_OPTIONS} ${SANITIZED_TARGETS_ADDITIONAL_COMPILE_OPTIONS}
          -fsanitize=address)
target_link_options(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE -fsanitize=address)
set_target_properties(
  ${TARGET_NAME_ADDRESS_SANITIZED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              "${CMAKE_CURRENT_BINARY_DIR}/address-sanitized")
target_include_directories(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME_ADDRESS_SANITIZED} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# add another tests target with UndefinedBehaviorSanitizer
set(TARGET_NAME_UNDEFINED_SANITIZED ${TARGET_NAME}-undefined-sanitized)
add_executable(${TARGET_NAME_UNDEFINED_SANITIZED} ${DS_ALGO_TEST_SRCS})
target_compile_options(
  ${TARGET_NAME_UNDEFINED_SANITIZED}
  PRIVATE ${ADDITIONAL_COMPILE_OPTIONS} ${SANITIZED_TARGETS_ADDITIONAL_COMPILE_OPTIONS}
          -fsanitize=undefined)
target_link_options(${TARGET_NAME_UNDEFINED_SANITIZED} PRIVATE -fsanitize=undefined)
set_target_properties(
  ${TARGET_NAME_UNDEFINED_SANITIZED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                "${CMAKE_CURRENT_BINARY_DIR}/undefined-sanitized")
target_include_directories(${TARGET_NAME_UNDEFINED_SANITIZED} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME_UNDEFINED_SANITIZED} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# add another tests target with ThreadSanitizer
set(TARGET_NAME_THREAD_SANITIZED ${TARGET_NAME}-thread-sanitized)
add_executable(${TARGET_NAME_THREAD_SANITIZED} ${DS_ALGO_TEST_SRCS})
target_compile_options(
  ${TARGET_NAME_THREAD_SANITIZED}
  PRIVATE ${ADDITIONAL_COMPILE_OPTIONS} ${SANITIZED_TARGETS_ADDITIONAL_COMPILE_OPTIONS}
          -fsanitize=thread)
target_link_options(${TARGET_NAME_THREAD_SANITIZED} PRIVATE -fsanitize=thread)
set_target_properties(
  ${TARGET_NAME_THREAD_SANITIZED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_CURRENT_BINARY_DIR}/thread-sanitized")
target_include_directories(${TARGET_NAME_THREAD_SANITIZED} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME_THREAD_SANITIZED} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})

# add another tests target with LeakSanitizer
set(TARGET_NAME_LEAK_SANITIZED ${TARGET_NAME}-leak-sanitized)
add_executable(${TARGET_NAME_LEAK_SANITIZED} ${DS_ALGO_TEST_SRCS})
target_compile_options(
  ${TARGET_NAME_LEAK_SANITIZED}
  PRIVATE ${ADDITIONAL_COMPILE_OPTIONS} ${SANITIZED_TARGETS_ADDITIONAL_COMPILE_OPTIONS}
          -fsanitize=leak)
target_link_options(${TARGET_NAME_LEAK_SANITIZED} PRIVATE -fsanitize=leak)
set_target_properties(
  ${TARGET_NAME_LEAK_SANITIZED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                           "${CMAKE_CURRENT_BINARY_DIR}/leak-sanitized")
target_include_directories(${TARGET_NAME_LEAK_SANITIZED} PRIVATE ${DS_ALGO_TEST_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME_LEAK_SANITIZED} PRIVATE ${DS_ALGO_TEST_LINK_LIBRARIES})
