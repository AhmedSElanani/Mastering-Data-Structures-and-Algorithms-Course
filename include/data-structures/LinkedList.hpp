#pragma once

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
    std::unique_ptr<Node>& append(T&& value) {
      m_next =
          std::make_unique<Node>(std::forward<T>(value), std::move(m_next));

      return m_next;
    }

    /// @brief method to return value stored in this node
    /// @return the value stored in this node
    T value() const noexcept { return m_value; }

    /// @brief method to return reference to next node in the list
    /// @return reference to the next node in the list
    std::unique_ptr<Node>& nextNode() noexcept { return m_next; }

    /// @brief the const overload of nextNode() method
    /// @return const reference to the next node in the list
    std::unique_ptr<Node> const& nextNode() const noexcept { return m_next; }

    /// @brief method to show whether this node is the last in the list or not
    /// @return true if last node in the list, false otherwise
    bool isLastNode() const noexcept { return m_next == nullptr; }

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
    constexpr auto noOfRemainingElements{sizeof...(Rem)};
    if constexpr (noOfRemainingElements == 0U) {
      return;
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToExtend{m_head};
    for (auto&& val : std::vector<T>{remValues...}) {
      nodeToExtend = nodeToExtend.get()->append(std::forward<T>(val));
    }

    m_tail = nodeToExtend;
    m_length += noOfRemainingElements;
  }

  /// @brief method to search for a node given the key
  /// @param key value with which the node is searched
  /// @return the first node holding a value equal to the key if found,
  ///         or reference to nullptr otherwise
  std::unique_ptr<Node> const& search(T key) const noexcept {
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
  std::unique_ptr<Node> const& enhancedSearch(T key) noexcept {
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

  std::unique_ptr<Node>& getNodeAt(std::size_t position) noexcept {
    if (isEmpty()) {
      return m_head;
    }

    if (position >= m_length) {
      return end();
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToTraverse{m_head};
    while (position--) {
      advance(nodeToTraverse);
    }

    return nodeToTraverse.get();
  }

  /// @brief method to return the value of first node in the list
  /// @return value of first node in list if not empty,
  ///         default initialzed otherwise
  constexpr T getHeadValue() const noexcept {
    return {m_head != nullptr ? m_head->value() : T{}};
  }

  /// @brief method to return the value of last node in the list
  /// @return value of last node in list if not empty,
  ///         default initialzed otherwise
  constexpr T getTailValue() const noexcept {
    return {m_tail.get() != nullptr ? m_tail.get()->value() : T{}};
  }

  /// @brief method to show the number of nodes in the linked list
  /// @return the number of nodes in the linked list
  constexpr std::size_t getLength() const noexcept { return m_length; }

  /// @brief method to display nodes' values in the list
  /// @return elements' values surrounded by square brackets
  auto display() const noexcept -> std::string {
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
  constexpr bool isEmpty() const noexcept { return m_head == nullptr; }

  /// @brief method that returns next ptr to the last Node by reference
  ///        if the list wasn't empty, which will be nullptr in this case,
  ///        or the first node if the list is empty, which will return nullptr
  ///        as well. Hence, it behaves in a similar way to the convention of
  ///        returning end() in STL containers
  /// @return next ptr to the last Node which is nullptr
  constexpr std::unique_ptr<Node>& end() noexcept {
    return {isEmpty() ? m_head : m_tail.get()->nextNode()};
  }

  /// @brief the const version of end(), where it calls the const overload of
  ///        nextNode() method in Node class
  /// @return const next ptr to the last Node which is nullptr
  constexpr std::unique_ptr<Node> const& cend() const noexcept {
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
  void advance(auto& node) const noexcept { node = node.get()->nextNode(); }

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
  bool isTailNode(std::unique_ptr<Node>& node) const noexcept {
    return node.get() == m_tail.get().get();
  }
};

}  // namespace data_structures
