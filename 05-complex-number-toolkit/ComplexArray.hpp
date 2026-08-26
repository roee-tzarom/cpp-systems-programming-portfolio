/**
 * @file ComplexArray.hpp
 * @brief Header file for the ComplexArray class managing a dynamic array of Complex numbers
 *
 * This file contains the declaration of the ComplexArray class. It demonstrates
 * composition (HAS-A relationship), dynamic memory management, deep copying
 * (Rule of Three), and operator overloading on custom collections.
 */

#ifndef COMPLEX_ARRAY_HPP
#define COMPLEX_ARRAY_HPP

#include "Complex.hpp"
#include <iostream>

namespace complex_math {

    class ComplexArray {
    private:
        Complex* data;
        int capacity;
        int size;

        // Static counters for tracking array allocations
        static int totalArraysCreated;
        static int currentArrayCount;

        /**
         * @brief Helper method to dynamically double the array's capacity
         */
        void resize();

    public:
        // ============ Constructors & Destructor (Rule of Three) ============
        ComplexArray();
        explicit ComplexArray(int initialCapacity);
        ComplexArray(const ComplexArray& otherArray);
        ~ComplexArray();

        ComplexArray& operator=(const ComplexArray& otherArray);

        // ============ Inline Getters ============
        inline int getSize() const { return size; }
        inline int getCapacity() const { return capacity; }
        inline bool isEmpty() const { return size == 0; }

        // ============ Array Management ============
        void add(const Complex& complexElement);
        void remove(int targetIndex);
        void clear();
        int find(const Complex& complexElement) const;
        bool contains(const Complex& complexElement) const;

        // ============ Mathematical Operations ============
        Complex sum() const;
        Complex average() const;
        Complex max() const;

        // ============ Bracket Operators ============
        Complex& operator[](int targetIndex);
        const Complex& operator[](int targetIndex) const;

        // ============ Arithmetic Operators ============
        ComplexArray operator+(const ComplexArray& otherArray) const;
        ComplexArray operator+(const Complex& scalarComplex) const;
        ComplexArray operator*(double scalarValue) const;

        // ============ Comparison Operators ============
        bool operator==(const ComplexArray& otherArray) const;
        bool operator!=(const ComplexArray& otherArray) const;

        // ============ Static Methods ============
        static int getTotalArraysCreated();
        static int getCurrentArrayCount();

        // ============ Stream Operator ============
        friend std::ostream& operator<<(std::ostream& outStream, const ComplexArray& complexArray);
    };

} // namespace complex_math

#endif // COMPLEX_ARRAY_HPP