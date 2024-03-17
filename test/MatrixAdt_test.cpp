#include "data-structures/MatrixAdt.hpp"

#include "data-structures/matrix-types/DiagonalMatrix.hpp"
#include "data-structures/matrix-types/NormalMatrix.hpp"
#include "gtest/gtest.h"

/// @brief namespace for matrixAdt_test tests
namespace data_structures_test::matrixAdt_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingMatrixAdts) {
  MatrixAdt<matrix_types::DiagonalMatrix<2U>> matrix1{1U, 2U};
  MatrixAdt<matrix_types::NormalMatrix<2U, 2U>> matrix2{{1U, 2U}, {1U, 2U}};
  MatrixAdt<matrix_types::NormalMatrix<2U, 2U>> matrix3{{1U, 0U}, {0U, 2U}};

  EXPECT_STRNE(matrix1.display().c_str(), matrix2.display().c_str());
  EXPECT_STREQ(matrix1.display().c_str(), matrix3.display().c_str());
}

}  // namespace data_structures_test::matrixAdt_test
