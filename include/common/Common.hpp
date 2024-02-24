#pragma once

// NOLINTNEXTLINE(misc-include-cleaner)
#include <concepts>

/// @brief namespace for common
namespace common {

/// @brief concept for natural numbers
template <typename T>
concept NaturalNumber = std::is_unsigned_v<T>;

}  // namespace common
