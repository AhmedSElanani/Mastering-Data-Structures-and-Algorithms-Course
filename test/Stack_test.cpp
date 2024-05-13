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

}  // namespace data_structures_test::stack_test
