#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <iterator>
#include <utility>

#include "data-structures/matrix-types/MatrixCommon.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief namespace for matrices types
namespace matrix_types {

/// @brief definition of class representing non-special case Matrix
/// @tparam ROWS number of rows of matrix
/// @tparam COLUMNS number of columns of matrix
/// @tparam T type of elements of matrix, default is std::size_t
template <common::NaturalNumber decltype(auto) ROWS,
          common::NaturalNumber decltype(auto) COLUMNS,
          typename T = std::size_t>
class NormalMatrix {
  /// @brief type alias for row type as it is currently used in several places
  /// @tparam Cs number of columns
  template <common::NaturalNumber decltype(auto) Cs = COLUMNS>
  using RowType = std::array<T, Cs>;

  /// @brief type alias for column type as it is currently used
  ///         in several places
  /// @tparam Rs number of rows
  template <common::NaturalNumber decltype(auto) Rs = ROWS>
  using ColumnType = std::array<T, Rs>;

  /// @brief type alias for matrix elements type as it is currently used
  ///        in several places
  /// @tparam Rs number of rows
  /// @tparam Cs number of columns
  template <common::NaturalNumber decltype(auto) Rs = ROWS,
            common::NaturalNumber decltype(auto) Cs = COLUMNS>
  using ElementsType = std::array<std::array<T, Cs>, Rs>;


public:
  /// @brief constructor that accepts multiple braced init lists
  /// @tparam ...Rows parameter pack for the braced init lists passed
  /// @param ...rows parameter pack passes to fill the elements of the matrix
  /// @note when passing a row shorter than expected, the remaining elements
  ///       are set to zero, while when  passing a row longer, extra elements
  ///       are ignored
  template <typename... Rows>
  constexpr explicit NormalMatrix(std::initializer_list<Rows>&&... rows)
      : m_elements{fillToMatrixRow(
            std::forward<std::initializer_list<Rows>>(rows))...} {}

  /// @brief overload to the constuctor that accepts 2D array to set the
  ///        elements  directly
  /// @param elements elements of the 2D array
  /// @note this constructor is especially useful for multiplication operator
  constexpr explicit NormalMatrix(ElementsType<> elements)
      : m_elements{std::move(elements)} {}

  /// @brief a constexpr method to return the [n*m] dimensions of the matrix
  /// @return a MatrixDimension object representing [n*m] dimensions
  static constexpr auto dimensions() noexcept {
    return matrix_common::MatrixDimensions<ROWS, COLUMNS>{};
  }

  /// @brief method to return the row in matrix at a given index
  /// @param index at which row should be returned
  /// @return the row at the given index
  constexpr auto row(std::size_t index) const { return m_elements[index]; }

  /// @brief method to return the column at the given index
  /// @param index order of the column in the matrix
  /// @return the column at the given index
  constexpr auto column(std::size_t index) const {
    if (index > COLUMNS - 1U) {
      throw std::out_of_range(
          std::format("Columns must be within the range: 0 - {}", COLUMNS - 1));
    }

    ColumnType<> column;
    std::transform(
        m_elements.cbegin(), m_elements.cend(), column.begin(),
        [columnIndex = index](const auto& row) { return row[columnIndex]; });

    return column;
  }

  /// @brief generic multiplication operator
  /// @param otherMatrix the second operand of multiplication
  /// @return NormalMatrix  containing the result of the multiplication
  auto operator*(const auto& otherMatrix) const {
    // assert both types are the same
    using OtherMatrixType = std::remove_const<
        typename std::remove_reference<decltype(otherMatrix)>::type>::type;

    static_assert(
        std::is_same_v<typename OtherMatrixType::value_type, value_type>,
        "Element types are not the same");

    // assert dimensons are compatible
    static_assert(COLUMNS == otherMatrix.dimensions().rows);

    constexpr auto noOfOtherMatrixColumns{otherMatrix.dimensions().columns};
    ElementsType<ROWS, noOfOtherMatrixColumns> resultElements;
    matrix_common::multiplyRowsByColumns(*this, otherMatrix, resultElements);

    return NormalMatrix<ROWS, noOfOtherMatrixColumns>{resultElements};
  }

  /// @brief method to check whether matrix type is symmetric or not
  /// @return true if matrix is symmetric, false otherwise
  constexpr auto isSymmetric() const noexcept {
    if constexpr (ROWS != COLUMNS) {
      return false;
    } else {  // it gives compilation errors on different sizes
              // without this else
      for (auto i{0U}; i < ROWS;
           ++i) {  // or i < COLUMNS, since it is a square matrix
        if (row(i) != column(i)) {
          return false;
        }
      }
    }

    return true;
  }

  /// @brief method to display elements of the matrix
  /// @return elements surrounded by matrix symbol
  constexpr auto display() const noexcept -> std::string {
    const auto stringifyMatrix{[&matrixElements = m_elements]() {
      const auto stringifyRow{[](auto&& row) {
        constexpr auto rowLength{COLUMNS};
        std::string result;
        for (std::size_t i{0U}; i < rowLength; ++i) {
          result += std::to_string(row[i]) + (i == rowLength - 1U ? "" : " ");
        }

        return std::string{std::format("|{}|", result)};
      }};

      constexpr auto numberOfRows{ROWS};
      std::string result;
      for (std::size_t i{0U}; i < numberOfRows; ++i) {
        result += stringifyRow(matrixElements[i]) +
                  (i == numberOfRows - 1U ? "" : "\n");
      }

      return result;
    }};

    return stringifyMatrix();
  }

  /// @brief type alias for T, used for assertions
  using value_type = T;

private:
  /// @brief elements of the matrix
  const ElementsType<> m_elements;

  /// @brief helper method to take braced init list passed and return a matrix
  ///        row filled with those passed elements
  /// @tparam Rows braced init list of elements to fill the matrix row
  /// @param elems elements to fill the matrix row
  /// @return filled matrix row
  template <typename Rows>
  constexpr auto fillToMatrixRow(Rows&& elems) const noexcept {
    RowType<> matrixRow{};

    const auto numberOfElementsPassed{
        static_cast<std::size_t>(std::distance(elems.begin(), elems.end()))};
    constexpr auto matrixRowLength{matrixRow.size()};

    const auto numberOfElementsToMove{numberOfElementsPassed <= matrixRowLength
                                          ? numberOfElementsPassed
                                          : matrixRowLength};
    std::move(elems.begin(), elems.begin() + numberOfElementsToMove,
              matrixRow.begin());
    return matrixRow;
  }
};

/// @brief derive in a non-intrusive way of the MatrixAdt type
/// @tparam ROWS number of rows of matrix
/// @tparam COLUMNS number of columns of matrix
/// @tparam T type of elements of matrix
template <common::NaturalNumber decltype(auto) ROWS,
          common::NaturalNumber decltype(auto) COLUMNS, typename T>
class IsMatrixAdt<NormalMatrix<COLUMNS, ROWS, T>> : public std::true_type {};
}  // namespace matrix_types
}  // namespace data_structures