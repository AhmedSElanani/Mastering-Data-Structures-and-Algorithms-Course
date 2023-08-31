#pragma once

#include <cstddef>
#include <type_traits>

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

  /// @brief method returns the factorial of the natural number N
  /// @param num input N value
  /// @return the factorial of the natural number N
  static constexpr auto factorial(NaturalNumber auto num) -> std::size_t {
    return (num == 0U || num == 1U) ? 1U : num * factorial(num - 1U);
  }

  /// @brief method returns the number raised to a certain power
  /// @param num the number to be raised to a power
  /// @param pow a natural number to be raised to
  /// @return the number raised to the power
  template <typename T>
  static constexpr auto power(T num, NaturalNumber auto pow) -> T {
    if (pow == 0U) {
      return 1;
    }

    if (pow == 1U) {
      return num;
    }

    return (pow % 2U ? num * power(num * num, pow / 2U)
                     : power(num * num, pow / 2U));
  }
};
}  // namespace algorithms
