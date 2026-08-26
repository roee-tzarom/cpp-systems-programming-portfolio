/**
 * @file DecltypeUtils.hpp
 * @brief Utilities demonstrating the use of decltype and type traits.
 *
 * This file contains template functions that accept mixed types and use
 * trailing return types with decltype to automatically deduce the correct
 * return type at compile-time. It also provides compile-time type checks.
 */

#pragma once

#include <type_traits>
#include <utility>

namespace metaengine {

/**
 * @brief Adds two values of potentially different types.
 * Uses trailing return type to deduce the result of the addition.
 *
 * @tparam T The type of the first operand.
 * @tparam U The type of the second operand.
 * @param a The first value.
 * @param b The second value.
 * @return The sum of a and b, with the type deduced by decltype.
 */
template <typename T, typename U>
constexpr auto add(T a, U b) -> decltype(a + b) {
    // The arrow (trailing return type) along with decltype allows the compiler to deduce the return type on its own (e.g., int + double = double)
    return a + b;
}

/**
 * @brief Multiplies two values of potentially different types.
 *
 * @tparam T The type of the first operand.
 * @tparam U The type of the second operand.
 * @param a The first value.
 * @param b The second value.
 * @return The product of a and b, with the type deduced by decltype.
 */
template <typename T, typename U>
constexpr auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

/**
 * @brief Finds the maximum of two values of potentially different types.
 * Uses std::remove_reference_t to ensure a value is returned, preventing
 * dangling references when both operands are of the same type.
 *
 * @tparam T The type of the first operand.
 * @tparam U The type of the second operand.
 * @param a The first value.
 * @param b The second value.
 * @return The maximum of a and b, strictly as a value.
 */
template <typename T, typename U>
constexpr auto maxOf(T a, U b) -> std::remove_reference_t<decltype(a > b ? a : b)> {
    // remove_reference_t is critical here: it prevents a severe bug of returning a reference to a local variable (dangling reference) in case both types are the same
    return a > b ? a : b;
}

/**
 * @brief Finds the minimum of two values of potentially different types.
 * Uses std::remove_reference_t to ensure a value is returned, preventing
 * dangling references when both operands are of the same type.
 *
 * @tparam T The type of the first operand.
 * @tparam U The type of the second operand.
 * @param a The first value.
 * @param b The second value.
 * @return The minimum of a and b, strictly as a value.
 */
template <typename T, typename U>
constexpr auto minOf(T a, U b) -> std::remove_reference_t<decltype(a < b ? a : b)> {
    return a < b ? a : b;
}

/**
 * @brief Checks at compile-time if the result of adding T and U is a floating-point type.
 *
 * Uses std::declval to simulate the addition of T and U without evaluating them,
 * and std::is_floating_point_v to check the resulting type.
 *
 * @tparam T The type of the first hypothetical operand.
 * @tparam U The type of the second hypothetical operand.
 * @return true if the resulting type of (T + U) is a floating-point type, false otherwise.
 */
template <typename T, typename U>
constexpr bool isAddResultFloating() {
    // std::declval fakes the creation of an object to check what happens if we add them, without requiring a default constructor from the type
    return std::is_floating_point_v<decltype(std::declval<T>() + std::declval<U>())>;
}

/**
 * @brief Checks at compile-time if the result of multiplying T and U is an integral type.
 *
 * @tparam T The type of the first hypothetical operand.
 * @tparam U The type of the second hypothetical operand.
 * @return true if the resulting type of (T * U) is an integral type, false otherwise.
 */
template <typename T, typename U>
constexpr bool isMulResultIntegral() {
    return std::is_integral_v<decltype(std::declval<T>() * std::declval<U>())>;
}

} // namespace metaengine