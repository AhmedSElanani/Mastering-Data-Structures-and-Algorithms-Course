#include "data-structures/matrix-types/DiagonalMatrix.hpp"

#include "gtest/gtest.h"

/// @brief namespace for matrixAdt_test tests
namespace data_structures_test::matrixAdt_test {
using namespace ::data_structures::matrix_types;

TEST(TestingConstruction, ConstructingDiagonallMatrices) {
  // 1-D Matrices
  EXPECT_NO_THROW({ (DiagonalMatrix<1U>{}); });
  EXPECT_NO_THROW({ (DiagonalMatrix<1U>{1U}); });

  // 2-D Matrices
  EXPECT_NO_THROW({ (DiagonalMatrix<2U>{}); });
  EXPECT_NO_THROW({ (DiagonalMatrix<2U>{1U, 2U}); });

  EXPECT_NO_THROW({ (DiagonalMatrix<3U>{}); });
  EXPECT_NO_THROW({ (DiagonalMatrix<3U>{1U, 2U, 3U}); });
}

TEST(TestingDisplay, DisplayDiagonalMatricesOfDifferentSizes) {
  EXPECT_NO_THROW({ (DiagonalMatrix<3U>{}); });
  EXPECT_NO_THROW({ (DiagonalMatrix<3U>{1U, 2U, 3U}); });

  EXPECT_STREQ((DiagonalMatrix<1U>{}).display().c_str(), "|0|");
  EXPECT_STREQ((DiagonalMatrix<1U>{1U}).display().c_str(), "|1|");

  EXPECT_STREQ((DiagonalMatrix<2U>{}).display().c_str(), "|0 0|\n|0 0|");
  EXPECT_STREQ((DiagonalMatrix<2U>{1U, 2U}).display().c_str(), "|1 0|\n|0 2|");

  EXPECT_STREQ((DiagonalMatrix<3U>{}).display().c_str(),
               "|0 0 0|\n|0 0 0|\n|0 0 0|");
  EXPECT_STREQ((DiagonalMatrix<3U>{1U, 2U, 3U}).display().c_str(),
               "|1 0 0|\n|0 2 0|\n|0 0 3|");
}

}  // namespace data_structures_test::matrixAdt_test
