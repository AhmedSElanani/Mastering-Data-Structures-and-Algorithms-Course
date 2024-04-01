#include "data-structures/matrix-types/NormalMatrix.hpp"

#include "gtest/gtest.h"

/// @brief namespace for matrixAdt_test tests
namespace data_structures_test::matrixAdt_test {
using namespace ::data_structures::matrix_types;

TEST(TestingConstruction, ConstructingNormalMatrices) {
  // 1-D Matrices
  EXPECT_NO_THROW({ (NormalMatrix<1U, 1U>{}); });
  EXPECT_NO_THROW({ (NormalMatrix<1U, 1U>{{1U}}); });

  EXPECT_NO_THROW({ (NormalMatrix<1U, 2U>{}); });
  EXPECT_NO_THROW({ (NormalMatrix<1U, 2U>{{1U, 2U}}); });

  // 2-D Matrices
  EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{}); });
  EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U}}); });

  EXPECT_NO_THROW({ (NormalMatrix<2U, 3U>{}); });
  EXPECT_NO_THROW({ (NormalMatrix<2U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}}); });

  EXPECT_NO_THROW({ (NormalMatrix<3U, 3U>{}); });
  EXPECT_NO_THROW(
      { (NormalMatrix<3U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}, {7U, 8U, 9U}}); });
}

TEST(TestingConstruction, ConstructingMatricesWithRowsLongerThanExpected) {
  {
    EXPECT_NO_THROW(
        { (NormalMatrix<3U, 2U>{{1U, 2U, 3U}, {4U, 5U}, {6U, 7U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U, 3U}, {4U, 5U}, {6U, 7U}})
            .display()
            .c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {4U, 5U}, {6U, 7U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW(
        { (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U, 5U}, {6U, 7U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U, 5U}, {6U, 7U}})
            .display()
            .c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {6U, 7U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW(
        { (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U, 7U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U, 7U}})
            .display()
            .c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U}}).display().c_str());
  }
}

TEST(TestingConstruction, ConstructingMatricesWithRowsShorterThanExpected) {
  {
    EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{{1U}, {2U, 3U}, {4U, 5U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U}, {2U, 3U}, {4U, 5U}}).display().c_str(),
        (NormalMatrix<3U, 2U>{{1U, 0U}, {2U, 3U}, {4U, 5U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{{1U, 2U}, {3U}, {4U, 5U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U}, {4U, 5U}}).display().c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 0U}, {4U, 5U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U}}).display().c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 0U}}).display().c_str());
  }
}

TEST(TestingConstruction, ConstructingMatricesWithRowsLessThanExpected) {
  // Note: While passing more rows than expected give compilation error
  {
    EXPECT_NO_THROW({ (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}}); });

    EXPECT_STREQ(
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}}).display().c_str(),
        (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {0U, 0U}}).display().c_str());
  }

  {
    EXPECT_NO_THROW({ (NormalMatrix<2U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}}); });

    EXPECT_STREQ(
        (NormalMatrix<2U, 3U>{{1U, 2U, 3U}}).display().c_str(),
        (NormalMatrix<2U, 3U>{{1U, 2U, 3U}, {0U, 0U, 0U}}).display().c_str());
  }
}

TEST(TestingConstruction, ConstructingMatricesWith2DArrays) {
  // TODO: complete this test suite
  EXPECT_NO_THROW({
    (NormalMatrix<3U, 2U>{std::array<std::array<std::size_t, 2U>, 3U>{
        {{{1U, 2U}}, {{3U, 4U}}, {{5U, 6U}}}}});
  });
}

TEST(TestingDimensions, DimensionsOfNormalMatricesWithDifferentSizes) {
  // 1-D Matrices
  {
    const auto &dimensions{(NormalMatrix<1U, 1U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 1U);
    EXPECT_EQ(dimensions.columns, 1U);
  }

  // 2-D Matrices
  {
    const auto &dimensions{(NormalMatrix<1U, 2U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 1U);
    EXPECT_EQ(dimensions.columns, 2U);
  }

  {
    const auto &dimensions{(NormalMatrix<2U, 1U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 2U);
    EXPECT_EQ(dimensions.columns, 1U);
  }

  {
    const auto &dimensions{(NormalMatrix<2U, 2U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 2U);
    EXPECT_EQ(dimensions.columns, 2U);
  }

  {
    const auto &dimensions{(NormalMatrix<3U, 2U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 3U);
    EXPECT_EQ(dimensions.columns, 2U);
  }

  {
    const auto &dimensions{(NormalMatrix<2U, 3U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 2U);
    EXPECT_EQ(dimensions.columns, 3U);
  }

  {
    const auto &dimensions{(NormalMatrix<3U, 3U>{}).dimensions()};

    EXPECT_EQ(dimensions.rows, 3U);
    EXPECT_EQ(dimensions.columns, 3U);
  }
}

TEST(TestingColumn, ReadNormalMatricesColumnsWithinRange) {
  // 1x1 Matrix
  {
    constexpr auto column{NormalMatrix<1U, 1U>{}.column(0U)};
    EXPECT_EQ(column, (decltype(column){0U}));
  }

  {
    constexpr auto column{NormalMatrix<1U, 1U>{{1U}}.column(0U)};
    EXPECT_EQ(column, (decltype(column){1U}));
  }

  // 2x1 Matrix
  {
    constexpr auto column{NormalMatrix<2U, 1U>{}.column(0U)};
    EXPECT_EQ(column, (decltype(column){0U, 0U}));
  }

  {
    constexpr auto column{NormalMatrix<2U, 1U>{{1U}, {2U}}.column(0U)};
    EXPECT_EQ(column, (decltype(column){1U, 2U}));
  }

  // 1x2 Matrix
  {
    constexpr auto column{NormalMatrix<1U, 2U>{}.column(0U)};
    EXPECT_EQ(column, (decltype(column){0U}));
  }

  {
    constexpr auto column{NormalMatrix<1U, 2U>{}.column(1U)};
    EXPECT_EQ(column, (decltype(column){0U}));
  }

  {
    constexpr auto column{NormalMatrix<1U, 2U>{{1U, 2U}}.column(0U)};
    EXPECT_EQ(column, (decltype(column){1U}));
  }

  {
    constexpr auto column{NormalMatrix<1U, 2U>{{1U, 2U}}.column(1U)};
    EXPECT_EQ(column, (decltype(column){2U}));
  }

  // 2x2 Matrix
  {
    constexpr auto column{NormalMatrix<2U, 2U>{}.column(0U)};
    EXPECT_EQ(column, (decltype(column){0U, 0U}));
  }

  {
    constexpr auto column{NormalMatrix<2U, 2U>{}.column(1U)};
    EXPECT_EQ(column, (decltype(column){0U, 0U}));
  }

  {
    constexpr auto column{NormalMatrix<2U, 2U>{{1U, 2U}, {3U, 4U}}.column(0U)};
    EXPECT_EQ(column, (decltype(column){1U, 3U}));
  }

  {
    constexpr auto column{NormalMatrix<2U, 2U>{{1U, 2U}, {3U, 4U}}.column(1U)};
    EXPECT_EQ(column, (decltype(column){2U, 4U}));
  }
}

TEST(TestingIterators, ReadNormalMatricesRowsUsingIterator) {
  // TODO
}

TEST(TestingIterators, ReadNormalMatricesColumnsUsingIterator) {
  // TODO
}

TEST(TestingColumn, ReadNormalMatricesColumnsOutOfRange) {
  // 1x1 Matrix
  EXPECT_NO_THROW((NormalMatrix<1U, 1U>{}.column(0U)));
  EXPECT_THROW((NormalMatrix<1U, 1U>{}.column(1U)), std::out_of_range);

  // 2x1 Matrix
  EXPECT_NO_THROW((NormalMatrix<2U, 1U>{}.column(0U)));
  EXPECT_THROW((NormalMatrix<2U, 1U>{}.column(1U)), std::out_of_range);

  // 1x2 Matrix
  EXPECT_NO_THROW((NormalMatrix<1U, 2U>{}.column(0U)));
  EXPECT_NO_THROW((NormalMatrix<1U, 2U>{}.column(1U)));
  EXPECT_THROW((NormalMatrix<1U, 2U>{}.column(2U)), std::out_of_range);

  // 2x2 Matrix
  EXPECT_NO_THROW((NormalMatrix<2U, 2U>{}.column(0U)));
  EXPECT_NO_THROW((NormalMatrix<2U, 2U>{}.column(1U)));
  EXPECT_THROW((NormalMatrix<2U, 2U>{}.column(2U)), std::out_of_range);

  // 3x2 Matrix
  EXPECT_NO_THROW((NormalMatrix<3U, 2U>{}.column(0U)));
  EXPECT_NO_THROW((NormalMatrix<3U, 2U>{}.column(1U)));
  EXPECT_THROW((NormalMatrix<3U, 2U>{}.column(2U)), std::out_of_range);

  // 2x3 Matrix
  EXPECT_NO_THROW((NormalMatrix<2U, 3U>{}.column(0U)));
  EXPECT_NO_THROW((NormalMatrix<2U, 3U>{}.column(1U)));
  EXPECT_NO_THROW((NormalMatrix<2U, 3U>{}.column(2U)));
  EXPECT_THROW((NormalMatrix<2U, 3U>{}.column(3U)), std::out_of_range);

  // 3x3 Matrix
  EXPECT_NO_THROW((NormalMatrix<3U, 3U>{}.column(0U)));
  EXPECT_NO_THROW((NormalMatrix<3U, 3U>{}.column(1U)));
  EXPECT_NO_THROW((NormalMatrix<3U, 3U>{}.column(2U)));
  EXPECT_THROW((NormalMatrix<3U, 3U>{}.column(3U)), std::out_of_range);
}

TEST(TestingMultiplication, NormalMatricesMultiplication) {
  // TODO: complete this test suite
  {
    const auto result{NormalMatrix<2U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}} *
                      NormalMatrix<3U, 4U>{{7U, 8U, 9U, 10U},
                                           {11U, 12U, 13U, 14U},
                                           {15U, 16U, 17U, 18U}}};

    EXPECT_STREQ(result.display().c_str(), "|74 80 86 92|\n|173 188 203 218|");
  }

  {
    const auto result{
        NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U}} *
        NormalMatrix<2U, 4U>{{7U, 8U, 9U, 10U}, {11U, 12U, 13U, 14U}}};

    EXPECT_STREQ(result.display().c_str(),
                 "|29 32 35 38|\n|65 72 79 86|\n|101 112 123 134|");
  }
}

TEST(TestingIsSymmetric, CheckSymmetricityOfNormalMatricesOfDifferentSizes) {
  // testing non-square matrices
  EXPECT_FALSE((NormalMatrix<2U, 3U>{}).isSymmetric());
  EXPECT_FALSE(
      (NormalMatrix<2U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}}).isSymmetric());

  EXPECT_FALSE((NormalMatrix<3U, 4U>{}).isSymmetric());
  EXPECT_FALSE(
      (NormalMatrix<3U, 4U>{
           {7U, 8U, 9U, 10U}, {11U, 12U, 13U, 14U}, {15U, 16U, 17U, 18U}})
          .isSymmetric());

  EXPECT_FALSE((NormalMatrix<3U, 2U>{}).isSymmetric());
  EXPECT_FALSE(
      (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U}}).isSymmetric());

  EXPECT_FALSE((NormalMatrix<2U, 4U>{}).isSymmetric());
  EXPECT_FALSE((NormalMatrix<2U, 4U>{{7U, 8U, 9U, 10U}, {11U, 12U, 13U, 14U}})
                   .isSymmetric());

  // testing asymmetric square matrices
  EXPECT_FALSE((NormalMatrix<2U, 2U>{{1U}, {1U}}).isSymmetric());

  EXPECT_FALSE((NormalMatrix<3U, 3U>{{1U}, {1U}, {1U}}).isSymmetric());

  // testing symmetric square matrices
  EXPECT_TRUE((NormalMatrix<1U, 1U>{}).isSymmetric());
  EXPECT_TRUE((NormalMatrix<1U, 1U>{{1U}}).isSymmetric());

  EXPECT_TRUE((NormalMatrix<2U, 2U>{{1U, 2U}, {2U, 3U}}).isSymmetric());

  EXPECT_TRUE((NormalMatrix<3U, 3U>{{1U, 2U, 3U}, {2U, 4U, 5U}, {3U, 5U, 6U}})
                  .isSymmetric());
}

TEST(TestingDisplay, DisplayNormalMatricesOfDifferentSizes) {
  EXPECT_STREQ((NormalMatrix<1U, 1U>{}).display().c_str(), "|0|");
  EXPECT_STREQ((NormalMatrix<1U, 1U>{{1U}}).display().c_str(), "|1|");

  EXPECT_STREQ((NormalMatrix<1U, 2U>{}).display().c_str(), "|0 0|");
  EXPECT_STREQ((NormalMatrix<1U, 2U>{{1U, 2U}}).display().c_str(), "|1 2|");

  EXPECT_STREQ((NormalMatrix<3U, 2U>{}).display().c_str(),
               "|0 0|\n|0 0|\n|0 0|");
  EXPECT_STREQ(
      (NormalMatrix<3U, 2U>{{1U, 2U}, {3U, 4U}, {5U, 6U}}).display().c_str(),
      "|1 2|\n|3 4|\n|5 6|");

  EXPECT_STREQ((NormalMatrix<3U, 3U>{}).display().c_str(),
               "|0 0 0|\n|0 0 0|\n|0 0 0|");
  EXPECT_STREQ((NormalMatrix<3U, 3U>{{1U, 2U, 3U}, {4U, 5U, 6U}, {7U, 8U, 9U}})
                   .display()
                   .c_str(),
               "|1 2 3|\n|4 5 6|\n|7 8 9|");
}

}  // namespace data_structures_test::matrixAdt_test
