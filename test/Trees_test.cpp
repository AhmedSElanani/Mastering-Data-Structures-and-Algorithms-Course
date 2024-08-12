#include "data-structures/Trees.hpp"

#include "gtest/gtest.h"

/// @brief namespace for trees_test tests
namespace data_structures_test::trees_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingCompleteBinaryTree) {
  // empty BTree
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{}); });

  // BTree of one node
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U}); });

  // BTree of several nodes
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U, 69U, 133U}); });
  EXPECT_NO_THROW(
      { (BinaryTree<char>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}

TEST(TestingConstruction, ConstructingInCompleteBinaryTree) {
  // empty BTree
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{std::nullopt}); });
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{std::nullopt, 1U, 2U, 3U}); });

  // BTree of one node
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U, std::nullopt}); });
  EXPECT_NO_THROW(
      { (BinaryTree<std::size_t>{42U, std::nullopt, std::nullopt}); });
  EXPECT_NO_THROW({
    (BinaryTree<std::size_t>{
        42U,
        std::nullopt,
        std::nullopt,
    });
  });

  // BTree of several nodes
  EXPECT_NO_THROW({ (BinaryTree<std::size_t>{42U, std::nullopt, 69U, 133U}); });
  EXPECT_NO_THROW({
    (BinaryTree<std::size_t>{42U, std::nullopt, 69U, std::nullopt, std::nullopt,
                             133U});
  });
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

  // custom constructed trees
  EXPECT_EQ((BinaryTree<ValueType>{'A', 'B', std::nullopt, std::nullopt, 'C',
                                   'D', 'E', std::nullopt})
                .traversePreOrder(),
            (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E'}));

  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', 'B', 'C', std::nullopt, std::nullopt, 'D',
                             'E', std::nullopt, std::nullopt, std::nullopt,
                             std::nullopt, 'F', 'G', 'H', 'I'})
          .traversePreOrder(),
      (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E'}));
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

  // custom constructed trees
  EXPECT_EQ((BinaryTree<ValueType>{'A', std::nullopt, 'B', std::nullopt, 'C',
                                   'D', 'E', std::nullopt})
                .traversePostOrder(),
            (std::vector<ValueType>{'D', 'E', 'C', 'B', 'A'}));

  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', std::nullopt, 'B', std::nullopt, 'C',
                             std::nullopt, 'D', std::nullopt, 'E', std::nullopt,
                             'F', std::nullopt, 'G', std::nullopt, 'H',
                             std::nullopt, 'I'})
          .traversePostOrder(),
      (std::vector<ValueType>{'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'}));

  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', 'B', std::nullopt, 'C', std::nullopt, 'D',
                             std::nullopt, 'E', std::nullopt, 'F', std::nullopt,
                             'G', std::nullopt, 'H', std::nullopt, 'I',
                             std::nullopt})
          .traversePostOrder(),
      (std::vector<ValueType>{'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'}));
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
  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', 'B', 'C', std::nullopt, 'D', std::nullopt,
                             'E', std::nullopt, std::nullopt, 'F', 'G'})
          .traverseInOrder(),
      (std::vector<ValueType>{'B', 'D', 'A', 'C', 'F', 'E', 'G'}));
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

  // custom constructed trees
  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', std::nullopt, 'B', std::nullopt, 'C',
                             std::nullopt, 'D', std::nullopt, 'E', std::nullopt,
                             'F', std::nullopt, 'G', std::nullopt, 'H',
                             std::nullopt, 'I'})
          .traverseLevelOrder(),
      (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}));

  EXPECT_EQ(
      (BinaryTree<ValueType>{'A', 'B', std::nullopt, 'C', std::nullopt, 'D',
                             std::nullopt, 'E', std::nullopt, 'F', std::nullopt,
                             'G', std::nullopt, 'H', std::nullopt, 'I',
                             std::nullopt})
          .traverseLevelOrder(),
      (std::vector<ValueType>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}));
}

TEST(TestingCount, CountNodesinEmptyBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> emptyTree1{};
  EXPECT_EQ(emptyTree1.count(), 0U);

  BinaryTree<ValueType> emptyTree2{std::nullopt, 1U, 2U, 3U};
  EXPECT_EQ(emptyTree2.count(), 0U);
}

TEST(TestingCount, CountNodesinSingleNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> singleNodeTree1{42U};
  EXPECT_EQ(singleNodeTree1.count(), 1U);

  BinaryTree<ValueType> singleNodeTree2{69U, std::nullopt, std::nullopt,
                                        1U,  2U,           3U};
  EXPECT_EQ(singleNodeTree2.count(), 1U);
}

TEST(TestingCount, CountNodesinMultiNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> multiNodeTree1{1U, 2U, 3U, 4U, 5U, 6U};
  EXPECT_EQ(multiNodeTree1.count(), 6U);

  BinaryTree<ValueType> multiNodeTree2{
      1U,           2U, 3U, std::nullopt, 4U, std::nullopt,
      std::nullopt, 5U, 6U, std::nullopt, 7U, 8U};
  EXPECT_EQ(multiNodeTree2.count(), 8U);

  BinaryTree<ValueType> multiNodeTree3{1U,           2U,
                                       3U,           std::nullopt,
                                       4U,           std::nullopt,
                                       std::nullopt, std::nullopt,
                                       std::nullopt, 5U,
                                       6U,           std::nullopt,
                                       7U,           8U};
  EXPECT_EQ(multiNodeTree3.count(), 4U);
}

TEST(TestingCountLeafNodes, CountLeafNodesinEmptyBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> emptyTree1{};
  EXPECT_EQ(emptyTree1.countLeafNodes(), 0U);

  BinaryTree<ValueType> emptyTree2{std::nullopt, 1U, 2U, 3U};
  EXPECT_EQ(emptyTree2.countLeafNodes(), 0U);
}

TEST(TestingCountLeafNodes, CountLeafNodesinSingleNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> singleNodeTree1{42U};
  EXPECT_EQ(singleNodeTree1.countLeafNodes(), 1U);

  BinaryTree<ValueType> singleNodeTree2{69U, std::nullopt, std::nullopt,
                                        1U,  2U,           3U};
  EXPECT_EQ(singleNodeTree2.countLeafNodes(), 1U);
}

TEST(TestingCountLeafNodes, CountLeafNodesinMultiNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> multiNodeTree1{1U, 2U, 3U, 4U, 5U, 6U};
  EXPECT_EQ(multiNodeTree1.countLeafNodes(), 3U);

  BinaryTree<ValueType> multiNodeTree2{
      1U,           2U, 3U, std::nullopt, 4U, std::nullopt,
      std::nullopt, 5U, 6U, std::nullopt, 7U, 8U};
  EXPECT_EQ(multiNodeTree2.countLeafNodes(), 3U);

  BinaryTree<ValueType> multiNodeTree3{1U,           2U,
                                       3U,           std::nullopt,
                                       4U,           std::nullopt,
                                       std::nullopt, std::nullopt,
                                       std::nullopt, 5U,
                                       6U,           std::nullopt,
                                       7U,           8U};
  EXPECT_EQ(multiNodeTree3.countLeafNodes(), 2U);
}

TEST(TestingHeight, HeightOfNodesinEmptyBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> emptyTree1{};
  EXPECT_EQ(emptyTree1.height(), std::numeric_limits<std::size_t>::max());

  BinaryTree<ValueType> emptyTree2{std::nullopt, 1U, 2U, 3U};
  EXPECT_EQ(emptyTree2.height(), std::numeric_limits<std::size_t>::max());
}

TEST(TestingHeight, HeightOfNodesinSingleNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> singleNodeTree1{42U};
  EXPECT_EQ(singleNodeTree1.height(), 0U);

  BinaryTree<ValueType> singleNodeTree2{69U, std::nullopt, std::nullopt,
                                        1U,  2U,           3U};
  EXPECT_EQ(singleNodeTree2.height(), 0U);
}

TEST(TestingHeight, HeightOfNodesinMultiNodeBinaryTrees) {
  using ValueType = std::size_t;

  BinaryTree<ValueType> multiNodeTree1{1U, 2U, 3U, 4U, 5U, 6U};
  EXPECT_EQ(multiNodeTree1.height(), 2U);

  BinaryTree<ValueType> multiNodeTree2{
      1U,           2U, 3U, std::nullopt, 4U, std::nullopt,
      std::nullopt, 5U, 6U, std::nullopt, 7U, 8U};
  EXPECT_EQ(multiNodeTree2.height(), 4U);

  BinaryTree<ValueType> multiNodeTree3{1U,           2U,
                                       3U,           std::nullopt,
                                       4U,           std::nullopt,
                                       std::nullopt, std::nullopt,
                                       std::nullopt, 5U,
                                       6U,           std::nullopt,
                                       7U,           8U};
  EXPECT_EQ(multiNodeTree3.height(), 2U);
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
  using ValueType = std::size_t;
  using traversalOrder = BinaryTree<ValueType>::traversalOrder;

  // empty BTree
  EXPECT_STREQ((BinaryTree<ValueType>{std::nullopt, 1U, 2U, 3U})
                   .display(traversalOrder::preOrder)
                   .c_str(),
               "{}");
  EXPECT_STREQ((BinaryTree<ValueType>{std::nullopt, 1U, 2U, 3U})
                   .display(traversalOrder::inOrder)
                   .c_str(),
               "{}");
  EXPECT_STREQ((BinaryTree<ValueType>{std::nullopt, 1U, 2U, 3U})
                   .display(traversalOrder::postOrder)
                   .c_str(),
               "{}");
  EXPECT_STREQ((BinaryTree<ValueType>{std::nullopt, 1U, 2U, 3U})
                   .display(traversalOrder::levelOrder)
                   .c_str(),
               "{}");

  // BTree of one node
  EXPECT_STREQ((BinaryTree<ValueType>{1U, std::nullopt, std::nullopt, 2U, 3U})
                   .display(traversalOrder::preOrder)
                   .c_str(),
               "{1}");
  EXPECT_STREQ((BinaryTree<ValueType>{1U, std::nullopt, std::nullopt, 2U, 3U})
                   .display(traversalOrder::inOrder)
                   .c_str(),
               "{1}");
  EXPECT_STREQ((BinaryTree<ValueType>{1U, std::nullopt, std::nullopt, 2U, 3U})
                   .display(traversalOrder::postOrder)
                   .c_str(),
               "{1}");
  EXPECT_STREQ((BinaryTree<ValueType>{1U, std::nullopt, std::nullopt, 2U, 3U})
                   .display(traversalOrder::levelOrder)
                   .c_str(),
               "{1}");

  // BTree of several nodes
  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U, 2U, 3U, std::nullopt, 4U, std::nullopt, 5U,
                             std::nullopt, std::nullopt, 6U, 7U, std::nullopt,
                             std::nullopt, std::nullopt, std::nullopt, 8U})
          .display(traversalOrder::preOrder)
          .c_str(),
      "{1,2,4,3,5,6,7}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U, 2U, 3U, std::nullopt, 4U, std::nullopt, 5U,
                             std::nullopt, std::nullopt, 6U, 7U, std::nullopt,
                             std::nullopt, std::nullopt, std::nullopt, 8U})
          .display(traversalOrder::inOrder)
          .c_str(),
      "{2,4,1,3,6,5,7}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U, 2U, 3U, std::nullopt, 4U, std::nullopt, 5U,
                             std::nullopt, std::nullopt, 6U, 7U, std::nullopt,
                             std::nullopt, std::nullopt, std::nullopt, 8U})
          .display(traversalOrder::postOrder)
          .c_str(),
      "{4,2,6,7,5,3,1}");

  EXPECT_STREQ(
      (BinaryTree<ValueType>{1U, 2U, 3U, std::nullopt, 4U, std::nullopt, 5U,
                             std::nullopt, std::nullopt, 6U, 7U, std::nullopt,
                             std::nullopt, std::nullopt, std::nullopt, 8U})
          .display(traversalOrder::levelOrder)
          .c_str(),
      "{1,2,3,4,5,6,7}");
}

}  // namespace data_structures_test::trees_test
