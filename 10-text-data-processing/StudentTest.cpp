/**
 * @file StudentTest.cpp
 * @brief 20 Custom unit tests based on AI-generated edge cases.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DataProcessor.hpp"
#include "TextAnalyzer.hpp"
#include "SetOperations.hpp"
#include "AlgorithmShowcase.hpp"
#include <vector>
#include <string>

using namespace datatools;

// ==========================================
// Section 1: Numbers (DataProcessor)
// ==========================================

TEST_CASE("StudentTest 1: Average - Standard case") {
    DataProcessor dp({85.0, 90.0, 95.0});
    CHECK(dp.average() == doctest::Approx(90.0));
}

TEST_CASE("StudentTest 2: Average - Edge Case (Empty list throws exception)") {
    DataProcessor dp;
    CHECK_THROWS_AS(dp.average(), std::invalid_argument);
}

TEST_CASE("StudentTest 3: Average - Edge Case (Mix of positive and negative)") {
    DataProcessor dp({-10.0, 0.0, 10.0});
    CHECK(dp.average() == doctest::Approx(0.0));
}

TEST_CASE("StudentTest 4: Filter Negative Numbers - Standard case") {
    DataProcessor dp({10.0, -5.0, 3.0, -1.0, 0.0});
    DataProcessor filtered = dp.filter([](double x) { return x >= 0; });
    auto data = filtered.getData();
    CHECK(data.size() == 3);
    CHECK(data[0] == doctest::Approx(10.0));
    CHECK(data[1] == doctest::Approx(3.0));
    CHECK(data[2] == doctest::Approx(0.0));
}

TEST_CASE("StudentTest 5: Filter Negative Numbers - Edge Case (All negative)") {
    DataProcessor dp({-1.0, -2.0, -3.0});
    DataProcessor filtered = dp.filter([](double x) { return x >= 0; });
    CHECK(filtered.empty() == true);
}

TEST_CASE("StudentTest 6: Dot Product - Standard case") {
    DataProcessor a({1.0, 2.0, 3.0});
    DataProcessor b({4.0, 5.0, 6.0});
    CHECK(a.innerProduct(b) == doctest::Approx(32.0));
}

TEST_CASE("StudentTest 7: Dot Product - Edge Case (Mismatched dimensions)") {
    DataProcessor a({1.0, 2.0});
    DataProcessor b({3.0, 4.0, 5.0});
    CHECK_THROWS_AS(a.innerProduct(b), std::invalid_argument);
}

// ==========================================
// Section 2: Text (TextAnalyzer)
// ==========================================

TEST_CASE("StudentTest 8: Longest Word - Standard case (Hyphenated)") {
    TextAnalyzer ta("Seat padded with high-quality foam");
    CHECK(ta.longestWord() == "high-quality");
}

TEST_CASE("StudentTest 9: Longest Word - Edge Case (Multiple words of same length)") {
    TextAnalyzer ta("Butter and Oil");
    // std::max_element finds the first occurrence of the max length
    CHECK(ta.longestWord() == "Butter");
}

TEST_CASE("StudentTest 10: Longest Word - Edge Case (Spaces only)") {
    TextAnalyzer ta("     ");
    CHECK(ta.longestWord() == "");
}

TEST_CASE("StudentTest 11: Word Frequency - Standard case") {
    TextAnalyzer ta("Docker Compose and Docker Nginx");
    auto freq = ta.getWordFrequency();
    CHECK(freq["Docker"] == 2);
    CHECK(freq["Compose"] == 1);
    CHECK(freq["Nginx"] == 1);
}

TEST_CASE("StudentTest 12: Word Frequency - Edge Case (Case sensitivity applied)") {
    TextAnalyzer ta("yes yes yes");
    auto freq = ta.getWordFrequency();
    CHECK(freq["yes"] == 3);
}

TEST_CASE("StudentTest 13: Vowels and Consonants - Standard case") {
    TextAnalyzer ta("Queue");
    CHECK(ta.countVowels() == 4);
    CHECK(ta.countConsonants() == 1);
}

TEST_CASE("StudentTest 14: Vowels and Consonants - Edge Case (No vowels)") {
    TextAnalyzer ta("SQL");
    CHECK(ta.countVowels() == 0);
    CHECK(ta.countConsonants() == 3);
}

TEST_CASE("StudentTest 15: Vowels and Consonants - Edge Case (Numbers and special chars)") {
    TextAnalyzer ta("123 !@#");
    CHECK(ta.countVowels() == 0);
    CHECK(ta.countConsonants() == 0);
}

// ==========================================
// Section 3: Sets & Combinatorics
// ==========================================

TEST_CASE("StudentTest 16: Symmetric Difference - Standard case") {
    auto diff = setSymmetricDifference({1, 2}, {2, 3});
    CHECK(diff == std::vector<int>{1, 3});
}

TEST_CASE("StudentTest 17: Symmetric Difference - Edge Case (Identical sets)") {
    auto diff = setSymmetricDifference({4, 5}, {4, 5});
    CHECK(diff.empty() == true);
}

TEST_CASE("StudentTest 18: Symmetric Difference - Edge Case (One empty set)") {
    auto diff = setSymmetricDifference({9, 10}, {});
    CHECK(diff == std::vector<int>{9, 10});
}

TEST_CASE("StudentTest 19: Permutations - Standard case") {
    auto perms = allPermutations({1, 2, 3});
    CHECK(perms.size() == 6);
}

TEST_CASE("StudentTest 20: Permutations - Edge Case (Empty set)") {
    auto perms = allPermutations({});
    CHECK(perms.size() == 1);
    CHECK(perms[0].empty() == true);
}