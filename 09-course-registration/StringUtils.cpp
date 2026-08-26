#include "StringUtils.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>

namespace registration {

std::string toUpper(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char chr) {
        return std::toupper(chr);
    });
    return result;
}

std::string toLower(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char chr) {
        return std::tolower(chr);
    });
    return result;
}

std::string trim(const std::string& text) {
    const std::string whitespace = " \t\n\r\f\v";
    // Finds the first actual character that is not a whitespace character
    size_t start = text.find_first_not_of(whitespace);
    // npos means "not found", meaning the entire string is just spaces
    if (start == std::string::npos) {
        return "";
    }
    // Same thing but from the end to the beginning
    size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string& text, char delimiter) {
    if (text.empty()) {
        return {""};
    }
    std::vector<std::string> parts;
    std::stringstream stream(text);
    std::string item;
    // Use getline with a custom delimiter (not just newline) to split words
    while (std::getline(stream, item, delimiter)) {
        parts.push_back(item);
    }
    // Edge case: if the string ends with the delimiter, add an empty string at the end
    if (!text.empty() && text.back() == delimiter) {
        parts.push_back("");
    }
    return parts;
}

std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        // Appends the delimiter only if it's not the last element
        if (i < parts.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

bool startsWith(const std::string& text, const std::string& prefix) {
    // Length check prevents an out of bounds crash
    if (prefix.length() > text.length()) {
        return false;
    }
    // compare returns 0 if the strings are identical in the checked part
    return text.compare(0, prefix.length(), prefix) == 0;
}

bool endsWith(const std::string& text, const std::string& suffix) {
    if (suffix.length() > text.length()) {
        return false;
    }
    // Calculates where the suffix should start and compares from there
    return text.compare(text.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string replaceAll(const std::string& text, const std::string& from, const std::string& toStr) {
    if (from.empty()) {
        return text;
    }
    std::string result = text;
    size_t pos = 0;
    while ((pos = result.find(from, pos)) != std::string::npos) {
        result.replace(pos, from.length(), toStr);
        // Advances pos by the length of the new string to prevent an infinite loop
        pos += toStr.length();
    }
    return result;
}

int countChar(const std::string& text, char targetChar) {
    return static_cast<int>(std::count(text.begin(), text.end(), targetChar));
}

bool isPalindrome(const std::string& text) {
    std::string cleaned;
    // First, remove spaces and convert everything to lowercase (so "A ba" will work)
    for (char chr : text) {
        if (std::isspace(static_cast<unsigned char>(chr)) == 0) {
            cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(chr)));
        }
    }
    std::string reversed = cleaned;
    std::reverse(reversed.begin(), reversed.end());
    return cleaned == reversed;
}

std::string reverseString(const std::string& text) {
    std::string result = text;
    std::reverse(result.begin(), result.end());
    return result;
}

} // namespace registration