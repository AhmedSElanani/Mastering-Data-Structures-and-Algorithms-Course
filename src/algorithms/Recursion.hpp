#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <limits>
#include <stack>
#include <type_traits>
#include <vector>

/// @brief namespace for algorithms implemented
namespace algorithms {

/// @brief concept for natural numbers
template <typename T>
concept NaturalNumber = std::is_unsigned_v<T>;

/// @brief namespace for needed constants to be defined
namespace {
constexpr auto kNumberOfTowersOfHanoi{3U};
}

/// @brief class holding recursive algorithms
class Recursion {
public:
  /// @brief method returns the sum of the first N natural numbers
  /// @param num input N value
  /// @return the sum of the first N natural numbers if input is 0 or more
  static consteval auto sumNaturalNums(NaturalNumber auto num) -> std::size_t {
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
  static constexpr auto exp(NaturalNumber auto arg, NaturalNumber auto n)
      -> double {
    if (arg == 0U || n == 0U) {
      return 1.0;
    }

    return (static_cast<double>(power(arg, n)) /
            static_cast<double>(factorial(n))) +
           exp(arg, n - 1U);
  }

  /// @brief another method that calculates e^x with resolution n-terms using
  ///        Taylor's Seires utilizing Horner's Rule this time to drop the
  ///        needed multiplications from O(N^2) to just O(N)
  /// @param x the power to which the natural number e is raised
  /// @param n the number of n-terms which also represents the resolution of
  ///          calculation
  /// @return e^x calculated at certain point with resolution n-terms using
  ///         Taylor's Series and Horner's Rule for optimization
  ///
  /// @note   Horner's Rule: e^x = 1 + x/1(1 + x/2(1 + x/3(...)))
  static auto expHornersRule(NaturalNumber auto arg, NaturalNumber auto n)
      -> double {
    if (arg == 0U || n == 0U) {
      return 1.0;
    }

    const std::function<double(std::size_t)> calculateTerms{
        [&calculateTerms, arg = arg, nTerms = n](auto termNo) {
          if (termNo > nTerms) {
            // it shouldn't calculate higher terms
            return 0.0;
          }

          const auto nextTerm{termNo == nTerms ? 1.0
                                               : calculateTerms(termNo + 1)};

          return 1.0 +
                 ((static_cast<double>(arg) / static_cast<double>(termNo)) *
                  nextTerm);
        }};

    return calculateTerms(1U);
  }

  /// @brief method that calculates Fibonacci series using lookup table, which
  ///        reduces its time complexity from O(2^N) to just O(N)
  /// @param num the input argument n
  /// @return Fibonacci series based on the input n
  static constexpr auto fibonacci(NaturalNumber auto num) -> std::size_t {
    // because zero-indexed
    if (m_fibValues.size() <= num) {
      const auto fib_2{fibonacci(num - 2U)};
      const auto fib_1{fibonacci(num - 1U)};

      m_fibValues.resize(num + 1U);
      m_fibValues[num] = fib_1 + fib_2;
    }

    return m_fibValues[num];
  }

  /// @brief a method that calculates combination formula
  /// @param nTotal the total number of elements available
  /// @param rSelected the number of selected elements no matter the order
  /// @return result of combination formula using Pascal's triangle
  static constexpr auto nCr(NaturalNumber auto nTotal,
                            NaturalNumber auto rSelected) -> std::size_t {
    if (nTotal < rSelected) {
      return std::numeric_limits<std::size_t>::max();
    }

    if (nTotal == rSelected || rSelected == 0U) {
      return 1U;
    }

    // Pascal's triangle for calculating Combination formula
    return nCr(nTotal - 1U, rSelected - 1U) + nCr(nTotal - 1U, rSelected);
  }

  /// @brief type definition for towers of Hanoi
  using towersOfHanoi =
      std::array<std::stack<std::size_t>, kNumberOfTowersOfHanoi>;

  /// @brief method that solves the tower of Hanoi problem using recursion
  /// @param towers the src, aux,and dest towers
  static auto solveTowersOfHanoi(towersOfHanoi towers) -> towersOfHanoi {
    // helper lambda to solve this recursively
    const std::function<void(std::size_t, std::stack<std::size_t> &,
                             std::stack<std::size_t> &,
                             std::stack<std::size_t> &)>
        toh{[&toh](std::size_t srcTowerHeight, auto &srcTower, auto &auxTower,
                   auto &dstTower) {
          if (srcTowerHeight == 0U) {
            return;
          }

          constexpr auto kMoveTopDiscFromTo{[](auto &src, auto &dst) {
            const auto topDisc{src.top()};
            src.pop();
            dst.push(topDisc);
          }};

          if (srcTowerHeight == 1U) {
            return kMoveTopDiscFromTo(srcTower, dstTower);
          }

          // notice the swap between src, aux, and dst towers
          toh(srcTowerHeight - 1U, srcTower, dstTower, auxTower);
          kMoveTopDiscFromTo(srcTower, dstTower);
          toh(srcTowerHeight - 1U, auxTower, srcTower, dstTower);
        }};

    // solution starts from here
    toh(towers[0].size(), towers[0], towers[1], towers[2]);
    return towers;
  }

private:
  static inline std::vector<std::size_t> m_fibValues{0U, 1U};
};

}  // namespace algorithms
