#include "Student.hpp"
#include <stdexcept>
#include <iostream>

namespace grading {

    int Student::totalStudentsCreated = 0;
    int Student::currentStudentCount = 0;

    void Student::resize() {
        int newCapacity = capacity * 2;
        if (newCapacity == 0) {
            newCapacity = 1;
        }

        Grade* newGrades = new Grade[static_cast<size_t>(newCapacity)];
        Course* newCourses = new Course[static_cast<size_t>(newCapacity)];

        for (int i = 0; i < gradeCount; ++i) {
            newGrades[i] = grades[i];
            newCourses[i] = courses[i];
        }

        delete[] grades;
        delete[] courses;

        grades = newGrades;
        courses = newCourses;
        capacity = newCapacity;
    }

    Student::Student() : name("Unknown"), studentID("000"), grades(nullptr), courses(nullptr), capacity(0), gradeCount(0) {
        totalStudentsCreated++;
        currentStudentCount++;
    }

    Student::Student(const std::string& name, const std::string& studentID, int capacity)
        : name(name), studentID(studentID), capacity(capacity > 0 ? capacity : 3), gradeCount(0) {
        grades = new Grade[static_cast<size_t>(this->capacity)];
        courses = new Course[static_cast<size_t>(this->capacity)];
        totalStudentsCreated++;
        currentStudentCount++;
    }

    Student::Student(const Student& other)
        : name(other.name), studentID(other.studentID), capacity(other.capacity), gradeCount(other.gradeCount) {
        
        grades = new Grade[static_cast<size_t>(capacity)];
        courses = new Course[static_cast<size_t>(capacity)];
        
        for (int i = 0; i < gradeCount; ++i) {
            grades[i] = other.grades[i];
            courses[i] = other.courses[i];
        }
        
        totalStudentsCreated++;
        currentStudentCount++;
    }

    Student& Student::operator=(const Student& other) {
        if (this == &other) {
            return *this;
        }

        delete[] grades;
        delete[] courses;

        name = other.name;
        studentID = other.studentID;
        capacity = other.capacity;
        gradeCount = other.gradeCount;

        grades = new Grade[static_cast<size_t>(capacity)];
        courses = new Course[static_cast<size_t>(capacity)];

        for (int i = 0; i < gradeCount; ++i) {
            grades[i] = other.grades[i];
            courses[i] = other.courses[i];
        }

        return *this;
    }

    Student::~Student() {
        delete[] grades;
        delete[] courses;
        currentStudentCount--;
    }

    void Student::addGrade(const Grade& grade, const Course& course) {
        if (gradeCount == capacity) {
            resize();
        }
        grades[gradeCount] = grade;
        courses[gradeCount] = course;
        gradeCount++;
    }

    void Student::addGrade(const Grade& grade, const std::string& courseName) {
        addGrade(grade, Course(courseName, "N/A", 0));
    }

    void Student::removeGrade(int index) {
        if (index < 0 || index >= gradeCount) {
            return;
        }
        
        for (int i = index; i < gradeCount - 1; ++i) {
            grades[i] = grades[i + 1];
            courses[i] = courses[i + 1];
        }
        gradeCount--;
    }

    void Student::printGrades() const {
        for (int i = 0; i < gradeCount; ++i) {
            std::cout << courses[i].name << ": " << grades[i] << "\n";
        }
    }

    Grade& Student::operator[](int index) {
        if (index < 0 || index >= gradeCount) {
            throw std::out_of_range("Index out of bounds");
        }
        return grades[index];
    }

    const Grade& Student::operator[](int index) const {
        if (index < 0 || index >= gradeCount) {
            throw std::out_of_range("Index out of bounds");
        }
        return grades[index];
    }

    Grade& Student::operator[](const std::string& courseName) {
        for (int i = 0; i < gradeCount; ++i) {
            if (courses[i].name == courseName) {
                return grades[i];
            }
        }
        throw std::out_of_range("Course not found");
    }

    const Grade& Student::operator[](const std::string& courseName) const {
        for (int i = 0; i < gradeCount; ++i) {
            if (courses[i].name == courseName) {
                return grades[i];
            }
        }
        throw std::out_of_range("Course not found");
    }

    double Student::operator()() const {
        return calculateAverage();
    }

    double Student::operator()(int limit) const {
        if (limit <= 0 || gradeCount == 0) {
            return 0.0;
        }
        int actualLimit = (limit < gradeCount) ? limit : gradeCount;
        
        double sum = 0;
        for (int i = 0; i < actualLimit; ++i) {
            sum += (double)grades[i];
        }
        return sum / actualLimit;
    }

    double Student::operator()(int start, int end) const {
        if (start < 0 || start >= gradeCount || end < start || gradeCount == 0) {
            return 0.0;
        }
        int actualEnd = (end < gradeCount) ? end : gradeCount - 1;
        
        double sum = 0;
        int count = 0;
        for (int i = start; i <= actualEnd; ++i) {
            sum += (double)grades[i];
            count++;
        }
        return count > 0 ? sum / count : 0.0;
    }

    double Student::operator()(int index, double weight) const {
        if (index < 0 || index >= gradeCount || gradeCount == 0) {
            return 0.0;
        }
        
        double sumOther = 0.0;
        for (int i = 0; i < gradeCount; ++i) {
            if (i != index) {
                sumOther += (double)grades[i];
            }
        }
        
        double weightedTarget = (double)grades[index] * weight;
        return (weightedTarget + sumOther) / (weight + (gradeCount - 1));
    }

    Student Student::operator+(double bonus) const {
        Student result(*this);
        for (int i = 0; i < result.gradeCount; ++i) {
            result.grades[i] += bonus;
        }
        return result;
    }

    Student Student::operator*(double factor) const {
        Student result(*this);
        for (int i = 0; i < result.gradeCount; ++i) {
            result.grades[i] *= factor;
        }
        return result;
    }

    Student& Student::operator+=(double bonus) {
        for (int i = 0; i < gradeCount; ++i) {
            grades[i] += bonus;
        }
        return *this;
    }

    Student& Student::operator*=(double factor) {
        for (int i = 0; i < gradeCount; ++i) {
            grades[i] *= factor;
        }
        return *this;
    }

    bool Student::operator==(const Student& other) const {
        return this->calculateGPA() == other.calculateGPA();
    }

    bool Student::operator!=(const Student& other) const {
        return !(*this == other);
    }

    bool Student::operator<(const Student& other) const {
        return this->calculateGPA() < other.calculateGPA();
    }

    bool Student::operator>(const Student& other) const {
        return this->calculateGPA() > other.calculateGPA();
    }

    double Student::calculateAverage() const {
        if (gradeCount == 0) {
            return 0.0;
        }
        double sum = 0.0;
        for (int i = 0; i < gradeCount; ++i) {
            sum += (double)grades[i];
        }
        return sum / gradeCount;
    }

    double Student::calculateGPA() const {
        if (gradeCount == 0) {
            return 0.0;
        }
        double sumPoints = 0.0;
        for (int i = 0; i < gradeCount; ++i) {
            sumPoints += grades[i].getGPAPoints();
        }
        return sumPoints / gradeCount;
    }

    const Grade& Student::getHighestGrade() const {
        if (gradeCount == 0) {
            throw std::out_of_range("No grades available");
        }
        int maxIndex = 0;
        for (int i = 1; i < gradeCount; ++i) {
            if (grades[i] > grades[maxIndex]) {
                maxIndex = i;
            }
        }
        return grades[maxIndex];
    }

    const Grade& Student::getLowestGrade() const {
        if (gradeCount == 0) {
            throw std::out_of_range("No grades available");
        }
        int minIndex = 0;
        for (int i = 1; i < gradeCount; ++i) {
            if (grades[i] < grades[minIndex]) {
                minIndex = i;
            }
        }
        return grades[minIndex];
    }

    int Student::countPassingGrades() const {
        int count = 0;
        for (int i = 0; i < gradeCount; ++i) {
            if (grades[i].isPassing()) {
                count++;
            }
        }
        return count;
    }

    int Student::getTotalStudentsCreated() { return totalStudentsCreated; }
    int Student::getCurrentStudentCount() { return currentStudentCount; }

    bool compareByAverage(const Student& student1, const Student& student2) {
        return student1.calculateAverage() > student2.calculateAverage();
    }

    bool haveSameGPA(const Student& student1, const Student& student2) {
        return student1.calculateGPA() == student2.calculateGPA();
    }

    std::ostream& operator<<(std::ostream& outStream, const Student& student) {
        outStream << "Student: " << student.name << " (ID: " << student.studentID << ")\n";
        for (int i = 0; i < student.gradeCount; ++i) {
            outStream << "- " << student.courses[i].name << ": " << student.grades[i] << "\n";
        }
        return outStream;
    }

}