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
      : m_first{std::make_unique<Node>(std::forward<T>(firstValue))} {
    if (sizeof...(Rem) == 0U) {
      return;
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToExtend{m_first};
    for (auto&& val : std::vector<T>{remValues...}) {
      nodeToExtend = nodeToExtend.get()->append(std::move(val));
    }

    m_tail = nodeToExtend;
  }

  /// @brief method to search for a node given the key
  /// @param key value with which the node is searched
  /// @return the first node holding a value equal to the key if found,
  ///         or reference to nullptr otherwise
  std::unique_ptr<Node>& search(T key) noexcept {
    if (isEmpty()) {
      return m_first;
    }

    std::reference_wrapper<std::unique_ptr<Node>> nodeToCheck{m_head};
    while (nodeToCheck.get()) {
      if (nodeToCheck.get()->value() == key) {
        return nodeToCheck.get();
      }

      advance(nodeToCheck);
    }

    // return next ptr to the last Node, which will be nullptr,
    // and somehow close to the convention of returning end() in STL containers
    return m_tail.get()->nextNode();
  }

  /// @brief method to return the value of first node in the list
  /// @return value of first node in list if not empty,
  ///         default initialzed otherwise
  constexpr T getHeadValue() const noexcept {
    return {m_head.get() != nullptr ? m_head.get()->value() : T{}};
  }

  /// @brief method to return the value of last node in the list
  /// @return value of last node in list if not empty,
  ///         default initialzed otherwise
  constexpr T getTailValue() const noexcept {
    return {m_tail.get() != nullptr ? m_tail.get()->value() : T{}};
  }

  /// @brief method to show the number of nodes in the linked list
  /// @return the number of nodes in the linked list
  constexpr std::size_t getLength() const noexcept {
    std::size_t numberOfNodes{0U};

    std::reference_wrapper<std::unique_ptr<Node>> nodeToCount{m_head};
    while (nodeToCount.get()) {
      ++numberOfNodes;

      advance(nodeToCount);
    }

    return numberOfNodes;
  }

  /// @brief method to display nodes' values in the list
  /// @return elements' values surrounded by square brackets
  auto display() const noexcept -> std::string {
    const auto stringifyFrom{[this](auto start) {
      std::string result;

      std::reference_wrapper<std::unique_ptr<Node>> nodeToRead{start};
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
  bool isEmpty() const noexcept { return m_first == nullptr; }

private:
  /// @brief  pointer to the first node of the linked list
  std::unique_ptr<Node> m_first{nullptr};

  /// @brief non-owning reference  to the first element of the list
  std::reference_wrapper<std::unique_ptr<Node>> m_head{m_first};

  /// @brief non-owning reference  to the last element of the list
  std::reference_wrapper<std::unique_ptr<Node>> m_tail{m_first};

  /// @brief helper method to advance node to the next one since similar code
  ///        was called in many places
  /// @param node the refernece to node to be advance
  void advance(
      std::reference_wrapper<std::unique_ptr<Node>>& node) const noexcept {
    node = node.get()->nextNode();
  }
};

}  // namespace data_structures
