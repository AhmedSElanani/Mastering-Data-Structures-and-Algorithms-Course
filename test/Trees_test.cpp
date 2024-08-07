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

TEST(TestingDisplay, DisplayEmptyTree) {
  using ValueType = std::size_t;
  using traversalOrder = BinaryTree<ValueType>::traversalOrder;

  EXPECT_STREQ(
      (BinaryTree<ValueType>{}).display(traversalOrder::preOrder).c_str(),
      "{}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{}).display(traversalOrder::inOrder).c_str(), "{}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{}).display(traversalOrder::postOrder).c_str(),
      "{}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{}).display(traversalOrder::levelOrder).c_str(),
      "{}");
}

TEST(TestingDisplay, DisplaySingleNodeTree) {
  using ValueType = std::size_t;
  using traversalOrder = BinaryTree<ValueType>::traversalOrder;

  EXPECT_STREQ(
      (BinaryTree<ValueType>{69U}).display(traversalOrder::preOrder).c_str(),
      "{69}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{69U}).display(traversalOrder::inOrder).c_str(),
      "{69}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{69U}).display(traversalOrder::postOrder).c_str(),
      "{69}");
  EXPECT_STREQ(
      (BinaryTree<ValueType>{69U}).display(traversalOrder::levelOrder).c_str(),
      "{69}");
}

TEST(TestingDisplay, DisplayMultiNodeTree) {
  using ValueType = std::size_t;
  using traversalOrder = BinaryTree<ValueType>::traversalOrder;

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U,
                             11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U})
          .display(traversalOrder::preOrder)
          .c_str(),
      "{1,2,4,8,16,17,9,18,19,5,10,20,11,3,6,12,13,7,14,15}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U,
                             11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U})
          .display(traversalOrder::inOrder)
          .c_str(),
      "{16,8,17,4,18,9,19,2,20,10,5,11,1,12,6,13,3,14,7,15}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U,
                             11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U})
          .display(traversalOrder::postOrder)
          .c_str(),
      "{16,17,8,18,19,9,4,20,10,11,5,2,12,13,6,14,15,7,3,1}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U,
                             11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U})
          .display(traversalOrder::levelOrder)
          .c_str(),
      "{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}");
}

TEST(TestingDisplay, DisplayCustomConstructedTree) {
  // TODO
}

}  // namespace data_structures_test::trees_test
