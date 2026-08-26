/**
 * @file main.cpp
 * @brief Demo for Text Analysis & Data Processing Tool
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
#include "DataProcessor.hpp"
#include "TextAnalyzer.hpp"
#include "SetOperations.hpp"
#include "AlgorithmShowcase.hpp"

using namespace datatools;

int main() {
    std::cout << "===== Text Analysis & Data Processing Tool Demo =====\n\n";

    // ---- Section 1: DataProcessor basics ----
    std::cout << "--- DataProcessor Basics ---\n";

    DataProcessor dp({5.0, 2.0, 8.0, 1.0, 9.0, 3.0, 7.0, 4.0, 6.0, 10.0});

    std::cout << "Data: " << dp.toString() << "\n";
    // Expected: Data: 5, 2, 8, 1, 9, 3, 7, 4, 6, 10

    std::cout << "Sum: " << dp.sum() << "\n";
    // Expected: Sum: 55

    std::cout << "Average: " << dp.average() << "\n";
    // Expected: Average: 5.5

    std::cout << "Min: " << dp.min() << ", Max: " << dp.max() << "\n";
    // Expected: Min: 1, Max: 10

    std::cout << "Count > 5: " << dp.countIf([](double x) { return x > 5; }) << "\n";
    // Expected: Count > 5: 5

    std::cout << "All positive: " << dp.allOf([](double x) { return x > 0; }) << "\n";
    // Expected: All positive: 1

    std::cout << "Any > 8: " << dp.anyOf([](double x) { return x > 8; }) << "\n";
    // Expected: Any > 8: 1

    std::cout << "None negative: " << dp.noneOf([](double x) { return x < 0; }) << "\n";
    // Expected: None negative: 1

    // ---- Section 2: Sorting ----
    std::cout << "\n--- Sorting ---\n";

    DataProcessor dp2({5.0, 2.0, 8.0, 1.0, 9.0});
    dp2.sort();
    std::cout << "Sorted: " << dp2.toString() << "\n";
    // Expected: Sorted: 1, 2, 5, 8, 9

    DataProcessor dp3({5.0, 2.0, 8.0, 1.0, 9.0});
    dp3.sort([](double a, double b) { return a > b; });
    std::cout << "Sorted desc: " << dp3.toString() << "\n";
    // Expected: Sorted desc: 9, 8, 5, 2, 1

    DataProcessor dp4({5.0, 2.0, 8.0, 1.0, 9.0, 3.0});
    dp4.partialSort(3);
    std::cout << "Partial sort (top 3): " << dp4.toString() << "\n";
    // Expected: Partial sort (top 3): 1, 2, 3, ...  (first 3 sorted, rest unspecified)

    // ---- Section 3: Transform ----
    std::cout << "\n--- Transform ---\n";

    DataProcessor dp5({1.0, 2.0, 3.0, 4.0, 5.0});
    dp5.applyTransform([](double x) { return x * x; });
    std::cout << "Squared: " << dp5.toString() << "\n";
    // Expected: Squared: 1, 4, 9, 16, 25

    DataProcessor dp6({1.0, 2.0, 3.0});
    DataProcessor doubled = dp6.transformed([](double x) { return x * 2; });
    std::cout << "Original: " << dp6.toString() << "\n";
    // Expected: Original: 1, 2, 3
    std::cout << "Doubled: " << doubled.toString() << "\n";
    // Expected: Doubled: 2, 4, 6

    DataProcessor dp7({1.0, 2.0, 3.0, 4.0});
    DataProcessor ps = dp7.partialSums();
    std::cout << "Partial sums: " << ps.toString() << "\n";
    // Expected: Partial sums: 1, 3, 6, 10

    // ---- Section 4: Filter, Replace, Fill, Generate ----
    std::cout << "\n--- Filter, Replace, Fill, Generate ---\n";

    DataProcessor dp8({1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    DataProcessor evens = dp8.filter([](double x) {
        return static_cast<int>(x) % 2 == 0;
    });
    std::cout << "Evens: " << evens.toString() << "\n";
    // Expected: Evens: 2, 4, 6

    DataProcessor dp9({1.0, 2.0, 3.0, 4.0, 5.0});
    dp9.replaceIf([](double x) { return x > 3; }, 0.0);
    std::cout << "Replaced >3 with 0: " << dp9.toString() << "\n";
    // Expected: Replaced >3 with 0: 1, 2, 3, 0, 0

    DataProcessor dp10({});
    dp10.fill(7.0);  // empty, no effect
    int counter = 0;
    dp10.generate(5, [&counter]() { return static_cast<double>(++counter); });
    std::cout << "Generated: " << dp10.toString() << "\n";
    // Expected: Generated: 1, 2, 3, 4, 5

    // iota constructor
    DataProcessor dp11(5, 10.0);
    std::cout << "Iota from 10: " << dp11.toString() << "\n";
    // Expected: Iota from 10: 10, 11, 12, 13, 14

    // ---- Section 5: Structure changers ----
    std::cout << "\n--- Structure Changers ---\n";

    DataProcessor dp12({1.0, -2.0, 3.0, -4.0, 5.0});
    int removed = dp12.removeIf([](double x) { return x < 0; });
    std::cout << "After removing negatives (" << removed << " removed): "
              << dp12.toString() << "\n";
    // Expected: After removing negatives (2 removed): 1, 3, 5

    DataProcessor dp13({1.0, 1.0, 2.0, 3.0, 3.0, 3.0, 4.0});
    dp13.unique();
    std::cout << "After unique: " << dp13.toString() << "\n";
    // Expected: After unique: 1, 2, 3, 4

    DataProcessor dp14({1.0, 2.0, 3.0, 4.0, 5.0});
    dp14.reverse();
    std::cout << "Reversed: " << dp14.toString() << "\n";
    // Expected: Reversed: 5, 4, 3, 2, 1

    DataProcessor dp15({1.0, 2.0, 3.0, 4.0, 5.0});
    dp15.rotate(2);
    std::cout << "Rotated by 2: " << dp15.toString() << "\n";
    // Expected: Rotated by 2: 3, 4, 5, 1, 2

    DataProcessor dp16({5.0, 1.0, 4.0, 2.0, 3.0, 6.0});
    int partCount = dp16.stablePartition([](double x) { return x <= 3; });
    std::cout << "Stable partition (<=3 first, " << partCount << " elements): "
              << dp16.toString() << "\n";
    // Expected: Stable partition (<=3 first, 3 elements): 1, 2, 3, 5, 4, 6

    // ---- Section 6: Inner product ----
    std::cout << "\n--- Inner Product ---\n";

    DataProcessor a({1.0, 2.0, 3.0});
    DataProcessor b({4.0, 5.0, 6.0});
    std::cout << "Dot product: " << a.innerProduct(b) << "\n";
    // Expected: Dot product: 32  (1*4 + 2*5 + 3*6)

    // ---- Section 7: Text Analyzer ----
    std::cout << "\n--- Text Analyzer ---\n";

    TextAnalyzer ta("The Quick Brown Fox Jumps Over The Lazy Dog 123");

    std::cout << "Vowels: " << ta.countVowels() << "\n";
    // Expected: Vowels: 11

    std::cout << "Consonants: " << ta.countConsonants() << "\n";
    // Expected: Consonants: 24

    std::cout << "Digits: " << ta.countDigits() << "\n";
    // Expected: Digits: 3

    std::cout << "Spaces: " << ta.countSpaces() << "\n";
    // Expected: Spaces: 9

    std::cout << "Upper: " << ta.toUpper() << "\n";
    // Expected: Upper: THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG 123

    std::cout << "Lower: " << ta.toLower() << "\n";
    // Expected: Lower: the quick brown fox jumps over the lazy dog 123

    std::cout << "No digits: [" << ta.removeDigits() << "]\n";
    // Expected: No digits: [The Quick Brown Fox Jumps Over The Lazy Dog ]
    // Note: There is a trailing space because only digits are removed, not surrounding spaces

    std::cout << "No vowels: " << ta.removeVowels() << "\n";
    // Expected: No vowels: Th Qck Brwn Fx Jmps vr Th Lzy Dg 123

    auto words = ta.getWords();
    std::cout << "Word count: " << words.size() << "\n";
    // Expected: Word count: 10

    std::cout << "Longest word: " << ta.longestWord() << "\n";
    // Expected: Longest word: Jumps  (or Brown — both 5 chars, depends on max_element behavior)

    std::cout << "Shortest word: " << ta.shortestWord() << "\n";
    // Expected: Shortest word: The  (or Fox — both 3 chars)

    auto unique = ta.getUniqueWords();
    std::cout << "Unique words: " << unique.size() << "\n";
    // Expected: Unique words: 9  ("the" appears twice but counted once)

    auto freq = ta.getWordFrequency();
    std::cout << "Frequency of 'the': " << freq["the"] << "\n";
    // Expected: Frequency of 'the': 2

    auto longWords = ta.wordsLongerThan(3);
    std::cout << "Words longer than 3 chars: " << longWords.size() << "\n";
    // Expected: Words longer than 3 chars: 5  (Quick, Brown, Jumps, Over, Lazy)

    // ---- Section 8: Set Operations ----
    std::cout << "\n--- Set Operations ---\n";

    std::vector<int> s1 = {1, 2, 3, 4, 5};
    std::vector<int> s2 = {3, 4, 5, 6, 7};

    auto u = setUnion(s1, s2);
    std::cout << "Union: ";
    for (int x : u) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Union: 1 2 3 4 5 6 7

    auto inter = setIntersection(s1, s2);
    std::cout << "Intersection: ";
    for (int x : inter) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Intersection: 3 4 5

    auto diff = setDifference(s1, s2);
    std::cout << "Difference (s1-s2): ";
    for (int x : diff) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Difference (s1-s2): 1 2

    auto symDiff = setSymmetricDifference(s1, s2);
    std::cout << "Symmetric difference: ";
    for (int x : symDiff) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Symmetric difference: 1 2 6 7

    auto merged = mergeSorted(s1, s2);
    std::cout << "Merged: ";
    for (int x : merged) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Merged: 1 2 3 3 4 4 5 5 6 7

    std::cout << "s1 includes {2,3}: " << includes(s1, {2, 3}) << "\n";
    // Expected: s1 includes {2,3}: 1

    std::cout << "s1 includes {2,6}: " << includes(s1, {2, 6}) << "\n";
    // Expected: s1 includes {2,6}: 0

    // ---- Section 9: Permutations ----
    std::cout << "\n--- Permutations ---\n";

    auto perms = allPermutations({1, 2, 3});
    std::cout << "Permutations of {1,2,3}: " << perms.size() << "\n";
    // Expected: Permutations of {1,2,3}: 6

    std::vector<int> perm = {1, 2, 3};
    nextPermutation(perm);
    std::cout << "Next perm of {1,2,3}: ";
    for (int x : perm) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Next perm of {1,2,3}: 1 3 2

    // ---- Section 10: IO Iterators ----
    std::cout << "\n--- IO Iterators ---\n";

    std::vector<int> ioData = {10, 20, 30, 40, 50};
    std::cout << "ostream_iterator: ";
    printWithIterator(ioData, std::cout);
    std::cout << "\n";
    // Expected: ostream_iterator: 10 20 30 40 50
    // Note: ostream_iterator appends the delimiter after each element, including the last

    std::cout << "Filtered (divisible by 20): ";
    printFiltered(ioData, std::cout, [](int x) { return x % 20 == 0; });
    std::cout << "\n";
    // Expected: Filtered (divisible by 20): 20 40
    // Note: ostream_iterator appends the delimiter after each element, including the last

    std::istringstream iss("100 200 300");
    auto readData = readFromStream(iss);
    std::cout << "Read from stream: ";
    for (int x : readData) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Read from stream: 100 200 300

    // ---- Section 11: Numeric algorithms ----
    std::cout << "\n--- Numeric Algorithms ---\n";

    auto seq = generateSequence(5, 1);
    std::cout << "iota(5,1): ";
    for (int x : seq) std::cout << x << " ";
    std::cout << "\n";
    // Expected: iota(5,1): 1 2 3 4 5

    auto running = runningTotal({1, 2, 3, 4, 5});
    std::cout << "Running total: ";
    for (int x : running) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Running total: 1 3 6 10 15

    std::cout << "Dot product: " << dotProduct({1, 2, 3}, {4, 5, 6}) << "\n";
    // Expected: Dot product: 32

    // ---- Section 12: Erase-Remove ----
    std::cout << "\n--- Erase-Remove ---\n";

    std::vector<int> erData = {1, 2, 3, 2, 4, 2, 5};
    int erCount = eraseValue(erData, 2);
    std::cout << "Erased " << erCount << " twos: ";
    for (int x : erData) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Erased 3 twos: 1 3 4 5

    std::vector<int> erData2 = {1, 2, 3, 4, 5, 6, 7, 8};
    int erCount2 = eraseIf(erData2, [](int x) { return x % 2 == 0; });
    std::cout << "Erased " << erCount2 << " evens: ";
    for (int x : erData2) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Erased 4 evens: 1 3 5 7

    std::vector<int> dupData = {1, 1, 2, 3, 3, 3, 4, 4, 5};
    uniqueInPlace(dupData);
    std::cout << "Unique: ";
    for (int x : dupData) std::cout << x << " ";
    std::cout << "\n";
    // Expected: Unique: 1 2 3 4 5

    std::cout << "\n===== Demo Complete =====\n";

    return 0;
}
