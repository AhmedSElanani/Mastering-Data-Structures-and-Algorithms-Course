#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "data-structures/matrix-types/MatrixCommon.hpp"

// Matrices Types supported
#include "data-structures/matrix-types/DiagonalMatrix.hpp"
#include "data-structures/matrix-types/LowerTriangularMatrix.hpp"
#include "data-structures/matrix-types/NormalMatrix.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief definition of interface class for Matrix ADT
/// @tparam MatrixT
template <matrix_types::MatrixAdtConcept MatrixT>
class MatrixAdt {
public:
  /// @brief default constructor to resolve ambiguity when passing empty list
  constexpr MatrixAdt() = default;

  /// @brief parametrized constructor accepting a single braced init list,
  ///        useful for matrices types accepting such parameters
  /// @tparam ...Args parameter pack for the braced init lists passed
  /// @param ...args elementsto be passed to the instantiated matrix
  template <typename... Args>
  constexpr explicit MatrixAdt(Args&&... args)
      : m_matrixImpl{std::make_unique<MatrixT>(std::forward<Args>(args)...)} {}

  /// @brief parametrized constructor accepting multiple braced init list,
  ///        useful for matrices types accepting such parameters
  /// @tparam ...Args parameter pack for the nested braced init lists passed
  /// @param ...args elementsto be passed to the instantiated matrix
  template <typename... Args>
  constexpr explicit MatrixAdt(std::initializer_list<Args>&&... args)
      : m_matrixImpl{std::make_unique<MatrixT>(
            std::forward<std::initializer_list<Args>>(args)...)} {}

  /// @brief method to display elements of the instantiated matrix
  /// @return stringified format of the instantiated matrix elements
  constexpr auto display() const noexcept -> std::string {
    return m_matrixImpl->display();
  }

private:
  /// @brief unique pointer to the matrix type instantiated
  std::unique_ptr<MatrixT> m_matrixImpl{std::make_unique<MatrixT>()};
};

}  // namespace data_structures