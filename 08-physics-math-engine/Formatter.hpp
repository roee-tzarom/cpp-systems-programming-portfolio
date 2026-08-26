/**
 * @file Formatter.hpp
 * @brief Template specializations for formatting different data types.
 *
 * This file demonstrates class template specializations. It provides a generic
 * template and specific full specializations for int, double, bool, and std::string,
 * each with tailored static formatting methods.
 */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace metaengine {

/**
 * @brief Primary template for Formatter.
 * Can be used as a fallback for unknown types.
 *
 * @tparam T The type to be formatted.
 */
template <typename T>
struct Formatter {
    /**
     * @brief Formats a generic value to string.
     * @param value The value to format.
     * @return std::string The string representation.
     */
    static std::string format(const T& value) {
        // Fallback that works with any type that supports the << operator
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};

/**
 * @brief Full specialization of Formatter for 'int'.
 * Provides methods for standard and hexadecimal formatting.
 */
// Full Specialization only for the int type
template <>
struct Formatter<int> {
    /**
     * @brief Formats an integer to a standard string.
     * @param value The integer value.
     * @return std::string Standard string representation.
     */
    static std::string format(int value) {
        return std::to_string(value);
    }

    /**
     * @brief Formats an integer to a hexadecimal string.
     * @param value The integer value.
     * @return std::string Hexadecimal representation prefixed with "0x".
     */
    static std::string formatHex(int value) {
        std::ostringstream oss;
        // The hex manipulator changes the output to base 16 (hexadecimal)
        oss << "0x" << std::hex << std::uppercase << value;
        return oss.str();
    }
};

/**
 * @brief Full specialization of Formatter for 'double'.
 * Provides methods for precision control and scientific notation.
 */
template <>
struct Formatter<double> {
    /**
     * @brief Formats a double with a specific decimal precision.
     * @param value The floating-point value.
     * @param precision The number of decimal places.
     * @return std::string The formatted string.
     */
    static std::string format(double value, int precision) {
        std::ostringstream oss;
        // fixed prevents the digits from "jumping" to scientific notation, and setprecision determines how many digits will be after the decimal point
        oss << std::fixed << std::setprecision(precision) << value;
        return oss.str();
    }

    /**
     * @brief Formats a double using scientific notation.
     * @param value The floating-point value.
     * @param precision The number of decimal places.
     * @return std::string The formatted scientific string (e.g., 1.230e+02).
     */
    static std::string formatScientific(double value, int precision) {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(precision) << value;
        return oss.str();
    }

    /**
     * @brief Formats a double with a custom text label.
     * @param label The descriptive label.
     * @param value The floating-point value.
     * @return std::string The combined label and value string.
     */
    static std::string formatWithLabel(const std::string& label, double value) {
        std::ostringstream oss;
        oss << label << ": " << value;
        return oss.str();
    }
};

/**
 * @brief Full specialization of Formatter for 'bool'.
 * Provides methods for various boolean text representations.
 */
template <>
struct Formatter<bool> {
    /**
     * @brief Formats a boolean as "true" or "false".
     * @param value The boolean value.
     * @return std::string "true" if true, "false" otherwise.
     */
    static std::string format(bool value) {
        return value ? "true" : "false";
    }

    /**
     * @brief Formats a boolean as "Yes" or "No".
     * @param value The boolean value.
     * @return std::string "Yes" if true, "No" otherwise.
     */
    static std::string formatYesNo(bool value) {
        return value ? "Yes" : "No";
    }

    /**
     * @brief Formats a boolean as "ON" or "OFF".
     * @param value The boolean value.
     * @return std::string "ON" if true, "OFF" otherwise.
     */
    static std::string formatOnOff(bool value) {
        return value ? "ON" : "OFF";
    }
};

/**
 * @brief Full specialization of Formatter for 'std::string'.
 * Provides string manipulation and annotation formatting.
 */
template <>
struct Formatter<std::string> {
    /**
     * @brief Formats a string by enclosing it in quotes.
     * @param value The string value.
     * @return std::string The quoted string.
     */
    static std::string format(const std::string& value) {
        return "\"" + value + "\"";
    }

    /**
     * @brief Formats a string to all uppercase letters.
     * @param value The string value.
     * @return std::string The uppercase string.
     */
    static std::string formatUpper(std::string value) {
        std::transform(value.begin(), value.end(), value.begin(), ::toupper);
        return value;
    }

    /**
     * @brief Formats a string to all lowercase letters.
     * @param value The string value.
     * @return std::string The lowercase string.
     */
    static std::string formatLower(std::string value) {
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        return value;
    }

    /**
     * @brief Formats a string with a label and includes its length.
     * @param label The descriptive label.
     * @param value The string value.
     * @return std::string A string formatted as: label: "value" (length: X).
     */
    static std::string formatWithLabel(const std::string& label, const std::string& value) {
        return label + ": \"" + value + "\" (length: " + std::to_string(value.length()) + ")";
    }
};

} // namespace metaengine