#pragma once

#include <array>
#include <format>

#include "data-structures/matrix-types/MatrixCommon.hpp"
#include "data-structures/matrix-types/NormalMatrix.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief namespace for matrices types
namespace matrix_types {

/// @brief definition of class representing diagonal Matrix
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix, default is std::size_t
/// @note diagonal matrix is by definition is a square matrix, hence it needs
///       only one parameter to define its size
template <common::NaturalNumber decltype(auto) N, typename T = std::size_t>
class DiagonalMatrix {
public:
  /// @brief constructor accepting braced init list representing the diagonal
  ///        elements of the matrix
  /// @tparam ...Elems parameter pack for the braced init lists passed
  /// @param ...elems elements of the diagonal to the matrix
  template <std::convertible_to<T>... Elems>
  constexpr explicit DiagonalMatrix(Elems&&... elems)
      : m_elements{std::forward<Elems>(elems)...} {}

  /// @brief a constexpr method to return the [n*m] dimensions of the matrix
  /// @return a MatrixDimension object representing [n*m] dimensions
  static constexpr auto dimensions() noexcept {
    return matrix_common::MatrixDimensions<N, N>{};
  }

  /// @brief method to return row at given index
  /// @param index at which row is requested
  /// @return the row at given index
  constexpr auto row(std::size_t index) const {
    if (index > N - 1U) {
      throw std::out_of_range(
          std::format("Rows must be within the range: 0 - {}", N - 1));
    }

    std::array<T, N> row{};
    row[index] = m_elements[index];

    return row;
  }

  /// @brief method to return the column at the given index
  /// @param index at which column should be returned
  /// @return the column at the given index
  constexpr auto column(std::size_t index) const {
    // by defintion of diagonal matrix, rows and columns are the same
    return row(index);
  }

  /// @brief multiplication operator that multiplies diagonal Matrix with
  ///        another and returns a result in NormalMatrix type
  /// @param otherMatrix
  /// @return the product of both matrices represented by NormalMatrix
  auto operator*(const auto& otherMatrix) const {
    // assert both types are the same
    using OtherMatrixType = std::remove_const<
        typename std::remove_reference<decltype(otherMatrix)>::type>::type;

    static_assert(
        std::is_same_v<typename OtherMatrixType::value_type, value_type>,
        "Element types are not the same");

    // assert dimensons are compatible
    static_assert(N == otherMatrix.dimensions().rows);

    constexpr auto noOfOtherMatrixColumns{otherMatrix.dimensions().columns};
    std::array<std::array<value_type, noOfOtherMatrixColumns>, N>
        resultElements;  // or use OtherMatrixType::value_type, since
                         // assertion should've passed above

    std::for_each(
        resultElements.begin(), resultElements.end(),
        [resultBegin = resultElements.begin(), &elements = m_elements,
         &otherMatrix](auto& resultRow) {
          const auto rowIndex{
              static_cast<std::size_t>(std::distance(resultBegin, &resultRow))};
          auto otherMatrixRow{otherMatrix.row(rowIndex)};

          auto elemIndex{0U};
          std::generate(  // an optimized way of diagonal matrix multiplication
              otherMatrixRow.begin(), otherMatrixRow.end(),
              [&otherMatrixRow, &rowIndex,
               &diagonalElement = elements[rowIndex], &elemIndex]() {
                return otherMatrixRow[elemIndex++] * diagonalElement;
              });

          resultRow = otherMatrixRow;  // after multiplying by diagonal element
        });

    return NormalMatrix<N, noOfOtherMatrixColumns>{resultElements};
  }

  /// @brief method to display elements of the matrix
  /// @return elements surrounded by matrix symbol
  constexpr auto display() const noexcept -> std::string {
    const auto stringifyRow{[&diagonalElements = m_elements](const auto& row) {
      constexpr auto rowLength{N};

      std::string result;
      for (std::size_t i{0U}; i < rowLength; ++i) {
        result += std::to_string(row[i]) + (i == rowLength - 1U ? "" : " ");
      }

      return std::string{std::format("|{}|", result)};
    }};

    constexpr auto numberOfRows{N};
    std::string result;
    for (std::size_t i{0U}; i < numberOfRows; ++i) {
      result += stringifyRow(row(i)) + (i == numberOfRows - 1U ? "" : "\n");
    }

    return result;
  }

  /// @brief type alias for T, used for assertions
  using value_type = T;

private:
  /// @brief diagonal elements of the matrix
  const std::array<T, N> m_elements;
};

/// @brief derive in a non-intrusive way of the MatrixAdt type
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix
template <common::NaturalNumber decltype(auto) N, typename T>
class IsMatrixAdt<DiagonalMatrix<N, T>> : public std::true_type {};

}  // namespace matrix_types
}  // namespace data_structures