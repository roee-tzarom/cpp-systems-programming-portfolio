#include "SetOperations.hpp"
#include <algorithm>
#include <iterator>

namespace datatools {

std::vector<int> setUnion(const std::vector<int>& firstSet, const std::vector<int>& secondSet) {
    std::vector<int> resultSet;
    // Set algorithms assume sorted input. back_inserter pushes the results into the new, empty vector
    std::set_union(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

std::vector<int> setIntersection(const std::vector<int>& firstSet, const std::vector<int>& secondSet) {
    std::vector<int> resultSet;
    // Intersection: returns to resultSet only the numbers that appear in both the first set and the second set
    std::set_intersection(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

std::vector<int> setDifference(const std::vector<int>& firstSet, const std::vector<int>& secondSet) {
    std::vector<int> resultSet;
    // Difference: takes what is in the first but filters out what appears in the second
    std::set_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

std::vector<int> setSymmetricDifference(const std::vector<int>& firstSet, const std::vector<int>& secondSet) {
    std::vector<int> resultSet;
    // Symmetric difference: takes elements that appear in only one of them, but not in both (the opposite of intersection)
    std::set_symmetric_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

std::vector<int> mergeSorted(const std::vector<int>& firstSet, const std::vector<int>& secondSet) {
    std::vector<int> resultSet;
    // Unlike set_union which filters duplicates, merge simply mixes them while maintaining the sort (duplicates will remain)
    std::merge(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

bool includes(const std::vector<int>& firstSet, const std::vector<int>& subset) {
    // Checks whether the entire second set is fully contained within the first set (returns only yes or no)
    return std::includes(firstSet.begin(), firstSet.end(), subset.begin(), subset.end());
}

std::vector<std::string> setUnionStr(const std::vector<std::string>& firstSet, const std::vector<std::string>& secondSet) {
    std::vector<std::string> resultSet;
    // The STL is generic. The same algorithm works perfectly on strings because they know how to be sorted alphabetically
    std::set_union(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

std::vector<std::string> setIntersectionStr(const std::vector<std::string>& firstSet, const std::vector<std::string>& secondSet) {
    std::vector<std::string> resultSet;
    // Intersection also works perfectly on strings. back_inserter takes care of dynamically expanding the vector.
    std::set_intersection(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), std::back_inserter(resultSet));
    return resultSet;
}

} // namespace datatools