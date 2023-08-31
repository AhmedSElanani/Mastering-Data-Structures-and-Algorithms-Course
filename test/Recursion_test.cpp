#include "algorithms/Recursion.hpp"

#include <limits>

#include "gtest/gtest.h"

/// @brief
namespace algorithms_test::sumNaturalNums_test {

/// @brief class for testing sumNaturalNums method
class SumNaturalNumsTest : public ::testing::Test {};

TEST_F(SumNaturalNumsTest, SumUpToZero) {
  EXPECT_EQ(::algorithms::Recursion::sumNaturalNums(0U), 0U);
}

TEST_F(SumNaturalNumsTest, SumUpToOne) {
  EXPECT_EQ(::algorithms::Recursion::sumNaturalNums(1U), 1U);
}

TEST_F(SumNaturalNumsTest, PositiveInputs) {
  EXPECT_EQ(::algorithms::Recursion::sumNaturalNums(5U), 15U);
  EXPECT_EQ(::algorithms::Recursion::sumNaturalNums(9U), 45U);
  EXPECT_EQ(::algorithms::Recursion::sumNaturalNums(42U), 903U);
}
}  // namespace algorithms_test::sumNaturalNums_test


}  // namespace algorithms_test
