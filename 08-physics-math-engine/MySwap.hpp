/**
 * @file MySwap.hpp
 * @brief Template specializations for swap operations.
 *
 * This file demonstrates function template specializations. It includes a generic
 * swap function and specific, optimized specializations for types like int (using XOR),
 * std::string (using the optimized built-in swap), and bool (using logical swap).
 */

#pragma once

#include <iostream>
#include <string>
#include <utility>

namespace metaengine {

/**
 * @brief Generic swap function for any type.
 * Uses standard move semantics to swap two values efficiently.
 * Prints "Generic swap" to standard output.
 * * @tparam T The type of the elements to be swapped.
 * @param a Reference to the first element.
 * @param b Reference to the second element.
 */
template <typename T>
void mySwap(T& a, T& b) {
    std::cout << "Generic swap\n";
    // Using std::move allows "stealing" the value without doing a heavy copy in memory (Move Semantics)
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

/**
 * @brief Full template specialization for 'int'.
 * Implements the XOR swap algorithm, which swaps two integers without 
 * requiring a temporary variable. Includes a safeguard against self-swapping 
 * (which would mistakenly zero out the variable).
 * Prints "Int XOR swap" to standard output.
 * * @param a Reference to the first integer.
 * @param b Reference to the second integer.
 */
template <>
inline void mySwap<int>(int& a, int& b) {
    std::cout << "Int XOR swap\n";
    // The check is critical: XOR on the same memory location will simply zero out the variable and erase it
    if (&a != &b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

/**
 * @brief Full template specialization for 'std::string'.
 * Uses the built-in, highly optimized std::string::swap method which typically
 * swaps internal pointers rather than copying character arrays.
 * Prints "String optimized swap" to standard output.
 * * @param a Reference to the first string.
 * @param b Reference to the second string.
 */
template <>
inline void mySwap<std::string>(std::string& a, std::string& b) {
    std::cout << "String optimized swap\n";
    // The built-in string swap function only swaps the character pointers instead of copying them all. Super fast.
    a.swap(b);
}

/**
 * @brief Full template specialization for 'bool'.
 * Implements a logical swap without a temporary variable using the != operator.
 * Includes a safeguard against self-swapping.
 * Prints "Bool logical swap" to standard output.
 * * @param a Reference to the first boolean.
 * @param b Reference to the second boolean.
 */
template <>
inline void mySwap<bool>(bool& a, bool& b) {
    std::cout << "Bool logical swap\n";
    // Check if they are not the same memory location
    if (&a != &b) {
        a = (a != b);
        b = (a != b);
        a = (a != b);
    }
}

} // namespace metaengine