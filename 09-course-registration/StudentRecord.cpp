#include "StudentRecord.hpp"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace registration {

StudentRecord createRecord(const std::string& name, int studentId, double grade) {
    if (studentId <= 0) {
        throw std::invalid_argument("ID must be greater than 0");
    }
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("Grade must be between 0 and 100");
    }
    // Packs the data into a tuple (a single object holding several different types of data)
    return std::make_tuple(name, studentId, grade);
}

std::string getName(const StudentRecord& record) {
    // Gets the element at position 0 from the tuple
    return std::get<0>(record);
}

int getId(const StudentRecord& record) {
    // Gets the element at position 1 from the tuple
    return std::get<1>(record);
}

double getGrade(const StudentRecord& record) {
    // Gets the element at position 2 from the tuple
    return std::get<2>(record);
}

void unpackRecord(const StudentRecord& record, std::string& name, int& studentId, double& grade) {
    // C++ trick: tie unpacks the tuple directly into the variables we passed
    std::tie(name, studentId, grade) = record;
}

std::string formatRecord(const StudentRecord& record) {
    std::ostringstream oss;
    // Builds the string efficiently (better than doing regular + concatenation)
    oss << getName(record) << " (ID: " << getId(record) << ", Grade: " << getGrade(record) << ")";
    return oss.str();
}

double averageGrade(const std::vector<StudentRecord>& records) {
    if (records.empty()) {
        throw std::invalid_argument("Cannot calculate average of an empty list");
    }
    double sum = 0.0;
    for (const auto& record : records) {
        sum += getGrade(record);
    }
    return sum / static_cast<double>(records.size());
}

StudentRecord bestStudent(const std::vector<StudentRecord>& records) {
    if (records.empty()) {
        throw std::invalid_argument("Cannot find best student in an empty list");
    }
    
    auto best = records[0];
    for (const auto& record : records) {
        if (getGrade(record) > getGrade(best)) {
            best = record;
        }
    }
    return best;
}

std::vector<StudentRecord> sortByGrade(std::vector<StudentRecord> records) {
    std::sort(records.begin(), records.end(), [](const StudentRecord& recordA, const StudentRecord& recordB) {
        // Returns true if the first grade is higher (this results in a descending sort from highest to lowest)
        return getGrade(recordA) > getGrade(recordB);
    });
    return records;
}

std::vector<StudentRecord> sortByName(std::vector<StudentRecord> records) {
    std::sort(records.begin(), records.end(), [](const StudentRecord& recordA, const StudentRecord& recordB) {
        // Returns true based on alphabetical order
        return getName(recordA) < getName(recordB);
    });
    return records;
}

std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double threshold) {
    std::vector<StudentRecord> filtered;
    for (const auto& record : records) {
        if (getGrade(record) > threshold) {
            filtered.push_back(record);
        }
    }
    return filtered;
}

} // namespace registration