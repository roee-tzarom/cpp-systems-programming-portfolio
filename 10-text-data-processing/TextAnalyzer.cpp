#include "TextAnalyzer.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>
#include <numeric>

namespace datatools {

TextAnalyzer::TextAnalyzer(const std::string& inputString) : textData(inputString) {}

int TextAnalyzer::countVowels() const {
    // Counts only if the character matches one of the vowels. Converts to lower so as not to check uppercase letters as well
    return static_cast<int>(std::count_if(textData.begin(), textData.end(), [](char chr) {
        char lowerChar = static_cast<char>(std::tolower(static_cast<unsigned char>(chr)));
        return lowerChar == 'a' || lowerChar == 'e' || lowerChar == 'i' || lowerChar == 'o' || lowerChar == 'u';
    }));
}

int TextAnalyzer::countConsonants() const {
    return static_cast<int>(std::count_if(textData.begin(), textData.end(), [](char chr) {
        // isalpha ensures we don't accidentally count numbers or spaces as consonants
        if (std::isalpha(static_cast<unsigned char>(chr)) == 0) {
            return false;
        }
        // De Morgan: ensures the letter is simply not a vowel
        char lowerChar = static_cast<char>(std::tolower(static_cast<unsigned char>(chr)));
        return lowerChar != 'a' && lowerChar != 'e' && lowerChar != 'i' && lowerChar != 'o' && lowerChar != 'u';
    }));
}

int TextAnalyzer::countDigits() const {
    // Checks one by one using isdigit which of them is a digit
    return static_cast<int>(std::count_if(textData.begin(), textData.end(), [](char chr) {
        return std::isdigit(static_cast<unsigned char>(chr)) != 0;
    }));
}

int TextAnalyzer::countSpaces() const {
    // isspace catches not only spaces but also tabs or newlines
    return static_cast<int>(std::count_if(textData.begin(), textData.end(), [](char chr) {
        return std::isspace(static_cast<unsigned char>(chr)) != 0;
    }));
}

int TextAnalyzer::countChar(char targetChar) const {
    // Simple counting function, doesn't need a lambda because we compare to a specific single character
    return static_cast<int>(std::count(textData.begin(), textData.end(), targetChar));
}

bool TextAnalyzer::isAlphaOnly() const {
    // all_of returns true only if the entire string consists solely of letters or spaces
    return std::all_of(textData.begin(), textData.end(), [](char chr) {
        return std::isalpha(static_cast<unsigned char>(chr)) != 0 || std::isspace(static_cast<unsigned char>(chr)) != 0;
    });
}

bool TextAnalyzer::hasDigits() const {
    // It is enough for one digit to be found for the function to return true (any_of)
    return std::any_of(textData.begin(), textData.end(), [](char chr) {
        return std::isdigit(static_cast<unsigned char>(chr)) != 0;
    });
}

std::string TextAnalyzer::toUpper() const {
    std::string result;
    // reserve saves us unnecessary memory allocations along the way because we know in advance how many characters there will be
    result.reserve(textData.size());
    std::transform(textData.begin(), textData.end(), std::back_inserter(result), [](char chr) {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(chr)));
    });
    return result;
}

std::string TextAnalyzer::toLower() const {
    std::string result;
    result.reserve(textData.size());
    // Applies tolower to each character and pushes it to the new string
    std::transform(textData.begin(), textData.end(), std::back_inserter(result), [](char chr) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(chr)));
    });
    return result;
}

std::string TextAnalyzer::reversed() const {
    std::string result = textData;
    // The reverse algorithm reverses in place, so we made a copy beforehand
    std::reverse(result.begin(), result.end());
    return result;
}

std::string TextAnalyzer::removeDigits() const {
    std::string result;
    // copy_if copies only the characters that are *not* digits
    std::copy_if(textData.begin(), textData.end(), std::back_inserter(result), [](char chr) {
        return std::isdigit(static_cast<unsigned char>(chr)) == 0;
    });
    return result;
}

std::string TextAnalyzer::removeVowels() const {
    std::string result;
    // Copy everything to the new string except vowels
    std::copy_if(textData.begin(), textData.end(), std::back_inserter(result), [](char chr) {
        char lowerChar = static_cast<char>(std::tolower(static_cast<unsigned char>(chr)));
        return lowerChar != 'a' && lowerChar != 'e' && lowerChar != 'i' && lowerChar != 'o' && lowerChar != 'u';
    });
    return result;
}

std::string TextAnalyzer::replaceChar(char fromChar, char toChar) const {
    std::string result = textData;
    // replace iterates over the entire array and replaces the old with the new in the same place (in-place)
    std::replace(result.begin(), result.end(), fromChar, toChar);
    return result;
}

std::vector<std::string> TextAnalyzer::getWords() const {
    std::vector<std::string> wordsList;
    std::istringstream stream(textData);
    std::string currentWord;
    // The << operator in strings automatically skips spaces, making it a perfect tool for extracting words
    while (stream >> currentWord) {
        wordsList.push_back(currentWord);
    }
    return wordsList;
}

std::vector<std::string> TextAnalyzer::getUniqueWords() const {
    std::vector<std::string> wordsList = getWords();
    // To delete duplicates efficiently in C++, first sort and then use erase and unique together
    std::sort(wordsList.begin(), wordsList.end());
    wordsList.erase(std::unique(wordsList.begin(), wordsList.end()), wordsList.end());
    return wordsList;
}

std::map<std::string, int> TextAnalyzer::getWordFrequency() const {
    std::map<std::string, int> frequencyMap;
    // A map is an ideal structure for frequency. Word is key, and amount is value. ++ increments by 1 for each occurrence.
    for (const std::string& currentWord : getWords()) {
        frequencyMap[currentWord]++;
    }
    return frequencyMap;
}

std::string TextAnalyzer::longestWord() const {
    std::vector<std::string> wordsList = getWords();
    if (wordsList.empty()) {
        return "";
    }
    // The lambda ensures that max_element compares the words by their size (length) and not lexicographically by letters
    auto iterator = std::max_element(wordsList.begin(), wordsList.end(), [](const std::string& strA, const std::string& strB) {
        return strA.length() < strB.length();
    });
    return *iterator; // Dereferences the iterator to return the string itself
}

std::string TextAnalyzer::shortestWord() const {
    std::vector<std::string> wordsList = getWords();
    if (wordsList.empty()) {
        return "";
    }
    // Same principle as the longest word, only using min_element
    auto iterator = std::min_element(wordsList.begin(), wordsList.end(), [](const std::string& strA, const std::string& strB) {
        return strA.length() < strB.length();
    });
    return *iterator;
}

std::vector<std::string> TextAnalyzer::wordsSortedByLength() const {
    std::vector<std::string> wordsList = getWords();
    // stable_sort ensures that if 2 words have the same length, they will remain in the same order as they appeared in the original sentence
    std::stable_sort(wordsList.begin(), wordsList.end(), [](const std::string& strA, const std::string& strB) {
        return strA.length() < strB.length();
    });
    return wordsList;
}

std::vector<std::string> TextAnalyzer::wordsLongerThan(size_t lengthThreshold) const {
    std::vector<std::string> wordsList = getWords();
    std::vector<std::string> resultList;
    // Filters into the new vector only words that pass the defined length threshold (lengthThreshold)
    std::copy_if(wordsList.begin(), wordsList.end(), std::back_inserter(resultList), [lengthThreshold](const std::string& currentWord) {
        return currentWord.length() > lengthThreshold;
    });
    return resultList;
}

std::string TextAnalyzer::joinWords(const std::string& delimiter) const {
    std::vector<std::string> wordsList = getWords();
    if (wordsList.empty()) {
        return "";
    }
    // accumulate concatenates everything into a single string. Starting from std::next (the second word) so a delimiter isn't prepended at the beginning.
    return std::accumulate(std::next(wordsList.begin()), wordsList.end(), wordsList[0], [&delimiter](const std::string& accumulatedData, const std::string& currentWord) {
        return accumulatedData + delimiter + currentWord;
    });
}

} // namespace datatools