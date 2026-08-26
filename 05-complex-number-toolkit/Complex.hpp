/**
 * @file Complex.hpp
 * @brief Header file for the Complex class representing complex numbers
 *
 * This file contains the declaration of the Complex class, demonstrating
 * operator overloading, explicit conversion operators, static members,
 * and standard memory management tracking.
 */

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <string>
#include <iostream>

namespace complex_math {

    class Complex {
    private:
        double real;
        double imag;

        // Static counters for tracking memory allocations
        static int totalComplexCreated;
        static int currentComplexCount;

    public:
        // ============ Constructors & Destructor ============
        Complex();
        explicit Complex(double realValue);
        Complex(double realValue, double imaginaryValue);
        Complex(const Complex& otherComplex);
        ~Complex();

        Complex& operator=(const Complex& otherComplex);

        // ============ Getters and Setters ============
        double getReal() const;
        double getImag() const;
        void setReal(double realValue);
        void setImag(double imaginaryValue);

        // ============ Mathematical Properties ============
        double magnitude() const;
        Complex conjugate() const;
        bool isZero() const;
        bool isReal() const;

        // ============ Explicit Conversion Operators ============
        explicit operator double() const;
        explicit operator bool() const;
        explicit operator std::string() const;
        std::string toRectangularString() const;

        // ============ Arithmetic Operators (Complex) ============
        Complex operator+(const Complex& otherComplex) const;
        Complex operator-(const Complex& otherComplex) const;
        Complex operator*(const Complex& otherComplex) const;
        Complex operator/(const Complex& otherComplex) const;

        // ============ Arithmetic Operators (Double) ============
        Complex operator+(double scalarValue) const;
        Complex operator-(double scalarValue) const;
        Complex operator*(double scalarValue) const;
        Complex operator/(double scalarValue) const;

        // ============ Unary Operators ============
        Complex operator-() const;

        // ============ Compound Assignment Operators (Complex) ============
        Complex& operator+=(const Complex& otherComplex);
        Complex& operator-=(const Complex& otherComplex);
        Complex& operator*=(const Complex& otherComplex);
        Complex& operator/=(const Complex& otherComplex);

        // ============ Compound Assignment Operators (Double) ============
        Complex& operator+=(double scalarValue);
        Complex& operator-=(double scalarValue);
        Complex& operator*=(double scalarValue);
        Complex& operator/=(double scalarValue);

        // ============ Increment / Decrement ============
        Complex& operator++();    // Prefix
        Complex operator++(int);  // Postfix
        Complex& operator--();    // Prefix
        Complex operator--(int);  // Postfix

        // ============ Comparison Operators ============
        bool operator==(const Complex& otherComplex) const;
        bool operator!=(const Complex& otherComplex) const;
        bool operator<(const Complex& otherComplex) const;
        bool operator>(const Complex& otherComplex) const;

        // ============ Static Methods ============
        static int getTotalComplexCreated();
        static int getCurrentComplexCount();
        static Complex fromPolar(double radius, double thetaAngle);

        // ============ Friend Functions ============
        friend double distance(const Complex& firstComplex, const Complex& secondComplex);
        friend std::ostream& operator<<(std::ostream& outStream, const Complex& complexNumber);
    };

} // namespace complex_math

#endif // COMPLEX_HPP