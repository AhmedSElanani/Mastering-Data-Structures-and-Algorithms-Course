#pragma once

#include <concepts>
#include <cstdint>

/// @brief namespace for algorithms implemented
namespace algorithms {

/// @brief concept for natural numbers
template <typename T>
concept NaturalNumber = std::is_unsigned_v<T>;

/// @brief class holding recursive algorithms
class Recursion {
public:
  /// @brief method returns the sum of the first N natural numbers
  /// @param num input N value
  /// @return the sum of the first N natural numbers if input is 0 or more
  static constexpr auto sumNaturalNums(NaturalNumber auto num) -> std::size_t {
    return (num == 0U || num == 1U) ? num : num + sumNaturalNums(num - 1U);
  }
  }
};
}  // namespace algorithms
