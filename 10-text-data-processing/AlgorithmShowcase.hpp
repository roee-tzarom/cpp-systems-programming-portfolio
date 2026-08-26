/**
 * @file AlgorithmShowcase.hpp
 * @brief Free functions showcasing various advanced STL algorithms.
 */

#pragma once

#include <vector>
#include <iostream>
#include <functional>
#include <string>

namespace datatools {

/**
 * @brief Generates all possible permutations of a given vector.
 * @param items The input vector.
 * @return std::vector<std::vector<int>> A vector containing all permutations.
 */
std::vector<std::vector<int>> allPermutations(const std::vector<int>& items);

/**
 * @brief Rearranges the elements into the next lexicographically greater permutation.
 * @param items The vector to rearrange.
 * @return true if the next permutation exists, false if it wrapped around to the first.
 */
bool nextPermutation(std::vector<int>& items);

/**
 * @brief Rearranges the elements into the previous lexicographically smaller permutation.
 * @param items The vector to rearrange.
 * @return true if the previous permutation exists, false if it wrapped around to the last.
 */
bool prevPermutation(std::vector<int>& items);

/**
 * @brief Prints the elements of an integer vector to an output stream using ostream_iterator.
 * @param items The vector to print.
 * @param outputStream The stream to output to.
 * @param delimiter The string to print after each element. Defaults to " ".
 */
void printWithIterator(const std::vector<int>& items, std::ostream& outputStream, const std::string& delimiter = " ");

/**
 * @brief Prints the elements of a double vector to an output stream using ostream_iterator.
 * @param items The vector to print.
 * @param outputStream The stream to output to.
 * @param delimiter The string to print after each element. Defaults to " ".
 */
void printDoublesWithIterator(const std::vector<double>& items, std::ostream& outputStream, const std::string& delimiter = " ");

/**
 * @brief Reads integers from an input stream into a vector using istream_iterator.
 * @param inputStream The stream to read from.
 * @return std::vector<int> The vector of read integers.
 */
std::vector<int> readFromStream(std::istream& inputStream);

/**
 * @brief Prints elements that satisfy a condition to an output stream using ostream_iterator and copy_if.
 * @param items The vector to filter.
 * @param outputStream The stream to output to.
 * @param predicate A lambda returning true for elements that should be printed.
 * @param delimiter The string to print after each printed element. Defaults to " ".
 */
void printFiltered(const std::vector<int>& items, std::ostream& outputStream, const std::function<bool(int)>& predicate, const std::string& delimiter = " ");

/**
 * @brief Generates a sequence of sequentially increasing values using std::iota.
 * @param count The number of values to generate.
 * @param startValue The starting value.
 * @return std::vector<int> The generated sequence.
 */
std::vector<int> generateSequence(int count, int startValue);

/**
 * @brief Computes the running total (partial sums) of a vector.
 * @param items The input vector.
 * @return std::vector<int> A new vector containing the running totals.
 */
std::vector<int> runningTotal(const std::vector<int>& items);

/**
 * @brief Computes the dot product of two integer vectors.
 * @param firstVector The first vector.
 * @param secondVector The second vector.
 * @return int The calculated dot product.
 * @throws std::invalid_argument if the sizes of the vectors do not match.
 */
int dotProduct(const std::vector<int>& firstVector, const std::vector<int>& secondVector);

/**
 * @brief Erases all occurrences of a specific value using the erase-remove idiom.
 * @param items The vector to modify in-place.
 * @param targetValue The value to remove.
 * @return int The number of elements erased.
 */
int eraseValue(std::vector<int>& items, int targetValue);

/**
 * @brief Erases all elements matching a condition using the erase-remove_if idiom.
 * @param items The vector to modify in-place.
 * @param predicate A lambda returning true for elements that should be removed.
 * @return int The number of elements erased.
 */
int eraseIf(std::vector<int>& items, const std::function<bool(int)>& predicate);

/**
 * @brief Removes consecutive duplicate elements using the erase-unique idiom.
 * @param items The vector to modify in-place.
 */
void uniqueInPlace(std::vector<int>& items);

} // namespace datatools