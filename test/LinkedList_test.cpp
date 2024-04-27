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
  EXPECT_NO_THROW({
    (LinkedList<char>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'});
  });
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
  LinkedList<std::size_t> nonEmptyLl{1U, 2U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 2U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{1U, 2U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesThreeNodes) {
  LinkedList<std::size_t> nonEmptyLl{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{1U, 2U, 3U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 3U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{2U, 1U, 3U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{3U, 2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesFourNodes) {
  LinkedList<std::size_t> nonEmptyLl{1U, 2U, 3U, 4U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{1U, 2U, 3U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{2U, 1U, 3U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 4U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{3U, 2U, 1U, 4U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(4U)->value(), 4U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{4U, 3U, 2U, 1U}).display().c_str());
}

TEST(TestingEnhancedSearch, SearchingLinkedListsForExistingValuesFiveNodes) {
  LinkedList<std::size_t> nonEmptyLl{1U, 2U, 3U, 4U, 5U};
  EXPECT_EQ(nonEmptyLl.enhancedSearch(1U)->value(), 1U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 1U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{1U, 2U, 3U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(2U)->value(), 2U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 2U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{2U, 1U, 3U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(3U)->value(), 3U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 3U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{3U, 2U, 1U, 4U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(4U)->value(), 4U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 4U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 5U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{4U, 3U, 2U, 1U, 5U}).display().c_str());

  EXPECT_EQ(nonEmptyLl.enhancedSearch(5U)->value(), 5U);
  EXPECT_EQ(nonEmptyLl.getHeadValue(), 5U);
  EXPECT_EQ(nonEmptyLl.getTailValue(), 1U);
  EXPECT_STREQ(nonEmptyLl.display().c_str(),
               (LinkedList<std::size_t>{5U, 4U, 3U, 2U, 1U}).display().c_str());
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
  LinkedList<std::size_t> const emptyLl1{};
  EXPECT_EQ(emptyLl1.getNodeAt(0U), emptyLl1.cend());

  LinkedList<std::size_t> const emptyLl2{};
  EXPECT_EQ(emptyLl2.getNodeAt(1U), emptyLl2.cend());

  LinkedList<std::size_t> const emptyLl3{};
  EXPECT_EQ(emptyLl3.getNodeAt(2U), emptyLl3.cend());

  // non-empty linkedlists
  LinkedList<std::size_t> const nonEmptyLl1{1U};
  EXPECT_EQ(nonEmptyLl1.getNodeAt(1U), nonEmptyLl1.cend());

  LinkedList<std::size_t> const nonEmptyLl2{1U, 2U};
  EXPECT_EQ(nonEmptyLl2.getNodeAt(2U), nonEmptyLl2.cend());

  LinkedList<std::size_t> const nonEmptyLl3{1U, 2U, 3U};
  EXPECT_EQ(nonEmptyLl3.getNodeAt(3U), nonEmptyLl3.cend());
}

TEST(TestingHeadAndTail, ReadingHeadAndTailValues) {
  // empty LL
  EXPECT_EQ((LinkedList<std::size_t>{}).getHeadValue(), std::size_t{});

  EXPECT_EQ((LinkedList<std::size_t>{}).getTailValue(), std::size_t{});

  // LL of one node
  EXPECT_EQ((LinkedList<std::size_t>{42U}).getHeadValue(), 42U);
  EXPECT_EQ((LinkedList<std::size_t>{42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedList<std::size_t>{69U}).getHeadValue(), 69U);
  EXPECT_EQ((LinkedList<std::size_t>{69U}).getTailValue(), 69U);

  // LL of several nodes
  EXPECT_EQ((LinkedList<std::size_t>{69U, 133U, 42U}).getHeadValue(), 69U);
  EXPECT_EQ((LinkedList<std::size_t>{69U, 133U, 42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedList<std::size_t>{42U, 133U, 69U}).getHeadValue(), 42U);
  EXPECT_EQ((LinkedList<std::size_t>{42U, 133U, 69U}).getTailValue(), 69U);

  EXPECT_EQ((LinkedList<std::size_t>{133U, 69U, 42U}).getHeadValue(), 133U);
  EXPECT_EQ((LinkedList<std::size_t>{133U, 69U, 42U}).getTailValue(), 42U);

  EXPECT_EQ((LinkedList<std::size_t>{133U, 42U, 69U}).getHeadValue(), 133U);
  EXPECT_EQ((LinkedList<std::size_t>{133U, 42U, 69U}).getTailValue(), 69U);
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
