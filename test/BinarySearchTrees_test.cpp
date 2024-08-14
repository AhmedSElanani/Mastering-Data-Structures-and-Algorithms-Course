#include "data-structures/Trees.hpp"
#include "gtest/gtest.h"

/// @brief namespace for trees_test tests
namespace data_structures_test::trees_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingCompleteBinarySearchTree) {
  // empty BTree
  EXPECT_NO_THROW({ (BinarySearchTree<std::size_t>{}); });

  // BTree of one node
  EXPECT_NO_THROW({ (BinarySearchTree<std::size_t>{42U}); });

  // BTree of several nodes
  EXPECT_NO_THROW({ (BinarySearchTree<std::size_t>{42U, 69U, 133U}); });
  EXPECT_NO_THROW(
      { (BinarySearchTree<char>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}


}  // namespace data_structures_test::trees_test
