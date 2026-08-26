/**
 * @file Student.hpp
 * @brief Header file for the Student class
 *
 * This file contains the declaration of the Student class which manages
 * parallel dynamic arrays of Grades and Courses. It demonstrates advanced
 * memory management (Rule of Three), bracket and parentheses operators,
 * and comprehensive state manipulation.
 *
 * Topics covered:
 * - Dynamic arrays and Destruct-arrays
 * - Deep Copying (Rule of Three)
 * - Bracket Operators []
 * - Functors / Parentheses Operators ()
 * - Friend functions and Ostream Overloading
 */

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <iostream>
#include "Grade.hpp"

namespace grading {

    /**
     * @brief Structure representing a course
     */
    struct Course {
        std::string name;
        std::string code;
        int credits;

        Course() : name("Unknown"), code("000"), credits(0) {}
        Course(const std::string& n, const std::string& c, int cr) 
            : name(n), code(c), credits(cr) {}
    };

    class Student {
    private:
        std::string name;
        std::string studentID;
        
        Grade* grades;
        Course* courses;
        
        int capacity;
        int gradeCount;

        static int totalStudentsCreated;
        static int currentStudentCount;

        /**
         * @brief Helper method to double the capacity of the arrays
         */
        void resize();

    public:
        // ============ Rule of Three ============
        Student();
        Student(const std::string& name, const std::string& studentID, int capacity = 3);
        Student(const Student& other);
        Student& operator=(const Student& other);
        ~Student();

        // ============ Getters (Inline) ============
        inline std::string getName() const { return name; }
        inline std::string getStudentID() const { return studentID; }
        inline int getCapacity() const { return capacity; }
        inline int getGradeCount() const { return gradeCount; }
        
        inline void setName(const std::string& newName) { name = newName; }

        // ============ Grade Management ============
        void addGrade(const Grade& grade, const Course& course);
        void addGrade(const Grade& grade, const std::string& courseName);
        void removeGrade(int index);
        void printGrades() const;

        // ============ Bracket Operators [] ============
        Grade& operator[](int index);
        const Grade& operator[](int index) const;
        
        Grade& operator[](const std::string& courseName);
        const Grade& operator[](const std::string& courseName) const;

        // ============ Parentheses Operators () ============
        double operator()() const;                         // General Average
        double operator()(int limit) const;                // Average of first N
        double operator()(int start, int end) const;       // Average of range
        double operator()(int index, double weight) const; // Weighted average

        // ============ Arithmetic Operators ============
        Student operator+(double bonus) const;
        Student operator*(double factor) const;
        
        Student& operator+=(double bonus);
        Student& operator*=(double factor);

        // ============ Comparison Operators ============
        bool operator==(const Student& other) const;
        bool operator!=(const Student& other) const;
        bool operator<(const Student& other) const;
        bool operator>(const Student& other) const;

        // ============ Analytics Methods ============
        double calculateAverage() const;
        double calculateGPA() const;
        const Grade& getHighestGrade() const;
        const Grade& getLowestGrade() const;
        int countPassingGrades() const;

        // ============ Static Methods ============
        static int getTotalStudentsCreated();
        static int getCurrentStudentCount();

        // ============ Friend Functions ============
        friend bool compareByAverage(const Student& student1, const Student& student2);
        friend bool haveSameGPA(const Student& student1, const Student& student2);
        friend std::ostream& operator<<(std::ostream& outStream, const Student& student);
    };

}

#endif