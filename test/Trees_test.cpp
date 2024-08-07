#include "data-structures/Trees.hpp"

#include "gtest/gtest.h"

/// @brief namespace for trees_test tests
namespace data_structures_test::trees_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingBinaryTree) {
  // empty BTree
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{}); });

  // BTree of one node
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U}); });

  // BTree of several nodes
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U, 69U, 133U}); });
  EXPECT_NO_THROW(
      { (BinaryTree<char>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}

TEST(TestingTraversals, TraversingPreOrderOfBinaryTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinaryTree<ValueType>{}).traversePreOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'x'}).traversePreOrder(),
            std::vector<ValueType>{'x'});

  // multi-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
                .traversePreOrder(),
            (std::vector<ValueType>{'D', 'E', 'D', 'F', 'B', 'A', 'E', 'E'}));

  // custom constructed tree
  // TODO
}

TEST(TestingTraversals, TraversingPostOrderOfBinaryTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinaryTree<ValueType>{}).traversePostOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'x'}).traversePostOrder(),
            std::vector<ValueType>{'x'});

  // multi-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
                .traversePostOrder(),
            (std::vector<ValueType>{'F', 'D', 'B', 'E', 'E', 'E', 'A', 'D'}));

  // custom constructed tree
  // TODO
}

TEST(TestingTraversals, TraversingInOrderOfBinaryTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinaryTree<ValueType>{}).traverseInOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'x'}).traverseInOrder(),
            std::vector<ValueType>{'x'});

  // multi-node tree
  EXPECT_EQ((BinaryTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
                .traverseInOrder(),
            (std::vector<ValueType>{'F', 'D', 'E', 'B', 'D', 'E', 'A', 'E'}));

  // custom constructed tree
  // TODO
}

TEST(TestingTraversals, TraversingLevelOrderOfBinaryTree) {
  using ValueType = std::size_t;

  // empty tree
  EXPECT_EQ((BinaryTree<ValueType>{}).traverseLevelOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinaryTree<ValueType>{42U}).traverseLevelOrder(),
            std::vector<ValueType>{42U});

  // multi-node tree
  EXPECT_EQ(
      (BinaryTree<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U,
                             11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U})
          .traverseLevelOrder(),
      (std::vector<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,
                              8U,  9U,  10U, 11U, 12U, 13U, 14U,
                              15U, 16U, 17U, 18U, 19U, 20U}));

  // custom constructed tree
  // TODO
}

}  // namespace data_structures_test::trees_test
