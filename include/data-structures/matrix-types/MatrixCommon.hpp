#pragma once

#include <concepts>

#include "common/Common.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief namespace for matrices types
namespace matrix_types {

/// @brief namespace for common data between matrices types
namespace matrix_common {

/// @brief struct to represent the dimensions of the matrix
template <common::NaturalNumber decltype(auto) ROWS,
          common::NaturalNumber decltype(auto) COLUMNS>
struct MatrixDimensions {
  static constexpr auto rows{ROWS};
  static constexpr auto columns{COLUMNS};
};
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
constexpr bool IsMatrixAdt_v = IsMatrixAdt<T>::value;

/// @brief concept for Matrix ADT interface
template <typename T>
concept MatrixAdtConcept = requires(T t) {
  t.display();
  t.dimensions().rows;
  t.dimensions().columns;

} && IsMatrixAdt_v<T>;

}  // namespace matrix_types
}  // namespace data_structures
