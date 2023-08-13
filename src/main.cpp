#include <iostream>

/// @brief return codes for main function
namespace {
constexpr auto kSuccess = 0;
constexpr auto kGeneralError = -1;
}  // namespace

/// @brief main entry point
/// @param argc
/// @param argv
/// @return SUCCESS or GENERAL_ERROR depending on the execution status
auto main(int, char *[]) -> int {
  std::cout << "Hello Data Structures and Algorithms!!" << std::endl;

  return kSuccess;
}
