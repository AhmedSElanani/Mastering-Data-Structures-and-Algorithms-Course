#pragma once

#include <cstdlib>
#include <format>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief class definition for LinkedList data structure
/// @tparam T type of values to hold
template <typename T>
class LinkedList {
  /// @brief class definition for Node type to hold the values in the list
  class Node {
  public:
    /// @brief parametrized constructor of the class accepting value and
    ///        optional pointer to the next node
    /// @param value the data to be held by the node
    constexpr explicit Node(T&& value, std::unique_ptr<Node> next = nullptr)
        : m_value{std::forward<T>(value)}, m_next{std::move(next)} {}

    /// @brief method to append a new node given to data to this node
    /// @param value the data to be held in the new appended node
    /// @return reference to the newly appended node
    auto append(T&& value) -> std::unique_ptr<Node>& {
      m_next =
          std::make_unique<Node>(std::forward<T>(value), std::move(m_next));

      return m_next;
    }

    /// @brief method to return value stored in this node
    /// @return the value stored in this node
    auto value() const noexcept -> T { return m_value; }

    /// @brief method to return reference to next node in the list
    /// @return reference to the next node in the list
    auto nextNode() noexcept -> std::unique_ptr<Node>& { return m_next; }

    /// @brief the const overload of nextNode() method
    /// @return const reference to the next node in the list
    auto nextNode() const noexcept -> std::unique_ptr<Node> const& {
      return m_next;
    }

    /// @brief method to show whether this node is the last in the list or not
    /// @return true if last node in the list, false otherwise
    [[nodiscard]] auto isLastNode() const noexcept -> bool {
      return m_next == nullptr;
    }

  private:
    /// @brief member to hold the data value of this node
    T m_value{};

    /// @brief  member to point to the next node if any
    std::unique_ptr<Node> m_next{nullptr};
  };

public:
  /// @brief default constructor of the linked list, the state after its called
  ///        is having zero nodes in the list
  constexpr LinkedList() = default;

  /// @brief parametrized constructor to Linked List, accepting one or
  ///        more values of the same type, where each of them will be
  ///        represented by an individual node
  /// @tparam ...Rem remaining values passed if any
  /// @param firstValue data to initialize the head node
  /// @param ...remValues data to initialize the remaining nodes if any
  /// @note this guarantees that first and remaining values are of same type
  template <typename... Rem>
  constexpr explicit LinkedList(T&& firstValue, Rem&&... remValues)
      : m_head{std::make_unique<Node>(std::forward<T>(firstValue))},
        m_length{1U} {
    constexpr auto kNoOfRemainingElements{sizeof...(Rem)};
    if constexpr (kNoOfRemainingElements == 0U) {
      return;
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToExtend{m_head};
    for (auto&& val : std::vector<T>{remValues...}) {
      nodeToExtend = nodeToExtend.get()->append(std::forward<T>(val));
    }

    m_tail = nodeToExtend;
    m_length += kNoOfRemainingElements;
  }

  /// @brief method to search for a node given the key
  /// @param key value with which the node is searched
  /// @return the first node holding a value equal to the key if found,
  ///         or reference to nullptr otherwise
  auto search(T key) const noexcept -> std::unique_ptr<Node> const& {
    if (isEmpty()) {
      return m_head;
    }

    std::reference_wrapper<std::unique_ptr<Node> const> nodeToCheck{m_head};
    while (nodeToCheck.get()) {
      if (nodeToCheck.get()->value() == key) {
        return nodeToCheck.get();
      }

      advance(nodeToCheck);
    }

    return cend();
  }

  /// @brief enhanced search does the same as search method, but also moves the
  ///        found node to the front for higher probability it will be searched
  ///        for again, and hence found more quickly
  /// @param key value with which the node is searched
  /// @return the first node holding a value equal to the key if found, where it
  ///         gets moved to the front in this case,
  ///         or reference to nullptr otherwise
  auto enhancedSearch(T key) noexcept -> std::unique_ptr<Node> const& {
    if (isEmpty()) {
      return m_head;
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToCheck{m_head};
    std::reference_wrapper<std::unique_ptr<Node>> prevNode{end()};
    while (nodeToCheck.get()) {
      if (nodeToCheck.get()->value() == key) {
        // the key difference in this search algorithm
        moveNodeToFront(prevNode, nodeToCheck);

        return m_head;
      }

      prevNode = nodeToCheck;
      advance(nodeToCheck);
    }

    return cend();
  }

  /// @brief method that inserts a new node at a given index
  /// @param value data to be stored in that new node
  /// @param position index at which this node shall be inserted
  /// @return true, if the node was inserted successfully, false otherwise
  auto insertAt(T&& value, std::size_t position) -> bool {
    if (position > m_length) {
      return false;
    }

    if (position == 0U) {
      // inserting at head position
      m_head =
          std::make_unique<Node>(std::forward<T>(value), std::move(m_head));

      ++m_length;
      return true;
    }

    std::unique_ptr<Node>& nodeToExtend{getNodeAt(position - 1U)};
    nodeToExtend->nextNode() = std::make_unique<Node>(
        std::forward<T>(value), std::move(nodeToExtend->nextNode()));

    if (position >= m_length - 1U) {
      // this means either the inserted node will be the new tail, or just
      // before the tail, hence, in either case, the tail reference need to be
      // shifted forward by one step
      advance(m_tail);
    }

    ++m_length;
    return true;
  }

  /// @brief method to delete node at a given position if valid
  /// @param position 0-indexed position of the node to be deleted
  /// @return the deleted node if position was valid,
  ///          or nullptr which can be checked against end() otherwise
  auto deleteNodeAt(std::size_t position) -> std::unique_ptr<Node> {
    if (position >= m_length) {
      return std::move(end());
    }

    // If tail was nulled due to a delete or shift to previous position, it will
    // need to be updated.
    const auto adjustTailIfNeeded{[](auto& tail, auto& prevNode) {
      if (tail.get() == nullptr) {
        tail = prevNode->nextNode() != nullptr
                   // this means the node before tail was removed and hence
                   // tail was shifted one step backwards
                   ? prevNode->nextNode()
                   // this means the tail node was removed and hence its
                   // predecessor node  shall be the tail now
                   : prevNode;
      }
    }};

    if (position == 0U) {
      std::unique_ptr<Node> nodeToRemove{std::move(m_head)};
      m_head = std::move(nodeToRemove->nextNode());
      --m_length;

      // if there are still other nodes, maybe the tail needs adjustment
      if (m_length != 0U) {
        adjustTailIfNeeded(m_tail, m_head);
      }

      return nodeToRemove;
    }

    std::unique_ptr<Node>& prevNode{getNodeAt(position - 1U)};
    std::unique_ptr<Node> nodeToRemove{std::move(prevNode->nextNode())};
    prevNode->nextNode() = std::move(nodeToRemove->nextNode());
    --m_length;

    adjustTailIfNeeded(m_tail, prevNode);

    return nodeToRemove;
  }

  /// @brief method to return the node at a given position
  /// @param position 0-indexed position at which the node shall be read
  /// @return the node at the given index if valid, end() otherwise
  auto getNodeAt(std::size_t position) noexcept -> std::unique_ptr<Node>& {
    if (isEmpty()) {
      return m_head;
    }

    if (position >= m_length) {
      return end();
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToTraverse{m_head};
    advance(nodeToTraverse, position);

    return nodeToTraverse.get();
  }

  /// @brief method to return the value of first node in the list
  /// @return value of first node in list if not empty,
  ///         default initialzed otherwise
  constexpr auto getHeadValue() const noexcept -> T {
    return {m_head != nullptr ? m_head->value() : T{}};
  }

  /// @brief method to return the value of last node in the list
  /// @return value of last node in list if not empty,
  ///         default initialzed otherwise
  constexpr auto getTailValue() const noexcept -> T {
    return {m_tail.get() != nullptr ? m_tail.get()->value() : T{}};
  }

  /// @brief method to show the number of nodes in the linked list
  /// @return the number of nodes in the linked list
  [[nodiscard]] constexpr auto getLength() const noexcept -> std::size_t {
    return m_length;
  }

  /// @brief method to display nodes' values in the list
  /// @return elements' values surrounded by square brackets
  [[nodiscard]] auto display() const noexcept -> std::string {
    auto const stringifyFrom{[this](auto const& start) {
      std::string result;

      std::reference_wrapper<std::unique_ptr<Node> const> nodeToRead{start};
      while (nodeToRead.get()) {
        result += std::to_string(nodeToRead.get()->value()) +
                  (nodeToRead.get()->isLastNode() ? "" : ",");

        advance(nodeToRead);
      }

      return result;
    }};

    return std::string{std::format("[{}]", stringifyFrom(m_head))};
  }

  /// @brief method to check if LinkedList is empty
  /// @return true if LinkedList has no nodes, false otherwise
  [[nodiscard]] constexpr auto isEmpty() const noexcept -> bool {
    return m_head == nullptr;
  }

  /// @brief method that returns next ptr to the last Node by reference
  ///        if the list wasn't empty, which will be nullptr in this case,
  ///        or the first node if the list is empty, which will return nullptr
  ///        as well. Hence, it behaves in a similar way to the convention of
  ///        returning end() in STL containers
  /// @return next ptr to the last Node which is nullptr
  constexpr auto end() noexcept -> std::unique_ptr<Node>& {
    return {isEmpty() ? m_head : m_tail.get()->nextNode()};
  }

  /// @brief the const version of end(), where it calls the const overload of
  ///        nextNode() method in Node class
  /// @return const next ptr to the last Node which is nullptr
  constexpr auto cend() const noexcept -> std::unique_ptr<Node> const& {
    return {isEmpty() ? m_head : m_tail.get()->nextNode()};
  }

private:
  /// @brief owning pointer to the first node of the linked list
  std::unique_ptr<Node> m_head{nullptr};

  /// @brief non-owning reference  to the last element of the list
  std::reference_wrapper<std::unique_ptr<Node>> m_tail{m_head};

  /// @brief data member to keep track of number of nodes in the list
  std::size_t m_length{0U};

  /// @brief helper method to advance node to the next one since similar code
  ///        was called in many places
  /// @param node the refernece to node to be advance
  /// @param positions the number of positions to advance the node, the default
  ///                  is one position
  void advance(auto& node, std::size_t positions = 1U) const noexcept {
    while ((positions--) != 0U) {
      node = node.get()->nextNode();
    }
  }

  /// @brief helper method to move a node to the beginning of the linked list
  /// @param nodeToMove the node to be moved to the front
  /// @param prevNode the previous node to it, as it would be needed in singly
  ///                 linked list implementation
  void moveNodeToFront(
      std::reference_wrapper<std::unique_ptr<Node>>& prevNode,
      std::reference_wrapper<std::unique_ptr<Node>>& nodeToMove) {
    if (nodeToMove.get() == m_head) {
      // node to be moved is already at the front
      return;
    }

    // check if tail would be modified
    const bool nodeToMoveIsTail{nodeToMove.get() == m_tail.get()};
    const bool nodeNextShallBeTail{isTailNode(nodeToMove.get()->nextNode())};

    // start moving the node to the front
    std::unique_ptr<Node> nextNode{std::move(nodeToMove.get()->nextNode())};
    nodeToMove.get()->nextNode() = std::move(m_head);
    m_head = std::move(nodeToMove.get());

    // check overlapp between prevNode reference and head, as the rest of the
    // implementation assumes previous node is beyond the head
    // Note: It's fine if there's overlap with nodeToMove reference as it's
    //       no longer needed in this method
    if (prevNode.get() == m_head) {
      advance(prevNode);
    }

    if (nextNode.get()) {
      prevNode.get()->nextNode() = std::move(nextNode);
    }

    if (nodeToMoveIsTail) {
      // point tail to the previous node
      m_tail = prevNode.get();
      return;
    }

    if (nodeNextShallBeTail) {
      // point tail to the final destination of nextNode
      m_tail = prevNode.get()->nextNode();
      return;
    }
  }

  /// @brief helper method to check whether a given node is the tail node or not
  /// @param node candidate node to be checked if it is the tail node
  /// @return true if it is indeed the tail node, false otherwise
  auto isTailNode(std::unique_ptr<Node>& node) const noexcept -> bool {
    return node.get() == m_tail.get().get();
  }
};

}  // namespace data_structures
