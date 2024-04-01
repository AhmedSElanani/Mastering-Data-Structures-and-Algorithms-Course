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

// TODO:
// test dimensions same as normal matrix

// TODO:
// test row() method

// test column() method

TEST(TestingMultiplication, DiagonalMatricesMultiplication) {
  // TODO: complete this test suite
  {
    const auto result{DiagonalMatrix<3U>{1U, 2U, 3U} *
                      DiagonalMatrix<3U>{4U, 5U, 6U}};

    EXPECT_STREQ(result.display().c_str(), "|4 0 0|\n|0 10 0|\n|0 0 18|");
  }

  {
    const auto result{DiagonalMatrix<5U>{1U, 2U, 3U, 4U, 5U} *
                      DiagonalMatrix<5U>{6U, 7U, 8U, 9U, 10U}};

    EXPECT_STREQ(
        result.display().c_str(),
        "|6 0 0 0 0|\n|0 14 0 0 0|\n|0 0 24 0 0|\n|0 0 0 36 0|\n|0 0 0 0 50|");
  }
}

TEST(TestingIsSymmetric, CheckSymmetricityOfDiagonalMatricesOfDifferentSizes) {
  EXPECT_TRUE((DiagonalMatrix<1U>{}).isSymmetric());
  EXPECT_TRUE((DiagonalMatrix<1U>{1U}).isSymmetric());

  EXPECT_TRUE((DiagonalMatrix<2U>{}).isSymmetric());
  EXPECT_TRUE((DiagonalMatrix<2U>{1U, 2U}).isSymmetric());

  EXPECT_TRUE((DiagonalMatrix<3U>{}).isSymmetric());
  EXPECT_TRUE((DiagonalMatrix<3U>{1U, 2U, 3U}).isSymmetric());
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
