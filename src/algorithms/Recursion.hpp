#pragma once

#include <cstddef>
#include <functional>
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

  /// @brief method that calculates e^x with resolution n-terms using Taylor's
  ///        Seires
  /// @param x the power to which the natural number e is raised
  /// @param n the number of n-terms which also represents the resolution of
  ///          calculation
  /// @return e^x calculated at certain point with resolution n-terms using
  ///         Taylor's Series
  /// @note from the expansion: e^x|N = 1 + x^1/2! + x^2/2! + ... + x^N/N!
  ///                                 = e^x|N-1 + x^N/N!
  ///
  ///                      and: X^N = X * X^N-1, N! = N * (N-1)!
  static constexpr auto exp(NaturalNumber auto x, NaturalNumber auto n)
      -> double {
    if (x == 0U || n == 0U) {
      return 1.0;
    }

    return (static_cast<double>(power(x, n)) /
            static_cast<double>(factorial(n))) +
           exp(x, n - 1U);
  }

  /// @brief another method that calculates e^x with resolution n-terms using
  ///        Taylor's Seires utilizing Horner's Rule this time to drop the
  ///        needed multiplications from O(N^2) to just O(N)
  /// @param x the power to which the natural number e is raised
  /// @param n the number of n-terms which also represents the resolution of
  ///          calculation
  /// @return e^x calculated at certain point with resolution n-terms using
  ///         Taylor's Series and Horner's Rule for optimization
  static constexpr auto exp_HornersRule(NaturalNumber auto x,
                                        NaturalNumber auto n) -> double {
    if (x == 0U || n == 0U) {
      return 1.0;
    }

    const std::function<double(std::size_t)> calculateTerms{
        [&calculateTerms, x = x, n = n](auto termNo) {
          if (termNo > n) {
            // it shouldn't calculate higher terms
            return 0.0;
          }

          const auto nextTerm{termNo == n ? 1.0 : calculateTerms(termNo + 1)};

          return 1.0 + ((static_cast<double>(x) / static_cast<double>(termNo)) *
                        nextTerm);
        }};

    return calculateTerms(1U);
  }
};
}  // namespace algorithms
