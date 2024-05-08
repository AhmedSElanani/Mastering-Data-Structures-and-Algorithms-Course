#include "data-structures/LinkedList.hpp"

#include "gtest/gtest.h"

/// @brief
namespace data_structures_test::linkedList_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingLinkedLists) {
  // empty LL
  EXPECT_NO_THROW({ (LinkedList<std::size_t>{}); });

  // LL of one node
  EXPECT_NO_THROW({ (LinkedList<std::size_t>{42U}); });

  // LL of several nodes
  EXPECT_NO_THROW({ (LinkedList<std::size_t>{42U, 69U, 133U}); });
  EXPECT_NO_THROW(
      { (LinkedList<char>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}

TEST(TestingSearch, SearchingEmptyLinkedLists) {
  LinkedList<std::size_t> const emptyLl1{};
  EXPECT_EQ(emptyLl1.search(0U), emptyLl1.cend());

  LinkedList<std::size_t> const emptyLl2{};
  EXPECT_EQ(emptyLl2.search(1U), emptyLl2.cend());

  LinkedList<std::size_t> const emptyLl3{};
  EXPECT_EQ(emptyLl3.search(2U), emptyLl3.cend());
}

TEST(TestingSearch, SearchingLinkedListsForNonExistingValues) {
  LinkedList<std::size_t> const nonEmptyLl1{1U};
  EXPECT_EQ(nonEmptyLl1.search(42U), nonEmptyLl1.cend());

  LinkedList<std::size_t> const nonEmptyLl2{1U, 2U};
  EXPECT_EQ(nonEmptyLl2.search(69U), nonEmptyLl2.cend());

  LinkedList<std::size_t> const nonEmptyLl3{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl3.search(666U), nonEmptyLl3.cend());
}

TEST(TestingSearch, SearchingLinkedListsForExistingValues) {
  EXPECT_EQ((LinkedList<std::size_t>{1U}).search(1U)->value(), 1U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).search(1U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).search(2U)->value(), 2U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(1U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(2U)->value(), 2U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(3U)->value(), 3U);
}

TEST(TestingEnhancedSearch, SearchingEmptyLinkedLists) {
  LinkedList<std::size_t> emptyLl1{};
  EXPECT_EQ(emptyLl1.enhancedSearch(0U), emptyLl1.end());

  LinkedList<std::size_t> emptyLl2{};
  EXPECT_EQ(emptyLl2.enhancedSearch(1U), emptyLl2.end());

  LinkedList<std::size_t> emptyLl3{};
  EXPECT_EQ(emptyLl3.enhancedSearch(2U), emptyLl3.end());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForNonExistingValues) {
  LinkedList<std::size_t> nonEmptyLl1{1U};
  EXPECT_EQ(nonEmptyLl1.enhancedSearch(42U), nonEmptyLl1.end());

  LinkedList<std::size_t> nonEmptyLl2{1U, 2U};
  EXPECT_EQ(nonEmptyLl2.enhancedSearch(69U), nonEmptyLl2.end());

  LinkedList<std::size_t> nonEmptyLl3{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl3.enhancedSearch(666U), nonEmptyLl3.end());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesOneNode) {
  LinkedList<std::size_t> nonEmptyLl{1U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesTwoNodes) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 2U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesThreeNodes) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 1U, 3U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{3U, 2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesFourNodes) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 1U, 3U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{3U, 2U, 1U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(4U)->value(), 4U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{4U, 3U, 2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesFiveNodes) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 1U, 3U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{3U, 2U, 1U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(4U)->value(), 4U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{4U, 3U, 2U, 1U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(5U)->value(), 5U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{5U, 4U, 3U, 2U, 1U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesAtInvalidPositions) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};
  const std::size_t currentListLength{nonEmptyLl.getLength()};

  EXPECT_FALSE(nonEmptyLl.insertAt(42U, currentListLength + 1U));
  EXPECT_FALSE(nonEmptyLl.insertAt(42U, currentListLength + 2U));
  EXPECT_FALSE(nonEmptyLl.insertAt(42U, currentListLength + 3U));

  // confirm linked list wasn't modified
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 5U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesNearHead) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{3U, 4U, 5U};
  EXPECT_TRUE(nonEmptyLl.insertAt(1U, 0U));

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 4U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 3U, 4U, 5U}).display().c_str());

  EXPECT_TRUE(nonEmptyLl.insertAt(2U, 1U));

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 5U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesNearTail) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U};

  // insert at the end of the list
  EXPECT_TRUE(nonEmptyLl.insertAt(3U, nonEmptyLl.getLength()));
  EXPECT_TRUE(nonEmptyLl.insertAt(5U, nonEmptyLl.getLength()));

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 4U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 5U}).display().c_str());

  // insert just before the tail
  EXPECT_TRUE(nonEmptyLl.insertAt(4U, 3U));

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 5U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesToEmptyLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType emptyLl{};

  // check negative scenario
  EXPECT_FALSE(emptyLl.insertAt(1U, 1U));
  EXPECT_FALSE(emptyLl.insertAt(2U, 2U));
  EXPECT_FALSE(emptyLl.insertAt(3U, 3U));

  EXPECT_TRUE(emptyLl.isEmpty());

  EXPECT_EQ(emptyLl.getHeadValue(), ValueType{});
  EXPECT_EQ(emptyLl.getTailValue(), ValueType{});
  EXPECT_EQ(emptyLl.getLength(), 0U);

  EXPECT_STREQ(emptyLl.display().c_str(), (LinkedListType{}).display().c_str());

  // check positive scenario
  EXPECT_TRUE(emptyLl.insertAt(1U, 0U));
  EXPECT_TRUE(emptyLl.insertAt(2U, 1U));
  EXPECT_TRUE(emptyLl.insertAt(3U, 2U));

  EXPECT_FALSE(emptyLl.isEmpty());

  EXPECT_EQ(emptyLl.getHeadValue(), 1U);
  EXPECT_EQ(emptyLl.getTailValue(), 3U);
  EXPECT_EQ(emptyLl.getLength(), 3U);

  EXPECT_STREQ(emptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesToOneNodeLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType oneNodeLl{1U};

  // check negative scenario
  EXPECT_FALSE(oneNodeLl.insertAt(2U, 3U));
  EXPECT_FALSE(oneNodeLl.insertAt(3U, 4U));
  EXPECT_FALSE(oneNodeLl.insertAt(4U, 5U));

  EXPECT_EQ(oneNodeLl.getHeadValue(), 1U);
  EXPECT_EQ(oneNodeLl.getTailValue(), 1U);
  EXPECT_EQ(oneNodeLl.getLength(), 1U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{1U}).display().c_str());

  // check positive scenario
  EXPECT_TRUE(oneNodeLl.insertAt(2U, 1U));
  EXPECT_TRUE(oneNodeLl.insertAt(3U, 2U));
  EXPECT_TRUE(oneNodeLl.insertAt(4U, 3U));

  EXPECT_EQ(oneNodeLl.getHeadValue(), 1U);
  EXPECT_EQ(oneNodeLl.getTailValue(), 4U);
  EXPECT_EQ(oneNodeLl.getLength(), 4U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U}).display().c_str());
}

TEST(TestingInsertingNodes, InsertingNodesToHeadAndTailOnlyLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // test insertion at head
    LinkedListType headAndTailOnlyLl{2U, 3U};

    headAndTailOnlyLl.insertAt(1U, 0U);

    EXPECT_EQ(headAndTailOnlyLl.getHeadValue(), 1U);
    EXPECT_EQ(headAndTailOnlyLl.getTailValue(), 3U);
    EXPECT_EQ(headAndTailOnlyLl.getLength(), 3U);

    EXPECT_STREQ(headAndTailOnlyLl.display().c_str(),
                 (LinkedListType{1U, 2U, 3U}).display().c_str());
  }

  {
    // test insertion at tail
    LinkedListType headAndTailOnlyLl{1U, 2U};

    headAndTailOnlyLl.insertAt(3U, 2U);

    EXPECT_EQ(headAndTailOnlyLl.getHeadValue(), 1U);
    EXPECT_EQ(headAndTailOnlyLl.getTailValue(), 3U);
    EXPECT_EQ(headAndTailOnlyLl.getLength(), 3U);

    EXPECT_STREQ(headAndTailOnlyLl.display().c_str(),
                 (LinkedListType{1U, 2U, 3U}).display().c_str());
  }
}

TEST(TestingInsertingNodes, InsertingNodesInTheMiddle) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 5U, 6U};
  nonEmptyLl.insertAt(3U, 2U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 6U);
  EXPECT_EQ(nonEmptyLl.getLength(), 5U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 5U, 6U}).display().c_str());

  nonEmptyLl.insertAt(4U, 3U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 6U);
  EXPECT_EQ(nonEmptyLl.getLength(), 6U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U, 6U}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesFromEmptyLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType emptyLl{};

  for (const auto index : {0U, 1U, 2U, 3U, 4U}) {
    EXPECT_EQ(emptyLl.deleteNodeAt(index), emptyLl.end());
  }

  EXPECT_EQ(emptyLl.getHeadValue(), ValueType{});
  EXPECT_EQ(emptyLl.getTailValue(), ValueType{});
  EXPECT_EQ(emptyLl.getLength(), 0U);

  EXPECT_STREQ(emptyLl.display().c_str(), (LinkedListType{}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesAtInvalidPositions) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};
  const std::size_t currentListLength{nonEmptyLl.getLength()};

  EXPECT_EQ(nonEmptyLl.deleteNodeAt(currentListLength), nonEmptyLl.end());
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(currentListLength + 1U), nonEmptyLl.end());
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(currentListLength + 2U), nonEmptyLl.end());

  // confirm linked list wasn't modified
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 5U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U, 4U, 5U}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesNearHead) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};

  // remove head node
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(0U)->value(), 1U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 4U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 3U, 4U, 5U}).display().c_str());

  // remove head's next node
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(1U)->value(), 3U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 3U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{2U, 4U, 5U}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesNearTail) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U};

  // delete the tail node
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(3U)->value(), 4U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getLength(), 3U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 3U}).display().c_str());

  // delete the node just before the tail
  EXPECT_EQ(nonEmptyLl.deleteNodeAt(1U)->value(), 2U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getLength(), 2U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 3U}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesFromOneNodeLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType oneNodeLl{42U};

  // delete the only node the exists
  EXPECT_EQ(oneNodeLl.deleteNodeAt(0U)->value(), 42U);

  EXPECT_EQ(oneNodeLl.getHeadValue(), ValueType{});
  EXPECT_EQ(oneNodeLl.getTailValue(), ValueType{});
  EXPECT_EQ(oneNodeLl.getLength(), 0U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{}).display().c_str());

  // try one mode time after deletion (It should behave as an empty list)
  EXPECT_EQ(oneNodeLl.deleteNodeAt(0U), oneNodeLl.end());

  EXPECT_EQ(oneNodeLl.getHeadValue(), ValueType{});
  EXPECT_EQ(oneNodeLl.getTailValue(), ValueType{});
  EXPECT_EQ(oneNodeLl.getLength(), 0U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{}).display().c_str());
}

TEST(TestingDeletingNodes, DeletingNodesFromHeadAndTailOnlyLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // test deletion of head
    LinkedListType nonEmptyLl{42U, 69U};

    EXPECT_EQ(nonEmptyLl.deleteNodeAt(0)->value(), 42U);

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 69U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 69U);
    EXPECT_EQ(nonEmptyLl.getLength(), 1U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{69U}).display().c_str());
  }

  {
    // test deletion of tail
    LinkedListType nonEmptyLl{42U, 69U};

    EXPECT_EQ(nonEmptyLl.deleteNodeAt(1)->value(), 69U);

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 42U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 42U);
    EXPECT_EQ(nonEmptyLl.getLength(), 1U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{42U}).display().c_str());
  }
}

TEST(TestingDeletingNodes, DeletingNodesFromTheMiddle) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};

  EXPECT_EQ(nonEmptyLl.deleteNodeAt(2U)->value(), 3U);

  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getLength(), 4U);

  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedListType{1U, 2U, 4U, 5U}).display().c_str());
}

TEST(TestingReversingLinkedLists, ReversingEmptyLinkedLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType emptyLl{};

  EXPECT_NO_THROW({ emptyLl.reverse(); });

  EXPECT_EQ(emptyLl.getHeadValue(), ValueType{});
  EXPECT_EQ(emptyLl.getTailValue(), ValueType{});
  EXPECT_EQ(emptyLl.getLength(), ValueType{});

  EXPECT_STREQ(emptyLl.display().c_str(), (LinkedListType{}).display().c_str());
}

TEST(TestingReversingLinkedLists, ReversingOneNodeLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType oneNodeLl{42U};

  EXPECT_NO_THROW({ oneNodeLl.reverse(); });

  EXPECT_EQ(oneNodeLl.getHeadValue(), 42U);
  EXPECT_EQ(oneNodeLl.getTailValue(), 42U);
  EXPECT_EQ(oneNodeLl.getLength(), 1U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{42U}).display().c_str());
}

TEST(TestingReversingLinkedLists, ReversingHeadAndTailOnlyLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType headAndTailLl{42U, 69U};

  EXPECT_NO_THROW({ headAndTailLl.reverse(); });

  EXPECT_EQ(headAndTailLl.getHeadValue(), 69U);
  EXPECT_EQ(headAndTailLl.getTailValue(), 42U);
  EXPECT_EQ(headAndTailLl.getLength(), 2U);

  EXPECT_STREQ(headAndTailLl.display().c_str(),
               (LinkedListType{69U, 42U}).display().c_str());
}

TEST(TestingReversingLinkedLists, ReversingArbitraryLongerLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // three nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U};

    EXPECT_NO_THROW({ nonEmptyLl.reverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 3U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{3U, 2U, 1U}).display().c_str());
  }

  {
    // four nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U, 4U};

    EXPECT_NO_THROW({ nonEmptyLl.reverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 4U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{4U, 3U, 2U, 1U}).display().c_str());
  }

  {
    // five nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};

    EXPECT_NO_THROW({ nonEmptyLl.reverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 5U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 5U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{5U, 4U, 3U, 2U, 1U}).display().c_str());
  }
}

TEST(TestingReversingLinkedLists, ReversingBackAndForthLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // empty
    LinkedListType before{};
    LinkedListType after{};

    EXPECT_NO_THROW({ before.reverse(); });
    EXPECT_NO_THROW({ before.reverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // one node
    LinkedListType before{69U};
    LinkedListType after{69U};

    EXPECT_NO_THROW({ before.reverse(); });
    EXPECT_NO_THROW({ before.reverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // head and tail
    LinkedListType before{42U, 69U};
    LinkedListType after{42U, 69U};

    EXPECT_NO_THROW({ before.reverse(); });
    EXPECT_NO_THROW({ before.reverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // three nodes
    LinkedListType before{1U, 2U, 3U};
    LinkedListType after{1U, 2U, 3U};

    EXPECT_NO_THROW({ before.reverse(); });
    EXPECT_NO_THROW({ before.reverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // six nodes
    LinkedListType before{1U, 2U, 3U, 4U, 5U, 6U};
    LinkedListType after{1U, 2U, 3U, 4U, 5U, 6U};

    EXPECT_NO_THROW({ before.reverse(); });
    EXPECT_NO_THROW({ before.reverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }
}

TEST(TestingRecursiveReversingLinkedLists, RReversingEmptyLinkedLists) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  LinkedListType emptyLl{};

  EXPECT_NO_THROW({ emptyLl.rReverse(); });

  EXPECT_EQ(emptyLl.getHeadValue(), ValueType{});
  EXPECT_EQ(emptyLl.getTailValue(), ValueType{});
  EXPECT_EQ(emptyLl.getLength(), ValueType{});

  EXPECT_STREQ(emptyLl.display().c_str(), (LinkedListType{}).display().c_str());
}

TEST(TestingRecursiveReversingLinkedLists, RReversingOneNodeLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType oneNodeLl{42U};

  EXPECT_NO_THROW({ oneNodeLl.rReverse(); });

  EXPECT_EQ(oneNodeLl.getHeadValue(), 42U);
  EXPECT_EQ(oneNodeLl.getTailValue(), 42U);
  EXPECT_EQ(oneNodeLl.getLength(), 1U);

  EXPECT_STREQ(oneNodeLl.display().c_str(),
               (LinkedListType{42U}).display().c_str());
}

TEST(TestingRecursiveReversingLinkedLists,
     RecursiveReversingHeadAndTailOnlyLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  LinkedListType headAndTailLl{42U, 69U};

  EXPECT_NO_THROW({ headAndTailLl.rReverse(); });

  EXPECT_EQ(headAndTailLl.getHeadValue(), 69U);
  EXPECT_EQ(headAndTailLl.getTailValue(), 42U);
  EXPECT_EQ(headAndTailLl.getLength(), 2U);

  EXPECT_STREQ(headAndTailLl.display().c_str(),
               (LinkedListType{69U, 42U}).display().c_str());
}

TEST(TestingRecursiveReversingLinkedLists,
     RecursiveReversingArbitraryLongerLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // three nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U};

    EXPECT_NO_THROW({ nonEmptyLl.rReverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 3U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{3U, 2U, 1U}).display().c_str());
  }

  {
    // four nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U, 4U};

    EXPECT_NO_THROW({ nonEmptyLl.rReverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 4U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{4U, 3U, 2U, 1U}).display().c_str());
  }

  {
    // five nodes
    LinkedListType nonEmptyLl{1U, 2U, 3U, 4U, 5U};

    EXPECT_NO_THROW({ nonEmptyLl.rReverse(); });

    EXPECT_EQ(nonEmptyLl.getHeadValue(), 5U);
    EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
    EXPECT_EQ(nonEmptyLl.getLength(), 5U);

    EXPECT_STREQ(nonEmptyLl.display().c_str(),
                 (LinkedListType{5U, 4U, 3U, 2U, 1U}).display().c_str());
  }
}

TEST(TestingRecursiveReversingLinkedLists, RReversingBackAndForthLinkedLists) {
  using LinkedListType = LinkedList<std::size_t>;

  {
    // empty
    LinkedListType before{};
    LinkedListType after{};

    EXPECT_NO_THROW({ before.rReverse(); });
    EXPECT_NO_THROW({ before.rReverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // one node
    LinkedListType before{69U};
    LinkedListType after{69U};

    EXPECT_NO_THROW({ before.rReverse(); });
    EXPECT_NO_THROW({ before.rReverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // head and tail
    LinkedListType before{42U, 69U};
    LinkedListType after{42U, 69U};

    EXPECT_NO_THROW({ before.rReverse(); });
    EXPECT_NO_THROW({ before.rReverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // three nodes
    LinkedListType before{1U, 2U, 3U};
    LinkedListType after{1U, 2U, 3U};

    EXPECT_NO_THROW({ before.rReverse(); });
    EXPECT_NO_THROW({ before.rReverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }

  {
    // six nodes
    LinkedListType before{1U, 2U, 3U, 4U, 5U, 6U};
    LinkedListType after{1U, 2U, 3U, 4U, 5U, 6U};

    EXPECT_NO_THROW({ before.rReverse(); });
    EXPECT_NO_THROW({ before.rReverse(); });

    EXPECT_EQ(before.getHeadValue(), after.getHeadValue());
    EXPECT_EQ(before.getTailValue(), after.getTailValue());
    EXPECT_EQ(before.getLength(), after.getLength());

    EXPECT_STREQ(before.display().c_str(), after.display().c_str());
  }
}

TEST(TestingIndexingNodes, ReadingNodesValuesAtWithinBoundsIndex) {
  EXPECT_EQ((LinkedList<std::size_t>{1U}).getNodeAt(0U)->value(), 1U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).getNodeAt(0U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).getNodeAt(1U)->value(), 2U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).getNodeAt(0U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).getNodeAt(1U)->value(), 2U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).getNodeAt(2U)->value(), 3U);
}

TEST(TestingIndexingNodes, ReadingNodesValuesAtOutOfBoundIndex) {
  // empty linkedlists
  LinkedList<std::size_t> emptyLl1{};
  EXPECT_EQ(emptyLl1.getNodeAt(0U), emptyLl1.end());

  LinkedList<std::size_t> emptyLl2{};
  EXPECT_EQ(emptyLl2.getNodeAt(1U), emptyLl2.end());

  LinkedList<std::size_t> emptyLl3{};
  EXPECT_EQ(emptyLl3.getNodeAt(2U), emptyLl3.end());

  // non-empty linkedlists
  LinkedList<std::size_t> nonEmptyLl1{1U};
  EXPECT_EQ(nonEmptyLl1.getNodeAt(1U), nonEmptyLl1.end());

  LinkedList<std::size_t> nonEmptyLl2{1U, 2U};
  EXPECT_EQ(nonEmptyLl2.getNodeAt(2U), nonEmptyLl2.end());

  LinkedList<std::size_t> nonEmptyLl3{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl3.getNodeAt(3U), nonEmptyLl3.end());
}

TEST(TestingHeadAndTail, ReadingHeadAndTailValues) {
  using ValueType = std::size_t;
  using LinkedListType = LinkedList<ValueType>;

  // empty LL
  EXPECT_EQ((LinkedListType{}).getHeadValue(), ValueType{});

  EXPECT_EQ((LinkedListType{}).getTailValue(), ValueType{});

  // LL of one node
  EXPECT_EQ((LinkedListType{42U}).getHeadValue(), 42U);
  EXPECT_EQ((LinkedListType{42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedListType{69U}).getHeadValue(), 69U);
  EXPECT_EQ((LinkedListType{69U}).getTailValue(), 69U);

  // LL of several nodes
  EXPECT_EQ((LinkedListType{69U, 133U, 42U}).getHeadValue(), 69U);
  EXPECT_EQ((LinkedListType{69U, 133U, 42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedListType{42U, 133U, 69U}).getHeadValue(), 42U);
  EXPECT_EQ((LinkedListType{42U, 133U, 69U}).getTailValue(), 69U);

  EXPECT_EQ((LinkedListType{133U, 69U, 42U}).getHeadValue(), 133U);
  EXPECT_EQ((LinkedListType{133U, 69U, 42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedListType{133U, 42U, 69U}).getHeadValue(), 133U);
  EXPECT_EQ((LinkedListType{133U, 42U, 69U}).getTailValue(), 69U);
}

TEST(TestingHeadAndTail, GettingLengthOfTheLinkedList) {
  // empty LL
  EXPECT_EQ((LinkedList<std::size_t>{}).getLength(), 0U);

  // LL of one node
  EXPECT_EQ((LinkedList<std::size_t>{42U}).getLength(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{69U}).getLength(), 1U);

  // LL of several nodes
  EXPECT_EQ((LinkedList<std::size_t>{69U, 42U}).getLength(), 2U);
  EXPECT_EQ((LinkedList<std::size_t>{42U, 69U}).getLength(), 2U);

  EXPECT_EQ((LinkedList<std::size_t>{69U, 133U, 42U}).getLength(), 3U);
  EXPECT_EQ((LinkedList<std::size_t>{69U, 133U, 42U}).getLength(), 3U);

  EXPECT_EQ((LinkedList<std::size_t>{69U, 42U, 69U, 42U}).getLength(), 4U);
  EXPECT_EQ((LinkedList<std::size_t>{42U, 69U, 42U, 69U}).getLength(), 4U);
}

TEST(TestingGetLength, GetLengthofLinkedListsWithDifferentSizes) {
  // empty LL
  EXPECT_EQ((LinkedList<std::size_t>{}).getLength(), 0U);

  // LL of one node
  EXPECT_EQ((LinkedList<std::size_t>{42U}).getLength(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{69U}).getLength(), 1U);

  // LL of several nodes
  EXPECT_EQ((LinkedList<std::size_t>{69U, 42U}).getLength(), 2U);
  EXPECT_EQ((LinkedList<std::size_t>{42U, 69U, 66U}).getLength(), 3U);
  EXPECT_EQ((LinkedList<std::size_t>{69U, 42U, 69U, 42U}).getLength(), 4U);
}

TEST(TestingDisplay, DisplayingLinkedLists) {
  // empty LL
  EXPECT_STREQ((LinkedList<std::size_t>{}).display().c_str(), "[]");

  // LL of one node
  EXPECT_STREQ((LinkedList<std::size_t>{42U}).display().c_str(), "[42]");
  EXPECT_STREQ((LinkedList<std::size_t>{69U}).display().c_str(), "[69]");

  // LL of several nodes
  EXPECT_STREQ((LinkedList<std::size_t>{69U, 42U, 69U, 42U}).display().c_str(),
               "[69,42,69,42]");
  EXPECT_STREQ((LinkedList<std::size_t>{42U, 69U, 42U, 69U}).display().c_str(),
               "[42,69,42,69]");
}

}  // namespace data_structures_test::linkedList_test
