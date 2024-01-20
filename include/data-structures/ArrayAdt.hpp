#pragma once

#include <algorithm>
#include <format>
#include <initializer_list>
#include <iterator>
#include <span>
#include <stdexcept>
#include <string>

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief class representing Array abstract data type
template <typename T, std::size_t N>
class ArrayAdt {
public:
  /// @brief default constructor for ArrayAdt class
  constexpr ArrayAdt() = default;

  /// @brief parametrized constructor taking initializer list
  /// @param initList list of elements to initialize the array
  /// @note it value initializes all the allocated elements
  constexpr explicit ArrayAdt(std::initializer_list<T> initList) {
    const auto initListSize{initList.size()};
    if (initListSize > m_size) {
      throw std::out_of_range(
          "Array size must be greater than or equal to init list size");
    }

    std::ranges::move(initList.begin(), initList.end(), std::begin(m_elements));
    m_no_of_elements = initListSize;
  }

  /// @brief method to display currently stored elements
  /// @return elements surrounded by square brackets
  constexpr std::string display() const noexcept {
    const auto stringify{[](auto elements[], auto length) {
      std::string result;
      for (std::size_t i{0U}; i < length; ++i) {
        result += std::string{elements[i]} + (i == length - 1U ? "" : ",");
      }
      return result;
    }};

    return std::string{
        // this expression gives: [return-from-stringify]
        std::format(R"([{}])", stringify(m_elements, m_no_of_elements))};
  }
  /// @brief method to insert element at the end
  /// @param elem element to be inserted
  /// @return true if element was inserted successfully, false otherwise
  constexpr bool append(const T& elem) noexcept {
    if (m_no_of_elements == m_size) {
      return false;
    }

    m_elements[m_no_of_elements] = elem;
    ++m_no_of_elements;
    return true;
  }

  /// @brief method to insert element at a given index
  /// @param elem element to be inserted
  /// @param index index to insert the element at
  /// @return true if element was inserted successfully, false otherwise
  /// @note if the index provided as discontiguous with the currently stored
  ///       elements in the array, the given element would be forced to be
  ///       placed after the last currently stored element, to ensure its
  ///       contiguity
  constexpr bool insert(const T& elem, std::size_t index) {
    if (m_no_of_elements == m_size) {
      // array is full
      return false;
    }

    if (index >= m_size) {
      // index out of range
      return false;
    }

    if (index < m_no_of_elements) {
      const auto elementsToShift{std::ranges::subrange(
          m_elements + index,
          m_elements + m_no_of_elements  // equivalent to end()
          )};
      std::ranges::move(elementsToShift, elementsToShift.begin() + 1U);

      m_elements[index] = elem;
    } else {
      // force the element to be at the end of the array anyway to keep the
      // elements stored contiguously
      m_elements[m_no_of_elements] = elem;
    }

    ++m_no_of_elements;
    return true;
  }

  /// @brief remove element at a certain given index of the array
  /// @param index the index at which the element shall be removed
  /// @return true if element was removed successfully, false otherwise
  constexpr bool remove(std::size_t index) {
    if (index >= m_no_of_elements) {
      return false;
    }

    const auto elementsToShift{std::ranges::subrange(
        m_elements + index + 1U,
        m_elements + m_no_of_elements + 1U  // equivalent to end()
        )};
    std::ranges::move(elementsToShift, elementsToShift.begin() - 1U);

    --m_no_of_elements;
    return true;
  }

  /// @brief method to find a certaim key in an array
  /// @param key the key used for search
  /// @return the index of the first element found,
  ///         std::numeric_limits<std::size_t>::max() otherwise
  constexpr std::size_t search(T key) const {
    const auto arrayElements{std::ranges::subrange(
        m_elements,
        m_elements + m_no_of_elements  // equivalent to end()
        )};

    const auto index{std::ranges::find(arrayElements, key)};
    return index != arrayElements.end()
               ? static_cast<std::size_t>(
                     std::distance(arrayElements.begin(), index))
               : std::numeric_limits<std::size_t>::max();
  }

  /// @brief method to return an element at a given index
  /// @param index the index at which the element shall be returned
  /// @return the element at the given index
  constexpr T get(std::size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index must be less than the array size defined");
    }

    return m_elements[index];
  }

private:
  /// @brief the actual elements of the array
  T m_elements[N]{};

  /// @brief the maximum size of the elements the array can hold
  /// @note this could be considered a compile-time alias instead of using the
  ///       template argument "N" across the file
  static constexpr auto m_size{N};

  /// @brief the number of elements currently stored in the array
  std::size_t m_no_of_elements{0U};
};

}  // namespace data_structures
