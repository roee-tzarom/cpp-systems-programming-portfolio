/**
 * @file Grade.hpp
 * @brief Header file for the Grade class
 *
 * This file contains the declaration of the Grade class which represents
 * a single student grade (0.0 to 100.0). It heavily demonstrates the use 
 * of operator overloading in C++, including arithmetic, comparison, 
 * increment/decrement, and explicit casting operators.
 *
 * Topics covered:
 * - Operator Overloading
 * - Explicit Type Conversion
 * - Static Members
 * - Friend Functions (Ostream)
 */

#ifndef GRADE_HPP
#define GRADE_HPP

#include <iostream>
#include <string>

namespace grading {

    class Grade {
    private:
        double value;

        static int totalGradesCreated;
        static constexpr double PASSING_GRADE = 60.0;

        /**
         * @brief Helper method to clamp the grade between 0.0 and 100.0
         */
        void bound();

    public:
        /**
         * @brief Constructor (Default and Parameterized)
         */
        Grade(double val = 0.0);

        // ============ Arithmetic Operators ============
        Grade operator+(const Grade& other) const;
        Grade operator-(const Grade& other) const;
        Grade operator*(const Grade& other) const;
        Grade operator/(const Grade& other) const;
        
        Grade operator+(double num) const;
        friend Grade operator+(double num, const Grade& grade);
        Grade operator-(double num) const;
        Grade operator*(double num) const;
        friend Grade operator*(double num, const Grade& grade);
        Grade operator/(double num) const;

        Grade& operator+=(const Grade& other);
        Grade& operator-=(const Grade& other);
        Grade& operator*=(const Grade& other);
        Grade& operator/=(const Grade& other);
        
        Grade& operator+=(double num);
        Grade& operator-=(double num);
        Grade& operator*=(double num);
        Grade& operator/=(double num);

        // ============ Comparison Operators ============
        bool operator==(const Grade& other) const;
        bool operator!=(const Grade& other) const;
        bool operator<(const Grade& other) const;
        bool operator>(const Grade& other) const;
        bool operator<=(const Grade& other) const;
        bool operator>=(const Grade& other) const;

        // ============ Prefix / Postfix Operators ============
        Grade& operator++();    // Pre-increment
        Grade operator++(int);  // Post-increment
        Grade& operator--();    // Pre-decrement
        Grade operator--(int);  // Post-decrement

        // ============ Explicit Conversion Operators ============
        explicit operator int() const;
        explicit operator double() const;
        explicit operator std::string() const;

        // ============ Getters, Setters and Logic ============
        double getScore() const;
        void setScore(double newScore);
        std::string getLetterGrade() const;
        bool isPassing() const;
        double getGPAPoints() const;

        // ============ Stream Operator ============
        /**
         * @brief Prints the grade in format: "85.50 (B)"
         */
        friend std::ostream& operator<<(std::ostream& outStream, const Grade& grade);

        // ============ Static Methods ============
        static int getTotalGradesCreated();
        static double getPassingGrade();
    };

} 

#endif