#pragma once

#include <array>
#include <format>

#include "common/Common.hpp"
#include "data-structures/matrix-types/MatrixConcept.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief definition of class representing diagonal Matrix
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix, default is std::size_t
/// @note diagonal matrix is by definition is a square matrix, hence it needs
///       only one parameter to define its size
template <common::NaturalNumber auto N, typename T = std::size_t>
class DiagonalMatrix {
public:
  /// @brief constructor accepting braced init list representing the diagonal
  ///        elements of the matrix
  /// @tparam ...Elems parameter pack for the braced init lists passed
  /// @param ...elems elements of the diagonal to the matrix
  template <std::convertible_to<T>... Elems>
  constexpr explicit DiagonalMatrix(Elems&&... elems)
      : m_elements{std::forward<Elems>(elems)...} {}

  /// @brief method to display elements of the matrix
  /// @return elements surrounded by matrix symbol
  constexpr auto display() const noexcept -> std::string {
    const auto stringifyRow{
        [&diagonalElements = m_elements](std::size_t rowIndex) {
          constexpr auto rowLength{N};
          const auto diagonalElem{diagonalElements[rowIndex]};

          std::string result;
          for (std::size_t i{0U}; i < rowLength; ++i) {
            result +=
                // concat. the diagonal element when reach it,
                // otherwise concat. zero
                (i == rowIndex ? std::to_string(diagonalElem)
                               : std::to_string(0U)) +
                // concat. space after each element except the last one
                (i == rowLength - 1U ? "" : " ");
          }

          return std::string{std::format("|{}|", result)};
        }};

    constexpr auto numberOfRows{N};
    std::string result;
    for (std::size_t i{0U}; i < numberOfRows; ++i) {
      result += stringifyRow(i) + (i == numberOfRows - 1U ? "" : "\n");
    }

    return result;
  }

private:
  /// @brief diagonal elements of the matrix
  const std::array<T, N> m_elements;
};

/// @brief derive in a non-intrusive way of the MatrixAdt type
/// @tparam N number of rows and columns of the matrix
/// @tparam T type of elements of matrix
template <common::NaturalNumber auto N, typename T>
class detail::IsMatrixAdt<DiagonalMatrix<N, T>> : public std::true_type {};

}  // namespace data_structures