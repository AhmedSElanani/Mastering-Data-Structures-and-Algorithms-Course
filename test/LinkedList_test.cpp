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
