/**
 * @file TypeInfo.hpp
 * @brief Type information traits with template specializations.
 *
 * This file demonstrates full and partial template specializations to extract
 * type information at compile-time using static constexpr variables and a
 * static describe() method.
 */

#pragma once

#include <string>
#include <sstream>
#include <limits>

namespace metaengine {

/**
 * @brief Primary template for TypeInfo.
 * Provides fallback information for unknown types.
 *
 * @tparam T The generic type to be queried.
 */
template <typename T>
struct TypeInfo {
    static constexpr const char* name = "Unknown";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr size_t size = sizeof(T);

    /**
     * @brief Generates a descriptive string for the unknown type.
     * @return std::string A description containing the size of the type.
     */
    static std::string describe() {
        return "Unknown type of size " + std::to_string(size) + " bytes";
    }
};

/**
 * @brief Full specialization of TypeInfo for 'int'.
 * Provides specific traits and value ranges for standard integers.
 */
template <>
struct TypeInfo<int> {
    static constexpr const char* name = "int";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr size_t size = sizeof(int);
    
    // Using (-2147483647 - 1) for INT_MIN to avoid compiler warnings about literal ranges
    // We write it this way to prevent the compiler from throwing an overflow warning on the maximum negative number
    static constexpr int min_value = (-2147483647 - 1); 
    static constexpr int max_value = 2147483647;

    /**
     * @brief Generates a descriptive string for the int type.
     * @return std::string A description containing traits, size, and numeric range.
     */
    static std::string describe() {
        return "int: numeric type, size " + std::to_string(size) + " bytes, range [" +
               std::to_string(min_value) + ", " + std::to_string(max_value) + "]";
    }
};

/**
 * @brief Full specialization of TypeInfo for 'double'.
 * Provides specific traits for double-precision floating-point numbers.
 */
template <>
struct TypeInfo<double> {
    static constexpr const char* name = "double";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr size_t size = sizeof(double);

    /**
     * @brief Generates a descriptive string for the double type.
     * @return std::string A description containing traits, size, and standard epsilon.
     */
    static std::string describe() {
        return "double: floating-point type, size " + std::to_string(size) + " bytes, epsilon 1e-9";
    }
};

/**
 * @brief Full specialization of TypeInfo for 'bool'.
 * Provides specific traits for boolean values.
 */
template <>
struct TypeInfo<bool> {
    static constexpr const char* name = "bool";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr size_t size = sizeof(bool);

    /**
     * @brief Generates a descriptive string for the bool type.
     * @return std::string A description containing traits and size.
     */
    static std::string describe() {
        return "bool: boolean type, size " + std::to_string(size) + " byte" + (size > 1 ? "s" : "");
    }
};

/**
 * @brief Full specialization of TypeInfo for 'std::string'.
 * Provides specific traits for standard strings.
 */
template <>
struct TypeInfo<std::string> {
    static constexpr const char* name = "string";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr size_t size = sizeof(std::string);

    /**
     * @brief Generates a descriptive string for the std::string type.
     * @return std::string A description containing traits and size (which is platform-dependent).
     */
    static std::string describe() {
        return "string: text type, size " + std::to_string(size) + " bytes";
    }
};

/**
 * @brief Partial specialization of TypeInfo for pointers (T*).
 * Matches any raw pointer type and extracts traits about the pointed-to type.
 *
 * @tparam T The type that the pointer points to.
 */
// Partial specialization: catches all pointer types whatsoever, and extracts the type the pointer points to (T)
template <typename T>
struct TypeInfo<T*> {
    static constexpr const char* name = "pointer";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = true;
    static constexpr size_t size = sizeof(T*);

    /**
     * @brief Generates a descriptive string for the pointer type.
     * @return std::string A description indicating the underlying type and the size of the pointer.
     */
    static std::string describe() {
        return "pointer to " + std::string(TypeInfo<T>::name) + ", size " + std::to_string(size) + " bytes";
    }
};

} // namespace metaengine