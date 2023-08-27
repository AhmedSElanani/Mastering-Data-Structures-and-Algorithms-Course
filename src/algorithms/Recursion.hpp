#pragma once

#include <cstdint>
#include <limits>

/// @brief namespace for algorithms implemented
namespace algorithms {

/// @brief class holding recursive algorithms
class Recursion {
public:
  /// @brief method returns the sum of the first N natural numbers
  /// @param num input N value
  /// @return the sum of the first N natural numbers if input is 0 or more,
  ///         uint64_t max for negative input
  static constexpr auto sumNaturalNums(int32_t num) -> uint64_t {
    if (num < 0) {
      return std::numeric_limits<uint64_t>::max();
    }

    if (num == 0 || num == 1) {
      return static_cast<uint64_t>(num);
    }

    return static_cast<uint64_t>(num) + sumNaturalNums(num - 1);
  }
};
}  // namespace algorithms
