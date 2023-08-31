#include "algorithms/Recursion.hpp"

#include "gtest/gtest.h"

/// @brief namespace for sumNaturalNums tests
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

/// @brief namespace for factorial tests
namespace algorithms_test::factorial_test {

/// @brief class for testing factorial method
class FactorialTest : public ::testing::Test {};

TEST_F(FactorialTest, FactorialZero) {
  EXPECT_EQ(::algorithms::Recursion::factorial(0U), 1U);
}

TEST_F(FactorialTest, FactorialOne) {
  EXPECT_EQ(::algorithms::Recursion::factorial(1U), 1U);
}

TEST_F(FactorialTest, PositiveInputs) {
  EXPECT_EQ(::algorithms::Recursion::factorial(2U), 2U);
  EXPECT_EQ(::algorithms::Recursion::factorial(3U), 6U);
  EXPECT_EQ(::algorithms::Recursion::factorial(4U), 24U);
  EXPECT_EQ(::algorithms::Recursion::factorial(5U), 120U);
  EXPECT_EQ(::algorithms::Recursion::factorial(6U), 720U);
}

}  // namespace algorithms_test::factorial_test

/// @brief namespace for power tests
namespace algorithms_test::power_test {

/// @brief class with parameters for testing power method
class PowerTestWithParam : public ::testing::TestWithParam<int> {};

TEST_P(PowerTestWithParam, PowerZero) {
  EXPECT_EQ(::algorithms::Recursion::power(GetParam(), 0U), 1U);
}

TEST_P(PowerTestWithParam, PowerOne) {
  const auto param{GetParam()};
  EXPECT_EQ(::algorithms::Recursion::power(param, 1U), param);
}

INSTANTIATE_TEST_SUITE_P(RangeTests, PowerTestWithParam,
                         ::testing::Range<int>(-3, 3));

/// @brief class for testing power method
class PowerTest : public ::testing::Test {};

TEST_F(PowerTest, PositiveInputs) {
  EXPECT_EQ(::algorithms::Recursion::power(3, 2U), 9U);
  EXPECT_EQ(::algorithms::Recursion::power(3, 3U), 27U);
  EXPECT_EQ(::algorithms::Recursion::power(3, 4U), 81U);
  EXPECT_EQ(::algorithms::Recursion::power(3, 5U), 243U);
  EXPECT_EQ(::algorithms::Recursion::power(3, 6U), 729U);
}

TEST_F(PowerTest, NegativeInputs) {
  EXPECT_EQ(::algorithms::Recursion::power(-4, 2U), 16);
  EXPECT_EQ(::algorithms::Recursion::power(-4, 3U), -64);
  EXPECT_EQ(::algorithms::Recursion::power(-4, 4U), 256);
  EXPECT_EQ(::algorithms::Recursion::power(-4, 5U), -1024);
  EXPECT_EQ(::algorithms::Recursion::power(-4, 6U), 4096);
}

}  // namespace algorithms_test::power_test
