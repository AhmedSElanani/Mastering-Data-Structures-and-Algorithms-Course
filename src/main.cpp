#include <iostream>
/// @brief return codes for main function
namespace {
static constexpr auto SUCCESS = 0;
static constexpr auto GENERAL_ERROR = -1;
}  // namespace

/// @brief main entry point
/// @param argc
/// @param argv
/// @return SUCCESS or GENERAL_ERROR depending on the execution status
int main(int argc, char* argv[]) {
  std::cout << "Hello Data Structures and Algorithms!!" << std::endl;

  return SUCCESS;
}
