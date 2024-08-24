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

TEST(TestingEqualityOperator, CompareSeveralBinarySearchTrees) {
  using ValueType = char;

  // comparing empty BSTs
  EXPECT_EQ((BinarySearchTree<ValueType>{}), (BinarySearchTree<ValueType>{}));

  // non-empty BST group 1
  EXPECT_EQ((BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'}),
            (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'}));
  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}),
      (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}));

  EXPECT_NE(
      (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                   'J'}),
      (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}));

  // non-empty BST group 2
  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'}),
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'}));
  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}),
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}));

  EXPECT_NE(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'}),
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}));

  // non-empty BST group 3
  EXPECT_EQ((BinarySearchTree<ValueType>{'S', 'T', 'E', 'V', 'E', 'N'}),
            (BinarySearchTree<ValueType>{'S', 'T', 'E', 'V', 'E', 'N'}));

  EXPECT_EQ((BinarySearchTree<ValueType>{'B', 'A', 'R', 'T', 'L', 'E', 'T'}),
            (BinarySearchTree<ValueType>{'B', 'A', 'R', 'T', 'L', 'E', 'T'}));

  EXPECT_NE((BinarySearchTree<ValueType>{'S', 'T', 'E', 'V', 'E', 'N'}),
            (BinarySearchTree<ValueType>{'B', 'A', 'R', 'T', 'L', 'E', 'T'}));
}

TEST(TestingInsertion, InsertNewValuesToBinarySearchTree) {
  using ValueType = char;

  //  start from empty tree
  BinarySearchTree<ValueType> emptyTree{};

  EXPECT_TRUE(emptyTree.insertNode('A'));
  EXPECT_TRUE(emptyTree.insertNode('B'));
  EXPECT_TRUE(emptyTree.insertNode('C'));

  EXPECT_EQ(emptyTree, (BinarySearchTree<ValueType>{'A', 'B', 'C'}));

  //  start from non-empty tree
  BinarySearchTree<ValueType> nonEmptyTree{'A', 'B', 'C', 'D'};

  EXPECT_TRUE(nonEmptyTree.insertNode('E'));
  EXPECT_TRUE(nonEmptyTree.insertNode('F'));
  EXPECT_TRUE(nonEmptyTree.insertNode('G'));
  EXPECT_TRUE(nonEmptyTree.insertNode('H'));

  EXPECT_EQ(nonEmptyTree, (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E',
                                                       'F', 'G', 'H'}));
}

TEST(TestingInsertion, InsertDuplicateValuesToBinarySearchTree) {
  using ValueType = char;

  //  start from empty tree
  BinarySearchTree<ValueType> emptyTree{};

  EXPECT_TRUE(emptyTree.insertNode('A'));
  EXPECT_FALSE(emptyTree.insertNode('A'));
  EXPECT_FALSE(emptyTree.insertNode('A'));

  EXPECT_EQ(emptyTree, (BinarySearchTree<ValueType>{'A'}));

  //  start from non-empty tree
  BinarySearchTree<ValueType> nonEmptyTree{'A', 'B', 'C', 'D'};

  EXPECT_FALSE(nonEmptyTree.insertNode('C'));
  EXPECT_FALSE(nonEmptyTree.insertNode('D'));
  EXPECT_TRUE(nonEmptyTree.insertNode('E'));
  EXPECT_TRUE(nonEmptyTree.insertNode('F'));

  EXPECT_EQ(nonEmptyTree,
            (BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F'}));
}

TEST(TestingTraversals, TraversingPreOrderOfBinarySearchTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinarySearchTree<ValueType>{}).traversePreOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinarySearchTree<ValueType>{'x'}).traversePreOrder(),
            std::vector<ValueType>{'x'});

  // multi-node trees
  EXPECT_EQ((BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'})
                .traversePreOrder(),
            (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'J'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
          .traversePreOrder(),
      (std::vector<ValueType>{'D', 'A', 'B', 'E', 'F'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'})
          .traversePreOrder(),
      (std::vector<ValueType>{'B', 'A', 'I', 'E', 'C', 'H', 'N', 'R', 'S',
                              'T'}));
}

TEST(TestingTraversals, TraversingPostOrderOfBinarySearchTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinarySearchTree<ValueType>{}).traversePostOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinarySearchTree<ValueType>{'x'}).traversePostOrder(),
            std::vector<ValueType>{'x'});

  // multi-node trees
  EXPECT_EQ((BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'})
                .traversePostOrder(),
            (std::vector<ValueType>{'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B',
                                    'A'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
          .traversePostOrder(),
      (std::vector<ValueType>{'B', 'A', 'F', 'E', 'D'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'})
          .traversePostOrder(),
      (std::vector<ValueType>{'A', 'C', 'H', 'E', 'T', 'S', 'R', 'N', 'I',
                              'B'}));
}

TEST(TestingTraversals, TraversingInOrderOfBinarySearchTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinarySearchTree<ValueType>{}).traverseInOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinarySearchTree<ValueType>{'x'}).traverseInOrder(),
            std::vector<ValueType>{'x'});

  // multi-node trees
  EXPECT_EQ((BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'})
                .traverseInOrder(),
            (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'J'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
          .traverseInOrder(),
      (std::vector<ValueType>{'A', 'B', 'D', 'E', 'F'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'})
          .traverseInOrder(),
      (std::vector<ValueType>{'A', 'B', 'C', 'E', 'H', 'I', 'N', 'R', 'S',
                              'T'}));
}

TEST(TestingTraversals, TraversingLevelOrderOfBinarySearchTree) {
  using ValueType = char;

  // empty tree
  EXPECT_EQ((BinarySearchTree<ValueType>{}).traverseLevelOrder(),
            std::vector<ValueType>{});

  // one-node tree
  EXPECT_EQ((BinarySearchTree<ValueType>{42U}).traverseLevelOrder(),
            std::vector<ValueType>{42U});

  // multi-node trees
  EXPECT_EQ((BinarySearchTree<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J'})
                .traverseLevelOrder(),
            (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'J'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'})
          .traverseLevelOrder(),
      (std::vector<ValueType>{'D', 'A', 'E', 'B', 'F'}));

  EXPECT_EQ(
      (BinarySearchTree<ValueType>{'B', 'I', 'N', 'A', 'R', 'S', 'E', 'A', 'R',
                                   'C', 'H', 'T', 'R', 'E', 'E', 'S'})
          .traverseLevelOrder(),
      (std::vector<ValueType>{'B', 'A', 'I', 'E', 'N', 'C', 'H', 'R', 'S',
                              'T'}));
}

}  // namespace data_structures_test::trees_test
