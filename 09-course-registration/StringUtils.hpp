/**
 * @file StringUtils.hpp
 * @brief Utility functions for string manipulation.
 */

#pragma once

#include <string>
#include <vector>

namespace registration {

/**
 * @brief Converts a string to uppercase.
 * @param text The input string.
 * @return A new string with all characters converted to uppercase.
 */
std::string toUpper(const std::string& text);

/**
 * @brief Converts a string to lowercase.
 * @param text The input string.
 * @return A new string with all characters converted to lowercase.
 */
std::string toLower(const std::string& text);

/**
 * @brief Removes leading and trailing whitespace from a string.
 * @param text The input string.
 * @return A new string with whitespace removed from both ends.
 */
std::string trim(const std::string& text);

/**
 * @brief Splits a string into a vector of substrings based on a delimiter.
 * @param text The input string to split.
 * @param delimiter The character used to split the string.
 * @return A vector containing the extracted substrings.
 */
std::vector<std::string> split(const std::string& text, char delimiter);

/**
 * @brief Joins a vector of strings into a single string with a delimiter.
 * @param parts The vector of strings to join.
 * @param delimiter The string used to separate the parts.
 * @return The joined string.
 */
std::string join(const std::vector<std::string>& parts, const std::string& delimiter);

/**
 * @brief Checks if a string starts with a specific prefix.
 * @param text The string to check.
 * @param prefix The prefix to look for.
 * @return true if the string starts with the prefix, false otherwise.
 */
bool startsWith(const std::string& text, const std::string& prefix);

/**
 * @brief Checks if a string ends with a specific suffix.
 * @param text The string to check.
 * @param suffix The suffix to look for.
 * @return true if the string ends with the suffix, false otherwise.
 */
bool endsWith(const std::string& text, const std::string& suffix);

/**
 * @brief Replaces all occurrences of a substring with another substring.
 * @param text The original string.
 * @param from The substring to replace.
 * @param to The substring to insert in place of 'from'.
 * @return A new string with the replacements applied.
 */
std::string replaceAll(const std::string& text, const std::string& from, const std::string& to);

/**
 * @brief Counts the occurrences of a specific character in a string.
 * @param text The string to search.
 * @param c The character to count.
 * @return The number of times the character appears in the string.
 */
int countChar(const std::string& text, char targetChar);

/**
 * @brief Checks if a string is a palindrome (ignoring spaces and case).
 * @param text The string to check.
 * @return true if the string is a palindrome, false otherwise.
 */
bool isPalindrome(const std::string& text);

/**
 * @brief Reverses the characters in a string.
 * @param text The string to reverse.
 * @return A new string with the characters in reverse order.
 */
std::string reverseString(const std::string& text);

} // namespace registration