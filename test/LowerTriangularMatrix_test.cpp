#include "data-structures/matrix-types/LowerTriangularMatrix.hpp"

#include "gtest/gtest.h"

/// @brief namespace for matrixAdt_test tests
namespace data_structures_test::matrixAdt_test {
using namespace ::data_structures::matrix_types;

TEST(TestingConstruction, ConstructingLowerTriangularMatrices) {
  // 1-D Matrices
  EXPECT_NO_THROW({ (LowerTriangularMatrix<1U>{}); });
  EXPECT_NO_THROW({ (LowerTriangularMatrix<1U>{{1U}}); });

  // // 2-D Matrices
  EXPECT_NO_THROW({ (LowerTriangularMatrix<2U>{}); });
  EXPECT_NO_THROW({ (LowerTriangularMatrix<2U>{{1U}, {2U, 3U}}); });

  EXPECT_NO_THROW({ (LowerTriangularMatrix<3U>{}); });
  EXPECT_NO_THROW(
      { (LowerTriangularMatrix<3U>{{1U}, {2U, 3U}, {4U, 5U, 6U}}); });
}

TEST(TestingConstruction,
     ConstructingMatricesLowerTriangularWithRowsLongerThanExpected) {
  {
    EXPECT_NO_THROW({ (LowerTriangularMatrix<1U>{{1U, 2U}}); });
    EXPECT_STREQ((LowerTriangularMatrix<1U>{{1U}}).display().c_str(),
                 (LowerTriangularMatrix<1U>{{1U, 2U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (LowerTriangularMatrix<2U>{{1U, 2U}, {3U, 4U, 5U}}); });
    EXPECT_STREQ(
        (LowerTriangularMatrix<2U>{{1U}, {3U, 4U}}).display().c_str(),
        (LowerTriangularMatrix<2U>{{1U, 2U}, {3U, 4U, 5U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({
      (LowerTriangularMatrix<3U>{{1U, 2U}, {3U, 4U, 5U}, {6U, 7U, 8U, 9U}});
    });
    EXPECT_STREQ(
        (LowerTriangularMatrix<2U>{{1U}, {3U, 4U}, {6U, 7U, 8U}})
            .display()
            .c_str(),
        (LowerTriangularMatrix<2U>{{1U, 2U}, {3U, 4U, 5U}, {6U, 7U, 8U, 9U}})
            .display()
            .c_str());
  }
}

TEST(TestingConstruction,
     ConstructingMatricesLowerTriangularWithRowsShorterThanExpected) {
  {
    EXPECT_NO_THROW({ (LowerTriangularMatrix<1U>{}); });
    EXPECT_STREQ((LowerTriangularMatrix<1U>{}).display().c_str(),
                 (LowerTriangularMatrix<1U>{{0U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (LowerTriangularMatrix<2U>{{1U}, {2U}}); });
    EXPECT_STREQ((LowerTriangularMatrix<2U>{{1U}, {2U}}).display().c_str(),
                 (LowerTriangularMatrix<2U>{{1U}, {2U, 0U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (LowerTriangularMatrix<3U>{{1U}, {2U}, {3U}}); });
    EXPECT_STREQ(
        (LowerTriangularMatrix<2U>{{1U}, {2U}, {3U}}).display().c_str(),
        (LowerTriangularMatrix<2U>{{1U}, {2U, 0U}, {3U, 0U, 0U}})
            .display()
            .c_str());
  }
}

// TODO:
// test dimensions same as normal matrix

// TODO:
// test row() method

// TODO:
// test column() method

TEST(TestingMultiplication, LowerTriangularMatricesMultiplication) {
  // TODO: complete this test suite
  {
    const auto result{
        LowerTriangularMatrix<3U>{{1U}, {2U, 3U}, {4U, 5U, 6U}} *
        LowerTriangularMatrix<3U>{{7U}, {8U, 9U}, {10U, 11U, 12U}}};

    EXPECT_STREQ(result.display().c_str(), "|7 0 0|\n|38 27 0|\n|128 111 72|");
  }

  {
    const auto result{
        LowerTriangularMatrix<4U>{
            {1U}, {2U, 3U}, {4U, 5U, 6U}, {7U, 8U, 9U, 10U}} *
        LowerTriangularMatrix<4U>{
            {11U}, {12U, 13U}, {14U, 15U, 16U}, {17U, 18U, 19U, 20U}}

    };

    EXPECT_STREQ(result.display().c_str(),
                 "|11 0 0 0|\n|58 39 0 0|\n|188 155 96 0|\n|469 419 334 200|");
  }
}

TEST(TestingDisplay, DisplayLowerTriangleMatricesOfDifferentSizes) {
  EXPECT_STREQ((LowerTriangularMatrix<1U>{}).display().c_str(), "|0|");
  EXPECT_STREQ((LowerTriangularMatrix<1U>{{1U}}).display().c_str(), "|1|");

  EXPECT_STREQ((LowerTriangularMatrix<2U>{{1U}, {2U}}).display().c_str(),
               "|1 0|\n|2 0|");
  EXPECT_STREQ((LowerTriangularMatrix<2U>{{1U}, {2U, 3U}}).display().c_str(),
               "|1 0|\n|2 3|");

  EXPECT_STREQ((LowerTriangularMatrix<3U>{{1U}, {2U}, {3U}}).display().c_str(),
               "|1 0 0|\n|2 0 0|\n|3 0 0|");
  EXPECT_STREQ((LowerTriangularMatrix<3U>{{1U}, {2U, 3U}, {4U, 5U, 6U}})
                   .display()
                   .c_str(),
               "|1 0 0|\n|2 3 0|\n|4 5 6|");
}

}  // namespace data_structures_test::matrixAdt_test
