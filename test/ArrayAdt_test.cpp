#include "data-structures/ArrayAdt.hpp"

#include "gtest/gtest.h"

/// @brief namespace for arrayAdt_test tests
namespace data_structures_test::arrayAdt_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingArrays) {
  EXPECT_NO_THROW({ (ArrayAdt<std::size_t, 5U>{}); });
  EXPECT_EQ((ArrayAdt<std::size_t, 5U>{}).length(), 0U);

  EXPECT_NO_THROW({ (ArrayAdt<std::size_t, 5U>{1, 2, 3, 4, 5}); });
  EXPECT_EQ((ArrayAdt<std::size_t, 5U>{1, 2, 3, 4, 5}).length(), 5U);

  EXPECT_THROW(
      { (ArrayAdt<std::size_t, 3U>{1, 2, 3, 4, 5}); }, std::out_of_range);
}

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

TEST(TestingRemove, RemoveElementsFromArray) {
  ArrayAdt<std::size_t, 10U> arr1{1, 2, 42, 3, 130, 4, 5};

  EXPECT_TRUE(arr1.remove(2));
  EXPECT_TRUE(arr1.remove(3));

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{1, 2, 3, 4, 5}).display().c_str());
}

TEST(TestingRemove, RemoveFromEmptyArray) {
  ArrayAdt<std::size_t, 10U> arr1;

  for (auto index{0U}; index < arr1.length(); ++index) {
    EXPECT_FALSE(arr1.remove(index));
  }

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{}).display().c_str());
}

TEST(TestingRemove, RemoveNonExistentElement) {
  ArrayAdt<int, 10U> arr1{1, 2, 3, 4, 5};

  for (auto index{5U}; index < arr1.length(); ++index) {
    EXPECT_FALSE(arr1.remove(index));
  }

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{1, 2, 3, 4, 5}).display().c_str());
}

TEST(TestingRemove, RemoveIndexOutsideBoundaries) {
  ArrayAdt<int, 10U> arr1{1, 2, 3, 4, 5};

  EXPECT_FALSE(arr1.remove(11U));
  EXPECT_FALSE(arr1.remove(21U));
  EXPECT_FALSE(arr1.remove(31U));

  EXPECT_STREQ((arr1).display().c_str(),
               (ArrayAdt<std::size_t, 10U>{1, 2, 3, 4, 5}).display().c_str());
}

TEST(TestingRemove, SearchForExistingElements) {
  ArrayAdt<int, 10U> arr1{1, 42, 3, 69, 5, 666};

  EXPECT_EQ(arr1.search(42), 1U);
  EXPECT_EQ(arr1.search(69), 3U);
  EXPECT_EQ(arr1.search(666), 5U);
}

TEST(TestingRemove, SearchForRepeatedElements) {
  ArrayAdt<int, 10U> arr1{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};

  EXPECT_EQ(arr1.search(1), 0U);
  EXPECT_EQ(arr1.search(2), 1U);
  EXPECT_EQ(arr1.search(3), 3U);
  EXPECT_EQ(arr1.search(4), 6U);
}

TEST(TestingRemove, SearchForNonExistentElements) {
  ArrayAdt<int, 10U> arr1{1, 2, 3, 4, 5, 6};

  EXPECT_EQ(arr1.search(42), std::numeric_limits<std::size_t>::max());
  EXPECT_EQ(arr1.search(69), std::numeric_limits<std::size_t>::max());
  EXPECT_EQ(arr1.search(666), std::numeric_limits<std::size_t>::max());
}

TEST(TestingSettersAndGetters, SetAndGetExistingElement) {
  ArrayAdt<unsigned int, 10U> arr1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto index{0U}; index < arr1.length(); ++index) {
    EXPECT_EQ(arr1.get(index), index);

    const auto newElem{42U + index};
    EXPECT_NO_THROW({ (arr1.set(newElem, index)); });
    EXPECT_EQ(arr1.get(index), newElem);
  }
}

TEST(TestingSettersAndGetters, SettingOutOfBoundElement) {
  ArrayAdt<unsigned int, 10U> arr1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_THROW(
      { (ArrayAdt<std::size_t, 3U>{}.set(0, 3U)); }, std::out_of_range);
}

TEST(TestingSettersAndGetters, GettingElementOutOfBounds) {
  ArrayAdt<unsigned int, 10U> arr1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_THROW({ (ArrayAdt<std::size_t, 3U>{}.get(3U)); }, std::out_of_range);
}

TEST(TestingMaxAndMin, UniqueMaxAndMinElement) {
  ArrayAdt<unsigned int, 10U> arr1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_EQ(arr1.max(), 9U);
  EXPECT_EQ(arr1.min(), 0U);
}

TEST(TestingMaxAndMin, RepeatedMaxAndMinElement) {
  ArrayAdt<unsigned int, 10U> arr1{1, 1, 2, 3, 3, 4, 5, 5, 6, 6};

  EXPECT_EQ(arr1.max(), 6U);
  EXPECT_EQ(arr1.min(), 1U);
}

TEST(TestingMaxAndMin, AllEqualElements) {
  ArrayAdt<unsigned int, 10U> arr1{1, 1, 1, 1};

  EXPECT_EQ(arr1.max(), 1U);
  EXPECT_EQ(arr1.min(), 1U);
  EXPECT_EQ(arr1.max(), arr1.min());
}

TEST(TestingSum, SumOneElementArray) {
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{1U}).sum(), 1U);
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{2U}).sum(), 2U);
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{3U}).sum(), 3U);
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{4U}).sum(), 4U);
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{5U}).sum(), 5U);
}

TEST(TestingSum, SumMultipleElementArray) {
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{1U, 2U, 3U, 4U}).sum(), 10U);
  EXPECT_EQ((ArrayAdt<unsigned int, 10U>{5U, 6U, 7U, 8U}).sum(), 26U);
}

TEST(TestingSum, SumEmptyArray) {
  EXPECT_EQ((ArrayAdt<unsigned int, 1U>{}).sum(), 0U);
  EXPECT_EQ((ArrayAdt<unsigned int, 2U>{}).sum(), 0U);
  EXPECT_EQ((ArrayAdt<unsigned int, 3U>{}).sum(), 0U);
  EXPECT_EQ((ArrayAdt<unsigned int, 4U>{}).sum(), 0U);
  EXPECT_EQ((ArrayAdt<unsigned int, 5U>{}).sum(), 0U);
}

TEST(TestingAvg, AverageOneElementArray) {
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{1U}).avg(), 1U);
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{2U}).avg(), 2U);
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{3U}).avg(), 3U);
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{4U}).avg(), 4U);
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{5U}).avg(), 5U);
}

TEST(TestingAvg, AverageMultipleElementArray) {
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{1U, 2U, 3U, 4U}).avg(), 2.5);
  EXPECT_DOUBLE_EQ((ArrayAdt<unsigned int, 10U>{5U, 6U, 7U, 8U}).avg(), 6.5);
}

TEST(TestingReverse, ReverseOneElementArray) {
  ArrayAdt<int, 5U> arr1{1};
  ArrayAdt<int, 5U> arr2{2};
  ArrayAdt<int, 5U> arr3{3};

  EXPECT_STREQ((arr1.reverse()).display().c_str(), (arr1).display().c_str());
  EXPECT_STREQ((arr2.reverse()).display().c_str(), (arr2).display().c_str());
  EXPECT_STREQ((arr3.reverse()).display().c_str(), (arr3).display().c_str());
}

TEST(TestingReverse, ReverseMultipleElementArray) {
  ArrayAdt<int, 5U> arr1{1, 2, 3, 4, 5};
  ArrayAdt<int, 5U> arr2{6, 7, 8, 9, 10};

  EXPECT_STREQ((arr1.reverse()).display().c_str(),
               (ArrayAdt<int, 5U>{5, 4, 3, 2, 1}).display().c_str());
  EXPECT_STREQ((arr2.reverse()).display().c_str(),
               (ArrayAdt<int, 5U>{10, 9, 8, 7, 6}).display().c_str());
}

TEST(TestingReverse, ReverseEmptyArray) {
  ArrayAdt<int, 10U> arr1{};

  EXPECT_EQ((arr1.reverse()).length(), (arr1).length());
  EXPECT_STREQ((arr1.reverse()).display().c_str(), (arr1).display().c_str());
}

TEST(TestingShift, ShiftEmptyArray) {
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(1U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(2U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(3U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(1U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(2U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.shift(3U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
}

TEST(TestingShift, ShiftOneElementArray) {
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(1U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(2U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(3U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(1U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(2U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.shift(3U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
}

TEST(TestingShift, ShiftZeroPositions) {
  EXPECT_STREQ(
      (ArrayAdt<int, 1U>{1}.shift(0U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 1U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 2U>{1, 2}.shift(0U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 2U>{1, 2}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 1U>{1}.shift(0U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 1U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 2U>{1, 2}.shift(0U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 2U>{1, 2}).display().c_str());
}

TEST(TestingShift, ShiftMultipleElementArray) {
  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(1U, shiftDir::left)};

    // remove last element(s) to eleminate undefined behavior
    arr.remove(arr.length() - 1U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{2, 3, 4, 5}).display().c_str());
  }

  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(2U, shiftDir::left)};

    // remove last element(s) to eleminate undefined behavior
    arr.remove(arr.length() - 1U);
    arr.remove(arr.length() - 1U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{3, 4, 5}).display().c_str());
  }

  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(3U, shiftDir::left)};

    // remove last element(s) to eleminate undefined behavior
    arr.remove(arr.length() - 1U);
    arr.remove(arr.length() - 1U);
    arr.remove(arr.length() - 1U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{4, 5}).display().c_str());
  }

  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(1U, shiftDir::right)};

    // remove first element(s) to eleminate undefined behavior
    arr.remove(0U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{1, 2, 3, 4}).display().c_str());
  }

  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(2U, shiftDir::right)};

    // remove first element(s) to eleminate undefined behavior
    arr.remove(0U);
    arr.remove(0U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{1, 2, 3}).display().c_str());
  }

  {
    auto arr{ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.shift(3U, shiftDir::right)};

    // remove first element(s) to eleminate undefined behavior
    arr.remove(0U);
    arr.remove(0U);
    arr.remove(0U);

    EXPECT_STREQ((arr).display().c_str(),
                 (ArrayAdt<int, 5U>{1, 2}).display().c_str());
  }
}

TEST(TestingRotate, RotateEmptyArray) {
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(1U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(2U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(3U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(1U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(2U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{}.rotate(3U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{}).display().c_str());
}

TEST(TestingRotate, RotateOneElementArray) {
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(1U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(2U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(3U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(1U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(2U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
  EXPECT_STREQ(
      (ArrayAdt<int, 5U>{1}.rotate(3U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 5U>{1}).display().c_str());
}

TEST(TestingRotate, RotateZeroPositions) {
  EXPECT_STREQ(
      (ArrayAdt<int, 1U>{1}.rotate(0U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 1U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 2U>{1, 2}.rotate(0U, shiftDir::left)).display().c_str(),
      (ArrayAdt<int, 2U>{1, 2}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 1U>{1}.rotate(0U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 1U>{1}).display().c_str());

  EXPECT_STREQ(
      (ArrayAdt<int, 2U>{1, 2}.rotate(0U, shiftDir::right)).display().c_str(),
      (ArrayAdt<int, 2U>{1, 2}).display().c_str());
}

TEST(TestingRotate, RotateMultipleElementArray) {
  EXPECT_STREQ((ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.rotate(1U, shiftDir::left))
                   .display()
                   .c_str(),
               (ArrayAdt<int, 5U>{2, 3, 4, 5, 1}).display().c_str());

  EXPECT_STREQ((ArrayAdt<int, 5U>{1, 2, 3, 4, 5}.rotate(2U, shiftDir::left))
                   .display()
                   .c_str(),
               (ArrayAdt<int, 5U>{3, 4, 5, 1, 2}).display().c_str());

  EXPECT_STREQ((ArrayAdt<int, 5U>{6, 7, 8, 9, 10}.rotate(1U, shiftDir::right))
                   .display()
                   .c_str(),
               (ArrayAdt<int, 5U>{10, 6, 7, 8, 9}).display().c_str());

  EXPECT_STREQ((ArrayAdt<int, 5U>{6, 7, 8, 9, 10}.rotate(2U, shiftDir::right))
                   .display()
                   .c_str(),
               (ArrayAdt<int, 5U>{9, 10, 6, 7, 8}).display().c_str());
}

TEST(TestingDisplay, DisplayArraysOfDifferentSizes) {
  EXPECT_STREQ((ArrayAdt<std::size_t, 1U>{}).display().c_str(), "[]");
  EXPECT_STREQ((ArrayAdt<std::size_t, 2U>{}).display().c_str(), "[]");
  EXPECT_STREQ((ArrayAdt<std::size_t, 3U>{}).display().c_str(), "[]");

  EXPECT_STREQ((ArrayAdt<std::size_t, 1U>{}).display().c_str(),
               (ArrayAdt<std::size_t, 3U>{}).display().c_str());

  EXPECT_STREQ((ArrayAdt<std::size_t, 4U>{2, 3}).display().c_str(), "[2,3]");
  EXPECT_STREQ((ArrayAdt<std::size_t, 4U>{4, 5}).display().c_str(), "[4,5]");

  EXPECT_STREQ((ArrayAdt<std::size_t, 8U>{2, 3, 4, 5}).display().c_str(),
               "[2,3,4,5]");
  EXPECT_STREQ((ArrayAdt<std::size_t, 9U>{6, 7, 8, 9}).display().c_str(),
               "[6,7,8,9]");
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
