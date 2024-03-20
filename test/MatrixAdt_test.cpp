#include "data-structures/MatrixAdt.hpp"

#include "gtest/gtest.h"

/// @brief namespace for matrixAdt_test tests
namespace data_structures_test::matrixAdt_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingMatrixAdts) {
  MatrixAdt<matrix_types::DiagonalMatrix<2U>> diagMatrix1{1U, 2U};
  MatrixAdt<matrix_types::NormalMatrix<2U, 2U>> normalMatrix1{{1U, 2U},
                                                              {1U, 2U}};
  MatrixAdt<matrix_types::NormalMatrix<2U, 2U>> normalMatrix2{{1U, 0U},
                                                              {0U, 2U}};
  MatrixAdt<matrix_types::LowerTriangularMatrix<2U>> triangularMatrix1{
      {1U}, {0U, 2U}};

  EXPECT_STRNE(diagMatrix1.display().c_str(), normalMatrix1.display().c_str());

  EXPECT_STREQ(diagMatrix1.display().c_str(), normalMatrix2.display().c_str());
  EXPECT_STREQ(triangularMatrix1.display().c_str(),
               normalMatrix2.display().c_str());
}

}  // namespace data_structures_test::matrixAdt_test
