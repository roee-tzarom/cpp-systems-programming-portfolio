/**
 * @file CourseManager.hpp
 * @brief Class definition for managing students and courses using STL containers.
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "StudentRecord.hpp"

namespace registration {

/**
 * @brief Manages the registration system including students, courses, enrollments, and grades.
 */
class CourseManager {
private:
    std::map<int, StudentRecord> students;
    std::set<std::string> courses;
    std::map<std::string, std::set<int>> enrollments;
    std::map<std::string, std::map<int, double>> grades;

public:
    /**
     * @brief Adds a new student to the system.
     * @param record The student record to add.
     * @throws std::invalid_argument if a student with the same ID already exists.
     */
    void addStudent(const StudentRecord& record);

    /**
     * @brief Retrieves a student record by ID.
     * @param id The ID of the student.
     * @return The requested StudentRecord.
     * @throws std::invalid_argument if the student does not exist.
     */
    StudentRecord getStudent(int id) const;

    /**
     * @brief Creates a new course in the system.
     * @param courseName The name of the course.
     * @throws std::invalid_argument if the course already exists.
     */
    void createCourse(const std::string& courseName);

    /**
     * @brief Enrolls a student in a specific course.
     * @param studentId The ID of the student.
     * @param courseName The name of the course.
     * @throws std::invalid_argument if the student/course do not exist, or if already enrolled.
     */
    void enrollStudent(int studentId, const std::string& courseName);

    /**
     * @brief Removes a student from a specific course.
     * @param studentId The ID of the student.
     * @param courseName The name of the course.
     * @throws std::invalid_argument if the student/course do not exist, or if not enrolled.
     */
    void removeStudent(int studentId, const std::string& courseName);

    /**
     * @brief Gets the total number of students enrolled in a specific course.
     * @param courseName The name of the course.
     * @return The number of enrolled students.
     * @throws std::invalid_argument if the course does not exist.
     */
    int getEnrollmentCount(const std::string& courseName) const;

    /**
     * @brief Checks if a student is enrolled in a specific course.
     * @param studentId The ID of the student.
     * @param courseName The name of the course.
     * @return true if enrolled, false otherwise.
     * @throws std::invalid_argument if the student or course do not exist.
     */
    bool isEnrolled(int studentId, const std::string& courseName) const;

    /**
     * @brief Retrieves a sorted list of student IDs enrolled in a course.
     * @param courseName The name of the course.
     * @return A vector of student IDs.
     * @throws std::invalid_argument if the course does not exist.
     */
    std::vector<int> getEnrolledStudents(const std::string& courseName) const;

    /**
     * @brief Retrieves a sorted list of courses a specific student is enrolled in.
     * @param studentId The ID of the student.
     * @return A vector of course names.
     * @throws std::invalid_argument if the student does not exist.
     */
    std::vector<std::string> getStudentCourses(int studentId) const;

    /**
     * @brief Finds students enrolled in both specified courses (Intersection).
     * @param course1 The first course.
     * @param course2 The second course.
     * @return A sorted vector of student IDs.
     * @throws std::invalid_argument if either course does not exist.
     */
    std::vector<int> studentsInBothCourses(const std::string& course1, const std::string& course2) const;

    /**
     * @brief Finds students enrolled in at least one of the specified courses (Union).
     * @param course1 The first course.
     * @param course2 The second course.
     * @return A sorted vector of student IDs.
     * @throws std::invalid_argument if either course does not exist.
     */
    std::vector<int> studentsInEitherCourse(const std::string& course1, const std::string& course2) const;

    /**
     * @brief Assigns a grade to a student for a specific course.
     * @param studentId The ID of the student.
     * @param courseName The name of the course.
     * @param grade The grade to assign (0.0 to 100.0).
     * @throws std::invalid_argument if student/course do not exist, student not enrolled, or grade invalid.
     */
    void assignGrade(int studentId, const std::string& courseName, double grade);

    /**
     * @brief Calculates the average grade of all students who received a grade in a course.
     * @param courseName The name of the course.
     * @return The average grade.
     * @throws std::invalid_argument if the course does not exist or no grades are assigned.
     */
    double getCourseAverage(const std::string& courseName) const;

    /**
     * @brief Retrieves all courses in the system.
     * @return A sorted vector of course names.
     */
    std::vector<std::string> getAllCourses() const;

    /**
     * @brief Retrieves all student IDs in the system.
     * @return A sorted vector of student IDs.
     */
    std::vector<int> getAllStudentIds() const;

    /**
     * @brief Gets the total number of registered students.
     * @return The number of students.
     */
    int getTotalStudents() const;

    /**
     * @brief Gets the total number of created courses.
     * @return The number of courses.
     */
    int getTotalCourses() const;
};

} // namespace registration