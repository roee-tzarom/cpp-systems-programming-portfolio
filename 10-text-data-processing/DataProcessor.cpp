#include "DataProcessor.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <cmath>

namespace datatools {

// Allows the compiler to generate the most efficient default constructor possible
DataProcessor::DataProcessor() = default;

// Receives the data by const reference to save double copying in memory
DataProcessor::DataProcessor(const std::vector<double>& initialData) : data(initialData) {}

DataProcessor::DataProcessor(int count, double start) {
    if (count > 0) {
        data.resize(static_cast<size_t>(count));
        // Fills the vector with ascending values elegantly instead of a for loop
        std::iota(data.begin(), data.end(), start);
    }
}

std::vector<double> DataProcessor::getData() const {
    return data;
}

size_t DataProcessor::size() const {
    return data.size();
}

bool DataProcessor::empty() const {
    return data.empty();
}

double DataProcessor::sum() const {
    // 0.0 tells accumulate that we are summing double and not int
    return std::accumulate(data.begin(), data.end(), 0.0);
}

double DataProcessor::product() const {
    // Start from 1.0 (so as not to zero out in multiplication). multiplies tells the algorithm to multiply instead of add
    return std::accumulate(data.begin(), data.end(), 1.0, std::multiplies<double>());
}

double DataProcessor::average() const {
    // Must ensure the vector is not empty to avoid dividing by zero and crashing the program
    if (data.empty()) {
        throw std::invalid_argument("Empty vector");
    }
    return sum() / static_cast<double>(data.size());
}

double DataProcessor::min() const {
    if (data.empty()) {
        throw std::invalid_argument("Empty vector");
    }
    // min_element returns an iterator (pointer), so we add * to extract the value itself
    return *std::min_element(data.begin(), data.end());
}

double DataProcessor::max() const {
    if (data.empty()) {
        throw std::invalid_argument("Empty vector");
    }
    // Extracts the largest value using dereference (*)
    return *std::max_element(data.begin(), data.end());
}

int DataProcessor::countIf(const std::function<bool(double)>& predicate) const {
    // count_if runs over all of them and counts only those that return true in the lambda
    return static_cast<int>(std::count_if(data.begin(), data.end(), predicate));
}

bool DataProcessor::allOf(const std::function<bool(double)>& predicate) const {
    // Returns true only if a-l-l of them meet the condition
    return std::all_of(data.begin(), data.end(), predicate);
}

bool DataProcessor::anyOf(const std::function<bool(double)>& predicate) const {
    // Returns true if at least one element meets the condition
    return std::any_of(data.begin(), data.end(), predicate);
}

bool DataProcessor::noneOf(const std::function<bool(double)>& predicate) const {
    // The opposite of anyOf. Returns true only if none of them meet the condition
    return std::none_of(data.begin(), data.end(), predicate);
}

double DataProcessor::findIf(const std::function<bool(double)>& predicate) const {
    // Stops and returns as soon as it finds the first element that meets the condition (O(N) in the worst case)
    auto iterator = std::find_if(data.begin(), data.end(), predicate);
    if (iterator == data.end()) {
        throw std::invalid_argument("Not found");
    }
    return *iterator;
}

double DataProcessor::innerProduct(const DataProcessor& other) const {
    // Critical protection for inner product - vectors must be of the same length
    if (data.size() != other.size()) {
        throw std::invalid_argument("Size mismatch");
    }
    return std::inner_product(data.begin(), data.end(), other.getData().begin(), 0.0);
}

void DataProcessor::sort() {
    // Default sort (from smallest to largest) modifies the existing vector
    std::sort(data.begin(), data.end());
}

void DataProcessor::sort(const std::function<bool(double, double)>& comparator) {
    // Sort according to the logic passed by the user (e.g., from largest to smallest)
    std::sort(data.begin(), data.end(), comparator);
}

void DataProcessor::partialSort(int n) {
    if (n > 0 && static_cast<size_t>(n) <= data.size()) {
        // Sorts only the first n elements, saving expensive runtime when a full sort is not needed (O(N log n))
        std::partial_sort(data.begin(), data.begin() + n, data.end());
    }
}

void DataProcessor::nthElement(int n) {
    if (n >= 0 && static_cast<size_t>(n) < data.size()) {
        // Places the element at the n-th position exactly where it would sit if the array was fully sorted (very efficient)
        std::nth_element(data.begin(), data.begin() + n, data.end());
    }
}

void DataProcessor::applyTransform(const std::function<double(double)>& transformer) {
    // Overwrites the existing vector with the results of the transformation (in-place)
    std::transform(data.begin(), data.end(), data.begin(), transformer);
}

DataProcessor DataProcessor::transformed(const std::function<double(double)>& transformer) const {
    std::vector<double> result(data.size());
    // Here we copy to a new vector so as not to overwrite the original data (the function is const)
    std::transform(data.begin(), data.end(), result.begin(), transformer);
    return DataProcessor(result);
}

DataProcessor DataProcessor::partialSums() const {
    std::vector<double> result(data.size());
    // Calculates running totals and saves in a new object
    std::partial_sum(data.begin(), data.end(), result.begin());
    return DataProcessor(result);
}

DataProcessor DataProcessor::filter(const std::function<bool(double)>& predicate) const {
    std::vector<double> result;
    // back_inserter takes care of push_back to our new vector for every element that matches
    std::copy_if(data.begin(), data.end(), std::back_inserter(result), predicate);
    return DataProcessor(result);
}

void DataProcessor::replaceIf(const std::function<bool(double)>& predicate, double newValue) {
    // Iterates over the array and replaces values that meet the condition (e.g., to zero out any negative number)
    std::replace_if(data.begin(), data.end(), predicate, newValue);
}

void DataProcessor::fill(double value) {
    // Overwrites all array elements with a single value
    std::fill(data.begin(), data.end(), value);
}

void DataProcessor::generate(int count, const std::function<double()>& generator) {
    if (count > 0) {
        data.resize(static_cast<size_t>(count));
        // Generates new values on the fly using the lambda function (generator)
        std::generate(data.begin(), data.end(), generator);
    } else {
        data.clear();
    }
}

int DataProcessor::removeIf(const std::function<bool(double)>& predicate) {
    auto initialSize = data.size();
    // Erase-Remove trick: remove_if moves elements to the end, erase physically cuts them out
    data.erase(std::remove_if(data.begin(), data.end(), predicate), data.end());
    return static_cast<int>(initialSize - data.size());
}

void DataProcessor::unique() {
    // Deletes only consecutive duplicates (one after the other)
    data.erase(std::unique(data.begin(), data.end()), data.end());
}

void DataProcessor::reverse() {
    // Reverses the order of the elements from end to end
    std::reverse(data.begin(), data.end());
}

void DataProcessor::rotate(int positions) {
    if (!data.empty()) {
        // Modulo protects us in case we are asked to rotate more times than the size of the array
        int safePositions = positions % static_cast<int>(data.size());
        if (safePositions < 0) {
            safePositions += static_cast<int>(data.size()); // Correction for negative rotation (left/right)
        }
        std::rotate(data.begin(), data.begin() + safePositions, data.end());
    }
}

int DataProcessor::partition(const std::function<bool(double)>& predicate) {
    // Pushes everyone who meets the condition to the beginning and the rest to the end. Returns an iterator to the partition point
    auto iterator = std::partition(data.begin(), data.end(), predicate);
    // distance simply calculates how many elements there are from the beginning to the partition point
    return static_cast<int>(std::distance(data.begin(), iterator));
}

int DataProcessor::stablePartition(const std::function<bool(double)>& predicate) {
    // Like partition, but preserves the original internal order among the moved elements (takes slightly more runtime)
    auto iterator = std::stable_partition(data.begin(), data.end(), predicate);
    return static_cast<int>(std::distance(data.begin(), iterator));
}

std::string DataProcessor::toString(const std::string& delimiter) const {
    if (data.empty()) {
        return "";
    }
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
        // Clever trick: if the rounded number equals itself, it is an integer. Print as long to prevent unnecessary zeros.
        if (std::floor(data[i]) == data[i]) {
            oss << static_cast<long long>(data[i]);
        } else {
            oss << data[i];
        }
        
        // Adds a delimiter to all except the last element (so there is no unnecessary trailing comma)
        if (i < data.size() - 1) {
            oss << delimiter;
        }
    }
    return oss.str();
}

} // namespace datatools