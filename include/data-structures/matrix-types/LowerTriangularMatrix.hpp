#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <iterator>
#include <string>
#include <type_traits>

#include "common/Common.hpp"
#include "data-structures/matrix-types/MatrixCommon.hpp"
#include "data-structures/matrix-types/NormalMatrix.hpp"

/// @brief namespace for matrices types
namespace data_structures::matrix_types {

/// @brief definition of class representing lower triangular Matrix
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix, default is std::size_t
template <common::NaturalNumber auto N, typename T = std::size_t>
class LowerTriangularMatrix {
public:
  /// @brief to handle when passing empty list
  constexpr LowerTriangularMatrix() = default;

  /// @brief constructor that accepts multiple braced init lists
  /// @tparam ...Rows parameter pack for the braced init lists passed
  /// @param ...rows parameter pack passes to fill the elements of the matrix
  /// @note when passing a row shorter than the expected triangle side width,
  ///       the remaining elements till the diagonal element are set to zero,
  ///       while when passing a row longer, extra elements are ignored
  template <typename... Rows>
  constexpr explicit LowerTriangularMatrix(
      std::initializer_list<Rows>&&... rows)
      : m_elements{fillTriangleElements(
            std::forward<std::initializer_list<Rows>>(rows)...)} {
    static_assert(sizeof...(rows) <= N);
  }

  /// @brief a constexpr method to return the [n*m] dimensions of the matrix
  /// @return a MatrixDimension object representing [n*m] dimensions
  static constexpr auto dimensions() noexcept {
    return matrix_common::MatrixDimensions<N, N>{};
  }

  /// @brief method to return the row in matrix at a given index
  /// @param index at which row should be returned
  /// @return the row at the given index
  constexpr auto row(std::size_t index) const {
    const auto rowStartPosition{numberOfTriangleElements(index)};
    std::array<T, N> result{};
    for (auto i{0U}; i <= index; ++i) {
      result[i] = m_elements[rowStartPosition + i];
    }

    return result;
  }

  /// @brief method to return the column at the given index
  /// @param index at which column should be returned
  /// @return the column at the given index
  constexpr auto column(std::size_t index) const {
    auto elemIndex{numberOfTriangleElements(index)};
    std::array<T, N> result{};
    for (auto i{index}; i < N; ++i, elemIndex += i) {
      result[i] = m_elements[index + elemIndex];
    }

    return result;
  }

  /// @brief generic multiplication operator
  /// @param otherMatrix the second operand of multiplication
  /// @return NormalMatrix containing the result of the multiplication
  auto operator*(const auto& otherMatrix) const {
    // assert both types are the same
    using OtherMatrixType =
        std::remove_const_t<std::remove_reference_t<decltype(otherMatrix)>>;

    static_assert(
        std::is_same_v<typename OtherMatrixType::value_type, value_type>,
        "Element types are not the same");

    // assert dimensons are compatible
    static_assert(N == otherMatrix.dimensions().kRows);

    constexpr auto kNoOfOtherMatrixColumns{otherMatrix.dimensions().kColumns};
    std::array<std::array<value_type, kNoOfOtherMatrixColumns>, N>
        resultElements;  // or use OtherMatrixType::value_type, since
                         // assertion should've passed above

    matrix_common::multiplyRowsByColumns(*this, otherMatrix, resultElements);

    return NormalMatrix<N, kNoOfOtherMatrixColumns>{resultElements};
  }

  /// @brief method to check whether matrix type is symmetric or not
  /// @return false
  /// @note for lower triangular matrix, this is always false
  constexpr auto isSymmetric() const noexcept { return false; }

  /// @brief method to display elements of the matrix
  /// @return elements surrounded by matrix symbol
  [[nodiscard]] constexpr auto display() const noexcept -> std::string {
    const auto stringifyRow{[&triangleElements = m_elements](const auto& row) {
      constexpr auto kRowLength{N};
      std::string result;
      for (std::size_t i{0U}; i < kRowLength; ++i) {
        result += std::to_string(row[i]) +
                  // concat. space after each element except the last one
                  (i == kRowLength - 1U ? "" : " ");
      }

      return std::string{std::format("|{}|", result)};
    }};

    constexpr auto kNumberOfRows{N};
    std::string result;
    for (auto i{0U}; i < kNumberOfRows; ++i) {
      result += stringifyRow(row(i)) + (i == kNumberOfRows - 1U ? "" : "\n");
    }

    return result;
  }

  /// @brief type alias for T, used for assertions
  using value_type = T;

private:
  /// @brief helper constexpr method to return the total number of elements in
  ///        a lower triangle matrix of a given number of rows n
  /// @param n number of rows of a given matrix
  /// @return the total number of lower triangle elements in the matrix
  static constexpr auto numberOfTriangleElements(auto n) noexcept
      -> std::size_t {
    // this returns the sum of {1, 2, ... , n}
    return (n * (n + 1U)) / 2U;
  }

  /// @brief elements of the lower triangle in the matrix
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  const std::array<T, numberOfTriangleElements(N)> m_elements{};

  /// @brief helper method to set the triangle elements of the matrix
  /// @tparam ...Rows
  /// @param ...triangleSides
  /// @return deserialized elements of the triangle
  template <typename... Rows>
  constexpr auto fillTriangleElements(auto&&... triangleSides) const noexcept {
    std::remove_const_t<std::remove_reference_t<decltype(m_elements)>>
        triangleElements{};

    const auto setTriangleSideElements{
        [&elems = triangleElements](auto&& triangleSide,
                                    std::size_t startPosition,
                                    std::size_t sideLength) {
          const auto numberOfElementsPassed{static_cast<std::size_t>(
              std::distance(triangleSide.begin(), triangleSide.end()))};

          const auto numberOfElementsToMove{numberOfElementsPassed <= sideLength
                                                ? numberOfElementsPassed
                                                : sideLength};

          std::move(triangleSide.begin(),
                    triangleSide.begin() + numberOfElementsToMove,
                    elems.begin() + startPosition);
        }};

    std::size_t sideLength{0U};
    std::size_t startPosition{0U};
    for (const auto& triangleSide : {triangleSides...}) {
      startPosition += sideLength;
      setTriangleSideElements(triangleSide, startPosition, ++sideLength);
    }

    return triangleElements;
  }
};

/// @brief derive in a non-intrusive way of the MatrixAdt type
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix
template <common::NaturalNumber auto N, typename T>
class IsMatrixAdt<LowerTriangularMatrix<N, T>> : public std::true_type {};
}  // namespace data_structures::matrix_types
