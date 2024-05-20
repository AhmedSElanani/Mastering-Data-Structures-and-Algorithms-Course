#pragma once

// NOLINTNEXTLINE(misc-include-cleaner)
#include <concepts>

/// @brief namespace for common
namespace common {

/// @brief concept for natural numbers
template <typename T>
concept NaturalNumber = std::is_unsigned_v<T>;

/// @brief defining a concept for checking a type against a parameter pack
///        whether they're not the same or not
template <typename T, typename... U>
concept NotSameType = (sizeof...(U) > 1U || std::is_same_v<T, U...> == false);

}  // namespace common
