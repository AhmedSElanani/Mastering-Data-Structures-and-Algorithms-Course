#pragma once

#include <functional>
#include <memory>
#include <utility>

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

  // TODO: equality operator

  // TODO: display

private:
  /// @brief  pointer to the first node of the linked list
  std::unique_ptr<Node> m_first{nullptr};

  /// @brief non-owning reference  to the first element of the list
  std::reference_wrapper<std::unique_ptr<Node>> m_head{m_first};

  /// @brief non-owning reference  to the last element of the list
  std::reference_wrapper<std::unique_ptr<Node>> m_tail{m_first};
};

}  // namespace data_structures
