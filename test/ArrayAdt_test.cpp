#include "data-structures/ArrayAdt.hpp"

#include "gtest/gtest.h"

/// @brief namespace for arrayAdt_test tests
namespace data_structures_test::arrayAdt_test {
using namespace ::data_structures;

TEST(TestingAppend, AppendElementsToEmptyArray) {
  ArrayAdt<std::size_t, 5U> arr1;

  EXPECT_TRUE(arr1.append(1));
  EXPECT_TRUE(arr1.append(2));
  EXPECT_TRUE(arr1.append(3));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 2, 3}).display().c_str());
}

TEST(TestingAppend, AppendElementsTillArrayIsFull) {
  ArrayAdt<std::size_t, 5U> arr1;

  while (arr1.append(1));

  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 1, 1, 1, 1}).display().c_str());
}

TEST(TestingAppend, AppendToHalfFullArray) {
  ArrayAdt<std::size_t, 5U> arr1{1, 2, 3};

  EXPECT_TRUE(arr1.append(4));

  EXPECT_EQ(arr1.length(), 4U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 2, 3, 4}).display().c_str());
}

TEST(TestingAppend, AppendToFullArray) {
  ArrayAdt<std::size_t, 3U> arr1{1, 2, 3};

  EXPECT_FALSE(arr1.append(4));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 3U>{1, 2, 3}).display().c_str());
}

TEST(TestingInsert, InsertElementsAtBeginOfEmptyArray) {
  ArrayAdt<std::size_t, 5U> arr1;

  EXPECT_TRUE(arr1.insert(3, 0));
  EXPECT_TRUE(arr1.insert(2, 0));
  EXPECT_TRUE(arr1.insert(1, 0));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 2, 3}).display().c_str());
}

TEST(TestingInsert, InsertElementsAtBeginOfEmptyArrayTillFull) {
  ArrayAdt<std::size_t, 5U> arr1;

  while (arr1.insert(1, 0));

  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 1, 1, 1, 1}).display().c_str());
}

TEST(TestingInsert, InsertElementsAtEndOfEmptyArray) {
  ArrayAdt<std::size_t, 5U> arr1;

  EXPECT_TRUE(arr1.insert(1, 0));
  EXPECT_TRUE(arr1.insert(2, 1));
  EXPECT_TRUE(arr1.insert(3, 2));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{1, 2, 3}).display().c_str());
}

TEST(TestingInsert, InsertElementsAtEndOfEmptyArrayTillFull) {
  ArrayAdt<std::size_t, 5U> arr1;

  while (arr1.insert(2, arr1.length()));

  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 5U>{2, 2, 2, 2, 2}).display().c_str());
}

TEST(TestingInsert, InsertingToHalfFullArray) {
  ArrayAdt<std::size_t, 10U> arr1{1, 4, 9};

  EXPECT_TRUE(arr1.insert(2, 1));
  EXPECT_TRUE(arr1.insert(3, 2));

  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{1, 2, 3, 4, 9}).display().c_str());

  EXPECT_TRUE(arr1.insert(5, 4));
  EXPECT_TRUE(arr1.insert(6, 5));
  EXPECT_TRUE(arr1.insert(7, 6));
  EXPECT_TRUE(arr1.insert(8, 7));
  EXPECT_TRUE(arr1.insert(10, 9));

  EXPECT_EQ(arr1.length(), 10U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
                   .display()
                   .c_str());
}

TEST(TestingInsert, InsertToFullArray) {
  ArrayAdt<std::size_t, 3U> arr1{1, 2, 3};

  EXPECT_FALSE(arr1.insert(4, 2));

  EXPECT_EQ(arr1.length(), 3U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 3U>{1, 2, 3}).display().c_str());
}

TEST(TestingInsert, InsertFarAfterArrayElements) {
  ArrayAdt<std::size_t, 30U> arr1{1, 2, 3};

  EXPECT_TRUE(arr1.insert(4, 10));
  EXPECT_EQ(arr1.length(), 4U);

  EXPECT_TRUE(arr1.insert(5, 20));
  EXPECT_EQ(arr1.length(), 5U);

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 30U>{1, 2, 3, 4, 5}).display().c_str());
}

TEST(TestingLength, LengthsOfArraysOfDifferentSizes) {
  EXPECT_EQ((ArrayAdt<std::size_t, 1U>{}).length(), 0U);

  EXPECT_EQ((ArrayAdt<std::size_t, 2U>{}).length(),
            (ArrayAdt<std::size_t, 3U>{}).length());

  EXPECT_EQ((ArrayAdt<std::size_t, 4U>{2, 3}).length(), 2U);

  EXPECT_EQ((ArrayAdt<std::size_t, 5U>{2, 3}).length(),
            (ArrayAdt<std::size_t, 6U>{4, 5}).length());

  EXPECT_EQ((ArrayAdt<std::size_t, 7U>{2, 3, 4, 5}).length(), 4U);

  EXPECT_EQ((ArrayAdt<std::size_t, 8U>{2, 3, 4, 5}).length(),
            (ArrayAdt<std::size_t, 9U>{6, 7, 8, 9}).length());
}

}  // namespace data_structures_test::arrayAdt_test
