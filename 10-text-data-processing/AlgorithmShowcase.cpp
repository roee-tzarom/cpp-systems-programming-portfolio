#include "AlgorithmShowcase.hpp"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <stdexcept>

namespace datatools {

std::vector<std::vector<int>> allPermutations(const std::vector<int>& items) {
    std::vector<std::vector<int>> result;
    std::vector<int> currentPermutation = items;
    // Must sort first so the algorithm starts from the smallest (lexicographical) option and doesn't miss anything
    std::sort(currentPermutation.begin(), currentPermutation.end());
    
    // Edge case: if the vector is empty, return a vector with one empty set
    if (currentPermutation.empty()) {
        result.push_back({});
        return result;
    }

    result.push_back(currentPermutation);
    // next_permutation changes the vector to the next arrangement and returns false when it loops back to the start
    while (std::next_permutation(currentPermutation.begin(), currentPermutation.end())) {
        result.push_back(currentPermutation);
    }
    
    return result;
}

bool nextPermutation(std::vector<int>& items) {
    // The built-in function does all the work for us (in-place)
    return std::next_permutation(items.begin(), items.end());
}

bool prevPermutation(std::vector<int>& items) {
    // Returns the arrangement one step back
    return std::prev_permutation(items.begin(), items.end());
}

void printWithIterator(const std::vector<int>& items, std::ostream& outputStream, const std::string& delimiter) {
    // ostream_iterator takes each element and prints it directly to the stream (like cout or a file) along with the delimiter
    std::copy(items.begin(), items.end(), std::ostream_iterator<int>(outputStream, delimiter.c_str()));
}

void printDoublesWithIterator(const std::vector<double>& items, std::ostream& outputStream, const std::string& delimiter) {
    // Same trick as before, just set to handle double
    std::copy(items.begin(), items.end(), std::ostream_iterator<double>(outputStream, delimiter.c_str()));
}

std::vector<int> readFromStream(std::istream& inputStream) {
    // The empty iterator at the end tells the function "read from the stream until you reach EOF or invalid input"
    return std::vector<int>(std::istream_iterator<int>(inputStream), std::istream_iterator<int>());
}

void printFiltered(const std::vector<int>& items, std::ostream& outputStream, const std::function<bool(int)>& predicate, const std::string& delimiter) {
    // copy_if copies to the output stream only elements that pass the lambda condition (predicate)
    std::copy_if(items.begin(), items.end(), std::ostream_iterator<int>(outputStream, delimiter.c_str()), predicate);
}

std::vector<int> generateSequence(int count, int startValue) {
    if (count <= 0) {
        return {};
    }
    std::vector<int> sequence(static_cast<size_t>(count));
    // iota simply runs over the vector and fills it with ascending numbers (e.g., 5, 6, 7...)
    std::iota(sequence.begin(), sequence.end(), startValue);
    return sequence;
}

std::vector<int> runningTotal(const std::vector<int>& items) {
    std::vector<int> result(items.size());
    // partial_sum creates a running total: element 1, then 1+2, then 1+2+3 and so on
    std::partial_sum(items.begin(), items.end(), result.begin());
    return result;
}

int dotProduct(const std::vector<int>& firstVector, const std::vector<int>& secondVector) {
    // Critical protection check: cannot perform dot product on vectors of different lengths
    if (firstVector.size() != secondVector.size()) {
        throw std::invalid_argument("Vector sizes must match for dot product");
    }
    // Multiplies each pair of corresponding elements, adds everything together. The 0 at the end is the initial value for the sum
    return std::inner_product(firstVector.begin(), firstVector.end(), secondVector.begin(), 0);
}

int eraseValue(std::vector<int>& items, int targetValue) {
    auto initialSize = items.size();
    // Using the Erase-Remove Idiom. remove pushes garbage to the end, erase physically cuts the size
    items.erase(std::remove(items.begin(), items.end(), targetValue), items.end());
    // Calculate how many were actually deleted
    return static_cast<int>(initialSize - items.size());
}

int eraseIf(std::vector<int>& items, const std::function<bool(int)>& predicate) {
    auto initialSize = items.size();
    // Like eraseValue, but with a lambda condition instead of a specific value
    items.erase(std::remove_if(items.begin(), items.end(), predicate), items.end());
    return static_cast<int>(initialSize - items.size());
}

void uniqueInPlace(std::vector<int>& items) {
    // Deletes duplicates that appear in a sequence. Again using the erase trick
    items.erase(std::unique(items.begin(), items.end()), items.end());
}

} // namespace datatools