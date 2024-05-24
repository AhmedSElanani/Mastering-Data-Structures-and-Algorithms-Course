#pragma once

#include <array>
#include <cstddef>
#include <format>
#include <string>
#include <utility>

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

  /// @brief index that behaves in a circular manner according to the cycle
  class CircularIndex {
  public:
    /// @brief parametrized constructor that takes the start position as well
    ///        the cycle size at which the index moves
    /// @param startPosition the initial value to the index
    /// @param cycle the size at which the index shall overflow and gets reset
    explicit constexpr CircularIndex(std::size_t startPosition,
                                     std::size_t cycle = N) noexcept
        : m_index{startPosition % cycle}, m_cycleSize{cycle} {}

    /// @brief preincrement operator to the index that maintains its circular
    ///        behavior
    /// @return a reference to the object after incrementing as per definition
    constexpr auto operator++() noexcept -> CircularIndex& {
      m_index = (m_index + 1U) % m_cycleSize;
      return *this;
    }

    /// @brief subtraction operator to the index that maintains its circular
    ///        behavior
    /// @param subtrahend the value that shall be subtracted from the index
    /// @return a new CircularIndex object that gets initialized with the
    ///         subtraction result
    constexpr auto operator-(std::size_t subtrahend) const noexcept -> CircularIndex {
      const auto normSub{subtrahend % m_cycleSize};
      const auto difference{m_index >= normSub ? m_index - normSub
                                               : m_cycleSize - normSub};
      return CircularIndex{difference};
    }

    /// @brief a method to reset the index to a certain position within its
    ///        defined cycle
    /// @param position the value at which the index shall be reset to
    constexpr void reset(std::size_t position) noexcept {
      m_index = position % m_cycleSize;
    }

    /// @brief a method to access the current value of the index
    /// @return the current value of the index
    [[nodiscard]] constexpr auto value() const noexcept -> std::size_t { return m_index; }

  private:
    /// @brief the underlying index value
    std::size_t m_index{0U};

    /// @brief the cycle size which defines when the index overflows
    ///         and gets reset
    std::size_t const m_cycleSize;
  };

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
      : m_data{std::forward<Elems>(elems)...},
        m_length{sizeof...(elems)},
        m_rear{CircularIndex{m_length} - 1U} {}

  /// @brief method that adds a new element to the end of the circular queue
  ///        in case it wasn't full
  /// @param element the element to be inserted to the queue
  /// @return true if the queue wasn't full and the element was inserted
  ///         successfully,
  ///         false otherwise
  constexpr auto enqueue(T&& element) noexcept -> bool {
    if (isFull()) {
      return false;
    }

    ++m_rear;
    m_data[m_rear.value()] = std::forward<T>(element);

    ++m_length;

    return true;
  }

  /// @brief method to remove the first element of the circular queue in case it
  ///        wasn't empty
  /// @return the dequeued element if the queue wasn't empty,
  ///         default initialized object otherwise
  constexpr auto dequeue() noexcept -> T {
    if (isEmpty()) {
      return T{};
    }

    T const dequeuedElement{std::move(m_data[m_front.value()])};
    ++m_front;

    --m_length;

    return dequeuedElement;
  }

  /// @brief method to clear the content of the queue
  constexpr void clear() {
    queue_container_type empty{};
    std::swap(m_data, empty);

    m_length = 0U;
    m_front.reset(0U);
    m_rear.reset(N - 1U);
  }

  /// @brief method to read the first element in the queue (i.e the element to
  ///        be dequeued next)
  /// @return the first element in the queue if not empty, otherwise a default
  ///         initialzed object
  constexpr auto firstElement() const noexcept -> T {
    return {!static_cast<bool>(isEmpty()) ? m_data[m_front.value()] : T{}};
  }

  /// @brief method to read the last element inserted to the queue
  /// @return the last element in the queue if not empty, otherwise a default
  ///         initialzed object
  constexpr auto lastElement() const noexcept -> T {
    return {!static_cast<bool>(isEmpty()) ? m_data[m_rear.value()] : T{}};
  }

  /// @brief method that returns the number of elements currently stored in
  ///        the queue
  /// @return the number of elements currently stored in the queue
  [[nodiscard]] auto length() const noexcept -> std::size_t { return m_length; }

  /// @brief method that returns the maximum size of the queue (i.e its
  ///        capacity)
  /// @return the maximum number of elements to be enqueued
  [[nodiscard]] auto size() const noexcept -> std::size_t { return N; }

  /// @brief a method to check whether the queue has no elements or not
  /// @return true if the queue has no elements at all, false otherwise
  [[nodiscard]] auto isEmpty() const noexcept -> bool { return m_length == 0U; }

  /// @brief a method to check whether the queue is full of elements or not
  /// @return true if the queue is completely full of elements,
  ///         false otherwise
  [[nodiscard]] auto isFull() const noexcept -> bool { return m_length == N; }

  /// @brief method to display currently stored elements in the queue
  /// @return elements of the queue surrounded by square brackets
  [[nodiscard]] auto display() const noexcept -> std::string {
    const auto stringify{
        [frontIndex{m_front.value()}](auto elements, auto length) {
          std::string result;
          if (length == 0U) {
            return result;
          }

          CircularIndex cIndex{frontIndex, N};
          while (length) {
            result += std::to_string(elements[cIndex.value()]) +
                      (length == 1U ? "" : ",");

            ++cIndex;
            --length;
          }

          return result;
        }};

    return std::string{std::format("[{}]", stringify(m_data, m_length))};
  }

private:
  /// @brief the underlying container that implements the queue ADT
  queue_container_type m_data{};

  /// @brief data member used to track the number of elements currently stored
  ///        in the queue
  std::size_t m_length{0U};
  /// @brief circular index used as the pointer to the position of dequeuing
  CircularIndex m_front{0U};

  /// @brief circular index used as the pointer to the position after enqueuing
  CircularIndex m_rear{N - 1U};
};

}  // namespace data_structures
