#include "data-structures/Queue.hpp"

#include "gtest/gtest.h"

/// @brief
namespace data_structures_test::stack_test {
using namespace ::data_structures;

TEST(TestingConstruction, ConstructingQueues) {
  // empty queue
  EXPECT_NO_THROW({ (Queue<std::size_t, 3U>{}); });

  // queue of one element
  EXPECT_NO_THROW({ (Queue<std::size_t, 1U>{}); });
  EXPECT_NO_THROW({ (Queue<std::size_t, 1U>{42U}); });

  // queue of several elements
  EXPECT_NO_THROW({ (Queue<std::size_t, 3U>{42U, 69U, 666U}); });
  EXPECT_NO_THROW({ (Queue<std::size_t, 5U>{42U, 69U, 666U}); });
  EXPECT_NO_THROW(
      { (Queue<char, 8U>{'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'}); });
}

TEST(TestingReadingFirstElement, ReadingFirstElementOfQueuesOfDifferentSizes) {
  using ValueType = std::size_t;

  // empty queue
  EXPECT_EQ((Queue<ValueType, 1U>{}).firstElement(), ValueType{});
  EXPECT_EQ((Queue<ValueType, 3U>{}).firstElement(), ValueType{});
  EXPECT_EQ((Queue<ValueType, 5U>{}).firstElement(), ValueType{});

  // queue of one element
  EXPECT_EQ((Queue<ValueType, 1U>{42U}).firstElement(), 42U);
  EXPECT_EQ((Queue<ValueType, 3U>{69U}).firstElement(), 69U);
  EXPECT_EQ((Queue<ValueType, 5U>{133U}).firstElement(), 133U);

  // queue of several elements
  EXPECT_EQ((Queue<ValueType, 3U>{69U, 42U, 133U}).firstElement(), 69U);
  EXPECT_EQ((Queue<ValueType, 5U>{1U, 2U, 3U, 4U, 5U}).firstElement(), 1U);
  EXPECT_EQ((Queue<ValueType, 7U>{101U, 102U, 103U, 104U, 105U}).firstElement(),
            101U);
}

TEST(TestingReadingLastElement, ReadingLastElementOfQueuesOfDifferentSizes) {
  using ValueType = std::size_t;

  // empty queue
  EXPECT_EQ((Queue<ValueType, 1U>{}).lastElement(), ValueType{});
  EXPECT_EQ((Queue<ValueType, 3U>{}).lastElement(), ValueType{});
  EXPECT_EQ((Queue<ValueType, 5U>{}).lastElement(), ValueType{});

  // queue of one element
  EXPECT_EQ((Queue<ValueType, 1U>{42U}).lastElement(), 42U);
  EXPECT_EQ((Queue<ValueType, 3U>{69U}).lastElement(), 69U);
  EXPECT_EQ((Queue<ValueType, 5U>{133U}).lastElement(), 133U);

  // queue of several elements
  EXPECT_EQ((Queue<ValueType, 1U>{42U}).lastElement(), 42U);
  EXPECT_EQ((Queue<ValueType, 3U>{133U, 42U, 69U}).lastElement(), 69U);
  EXPECT_EQ((Queue<ValueType, 5U>{101U, 102U, 103U}).lastElement(), 103U);
}

TEST(TestingIsEmpty, CheckingIsEmptyForQueuesOfDifferentSizes) {
  using ValueType = std::size_t;

  // empty queue
  EXPECT_TRUE((Queue<ValueType, 1U>{}).isEmpty());
  EXPECT_TRUE((Queue<ValueType, 3U>{}).isEmpty());
  EXPECT_TRUE((Queue<ValueType, 5U>{}).isEmpty());

  // queue of one element
  EXPECT_FALSE((Queue<ValueType, 1U>{42U}).isEmpty());
  EXPECT_FALSE((Queue<ValueType, 3U>{69U}).isEmpty());
  EXPECT_FALSE((Queue<ValueType, 5U>{133U}).isEmpty());

  // queue of several elements
  EXPECT_FALSE((Queue<ValueType, 1U>{42U}).isEmpty());
  EXPECT_FALSE((Queue<ValueType, 3U>{133U, 42U, 69U}).isEmpty());
  EXPECT_FALSE((Queue<ValueType, 5U>{101U, 102U, 103U}).isEmpty());
}

TEST(TestingIsFull, CheckingIsFullForQueuesOfDifferentSizes) {
  using ValueType = std::size_t;

  // empty queue
  EXPECT_FALSE((Queue<ValueType, 1U>{}).isFull());
  EXPECT_FALSE((Queue<ValueType, 3U>{}).isFull());
  EXPECT_FALSE((Queue<ValueType, 5U>{}).isFull());

  // partially filled queues
  EXPECT_FALSE((Queue<ValueType, 3U>{42U}).isFull());
  EXPECT_FALSE((Queue<ValueType, 4U>{69U, 42U}).isFull());
  EXPECT_FALSE((Queue<ValueType, 5U>{133U, 69U, 42U}).isFull());

  // completely filled queues
  EXPECT_TRUE((Queue<ValueType, 1U>{42U}).isFull());
  EXPECT_TRUE((Queue<ValueType, 3U>{133U, 42U, 69U}).isFull());
  EXPECT_TRUE((Queue<ValueType, 5U>{101U, 102U, 103U, 104U, 105U}).isFull());
}

TEST(TestingLength, ReadingLengthsOfQueuesOfDifferentSizes) {
  using ValueType = std::size_t;

  // empty queue
  EXPECT_EQ((Queue<ValueType, 1U>{}).length(), 0U);
  EXPECT_EQ((Queue<ValueType, 3U>{}).length(), 0U);
  EXPECT_EQ((Queue<ValueType, 5U>{}).length(), 0U);

  // partially filled queues
  EXPECT_EQ((Queue<ValueType, 3U>{42U}).length(), 1U);
  EXPECT_EQ((Queue<ValueType, 4U>{69U, 42U}).length(), 2U);
  EXPECT_EQ((Queue<ValueType, 5U>{133U, 69U, 42U}).length(), 3U);

  // completely filled queues
  EXPECT_EQ((Queue<ValueType, 1U>{42U}).length(), 1U);
  EXPECT_EQ((Queue<ValueType, 3U>{133U, 42U, 69U}).length(), 3U);
  EXPECT_EQ((Queue<ValueType, 5U>{101U, 102U, 103U, 104U, 105U}).length(), 5U);
}

TEST(TestingDisplay, DisplayingElementsInQueuesOfDifferentSizes) {
  EXPECT_STREQ((Queue<std::size_t, 1U>{}).display().c_str(), "[]");
  EXPECT_STREQ((Queue<std::size_t, 2U>{}).display().c_str(), "[]");
  EXPECT_STREQ((Queue<std::size_t, 3U>{}).display().c_str(), "[]");

  EXPECT_STREQ((Queue<std::size_t, 1U>{}).display().c_str(),
               (Queue<std::size_t, 3U>{}).display().c_str());

  EXPECT_STREQ((Queue<std::size_t, 4U>{2U, 3U}).display().c_str(), "[2,3]");
  EXPECT_STREQ((Queue<std::size_t, 4U>{4U, 5U}).display().c_str(), "[4,5]");

  EXPECT_STREQ((Queue<std::size_t, 8U>{2U, 3U, 4U, 5U}).display().c_str(),
               "[2,3,4,5]");
  EXPECT_STREQ((Queue<std::size_t, 9U>{6U, 7U, 8U, 9U}).display().c_str(),
               "[6,7,8,9]");
}

TEST(TestingEnqueueOnly, CheckingEnqueueElementsBehavior) {
  using ValueType = std::size_t;

  // start initially with empty queue
  Queue<ValueType, 3U> queue{};

  // check its state
  EXPECT_EQ(queue.firstElement(), ValueType{});
  EXPECT_EQ(queue.lastElement(), ValueType{});
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 0U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{}).display().c_str());

  EXPECT_TRUE(queue.enqueue(42U));

  // check its state again after enqueue
  EXPECT_EQ(queue.firstElement(), 42U);
  EXPECT_EQ(queue.lastElement(), 42U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 1U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{42U}).display().c_str());

  EXPECT_TRUE(queue.enqueue(69U));

  // check its state again after enqueue
  EXPECT_EQ(queue.firstElement(), 42U);
  EXPECT_EQ(queue.lastElement(), 69U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 2U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{42U, 69U}).display().c_str());

  EXPECT_TRUE(queue.enqueue(133U));

  // check its state again after enqueue
  EXPECT_EQ(queue.firstElement(), 42U);
  EXPECT_EQ(queue.lastElement(), 133U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_TRUE(queue.isFull());
  EXPECT_EQ(queue.length(), 3U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{42U, 69U, 133U}).display().c_str());

  // try enqueueing while it's full, and then confirm its state wasn't altered
  EXPECT_FALSE(queue.enqueue(133U));

  const auto finalStateOfTheQueue{Queue<ValueType, 3U>{42U, 69U, 133U}};

  EXPECT_EQ(queue.firstElement(), finalStateOfTheQueue.firstElement());
  EXPECT_EQ(queue.lastElement(), finalStateOfTheQueue.lastElement());
  EXPECT_EQ(queue.isEmpty(), finalStateOfTheQueue.isEmpty());
  EXPECT_EQ(queue.isFull(), finalStateOfTheQueue.isFull());
  EXPECT_EQ(queue.length(), finalStateOfTheQueue.length());
  EXPECT_STREQ(queue.display().c_str(), finalStateOfTheQueue.display().c_str());
}

TEST(TestingDequeueOnly, CheckingDequeueElementsBehavior) {
  using ValueType = std::size_t;

  // start initially with empty queue
  Queue<ValueType, 3U> queue{101U, 102U, 103U};

  // check its state
  EXPECT_EQ(queue.firstElement(), 101U);
  EXPECT_EQ(queue.lastElement(), 103U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_TRUE(queue.isFull());
  EXPECT_EQ(queue.length(), 3U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{101U, 102U, 103U}).display().c_str());

  EXPECT_EQ(queue.dequeue(), 101U);

  // check its state again after dequeue
  EXPECT_EQ(queue.firstElement(), 102U);
  EXPECT_EQ(queue.lastElement(), 103U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 2U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{102U, 103U}).display().c_str());

  EXPECT_EQ(queue.dequeue(), 102U);

  // check its state again after dequeue
  EXPECT_EQ(queue.firstElement(), 103U);
  EXPECT_EQ(queue.lastElement(), 103U);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 1U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{103U}).display().c_str());

  EXPECT_EQ(queue.dequeue(), 103U);

  // check its state again after dequeue
  EXPECT_EQ(queue.firstElement(), ValueType{});
  EXPECT_EQ(queue.lastElement(), ValueType{});
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_FALSE(queue.isFull());
  EXPECT_EQ(queue.length(), 0U);
  EXPECT_STREQ(queue.display().c_str(),
               (Queue<ValueType, 3U>{}).display().c_str());

  // try dequeueing while it's empty, and then confirm its state wasn't altered
  EXPECT_EQ(queue.dequeue(), ValueType{});

  const auto finalStateOfTheQueue{Queue<ValueType, 3U>{}};

  EXPECT_EQ(queue.firstElement(), finalStateOfTheQueue.firstElement());
  EXPECT_EQ(queue.lastElement(), finalStateOfTheQueue.lastElement());
  EXPECT_EQ(queue.isEmpty(), finalStateOfTheQueue.isEmpty());
  EXPECT_EQ(queue.isFull(), finalStateOfTheQueue.isFull());
  EXPECT_EQ(queue.length(), finalStateOfTheQueue.length());
  EXPECT_STREQ(queue.display().c_str(), finalStateOfTheQueue.display().c_str());
}

TEST(TestingEnqeueAndDequeue, CheckingEnqueueingAndDequeueingElementsBehavior) {
  // used for comparison
  const auto emptyQueue{Queue<std::size_t, 5U>{}};

  Queue<std::size_t, 5U> queue{};

  EXPECT_TRUE(queue.enqueue(1U));
  EXPECT_TRUE(queue.enqueue(2U));
  EXPECT_TRUE(queue.enqueue(3U));
  EXPECT_TRUE(queue.enqueue(4U));
  EXPECT_TRUE(queue.enqueue(5U));

  EXPECT_EQ(queue.dequeue(), 1U);
  EXPECT_EQ(queue.dequeue(), 2U);
  EXPECT_EQ(queue.dequeue(), 3U);
  EXPECT_EQ(queue.dequeue(), 4U);
  EXPECT_EQ(queue.dequeue(), 5U);

  EXPECT_EQ(queue.firstElement(), emptyQueue.firstElement());
  EXPECT_EQ(queue.lastElement(), emptyQueue.lastElement());
  EXPECT_EQ(queue.isEmpty(), emptyQueue.isEmpty());
  EXPECT_EQ(queue.isFull(), emptyQueue.isFull());
  EXPECT_EQ(queue.length(), emptyQueue.length());
  EXPECT_STREQ(queue.display().c_str(), emptyQueue.display().c_str());
}

TEST(TestingCircularBehavior, PartiallyReplacingQueueElements) {
  using ValueType = std::size_t;

  {
    // for two-elements queue
    Queue<ValueType, 2U> queue{1U, 2U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 2U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{1U, 2U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 2U);
    EXPECT_EQ(queue.lastElement(), 42U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{2U, 42U}).display().c_str());
  }

  {
    // for three-elements queue
    Queue<ValueType, 3U> queue{1U, 2U, 3U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 3U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 5U>{1U, 2U, 3U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(69U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 3U);
    EXPECT_EQ(queue.lastElement(), 69U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 3U>{3U, 42U, 69U}).display().c_str());
  }

  {
    // for five-elements queue
    Queue<ValueType, 5U> queue{1U, 2U, 3U, 4U, 5U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 5U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 5U>{1U, 2U, 3U, 4U, 5U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(69U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(666U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 4U);
    EXPECT_EQ(queue.lastElement(), 666U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(
        queue.display().c_str(),
        (Queue<ValueType, 5U>{4U, 5U, 42U, 69U, 666U}).display().c_str());
  }
}

TEST(TestingCircularBehavior, FullyReplacingQueueElements) {
  using ValueType = std::size_t;

  {
    // for one-elements queue
    Queue<ValueType, 1U> queue{1U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 1U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 1U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 1U>{1U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 42U);
    EXPECT_EQ(queue.lastElement(), 42U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 1U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 1U>{42U}).display().c_str());
  }

  {
    // for two-elements queue
    Queue<ValueType, 2U> queue{1U, 2U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 2U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{1U, 2U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(69U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(42U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 69U);
    EXPECT_EQ(queue.lastElement(), 42U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{69U, 42U}).display().c_str());
  }

  {
    // for three-elements queue
    Queue<ValueType, 3U> queue{1U, 2U, 3U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 3U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 3U>{1U, 2U, 3U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(69U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(666U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 42U);
    EXPECT_EQ(queue.lastElement(), 666U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 3U>{42U, 69U, 666U}).display().c_str());
  }

  {
    // for five-elements queue
    Queue<ValueType, 5U> queue{1U, 2U, 3U, 4U, 5U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 5U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 5U>{1U, 2U, 3U, 4U, 5U}).display().c_str());

    // update its elements forcing its circular behavior
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(42U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(69U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(133U));

    EXPECT_EQ(queue.dequeue(), 4U);
    EXPECT_TRUE(queue.enqueue(666U));

    EXPECT_EQ(queue.dequeue(), 5U);
    EXPECT_TRUE(queue.enqueue(74U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 42U);
    EXPECT_EQ(queue.lastElement(), 74U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(
        queue.display().c_str(),
        (Queue<ValueType, 5U>{42U, 69U, 133U, 666U, 74U}).display().c_str());
  }
}

TEST(TestingCircularBehavior, PerformingTwoFullCycles) {
  using ValueType = std::size_t;

  {
    // for one-elements queue
    Queue<ValueType, 1U> queue{1U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 1U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 1U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 1U>{1U}).display().c_str());

    // update its elements forcing its circular behavior twice
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(2U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(3U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 3U);
    EXPECT_EQ(queue.lastElement(), 3U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 1U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 1U>{3U}).display().c_str());
  }

  {
    // for two-elements queue
    Queue<ValueType, 2U> queue{1U, 2U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 2U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{1U, 2U}).display().c_str());

    // update its elements forcing its circular behavior twice
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(3U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(4U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(5U));

    EXPECT_EQ(queue.dequeue(), 4U);
    EXPECT_TRUE(queue.enqueue(6U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 5U);
    EXPECT_EQ(queue.lastElement(), 6U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 2U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 2U>{5U, 6U}).display().c_str());
  }

  {
    // for three-elements queue
    Queue<ValueType, 3U> queue{1U, 2U, 3U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 3U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 3U>{1U, 2U, 3U}).display().c_str());

    // update its elements forcing its circular behavior twice
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(4U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(5U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(6U));

    EXPECT_EQ(queue.dequeue(), 4U);
    EXPECT_TRUE(queue.enqueue(7U));

    EXPECT_EQ(queue.dequeue(), 5U);
    EXPECT_TRUE(queue.enqueue(8U));

    EXPECT_EQ(queue.dequeue(), 6U);
    EXPECT_TRUE(queue.enqueue(9U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 7U);
    EXPECT_EQ(queue.lastElement(), 9U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 3U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 3U>{7U, 8U, 9U}).display().c_str());
  }

  {
    // for five-elements queue
    Queue<ValueType, 5U> queue{1U, 2U, 3U, 4U, 5U};

    // check its initial state
    EXPECT_EQ(queue.firstElement(), 1U);
    EXPECT_EQ(queue.lastElement(), 5U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(queue.display().c_str(),
                 (Queue<ValueType, 5U>{1U, 2U, 3U, 4U, 5U}).display().c_str());

    // update its elements forcing its circular behavior twice
    EXPECT_EQ(queue.dequeue(), 1U);
    EXPECT_TRUE(queue.enqueue(6U));

    EXPECT_EQ(queue.dequeue(), 2U);
    EXPECT_TRUE(queue.enqueue(7U));

    EXPECT_EQ(queue.dequeue(), 3U);
    EXPECT_TRUE(queue.enqueue(8U));

    EXPECT_EQ(queue.dequeue(), 4U);
    EXPECT_TRUE(queue.enqueue(9U));

    EXPECT_EQ(queue.dequeue(), 5U);
    EXPECT_TRUE(queue.enqueue(10U));

    EXPECT_EQ(queue.dequeue(), 6U);
    EXPECT_TRUE(queue.enqueue(11U));

    EXPECT_EQ(queue.dequeue(), 7U);
    EXPECT_TRUE(queue.enqueue(12U));

    EXPECT_EQ(queue.dequeue(), 8U);
    EXPECT_TRUE(queue.enqueue(13U));

    EXPECT_EQ(queue.dequeue(), 9U);
    EXPECT_TRUE(queue.enqueue(14U));

    EXPECT_EQ(queue.dequeue(), 10U);
    EXPECT_TRUE(queue.enqueue(15U));

    // check its final state
    EXPECT_EQ(queue.firstElement(), 11U);
    EXPECT_EQ(queue.lastElement(), 15U);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.length(), 5U);
    EXPECT_STREQ(
        queue.display().c_str(),
        (Queue<ValueType, 5U>{11U, 12U, 13U, 14U, 15U}).display().c_str());
  }
}

TEST(TestingClear, CheckingClearingQueueBehavior) {
  // used for comparison
  const auto emptyQueue{Queue<std::size_t, 1U>{}};

  {
    // one element queue
    Queue<std::size_t, 1U> queue{666U};
    queue.clear();

    EXPECT_EQ(queue.firstElement(), emptyQueue.firstElement());
    EXPECT_EQ(queue.lastElement(), emptyQueue.lastElement());
    EXPECT_EQ(queue.isEmpty(), emptyQueue.isEmpty());
    EXPECT_EQ(queue.isFull(), emptyQueue.isFull());
    EXPECT_EQ(queue.length(), emptyQueue.length());
    EXPECT_STREQ(queue.display().c_str(), emptyQueue.display().c_str());
  }

  {
    // three element queue
    Queue<std::size_t, 3U> queue{42U, 69U, 666U};
    queue.clear();

    EXPECT_EQ(queue.firstElement(), emptyQueue.firstElement());
    EXPECT_EQ(queue.lastElement(), emptyQueue.lastElement());
    EXPECT_EQ(queue.isEmpty(), emptyQueue.isEmpty());
    EXPECT_EQ(queue.isFull(), emptyQueue.isFull());
    EXPECT_EQ(queue.length(), emptyQueue.length());
    EXPECT_STREQ(queue.display().c_str(), emptyQueue.display().c_str());
  }

  {
    // four element queue
    Queue<std::size_t, 9U> queue{6U, 7U, 8U, 9U};
    queue.clear();

    EXPECT_EQ(queue.firstElement(), emptyQueue.firstElement());
    EXPECT_EQ(queue.lastElement(), emptyQueue.lastElement());
    EXPECT_EQ(queue.isEmpty(), emptyQueue.isEmpty());
    EXPECT_EQ(queue.isFull(), emptyQueue.isFull());
    EXPECT_EQ(queue.length(), emptyQueue.length());
    EXPECT_STREQ(queue.display().c_str(), emptyQueue.display().c_str());
  }

  {
    // five element queue
    Queue<std::size_t, 5U> queue{1U, 2U, 3U, 4U, 5U};
    queue.clear();

    EXPECT_EQ(queue.firstElement(), emptyQueue.firstElement());
    EXPECT_EQ(queue.lastElement(), emptyQueue.lastElement());
    EXPECT_EQ(queue.isEmpty(), emptyQueue.isEmpty());
    EXPECT_EQ(queue.isFull(), emptyQueue.isFull());
    EXPECT_EQ(queue.length(), emptyQueue.length());
    EXPECT_STREQ(queue.display().c_str(), emptyQueue.display().c_str());
  }
}

}  // namespace data_structures_test::stack_test
