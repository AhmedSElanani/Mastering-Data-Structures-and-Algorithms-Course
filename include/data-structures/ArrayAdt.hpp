#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>

// NOLINTNEXTLINE(misc-include-cleaner)
#include <format>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <numeric>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// NOLINTNEXTLINE(misc-include-cleaner)
#include "common/Common.hpp"

/// @brief namespace for data structures implemented
namespace data_structures {

/// @brief directions for shifting the elements
enum class shiftDir : uint8_t { kLeft, kRight };

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
    if (initListSize > kMSize) {
      throw std::out_of_range(
          "Array size must be greater than or equal to init list size");
    }

    std::ranges::move(initList.begin(), initList.end(), std::begin(m_elements));
    m_numberOfElements = initListSize;
  }

  /// @brief method to insert element at the end
  /// @param elem element to be inserted
  /// @return true if element was inserted successfully, false otherwise
  constexpr auto append(const T& elem) noexcept -> bool {
    if (m_numberOfElements == kMSize) {
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
  constexpr auto insert(const T& elem, std::size_t index) -> bool {
    if (m_numberOfElements == kMSize) {
      // array is full
      return false;
    }

    if (index >= kMSize) {
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
  constexpr auto remove(std::size_t index) -> bool {
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
  constexpr auto search(T key) const -> std::size_t {
    const auto arrayElements{std::ranges::subrange(
        m_elements,
        m_elements + m_numberOfElements  // equivalent to end()
        )};

    const auto index{std::ranges::find(arrayElements, key)};
    return index != arrayElements.end()
               ? static_cast<std::size_t>(
                     std::distance(arrayElements.cbegin(), index))
               : std::numeric_limits<std::size_t>::max();
  }

  /// @brief method to set an element at a given index
  /// @param elem the element to be set at the given index
  /// @param index the index at which the element shall be set
  /// @note this method assumes element exists already, i.e size won't increase
  constexpr void set(const T& elem, std::size_t index) {
    if (index >= kMSize) {
      throw std::out_of_range("Index must be less than the array size defined");
    }

    m_elements[index] = elem;
  }

  /// @brief method to return an element at a given index
  /// @param index the index at which the element shall be returned
  /// @return the element at the given index
  constexpr auto get(std::size_t index) const -> T {
    if (index >= kMSize) {
      throw std::out_of_range("Index must be less than the array size defined");
    }

    return m_elements[index];
  }

  /// @brief returns the maximum element of the array
  /// @return the maximum element of the array
  constexpr auto max() const -> T {
    return std::ranges::max(std::span{m_elements, m_numberOfElements});
  }

  /// @brief returns the minimum element of the array
  /// @return the minimum element of the array
  constexpr auto min() const -> T {
    return std::ranges::min(std::span{m_elements, m_numberOfElements});
  }

  /// @brief calculates the total sum of all elements of the array
  /// @return the sum of all elements of the array
  constexpr auto sum() const -> T {
    const std::span arr{
        std::begin(m_elements),
        std::begin(m_elements) + m_numberOfElements  // equivalent to end()
    };

    return std::accumulate(arr.cbegin(), arr.cend(),
                           0U  // accumulate elements to initial value of zero,
                               // to have their sum only
    );
  }

  /// @brief calculates the average of all elements of the array
  /// @return the average of all elements of the array
  [[nodiscard]] constexpr auto avg() const -> double {
    return static_cast<double>(sum()) / static_cast<double>(m_numberOfElements);
  }

  /// @brief method to reverse the array elements
  /// @return a reference to the current object to support chained operations
  constexpr auto reverse() -> ArrayAdt& {
    std::ranges::reverse(std::span{m_elements, m_numberOfElements});
    return *this;  // to enable chained operations if needed
  }

  /// @brief a method to shift the elements in both directions
  /// @param numberOfShifts number of places to shift
  /// @param dir direction of shifting left or right
  /// @note currently, there are no gurantees on the objects's states on the
  ///       shifted sides
  /// @return a reference to the current object to support chained operations
  constexpr auto shift(std::size_t numberOfShifts, shiftDir dir) -> ArrayAdt& {
    switch (std::span arr{m_elements, m_numberOfElements}; dir) {
      case (shiftDir::kLeft): {
        std::shift_left(
            arr.begin(), arr.end(),
            static_cast<std::make_signed_t<decltype(numberOfShifts)>>(
                numberOfShifts));
      } break;

      case (shiftDir::kRight): {
        std::shift_right(
            arr.begin(), arr.end(),
            static_cast<std::make_signed_t<decltype(numberOfShifts)>>(
                numberOfShifts));
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
  constexpr auto rotate(std::size_t numberOfShifts, shiftDir dir) -> ArrayAdt& {
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
      case (shiftDir::kLeft): {
        std::ranges::rotate(
            arr, arr.begin() +
                     static_cast<std::make_signed_t<decltype(numberOfShifts)>>(
                         numberOfShifts));
      } break;

      case (shiftDir::kRight): {
        std::ranges::rotate(
            arr, arr.end() -
                     static_cast<std::make_signed_t<decltype(numberOfShifts)>>(
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
  constexpr auto mergeWith(const ArrayAdt<T, Ne>& input) -> bool {
    const auto outputArraySize{m_numberOfElements + input.m_numberOfElements};
    if (outputArraySize > kMSize) {
      return false;
    }

    auto mergetwoArrays{[](auto firstInputArr, auto secondInputArr,
                           auto outArr) {
      const auto mergingPrecondition{std::ranges::is_sorted(firstInputArr) &&
                                     std::ranges::is_sorted(secondInputArr)};
      if (!mergingPrecondition) {
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

    if (!arraysMerged) {
      return false;
    }

    std::ranges::move(mergeResult.begin(), mergeResult.end(),
                      std::begin(m_elements));
    m_numberOfElements = mergeResult.size();
    return true;
  }

  /// @brief a function to return the union of two ArrayAdts passed
  /// @param arr1 first ArrayAdt passed
  /// @param arr2 second ArrayAdt passed
  /// @return the union of both arrays in object of capacity that must be
  ///         equal to or more than the sum of both passed arrays
  /// @note preconditions: both arrays are sorted and fit in the set
  ///       destination array.
  template <common::NaturalNumber auto N1, common::NaturalNumber auto N2>
  static constexpr auto unionSet(const ArrayAdt<T, N1>& arr1,
                                 const ArrayAdt<T, N2>& arr2) -> ArrayAdt {
    constexpr auto kResultSize{kMSize};
    const auto combinedSizes{arr1.length() + arr2.length()};
    if (kResultSize < combinedSizes) {
      return {};
    }

    const std::span firstInputArr{arr1.m_elements, arr1.m_numberOfElements};
    const std::span secondInputArr{arr2.m_elements, arr2.m_numberOfElements};

    const auto bothInputsSorted{std::ranges::is_sorted(firstInputArr) &&
                                std::ranges::is_sorted(secondInputArr)};
    if (!bothInputsSorted) {
      return {};
    }

    auto unionResult{std::vector<T>(combinedSizes)};
    const auto ret{std::ranges::set_union(firstInputArr, secondInputArr,
                                          unionResult.begin())};

    // take only the elements resulting from the set operation
    ArrayAdt<T, kResultSize> unifiedArrays;

    unifiedArrays.m_numberOfElements =
        static_cast<std::size_t>(std::distance(unionResult.begin(), ret.out));

    std::ranges::move(unionResult.begin(), ret.out,
                      std::begin(unifiedArrays.m_elements));

    return unifiedArrays;
  }

  /// @brief a function that returns an array containing elements which
  ///        exclusively found in first passed array only
  /// @param arr1 first ArrayAdt passed
  /// @param arr2 second ArrayAdt passed
  /// @return an array containing elements which exclusively found in first
  ///         passed array only
  /// @note preconditions: both arrays are sorted and fit in the set
  ///       destination array.
  template <common::NaturalNumber auto N1, common::NaturalNumber auto N2>
  static constexpr auto differenceSet(const ArrayAdt<T, N1>& arr1,
                                      const ArrayAdt<T, N2>& arr2) -> ArrayAdt {
    constexpr auto kResultSize{kMSize};
    const auto maxPossibleSize{arr1.length()};
    if (kResultSize < maxPossibleSize) {
      return {};
    }

    const std::span firstInputArr{arr1.m_elements, arr1.m_numberOfElements};
    const std::span secondInputArr{arr2.m_elements, arr2.m_numberOfElements};

    const auto bothInputsSorted{std::ranges::is_sorted(firstInputArr) &&
                                std::ranges::is_sorted(secondInputArr)};
    if (!bothInputsSorted) {
      return {};
    }

    auto differenceResult{std::vector<T>(maxPossibleSize)};
    const auto ret{std::ranges::set_difference(firstInputArr, secondInputArr,
                                               differenceResult.begin())};

    // take only the elements resulting from the set operation
    ArrayAdt<T, kResultSize> differenceArray;

    differenceArray.m_numberOfElements = static_cast<std::size_t>(
        std::distance(differenceResult.begin(), ret.out));

    std::ranges::move(differenceResult.begin(), ret.out,
                      std::begin(differenceArray.m_elements));

    return differenceArray;
  }

  /// @brief a function that returns an array containing elements which exist in
  ///        both given arrays
  /// @param arr1 first ArrayAdt passed
  /// @param arr2 second ArrayAdt passed
  /// @return an array containing elements which which exist in both given
  ///         arrays
  /// @note preconditions: both arrays are sorted and the larger of them fit in
  ///       the set destination array.
  template <common::NaturalNumber auto N1, common::NaturalNumber auto N2>
  static constexpr auto intersectionSet(
      const ArrayAdt<T, N1>& arr1, const ArrayAdt<T, N2>& arr2) -> ArrayAdt {
    constexpr auto kResultSize{kMSize};
    const auto maxOfBothArrSize{std::max(arr1.length(), arr2.length())};
    if (kResultSize < maxOfBothArrSize) {
      return {};
    }

    const std::span firstInputArr{arr1.m_elements, arr1.m_numberOfElements};
    const std::span secondInputArr{arr2.m_elements, arr2.m_numberOfElements};

    const auto bothInputsSorted{std::ranges::is_sorted(firstInputArr) &&
                                std::ranges::is_sorted(secondInputArr)};
    if (!bothInputsSorted) {
      return {};
    }

    auto intersectionResult{std::vector<T>(maxOfBothArrSize)};
    const auto ret{std::ranges::set_intersection(firstInputArr, secondInputArr,
                                                 intersectionResult.begin())};

    // take only the elements resulting from the set operation
    ArrayAdt<T, kResultSize> intersectionArray;

    intersectionArray.m_numberOfElements = static_cast<std::size_t>(
        std::distance(intersectionResult.begin(), ret.out));

    std::ranges::move(intersectionResult.begin(), ret.out,
                      std::begin(intersectionArray.m_elements));

    return intersectionArray;
  }

  /// @brief method to display currently stored elements
  /// @return elements surrounded by square brackets
  [[nodiscard]] constexpr auto display() const noexcept -> std::string {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
    const auto stringify{[](auto elements[], auto length) {
      std::string result;
      for (std::size_t i{0U}; i < length; ++i) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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
  [[nodiscard]] constexpr auto length() const noexcept -> std::size_t {
    return m_numberOfElements;
  }

  /// @brief method to get the largest possible number of elements that can be
  ///        stored in the array
  /// @return the largest possible number of elements that can be stored in the
  ///         array
  static constexpr auto size() noexcept -> std::size_t { return kMSize; }

private:
  /// @brief the actual elements of the array
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
  T m_elements[N]{};

  /// @brief the maximum size of the elements the array can hold
  /// @note this could be considered a compile-time alias instead of using the
  ///       template argument "N" across the file
  static constexpr auto kMSize{N};

  /// @brief the number of elements currently stored in the array
  std::size_t m_numberOfElements{0U};

  /// @brief friend with ArrayAdt instances of different sizes and types
  /// @tparam U  type of the elements of the friend ArrayAdt instance
  /// @tparam Ne size of the other  ArrayAdt instance
  template <typename U, common::NaturalNumber auto Ne>
  friend class ArrayAdt;
};

}  // namespace data_structures
