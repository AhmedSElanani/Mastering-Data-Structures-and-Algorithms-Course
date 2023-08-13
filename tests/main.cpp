#include "gtest/gtest.h"

/// @brief main entry point for tests
/// @param argc
/// @param argv
/// @return status from executing the test cases
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
