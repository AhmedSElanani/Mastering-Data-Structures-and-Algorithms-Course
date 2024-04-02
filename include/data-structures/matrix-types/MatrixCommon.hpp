#pragma once

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <type_traits>
// NOLINTNEXTLINE(misc-include-cleaner)
#include <vector>

// NOLINTNEXTLINE(clang-diagnostic-error)
#include "common/Common.hpp"

/// @brief namespace for matrices types
namespace data_structures::matrix_types {

/// @brief namespace for common data between matrices types
namespace matrix_common {

/// @brief struct to represent the dimensions of the matrix
template <common::NaturalNumber auto ROWS, common::NaturalNumber auto COLUMNS>
struct MatrixDimensions {
  static constexpr auto kRows{ROWS};
  static constexpr auto kColumns{COLUMNS};
};

/// @brief helper function to multiply rows of first matrix by columns of second
///        matrix, i.e the definition of matrices multiplication
/// @param firstMatrix first operand of matrices multiplication
/// @param secondMatrix second operand of matrices multiplication
/// @param productResult an array of arrays the hold the result elements
// TODO(salah): make it accept matrix adt concept for first two parameters
static void multiplyRowsByColumns(const auto& firstMatrix,
                                  const auto& secondMatrix,
                                  auto& productResult) {
  std::for_each(
      productResult.begin(), productResult.end(),
      [resultBegin = productResult.begin(), &firstMatrix,
       &secondMatrix](auto& resultRow) {
        const auto rowIndex{
            static_cast<std::size_t>(std::distance(resultBegin, &resultRow))};
        const auto currentRow{firstMatrix.row(rowIndex)};

        // TODO(salah): use iterators instead
        auto colIndex{0U};
        std::generate(
            resultRow.begin(), resultRow.end(),
            [&currentRow, &secondMatrix, &colIndex] {
              auto column{secondMatrix.column(colIndex++)};

              // type alias for element type in in either of both matrices
              using value_type = std::remove_const<std::remove_reference_t<
                  decltype(firstMatrix)>>::type::value_type;  // or secondMatrix

              std::vector<value_type> elemsProduct(
                  currentRow.size()  // or column.size()
              );
              std::transform(currentRow.cbegin(), currentRow.cend(),
                             column.cbegin(), elemsProduct.begin(),
                             std::multiplies<value_type>());

              return std::accumulate(elemsProduct.cbegin(), elemsProduct.cend(),
                                     0U);
            });
      });
}

}  // namespace matrix_common

/// @brief a tag to be used to strict matrices types only
/// @note it can be used in an intrusive approach via inheritance (preferred
///       privately tho), or non-intrusively through specialization
class MatrixAdtTag {};

/// @brief this indirection to limit classes to MatrixAdt type
/// @tparam T the type in question
template <typename T>
class IsMatrixAdt : public std::is_base_of<MatrixAdtTag, T> {};

/// @brief a compile-time non-intrusive indirecion that utilizes above class
///       definition
/// @tparam T the type of question
template <typename T>
constexpr bool kIsMatrixAdtV = IsMatrixAdt<T>::value;

/// @brief concept for Matrix ADT interface
template <typename T>
concept MatrixAdtConcept = requires(T matrix) {
  matrix.display();

  matrix.dimensions().kRows;
  matrix.dimensions().kColumns;

  matrix.isSymmetric();

  typename T::value_type;
} && requires(T matrix, std::size_t index) {
  // TODO(salah):
  // 1- implement rows() and columns() in the remaining matrices types
  // 2- added them to the concept here
  // 3- remove row(index) and column(index) from the concept and from the public
  //    section as well
  matrix.row(index);
  matrix.column(index);
} && kIsMatrixAdtV<T>;

}  // namespace data_structures::matrix_types
