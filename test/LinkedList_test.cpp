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
  EXPECT_EQ((LinkedList<std::size_t>{}).search(0U), nullptr);
  EXPECT_EQ((LinkedList<std::size_t>{}).search(1U), nullptr);
  EXPECT_EQ((LinkedList<std::size_t>{}).search(2U), nullptr);
}

TEST(TestingSearch, SearchingLinkedListsForNonExistingValues) {
  EXPECT_EQ((LinkedList<std::size_t>{1U}).search(42U), nullptr);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).search(69U), nullptr);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(666U), nullptr);
}

TEST(TestingSearch, SearchingLinkedListsForExistingValues) {
  EXPECT_EQ((LinkedList<std::size_t>{1U}).search(1U)->value(), 1U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).search(1U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U}).search(2U)->value(), 2U);

  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(1U)->value(), 1U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(2U)->value(), 2U);
  EXPECT_EQ((LinkedList<std::size_t>{1U, 2U, 3U}).search(3U)->value(), 3U);
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
