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

TEST(TestingDimensions, DimensionsOfNormalMatricesWithDifferentSizes) {
  // 1-D Matrices
  {
    const auto &[rows, columns]{(NormalMatrix<1U, 1U>{}).dimensions()};

    EXPECT_EQ(rows, 1U);
    EXPECT_EQ(columns, 1U);
  }

  // 2-D Matrices
  {
    const auto &[rows, columns]{(NormalMatrix<1U, 2U>{}).dimensions()};

    EXPECT_EQ(rows, 1U);
    EXPECT_EQ(columns, 2U);
  }

  {
    const auto &[rows, columns]{(NormalMatrix<2U, 1U>{}).dimensions()};

    EXPECT_EQ(rows, 2U);
    EXPECT_EQ(columns, 1U);
  }

  {
    const auto &[rows, columns]{(NormalMatrix<2U, 2U>{}).dimensions()};

    EXPECT_EQ(rows, 2U);
    EXPECT_EQ(columns, 2U);
  }

  {
    const auto &[rows, columns]{(NormalMatrix<3U, 2U>{}).dimensions()};

    EXPECT_EQ(rows, 3U);
    EXPECT_EQ(columns, 2U);
  }

  {
    const auto &[rows, columns]{(NormalMatrix<2U, 3U>{}).dimensions()};

    EXPECT_EQ(rows, 2U);
    EXPECT_EQ(columns, 3U);
  }

  {
    const auto &[rows, columns]{(NormalMatrix<3U, 3U>{}).dimensions()};

    EXPECT_EQ(rows, 3U);
    EXPECT_EQ(columns, 3U);
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
