#pragma once

#include <algorithm>
#include <cstdint>
#include <format>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

#include "common/Common.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief directions for shifting the elements
enum class shiftDir : uint8_t { left, right };

/// @brief class representing Array abstract data type
template <typename T, common::NaturalNumber auto N>
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
    m_numberOfElements = initListSize;
  }

  /// @brief method to insert element at the end
  /// @param elem element to be inserted
  /// @return true if element was inserted successfully, false otherwise
  constexpr bool append(const T& elem) noexcept {
    if (m_numberOfElements == m_size) {
      return false;
    }

    m_elements[m_numberOfElements] = elem;
    ++m_numberOfElements;
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
    if (m_numberOfElements == m_size) {
      // array is full
      return false;
    }

    if (index >= m_size) {
      // index out of range
      return false;
    }

    if (index < m_numberOfElements) {
      const auto elementsToShift{std::ranges::subrange(
          m_elements + index,
          m_elements + m_numberOfElements  // equivalent to end()
          )};
      std::ranges::move(elementsToShift, elementsToShift.begin() + 1U);

      m_elements[index] = elem;
    } else {
      // force the element to be at the end of the array anyway to keep the
      // elements stored contiguously
      m_elements[m_numberOfElements] = elem;
    }

    ++m_numberOfElements;
    return true;
  }

  /// @brief remove element at a certain given index of the array
  /// @param index the index at which the element shall be removed
  /// @return true if element was removed successfully, false otherwise
  constexpr bool remove(std::size_t index) {
    if (index >= m_numberOfElements) {
      return false;
    }

    const auto elementsToShift{std::ranges::subrange(
        m_elements + index + 1U,
        m_elements + m_numberOfElements + 1U  // equivalent to end()
        )};
    std::ranges::move(elementsToShift, elementsToShift.begin() - 1U);

    --m_numberOfElements;
    return true;
  }

  /// @brief method to find a certaim key in an array
  /// @param key the key used for search
  /// @return the index of the first element found,
  ///         std::numeric_limits<std::size_t>::max() otherwise
  constexpr std::size_t search(T key) const {
    const auto arrayElements{std::ranges::subrange(
        m_elements,
        m_elements + m_numberOfElements  // equivalent to end()
        )};

    const auto index{std::ranges::find(arrayElements, key)};
    return index != arrayElements.end()
               ? static_cast<std::size_t>(
                     std::distance(arrayElements.begin(), index))
               : std::numeric_limits<std::size_t>::max();
  }

  /// @brief method to set an element at a given index
  /// @param elem the element to be set at the given index
  /// @param index the index at which the element shall be set
  /// @note this method assumes element exists already, i.e size won't increase
  constexpr void set(const T& elem, std::size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("Index must be less than the array size defined");
    }

    m_elements[index] = elem;
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

  /// @brief returns the maximum element of the array
  /// @return the maximum element of the array
  constexpr T max() const {
    return std::ranges::max(std::span{m_elements, m_numberOfElements});
  }

  /// @brief returns the minimum element of the array
  /// @return the minimum element of the array
  constexpr T min() const {
    return std::ranges::min(std::span{m_elements, m_numberOfElements});
  }

  /// @brief calculates the total sum of all elements of the array
  /// @return the sum of all elements of the array
  constexpr T sum() const {
    const std::span arr{
        std::begin(m_elements),
        std::begin(m_elements) + m_numberOfElements  // equivalent to end()
    };

    return std::accumulate(arr.begin(), arr.end(),
                           0U  // accumulate elements to initial value of zero,
                               // to have their sum only
    );
  }

  /// @brief calculates the average of all elements of the array
  /// @return the average of all elements of the array
  constexpr double avg() const {
    return static_cast<double>(sum()) / static_cast<double>(m_numberOfElements);
  }

  /// @brief method to reverse the array elements
  /// @return a reference to the current object to support chained operations
  constexpr ArrayAdt& reverse() {
    std::ranges::reverse(std::span{m_elements, m_numberOfElements});
    return *this;  // to enable chained operations if needed
  }

  /// @brief a method to shift the elements in both directions
  /// @param numberOfShifts number of places to shift
  /// @param dir direction of shifting left or right
  /// @note currently, there are no gurantees on the objects's states on the
  ///       shifted sides
  /// @return a reference to the current object to support chained operations
  constexpr ArrayAdt& shift(std::size_t numberOfShifts, shiftDir dir) {
    switch (std::span arr{m_elements, m_numberOfElements}; dir) {
      case (shiftDir::left): {
        std::shift_left(
            arr.begin(), arr.end(),
            std::make_signed_t<decltype(numberOfShifts)>(numberOfShifts));
      } break;

      case (shiftDir::right): {
        std::shift_right(
            arr.begin(), arr.end(),
            std::make_signed_t<decltype(numberOfShifts)>(numberOfShifts));
      } break;

      default: {
      } break;
    }

    return *this;  // to enable chained operations if needed
  }

  /// @brief a method to rotate the elements in both directions
  /// @param numberOfShifts number of places to shift
  /// @param dir direction of rotation left or right
  /// @return a reference to the current object to support chained operations
  constexpr ArrayAdt& rotate(std::size_t numberOfShifts, shiftDir dir) {
    if (m_numberOfElements == 0U) {
      // there are no elements to rotate
      return *this;  // to enable chained operations if needed
    }

    // normalize shift positions
    numberOfShifts = numberOfShifts % m_numberOfElements;
    if (numberOfShifts == 0U) {
      // shift is not needed
      return *this;  // to enable chained operations if needed
    }

    switch (std::span arr{m_elements, m_numberOfElements}; dir) {
      case (shiftDir::left): {
        std::ranges::rotate(
            arr, arr.begin() + std::make_signed_t<decltype(numberOfShifts)>(
                                   numberOfShifts));
      } break;

      case (shiftDir::right): {
        std::ranges::rotate(
            arr, arr.end() - std::make_signed_t<decltype(numberOfShifts)>(
                                 numberOfShifts));
      } break;

      default: {
      } break;
    }

    return *this;  // to enable chained operations if needed
  }

  /// @brief method to merge current array with a given input array
  /// @param input given input array to be merged with current one
  /// @return true in case of successful merge, false otherwise
  /// @note preconditions: both arrays are sorted and fit in the current
  ///       destination array.
  template <common::NaturalNumber auto Ne>
  constexpr bool mergeWith(const ArrayAdt<T, Ne>& input) {
    const auto outputArraySize{m_numberOfElements + input.m_numberOfElements};
    if (outputArraySize > m_size) {
      return false;
    }

    auto mergetwoArrays{[](auto firstInputArr, auto secondInputArr,
                           auto outArr) {
      const auto mergingPrecondition{std::ranges::is_sorted(firstInputArr) &&
                                     std::ranges::is_sorted(secondInputArr)};
      if (mergingPrecondition == false) {
        return false;
      }

      std::ranges::merge(firstInputArr, secondInputArr, outArr);
      return true;
    }};

    auto mergeResult{std::vector<T>(outputArraySize)};
    auto arraysMerged{
        mergetwoArrays(std::span{m_elements, m_numberOfElements},
                       std::span{input.m_elements, input.m_numberOfElements},
                       mergeResult.begin())};

    if (arraysMerged == false) {
      return false;
    }

    std::ranges::move(mergeResult.begin(), mergeResult.end(),
                      std::begin(m_elements));
    m_numberOfElements = mergeResult.size();
    return true;
  }

  /// @brief method to display currently stored elements
  /// @return elements surrounded by square brackets
  constexpr std::string display() const noexcept {
    const auto stringify{[](auto elements[], auto length) {
      std::string result;
      for (std::size_t i{0U}; i < length; ++i) {
        result += std::to_string(elements[i]) + (i == length - 1U ? "" : ",");
      }
      return result;
    }};

    return std::string{
        // this expression gives: [return-from-stringify]
        std::format("[{}]", stringify(m_elements, m_numberOfElements))};
  }

  /// @brief method to find the current number of elements stored in the array
  /// @return the current number of elements stored in the array
  constexpr std::size_t length() const noexcept { return m_numberOfElements; }

  /// @brief method to get the largest possible number of elements that can be
  ///        stored in the array
  /// @return the largest possible number of elements that can be stored in the
  ///         array
  constexpr std::size_t size() const noexcept { return m_size; }

private:
  /// @brief the actual elements of the array
  T m_elements[N]{};

  /// @brief the maximum size of the elements the array can hold
  /// @note this could be considered a compile-time alias instead of using the
  ///       template argument "N" across the file
  static constexpr auto m_size{N};

  /// @brief the number of elements currently stored in the array
  std::size_t m_numberOfElements{0U};

  /// @brief friend with ArrayAdt instances of different sizes and types
  /// @tparam U  type of the elements of the friend ArrayAdt instance
  /// @tparam Ne size of the other  ArrayAdt instance
  template <typename U, common::NaturalNumber auto Ne>
  friend class ArrayAdt;
};

}  // namespace data_structures
