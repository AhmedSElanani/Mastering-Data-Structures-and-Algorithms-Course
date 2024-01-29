#include "data-structures/ArrayAdt.hpp"

#include "gtest/gtest.h"

/// @brief namespace for arrayAdt_test tests
namespace data_structures_test::arrayAdt_test {
using namespace ::data_structures;

TEST(TestingAppend, LengthsOfArraysOfDifferentSizes) {
  EXPECT_EQ((ArrayAdt<std::size_t, 1>{}).length(), 0U);

  EXPECT_EQ((ArrayAdt<std::size_t, 2>{}).length(),
            (ArrayAdt<std::size_t, 3>{}).length());

  EXPECT_EQ((ArrayAdt<std::size_t, 4>{2, 3}).length(), 2U);

  EXPECT_EQ((ArrayAdt<std::size_t, 5>{2, 3}).length(),
            (ArrayAdt<std::size_t, 6>{4, 5}).length());

  EXPECT_EQ((ArrayAdt<std::size_t, 7>{2, 3, 4, 5}).length(), 4U);

  EXPECT_EQ((ArrayAdt<std::size_t, 8>{2, 3, 4, 5}).length(),
            (ArrayAdt<std::size_t, 9>{6, 7, 8, 9}).length());
}

TEST(TestingAppend, AppendElementsToEmptyArray) {
  ArrayAdt<std::size_t, 5> arr1;

  EXPECT_TRUE(arr1.append(1));
  EXPECT_TRUE(arr1.append(2));
  EXPECT_TRUE(arr1.append(3));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5>{1, 2, 3}).display().c_str());
}

TEST(TestingAppend, AppendElementsTillArrayIsFull) {
  ArrayAdt<std::size_t, 5> arr1;

  while (arr1.append(1));

  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5>{1, 1, 1, 1, 1}).display().c_str());
}

TEST(TestingAppend, AppendToHalfFullArray) {
  ArrayAdt<std::size_t, 5> arr1{1, 2, 3};

  EXPECT_TRUE(arr1.append(4));

  EXPECT_EQ(arr1.length(), 4U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5>{1, 2, 3, 4}).display().c_str());
}

TEST(TestingAppend, AppendToFullArray) {
  ArrayAdt<std::size_t, 3> arr1{1, 2, 3};

  EXPECT_FALSE(arr1.append(4));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 3>{1, 2, 3}).display().c_str());
}
}  // namespace data_structures_test::arrayAdt_test
