/**
 * @file StudentRecord.hpp
 * @brief Functions and type definitions for managing student records using std::tuple.
 */

#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace registration {

/**
 * @brief Type alias for a student record containing: Name, ID, Grade.
 */
using StudentRecord = std::tuple<std::string, int, double>;

/**
 * @brief Creates a new student record.
 * @param name The student's name.
 * @param id The student's ID (must be > 0).
 * @param grade The student's grade (must be between 0.0 and 100.0).
 * @return A new StudentRecord tuple.
 * @throws std::invalid_argument if ID or grade are out of valid range.
 */
StudentRecord createRecord(const std::string& name, int id, double grade);

/**
 * @brief Extracts the name from a student record.
 * @param record The student record tuple.
 * @return The student's name.
 */
std::string getName(const StudentRecord& record);

/**
 * @brief Extracts the ID from a student record.
 * @param record The student record tuple.
 * @return The student's ID.
 */
int getId(const StudentRecord& record);

/**
 * @brief Extracts the grade from a student record.
 * @param record The student record tuple.
 * @return The student's grade.
 */
double getGrade(const StudentRecord& record);

/**
 * @brief Unpacks a student record into individual variables using std::tie.
 * @param record The student record to unpack.
 * @param name Reference to store the unpacked name.
 * @param id Reference to store the unpacked ID.
 * @param grade Reference to store the unpacked grade.
 */
void unpackRecord(const StudentRecord& record, std::string& name, int& id, double& grade);

/**
 * @brief Formats the student record as a readable string.
 * @param record The student record to format.
 * @return A formatted string: "Name (ID: X, Grade: Y)"
 */
std::string formatRecord(const StudentRecord& record);

/**
 * @brief Calculates the average grade of a list of students.
 * @param records A vector of student records.
 * @return The average grade.
 * @throws std::invalid_argument if the list is empty.
 */
double averageGrade(const std::vector<StudentRecord>& records);

/**
 * @brief Finds the student with the highest grade.
 * @param records A vector of student records.
 * @return The student record with the highest grade.
 * @throws std::invalid_argument if the list is empty.
 */
StudentRecord bestStudent(const std::vector<StudentRecord>& records);

/**
 * @brief Sorts a list of students by grade in descending order.
 * @param records A vector of student records.
 * @return A newly sorted vector.
 */
std::vector<StudentRecord> sortByGrade(std::vector<StudentRecord> records);

/**
 * @brief Sorts a list of students by name in ascending alphabetical order.
 * @param records A vector of student records.
 * @return A newly sorted vector.
 */
std::vector<StudentRecord> sortByName(std::vector<StudentRecord> records);

/**
 * @brief Filters the list to return only students with a grade strictly greater than the threshold.
 * @param records A vector of student records.
 * @param threshold The minimum grade required to pass the filter.
 * @return A vector of filtered student records.
 */
std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double threshold);

} // namespace registration