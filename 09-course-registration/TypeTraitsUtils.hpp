/**
 * @file TypeTraitsUtils.hpp
 * @brief Template functions and type traits utilities for compile-time type checking.
 */

#pragma once

#include <string>
#include <type_traits>
#include <sstream>

namespace registration {

/**
 * @brief Describes the category of a given type at compile-time.
 * @tparam T The type to analyze.
 * @return A string representing the type category ("integral", "floating-point", "string", "pointer", or "unknown").
 */
template <typename T>
std::string describeType() {
    if constexpr (std::is_pointer_v<T>) {
        return "pointer";
    } else if constexpr (std::is_integral_v<T>) {
        return "integral";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating-point";
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "string";
    } else {
        return "unknown";
    }
}

/**
 * @brief Checks if a given type is a numeric type (integral or floating-point).
 * @tparam T The type to check.
 * @return true if the type is arithmetic, false otherwise.
 */
template <typename T>
constexpr bool isNumeric() {
    return std::is_arithmetic_v<T>;
}

/**
 * @brief Checks if two given types are exactly the same.
 * @tparam T The first type.
 * @tparam U The second type.
 * @return true if T and U are the same type, false otherwise.
 */
template <typename T, typename U>
constexpr bool areSameType() {
    return std::is_same_v<T, U>;
}

/**
 * @brief Converts a numeric value to its string representation.
 * Automatically formats whole floating-point numbers with .00 to match formatting rules.
 * @tparam T The type of the value.
 * @param val The value to convert.
 * @return The string representation of the value.
 */
template <typename T>
std::string numericToString(T val) {
    std::ostringstream oss;
    oss << val;
    std::string res = oss.str();
    
    // Add ".00" for floating point numbers that evaluate to whole integers (like 0.0)
    if constexpr (std::is_floating_point_v<T>) {
        if (res.find('.') == std::string::npos) {
            res += ".00";
        }
    }
    return res;
}

/**
 * @brief Safely adds two numeric values.
 * If both values are integral, promotes the result to long long to prevent overflow.
 * @tparam T The type of the first operand.
 * @tparam U The type of the second operand.
 * @param a The first value.
 * @param b The second value.
 * @return The sum of a and b, with appropriate type promotion.
 */
template <typename T, typename U>
auto safeAdd(T a, U b) {
    if constexpr (std::is_integral_v<T> && std::is_integral_v<U>) {
        return static_cast<long long>(a) + static_cast<long long>(b);
    } else {
        return a + b;
    }
}

/**
 * @brief Returns the default "zero" or empty value for a specific type.
 * @tparam T The type to generate the zero value for.
 * @return 0 for numbers, "" for strings.
 */
template <typename T>
T getZero() {
    if constexpr (std::is_same_v<T, std::string>) {
        return "";
    } else {
        return static_cast<T>(0);
    }
}

} // namespace registration