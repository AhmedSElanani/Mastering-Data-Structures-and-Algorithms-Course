#include "algorithms/Recursion.hpp"

#include <cstdint>

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

/// @brief namespace for exp tests
namespace algorithms_test::exp_test {

/// @brief class with parameters for testing exp method
class ExpTestwithParam : public ::testing::TestWithParam<std::uint8_t> {};

TEST_P(ExpTestwithParam, ExpZero) {
  EXPECT_EQ(::algorithms::Recursion::exp(0U, GetParam()), 1U);
}

INSTANTIATE_TEST_SUITE_P(RangeTests, ExpTestwithParam,
                         ::testing::Range<std::uint8_t>(1U, 10U));

/// @brief class for testing exp method
class ExpTest : public ::testing::Test {};

TEST_F(ExpTest, ExpOne) {
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 0U), 1.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 1U), 2.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 2U), 2.5, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 3U), 2.666667, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 4U), 2.708334, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(1U, 5U), 2.716667, 0.000001);
}

TEST_F(ExpTest, ExpTwo) {
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 0U), 1.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 1U), 3.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 2U), 5, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 3U), 6.333333, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 4U), 7.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::exp(2U, 5U), 7.266667, 0.000001);
}

}  // namespace algorithms_test::exp_test

/// @brief namespace for exp Horner's Rule tests
namespace algorithms_test::exp_HornersRule_test {

/// @brief class with parameters for testing expHornersRule method
class ExpHornersRuleTestwithParam
    : public ::testing::TestWithParam<std::uint8_t> {};

TEST_P(ExpHornersRuleTestwithParam, ExpZero) {
  EXPECT_EQ(::algorithms::Recursion::expHornersRule(0U, GetParam()), 1U);
}

INSTANTIATE_TEST_SUITE_P(RangeTests, ExpHornersRuleTestwithParam,
                         ::testing::Range<std::uint8_t>(1U, 10U));

/// @brief class for testing expHornersRule method
class ExpHornersRuleTest : public ::testing::Test {};

TEST_F(ExpHornersRuleTest, ExpOne) {
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 0U), 1.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 1U), 2.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 2U), 2.5, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 3U), 2.666667,
              0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 4U), 2.708334,
              0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(1U, 5U), 2.716667,
              0.000001);
}

TEST_F(ExpHornersRuleTest, ExpTwo) {
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 0U), 1.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 1U), 3.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 2U), 5, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 3U), 6.333333,
              0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 4U), 7.0, 0.000001);
  EXPECT_NEAR(::algorithms::Recursion::expHornersRule(2U, 5U), 7.266667,
              0.000001);
}

}  // namespace algorithms_test::exp_HornersRule_test
