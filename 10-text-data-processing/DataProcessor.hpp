/**
 * @file DataProcessor.hpp
 * @brief Class for numerical data processing using STL algorithms.
 */

#pragma once

#include <vector>
#include <string>
#include <functional>

namespace datatools {

/**
 * @brief Manages a collection of double-precision numbers and provides
 * various STL-based processing capabilities.
 */
class DataProcessor {
private:
    std::vector<double> data;

public:
    /**
     * @brief Default constructor creating an empty DataProcessor.
     */
    DataProcessor();

    /**
     * @brief Constructs a DataProcessor from an existing vector.
     * @param initialData The initial vector of doubles.
     */
    DataProcessor(const std::vector<double>& initialData);

    /**
     * @brief Constructs a DataProcessor containing sequential values (iota).
     * @param count Number of elements to generate.
     * @param start The starting value.
     */
    explicit DataProcessor(int count, double start);

    /**
     * @brief Returns a copy of the underlying data vector.
     * @return std::vector<double> representing the data.
     */
    std::vector<double> getData() const;

    /**
     * @brief Gets the number of elements in the processor.
     * @return size_t The size of the data.
     */
    size_t size() const;

    /**
     * @brief Checks if the data container is empty.
     * @return true if empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Calculates the sum of all elements.
     * @return double The sum, or 0.0 if empty.
     */
    double sum() const;

    /**
     * @brief Calculates the product of all elements.
     * @return double The product.
     */
    double product() const;

    /**
     * @brief Calculates the average (mean) of all elements.
     * @return double The average.
     * @throws std::invalid_argument if the collection is empty.
     */
    double average() const;

    /**
     * @brief Finds the minimum element in the data.
     * @return double The minimum value.
     * @throws std::invalid_argument if the collection is empty.
     */
    double min() const;

    /**
     * @brief Finds the maximum element in the data.
     * @return double The maximum value.
     * @throws std::invalid_argument if the collection is empty.
     */
    double max() const;

    /**
     * @brief Counts elements that satisfy a given condition.
     * @param predicate A lambda function returning bool.
     * @return int The number of elements matching the condition.
     */
    int countIf(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Checks if all elements satisfy a given condition.
     * @param predicate A lambda function returning bool.
     * @return true if all match, false otherwise.
     */
    bool allOf(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Checks if any element satisfies a given condition.
     * @param predicate A lambda function returning bool.
     * @return true if at least one matches, false otherwise.
     */
    bool anyOf(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Checks if no elements satisfy a given condition.
     * @param predicate A lambda function returning bool.
     * @return true if none match, false otherwise.
     */
    bool noneOf(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Finds the first element satisfying a condition.
     * @param predicate A lambda function returning bool.
     * @return double The first matching element.
     * @throws std::invalid_argument if no element matches.
     */
    double findIf(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Computes the dot product with another DataProcessor.
     * @param other The other DataProcessor.
     * @return double The inner product.
     * @throws std::invalid_argument if sizes do not match.
     */
    double innerProduct(const DataProcessor& other) const;

    /**
     * @brief Sorts the elements in ascending order.
     */
    void sort();

    /**
     * @brief Sorts the elements using a custom comparator.
     * @param comparator A lambda defining the sorting logic.
     */
    void sort(const std::function<bool(double, double)>& comparator);

    /**
     * @brief Partially sorts the first 'n' elements in ascending order.
     * @param n The number of elements to fully sort.
     */
    void partialSort(int n);

    /**
     * @brief Reorders elements so the nth element is at its correct sorted position.
     * @param n The index.
     */
    void nthElement(int n);

    /**
     * @brief Applies a transformation function to all elements in-place.
     * @param transformer A lambda function modifying a double.
     */
    void applyTransform(const std::function<double(double)>& transformer);

    /**
     * @brief Returns a new DataProcessor with transformed elements.
     * @param transformer A lambda function returning a modified double.
     * @return DataProcessor A new processor with the transformed data.
     */
    DataProcessor transformed(const std::function<double(double)>& transformer) const;

    /**
     * @brief Computes the partial sums of the data.
     * @return DataProcessor A new processor holding the partial sums.
     */
    DataProcessor partialSums() const;

    /**
     * @brief Filters elements based on a condition, keeping those that match.
     * @param predicate A lambda function returning bool.
     * @return DataProcessor A new processor containing only matching elements.
     */
    DataProcessor filter(const std::function<bool(double)>& predicate) const;

    /**
     * @brief Replaces elements matching a condition with a new value.
     * @param predicate A lambda function returning bool.
     * @param newValue The value to insert when the condition is met.
     */
    void replaceIf(const std::function<bool(double)>& predicate, double newValue);

    /**
     * @brief Overwrites all elements with a single value.
     * @param value The value to fill the container with.
     */
    void fill(double value);

    /**
     * @brief Generates new elements using a generator function.
     * Replaces existing data.
     * @param count Number of elements to generate.
     * @param generator A lambda function providing the values.
     */
    void generate(int count, const std::function<double()>& generator);

    /**
     * @brief Removes elements satisfying a condition.
     * Utilizes the erase-remove idiom.
     * @param predicate A lambda function returning bool.
     * @return int The number of elements removed.
     */
    int removeIf(const std::function<bool(double)>& predicate);

    /**
     * @brief Removes consecutive duplicate elements.
     * Utilizes the erase-unique idiom.
     */
    void unique();

    /**
     * @brief Reverses the order of elements in-place.
     */
    void reverse();

    /**
     * @brief Rotates the elements left by a given number of positions.
     * @param positions The number of positions to rotate.
     */
    void rotate(int positions);

    /**
     * @brief Partitions the elements based on a condition.
     * @param predicate A lambda function returning bool.
     * @return int The count of elements in the first group.
     */
    int partition(const std::function<bool(double)>& predicate);

    /**
     * @brief Stably partitions the elements based on a condition.
     * @param predicate A lambda function returning bool.
     * @return int The count of elements in the first group.
     */
    int stablePartition(const std::function<bool(double)>& predicate);

    /**
     * @brief Converts the data to a formatted string.
     * Whole numbers are printed without trailing zeros.
     * @param delimiter The string to place between elements. Defaults to ", ".
     * @return std::string The formatted string.
     */
    std::string toString(const std::string& delimiter = ", ") const;
};

} // namespace datatools