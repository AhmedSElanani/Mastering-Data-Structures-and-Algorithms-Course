#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <format>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <ranges>

#include "common/Common.hpp"
#include "data-structures/matrix-types/MatrixConcept.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief namespace for matrices types
namespace matrix_types {

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
            std::forward<std::initializer_list<Rows>>(rows)...)} {}

  /// @brief method to display elements of the matrix
  /// @return elements surrounded by matrix symbol
  constexpr auto display() const noexcept -> std::string {
    const auto stringifyRow{
        [&triangleElements = m_elements](const auto rowIndex) {
          constexpr auto rowLength{N};
          const auto rowStartPosition{numberOfTriangleElements(rowIndex)};
          std::string result;
          for (std::size_t i{0U}; i < rowLength; ++i) {
            result +=
                // concat. the next triangle element until the diagonal,
                // after that concat. zero
                (i <= rowIndex
                     ? std::to_string(triangleElements[rowStartPosition + i])
                     : std::to_string(0U)) +
                // concat. space after each element except the last one
                (i == rowLength - 1U ? "" : " ");
          }

          return std::string{std::format("|{}|", result)};
        }};

    constexpr auto numberOfRows{N};
    std::string result;
    for (auto i{0U}; i < numberOfRows; ++i) {
      result += stringifyRow(i) + (i == numberOfRows - 1U ? "" : "\n");
    }

    return result;
  }

private:
  /// @brief helper constexpr method to return the total number of elements in
  ///        a lower triangle matrix of a given number of rows n
  /// @param n number of rows of a given matrix
  /// @return the total number of lower triangle elements in the matrix
  static constexpr auto numberOfTriangleElements(auto n) noexcept
      -> std::size_t {
    // this returns the sum of {0, 1, .. , n}
    std::ranges::iota_view elemsInEachRow{0U, n + 1U};
    return std::accumulate(elemsInEachRow.begin(), elemsInEachRow.end(), 0U);
  }

  /// @brief elements of the lower triangle in the matrix
  const std::array<T, numberOfTriangleElements(N)> m_elements{};

  /// @brief helper method to set the triangle elements of the matrix
  /// @tparam ...Rows
  /// @param ...triangleSides
  /// @return deserialized elements of the triangle
  template <typename... Rows>
  constexpr auto fillTriangleElements(auto&&... triangleSides) const noexcept {
    typename std::remove_const<
        typename std::remove_reference<decltype(m_elements)>::type>::type
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
}  // namespace matrix_types
}  // namespace data_structures