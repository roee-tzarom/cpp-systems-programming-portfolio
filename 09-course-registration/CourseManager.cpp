#include "CourseManager.hpp"
#include <stdexcept>
#include <algorithm>

namespace registration {

void CourseManager::addStudent(const StudentRecord& record) {
    int studentId = getId(record);
    // If find doesn't return end(), it means the student was found in the map
    if (students.find(studentId) != students.end()) {
        throw std::invalid_argument("Student already exists");
    }
    students[studentId] = record;
}

StudentRecord CourseManager::getStudent(int studentId) const {
    auto iterator = students.find(studentId);
    if (iterator == students.end()) {
        throw std::invalid_argument("Student not found");
    }
    // In a map, first is the key (ID) and second is the value (the student itself)
    return iterator->second;
}

void CourseManager::createCourse(const std::string& courseName) {
    if (courses.find(courseName) != courses.end()) {
        throw std::invalid_argument("Course already exists");
    }
    courses.insert(courseName);
    // Initialize empty lists for the new course to prevent access errors later
    enrollments[courseName] = std::set<int>();
    grades[courseName] = std::map<int, double>();
}

void CourseManager::enrollStudent(int studentId, const std::string& courseName) {
    if (students.find(studentId) == students.end()) {
        throw std::invalid_argument("Student not found");
    }
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    if (enrollments[courseName].find(studentId) != enrollments[courseName].end()) {
        throw std::invalid_argument("Student already enrolled");
    }
    enrollments[courseName].insert(studentId);
}

void CourseManager::removeStudent(int studentId, const std::string& courseName) {
    if (students.find(studentId) == students.end()) {
        throw std::invalid_argument("Student not found");
    }
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    auto iterator = enrollments[courseName].find(studentId);
    if (iterator == enrollments[courseName].end()) {
        throw std::invalid_argument("Student not enrolled");
    }
    // Must delete from both enrollments and grades to maintain synchronization
    enrollments[courseName].erase(iterator);
    grades[courseName].erase(studentId);
}

int CourseManager::getEnrollmentCount(const std::string& courseName) const {
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    // Use 'at' for safe access (throws an error if it doesn't exist, even though we already checked)
    return static_cast<int>(enrollments.at(courseName).size());
}

bool CourseManager::isEnrolled(int studentId, const std::string& courseName) const {
    if (students.find(studentId) == students.end()) {
        throw std::invalid_argument("Student not found");
    }
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    return enrollments.at(courseName).find(studentId) != enrollments.at(courseName).end();
}

std::vector<int> CourseManager::getEnrolledStudents(const std::string& courseName) const {
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    const auto& enrolledSet = enrollments.at(courseName);
    // Copy the set into a vector using the set's iterators
    return std::vector<int>(enrolledSet.begin(), enrolledSet.end());
}

std::vector<std::string> CourseManager::getStudentCourses(int studentId) const {
    if (students.find(studentId) == students.end()) {
        throw std::invalid_argument("Student not found");
    }
    std::vector<std::string> studentCourses;
    // Iterate through all courses and check which ones the student is enrolled in
    for (const auto& pair : enrollments) {
        if (pair.second.find(studentId) != pair.second.end()) {
            studentCourses.push_back(pair.first);
        }
    }
    return studentCourses;
}

std::vector<int> CourseManager::studentsInBothCourses(const std::string& course1, const std::string& course2) const {
    if (courses.find(course1) == courses.end() || courses.find(course2) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    const auto& set1 = enrollments.at(course1);
    const auto& set2 = enrollments.at(course2);
    std::vector<int> result;
    // Finds the common elements (intersection). back_inserter ensures the vector grows as needed
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(result));
    return result;
}

std::vector<int> CourseManager::studentsInEitherCourse(const std::string& course1, const std::string& course2) const {
    if (courses.find(course1) == courses.end() || courses.find(course2) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    const auto& set1 = enrollments.at(course1);
    const auto& set2 = enrollments.at(course2);
    std::vector<int> result;
    // Merges both lists into a single array (without duplicates, because these are sets)
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(result));
    return result;
}

void CourseManager::assignGrade(int studentId, const std::string& courseName, double grade) {
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("Invalid grade");
    }
    if (!isEnrolled(studentId, courseName)) {
        throw std::invalid_argument("Student not enrolled in course");
    }
    grades[courseName][studentId] = grade;
}

double CourseManager::getCourseAverage(const std::string& courseName) const {
    if (courses.find(courseName) == courses.end()) {
        throw std::invalid_argument("Course not found");
    }
    const auto& courseGrades = grades.at(courseName);
    if (courseGrades.empty()) {
        throw std::invalid_argument("No grades assigned");
    }
    double sum = 0.0;
    // Iterates over all (ID, grade) pairs of the course and sums only the grades (second)
    for (const auto& pair : courseGrades) {
        sum += pair.second;
    }
    return sum / static_cast<double>(courseGrades.size());
}

std::vector<std::string> CourseManager::getAllCourses() const {
    // Builds a vector directly from the set of courses
    return std::vector<std::string>(courses.begin(), courses.end());
}

std::vector<int> CourseManager::getAllStudentIds() const {
    std::vector<int> ids;
    // reserve saves memory allocations because we know how many students there are
    ids.reserve(students.size());
    for (const auto& pair : students) {
        ids.push_back(pair.first);
    }
    return ids;
}

int CourseManager::getTotalStudents() const {
    return static_cast<int>(students.size());
}

int CourseManager::getTotalCourses() const {
    return static_cast<int>(courses.size());
}

} // namespace registration