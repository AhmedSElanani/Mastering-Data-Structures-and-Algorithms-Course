#include <iostream>

/// @brief return codes for main function
namespace {
constexpr auto kSuccess = 0;
}  // namespace

/// @brief main entry point
/// @param
/// @param
/// @return the execution status
auto main(int /*unused*/, char* /*unused*/[]) -> int {
  std::cout << "Hello Data Structures and Algorithms!!" << '\n';

  return kSuccess;
}
