/**
 * @file TextAnalyzer.hpp
 * @brief Class for analyzing and manipulating text using STL algorithms.
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstddef>

namespace datatools {

/**
 * @brief Analyzes and transforms text data.
 */
class TextAnalyzer {
private:
    std::string textData;

public:
    /**
     * @brief Constructs a TextAnalyzer with the given string.
     * @param inputString The text to analyze.
     */
    TextAnalyzer(const std::string& inputString);

    /**
     * @brief Counts the number of vowels in the text.
     * @return int The number of vowels.
     */
    int countVowels() const;

    /**
     * @brief Counts the number of consonants in the text.
     * @return int The number of consonants.
     */
    int countConsonants() const;

    /**
     * @brief Counts the number of digit characters in the text.
     * @return int The number of digits.
     */
    int countDigits() const;

    /**
     * @brief Counts the number of space characters in the text.
     * @return int The number of spaces.
     */
    int countSpaces() const;

    /**
     * @brief Counts occurrences of a specific character.
     * @param targetChar The character to search for.
     * @return int The number of occurrences.
     */
    int countChar(char targetChar) const;

    /**
     * @brief Checks if the text contains only alphabetic characters and spaces.
     * @return true if only letters and spaces are present, false otherwise.
     */
    bool isAlphaOnly() const;

    /**
     * @brief Checks if the text contains at least one digit.
     * @return true if a digit is found, false otherwise.
     */
    bool hasDigits() const;

    /**
     * @brief Converts all characters to uppercase.
     * @return std::string The uppercase string.
     */
    std::string toUpper() const;

    /**
     * @brief Converts all characters to lowercase.
     * @return std::string The lowercase string.
     */
    std::string toLower() const;

    /**
     * @brief Reverses the text.
     * @return std::string The reversed string.
     */
    std::string reversed() const;

    /**
     * @brief Removes all digit characters from the text.
     * @return std::string The text without digits.
     */
    std::string removeDigits() const;

    /**
     * @brief Removes all vowels from the text.
     * @return std::string The text without vowels.
     */
    std::string removeVowels() const;

    /**
     * @brief Replaces all occurrences of a character with a new one.
     * @param fromChar The character to replace.
     * @param toChar The character to insert.
     * @return std::string The modified string.
     */
    std::string replaceChar(char fromChar, char toChar) const;

    /**
     * @brief Extracts all words from the text (separated by whitespace).
     * @return std::vector<std::string> A vector of words.
     */
    std::vector<std::string> getWords() const;

    /**
     * @brief Extracts all unique words from the text.
     * @return std::vector<std::string> A vector of unique words.
     */
    std::vector<std::string> getUniqueWords() const;

    /**
     * @brief Calculates the frequency of each word in the text.
     * @return std::map<std::string, int> A map of word frequencies.
     */
    std::map<std::string, int> getWordFrequency() const;

    /**
     * @brief Finds the longest word in the text.
     * @return std::string The longest word.
     */
    std::string longestWord() const;

    /**
     * @brief Finds the shortest word in the text.
     * @return std::string The shortest word.
     */
    std::string shortestWord() const;

    /**
     * @brief Returns words sorted by their length (shortest to longest).
     * @return std::vector<std::string> The sorted words.
     */
    std::vector<std::string> wordsSortedByLength() const;

    /**
     * @brief Returns words that are strictly longer than a given length.
     * @param lengthThreshold The minimum length threshold.
     * @return std::vector<std::string> Words longer than the threshold.
     */
    std::vector<std::string> wordsLongerThan(size_t lengthThreshold) const;

    /**
     * @brief Joins all words using a specific delimiter.
     * @param delimiter The string used to join the words.
     * @return std::string The joined string.
     */
    std::string joinWords(const std::string& delimiter) const;
};

} // namespace datatools