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

TEST(TestingMultiplication, MultiplyingMatricesOfSameTypes) {
  {
    const auto result{
        MatrixAdt<matrix_types::DiagonalMatrix<5U>>{1U, 2U, 3U, 4U, 5U} *
        MatrixAdt<matrix_types::DiagonalMatrix<5U>>{6U, 7U, 8U, 9U, 10U}};

    EXPECT_STREQ(
        result.display().c_str(),
        "|6 0 0 0 0|\n|0 14 0 0 0|\n|0 0 24 0 0|\n|0 0 0 36 0|\n|0 0 0 0 50|");
  }

  {
    const auto result{
        MatrixAdt<matrix_types::LowerTriangularMatrix<4U>>{
            {1U}, {2U, 3U}, {4U, 5U, 6U}, {7U, 8U, 9U, 10U}} *
        MatrixAdt<matrix_types::LowerTriangularMatrix<4U>>{
            {11U}, {12U, 13U}, {14U, 15U, 16U}, {17U, 18U, 19U, 20U}}

    };

    EXPECT_STREQ(result.display().c_str(),
                 "|11 0 0 0|\n|58 39 0 0|\n|188 155 96 0|\n|469 419 334 200|");
  }

  {
    const auto result{
        MatrixAdt<matrix_types::NormalMatrix<2U, 2U>>{{1U, 2U}, {3U, 4U}} *
        MatrixAdt<matrix_types::NormalMatrix<2U, 2U>>{{5U, 6U}, {7U, 8U}}};

    EXPECT_STREQ(result.display().c_str(), "|19 22|\n|43 50|");
  }
}

TEST(TestingMultiplication, MultiplyingMatricesOfDifferentTypes) {
  {
    const auto result{MatrixAdt<matrix_types::NormalMatrix<3U, 2U>>{
                          {1U, 2U}, {3U, 4U}, {5U, 6U}} *
                      MatrixAdt<matrix_types::NormalMatrix<2U, 4U>>{
                          {7U, 8U, 9U, 10U}, {11U, 12U, 13U, 14U}}};

    EXPECT_STREQ(result.display().c_str(),
                 "|29 32 35 38|\n|65 72 79 86|\n|101 112 123 134|");
  }

  {
    const auto result1{
        MatrixAdt<matrix_types::LowerTriangularMatrix<4U>>{
            {1U}, {2U, 3U}, {4U, 5U, 6U}, {7U, 8U, 9U, 10U}} *
        MatrixAdt<matrix_types::NormalMatrix<4U, 3U>>{{11U, 12U, 13U},
                                                      {14U, 15U, 16U},
                                                      {17U, 18U, 19U},
                                                      {20U, 21U, 22U}}};

    EXPECT_STREQ(result1.display().c_str(),
                 "|11 12 13|\n|64 69 74|\n|216 231 246|\n|542 576 610|");

    const auto result2{
        result1 * MatrixAdt<matrix_types::DiagonalMatrix<3U>>{23U, 24U, 25U}};

    EXPECT_STREQ(result2.display().c_str(),
                 "|253 288 325|\n|1472 1656 1850|\n|4968 5544 6150|\n|12466 "
                 "13824 15250|");
  }
}

}  // namespace data_structures_test::matrixAdt_test
