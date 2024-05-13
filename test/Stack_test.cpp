#include "data-structures/Stack.hpp"

#include "data-structures/LinkedList.hpp"
#include "gtest/gtest.h"

/// @brief
namespace data_structures_test::stack_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingStacksBasedOnLinkedLists) {
  // empty stack
  EXPECT_NO_THROW({ (Stack<LinkedList<std::size_t>>{}); });

  // stack of one element
  EXPECT_NO_THROW({ (Stack<LinkedList<std::size_t>>{42U}); });

  // stack of several elements
  EXPECT_NO_THROW({ (Stack<LinkedList<std::size_t>>{42U, 69U, 666U}); });
  EXPECT_NO_THROW(
      { (Stack<LinkedList<char>>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}

TEST(TestingReadingTopValue, ReadingTopValueOfEmptyStack) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  EXPECT_EQ((Stack<ContainerType>{}).top(), ValueType{});
}

TEST(TestingReadingTopValue, ReadingTopValueOfOneNodeStacks) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  EXPECT_EQ((Stack<ContainerType>{42U}).top(), 42U);
  EXPECT_EQ((Stack<ContainerType>{69U}).top(), 69U);
  EXPECT_EQ((Stack<ContainerType>{666U}).top(), 666U);
}

TEST(TestingReadingTopValue, ReadingTopValueOfArbitrarySizesOfStacks) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  EXPECT_EQ((Stack<ContainerType>{42U, 69U, 666U}).top(), 666U);
  EXPECT_EQ((Stack<ContainerType>{666U, 42U, 69U}).top(), 69U);
  EXPECT_EQ((Stack<ContainerType>{69U, 666U, 42U}).top(), 42U);

  EXPECT_EQ((Stack<ContainerType>{1U, 2U, 3U, 4U}).top(), 4U);
  EXPECT_EQ((Stack<ContainerType>{1U, 2U, 3U, 4U, 5U}).top(), 5U);
  EXPECT_EQ((Stack<ContainerType>{1U, 2U, 3U, 4U, 5U, 6U}).top(), 6U);
}

TEST(TestingIsEmpty, CheckingIsEmptyOfArbitrarySizesOfStacks) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  // empty stack
  EXPECT_TRUE((Stack<ContainerType>{}).isEmpty());

  // one element stack
  EXPECT_FALSE((Stack<ContainerType>{42U}).isEmpty());
  EXPECT_FALSE((Stack<ContainerType>{69U}).isEmpty());
  EXPECT_FALSE((Stack<ContainerType>{666U}).isEmpty());

  // three elements stack
  EXPECT_FALSE((Stack<ContainerType>{666U, 42U, 69U}).isEmpty());
  EXPECT_FALSE((Stack<ContainerType>{69U, 666U, 42U}).isEmpty());

  // four and five elements stack
  EXPECT_FALSE((Stack<ContainerType>{1U, 2U, 3U, 4U}).isEmpty());
  EXPECT_FALSE((Stack<ContainerType>{1U, 2U, 3U, 4U, 5U}).isEmpty());
}

TEST(TestingSize, CheckingSizesOfArbitrarySizesOfStacks) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  // empty stack
  EXPECT_EQ((Stack<ContainerType>{}).size(), 0U);

  // one element stack
  EXPECT_EQ((Stack<ContainerType>{42U}).size(), 1U);
  EXPECT_EQ((Stack<ContainerType>{69U}).size(), 1U);
  EXPECT_EQ((Stack<ContainerType>{666U}).size(), 1U);

  // three elements stack
  EXPECT_EQ((Stack<ContainerType>{666U, 42U, 69U}).size(), 3U);
  EXPECT_EQ((Stack<ContainerType>{69U, 666U, 42U}).size(), 3U);

  // four and five elements stack
  EXPECT_EQ((Stack<ContainerType>{1U, 2U, 3U, 4U}).size(), 4U);
  EXPECT_EQ((Stack<ContainerType>{1U, 2U, 3U, 4U, 5U}).size(), 5U);
}

TEST(TestingPushOnly, CheckingPushToStackBehavior) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  Stack<ContainerType> stack;

  EXPECT_EQ(stack.size(), 0U);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.top(), ValueType{});

  EXPECT_NO_THROW({ stack.push(1U); });
  EXPECT_EQ(stack.size(), 1U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 1U);

  EXPECT_NO_THROW({ stack.push(2U); });
  EXPECT_EQ(stack.size(), 2U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 2U);

  EXPECT_NO_THROW({ stack.push(3U); });
  EXPECT_EQ(stack.size(), 3U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 3U);

  EXPECT_NO_THROW({ stack.push(4U); });
  EXPECT_EQ(stack.size(), 4U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 4U);

  EXPECT_NO_THROW({ stack.push(5U); });
  EXPECT_EQ(stack.size(), 5U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 5U);
}

TEST(TestingPopOnly, PoppingEmptyStack) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  Stack<ContainerType> stack;

  EXPECT_EQ(stack.size(), 0U);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.top(), ValueType{});

  EXPECT_EQ(stack.pop(), ValueType{});

  EXPECT_EQ(stack.size(), 0U);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.top(), ValueType{});
}

TEST(TestingPopOnly, PoppingNonEmptyStack) {
  using ValueType = std::size_t;
  using ContainerType = LinkedList<ValueType>;

  Stack<ContainerType> stack{1U, 2U, 3U, 4U, 5U};

  EXPECT_EQ(stack.size(), 5U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 5U);

  EXPECT_EQ(stack.pop(), 5U);

  EXPECT_EQ(stack.size(), 4U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 4U);

  EXPECT_EQ(stack.pop(), 4U);

  EXPECT_EQ(stack.size(), 3U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 3U);

  EXPECT_EQ(stack.pop(), 3U);

  EXPECT_EQ(stack.size(), 2U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 2U);

  EXPECT_EQ(stack.pop(), 2U);

  EXPECT_EQ(stack.size(), 1U);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.top(), 1U);

  EXPECT_EQ(stack.pop(), 1U);

  EXPECT_EQ(stack.size(), 0U);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.top(), ValueType{});

  EXPECT_EQ(stack.pop(), ValueType{});

  EXPECT_EQ(stack.size(), 0U);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.top(), ValueType{});
}

}  // namespace data_structures_test::stack_test
