#pragma once

#include <concepts>
#include <utility>

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief concept for Stackable container type
template <typename T>
concept Stackable = requires(T container) {
  typename T::value_type;

  container.getHeadValue();
  container.isEmpty();
  container.getLength();

  container.insertAt({}, std::size_t{});

  container.deleteAt(std::size_t{})->value();
};

/// @brief defining a concept for checking a type against a parameter pack
///        whether they're not the same or not
template <typename T, typename... U>
concept NotSameType = (sizeof...(U) > 1U || std::is_same_v<T, U...> == false);

/// @brief class definition for Stack data structure
/// @tparam CONTAINER stackable container type of values to hold
template <Stackable CONTAINER>
class Stack {
  /// @brief type alias for the elements type stored in the stack
  using ElementType = CONTAINER::value_type;

public:
  /// @brief parametrized constructor that accepts a parameter pack of elements
  ///        to initialize the stack
  /// @tparam ...Elems parameter pack type of the elements that shall be stored
  ///                  in the stack
  /// @param ...elems the actual elements to initialize and to be stored in the
  ///                 stack
  /// @note the constraint expression is used to avoid this universal reference
  ///       overload to take over the copy and move constructors
  template <typename... Elems>
    requires(NotSameType<Stack, Elems...>)
  constexpr explicit Stack(Elems&&... elems)
      : m_container{std::forward<Elems>(elems)...} {}

  /// @brief default constructor that initializes the stack in empty state
  Stack() = default;

  /// @brief a method to return the top element in the stack
  /// @return the value of the top element if the stack is not empty, otherwise
  ///         it returns default initialized element
  ElementType top() const noexcept { return m_container.getHeadValue(); }

  /// @brief a method to show whether the stack is empty or not
  /// @return true if the stack is empty, false otherwise
  bool isEmpty() const noexcept { return m_container.isEmpty(); }

  /// @brief a method to show the number of elements stored in the stack
  /// @return the number of elements in the stack
  std::size_t size() const noexcept { return m_container.getLength(); }

  /// @brief a method to push a new element at the top of the stack
  /// @param element the element to be pushed at the top of the stack
  void push(ElementType element) noexcept {
    // inserting at the front would always be more efficient for the different
    // underlying containers that could be used
    m_container.insertAt(std::move(element), 0U);
  }

  /// @brief a method to remove the last element at the stack
  /// @return the popped element if the stack wasn't empty,
  ///         otherwise a default initialized element
  ElementType pop() noexcept {
    // deleting at the front would always be more efficient for the different
    // underlying containers that could be used
    return {m_container.isEmpty() ? ElementType{}
                                  : m_container.deleteAt(0U)->value()};
  }

private:
  /// @brief the underlying container that implements the stack ADT
  CONTAINER m_container{};
};

}  // namespace data_structures
