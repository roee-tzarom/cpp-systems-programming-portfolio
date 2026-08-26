/**
 * @file SetOperations.hpp
 * @brief Free functions demonstrating STL set algorithms on sorted vectors.
 */

#pragma once

#include <vector>
#include <string>

namespace datatools {

/**
 * @brief Computes the union of two sorted vectors (elements in either set).
 * @param firstSet The first sorted vector.
 * @param secondSet The second sorted vector.
 * @return std::vector<int> The sorted union of the two vectors.
 */
std::vector<int> setUnion(const std::vector<int>& firstSet, const std::vector<int>& secondSet);

/**
 * @brief Computes the intersection of two sorted vectors (elements in both sets).
 * @param firstSet The first sorted vector.
 * @param secondSet The second sorted vector.
 * @return std::vector<int> The sorted intersection of the two vectors.
 */
std::vector<int> setIntersection(const std::vector<int>& firstSet, const std::vector<int>& secondSet);

/**
 * @brief Computes the difference of two sorted vectors (elements in the first but not the second).
 * @param firstSet The first sorted vector.
 * @param secondSet The second sorted vector.
 * @return std::vector<int> The sorted difference.
 */
std::vector<int> setDifference(const std::vector<int>& firstSet, const std::vector<int>& secondSet);

/**
 * @brief Computes the symmetric difference (elements in either set, but not in both).
 * @param firstSet The first sorted vector.
 * @param secondSet The second sorted vector.
 * @return std::vector<int> The sorted symmetric difference.
 */
std::vector<int> setSymmetricDifference(const std::vector<int>& firstSet, const std::vector<int>& secondSet);

/**
 * @brief Merges two sorted vectors into one sorted vector (keeps duplicates).
 * @param firstSet The first sorted vector.
 * @param secondSet The second sorted vector.
 * @return std::vector<int> The merged sorted vector.
 */
std::vector<int> mergeSorted(const std::vector<int>& firstSet, const std::vector<int>& secondSet);

/**
 * @brief Checks if the first sorted vector includes all elements of the second sorted subset.
 * @param firstSet The main sorted vector.
 * @param subset The sorted subset to check for.
 * @return true if the subset is fully contained, false otherwise.
 */
bool includes(const std::vector<int>& firstSet, const std::vector<int>& subset);

/**
 * @brief Computes the union of two sorted vectors of strings.
 * @param firstSet The first sorted string vector.
 * @param secondSet The second sorted string vector.
 * @return std::vector<std::string> The sorted union of the strings.
 */
std::vector<std::string> setUnionStr(const std::vector<std::string>& firstSet, const std::vector<std::string>& secondSet);

/**
 * @brief Computes the intersection of two sorted vectors of strings.
 * @param firstSet The first sorted string vector.
 * @param secondSet The second sorted string vector.
 * @return std::vector<std::string> The sorted intersection of the strings.
 */
std::vector<std::string> setIntersectionStr(const std::vector<std::string>& firstSet, const std::vector<std::string>& secondSet);

} // namespace datatools