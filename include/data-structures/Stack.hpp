#pragma once

#include <concepts>
#include <utility>

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief concept for Stackable container type
template <typename T>
concept Stackable = requires(T container) {
};

/// @brief defining a concept for checking a type against a parameter pack
///        whether they're not the same or not
template <typename T, typename... U>
concept NotSameType = (sizeof...(U) > 1U || std::is_same_v<T, U...> == false);

/// @brief class definition for Stack data structure
/// @tparam CONTAINER stackable container type of values to hold
template <Stackable CONTAINER>
class Stack {
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
private:
  /// @brief the underlying container that implements the stack ADT
  CONTAINER m_container{};
};

}  // namespace data_structures
