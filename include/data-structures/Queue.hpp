#pragma once

#include <array>
#include <concepts>
#include "common/Common.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief class definition for Queue data structure based on circular array
///        two and pointers implementation
/// @tparam T type of data to be stored in the queue
/// @tparam N maximum size of the queue
template <typename T, std::size_t N>
class Queue {
  /// @brief type alias for underlying data structure for implementing the queue
  using queue_container_type = std::array<T, N>;

public:
  /// @brief default constructor that initializes the queue in empty state
  constexpr Queue() = default;

  /// @brief parametrized constructor that accepts a parameter pack of elements
  ///        to initialize the queue
  /// @tparam ...Elems parameter pack type of the elements that shall be stored
  ///                  in the queue
  /// @param ...elems the actual elements to initialize and to be stored in the
  ///                 queue
  /// @note the constraint expression is used to avoid this universal reference
  ///       overload to take over the copy and move constructors
  template <typename... Elems>
    requires(common::NotSameType<Queue, Elems...>)
  constexpr explicit Queue(Elems&&... elems)
      : m_data{std::forward<Elems>(elems)...} {
    constexpr std::size_t numberOfElements{sizeof...(elems)};
    m_length = numberOfElements;
    m_rear = numberOfElements - 1U;  // because 0-indexed
  }

private:
  /// @brief the underlying container that implements the queue ADT
  queue_container_type m_data{};

  /// @brief index used as the pointer to the position of dequeuing
  std::size_t m_front{0U};

  /// @brief index used as the pointer to the position of enqueuing
  std::size_t m_rear{0U};

  /// @brief data member used to track the number of elements currently stored
  ///        in the queue
  std::size_t m_length{0U};
};

}  // namespace data_structures
