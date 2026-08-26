/**
 * @file Algorithms.hpp
 * @brief Header file for generic algorithms
 *
 * This file contains template functions for searching, modifying,
 * and aggregating data within the generic Container classes.
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

namespace containers {

    // ============ Print & Formatting ============

    template <typename T>
    void print(const Container<T>& c, std::ostream& os = std::cout) {
        os << "[";
        bool first = true;
        for (const auto& val : c) {
            if (!first) os << ", ";
            os << val;
            first = false;
        }
        os << "]";
    }

    // Template overloading: If we pass a Stack, the compiler will know to run this function instead of the general one
    template <typename T>
    void print(const Stack<T>& s, std::ostream& os = std::cout) {
        os << "Stack(bottom -> top): [";
        bool first = true;
        for (const auto& val : s) {
            if (!first) os << ", ";
            os << val;
            first = false;
        }
        os << "]";
    }

    template <typename T>
    void print(const Queue<T>& q, std::ostream& os = std::cout) {
        os << "Queue(front -> back): [";
        bool first = true;
        for (const auto& val : q) {
            if (!first) os << ", ";
            os << val;
            first = false;
        }
        os << "]";
    }

    template <typename T>
    std::string toString(const Container<T>& c) {
        std::ostringstream oss;
        // Passes the stream (oss) as a parameter, so the function prints into it instead of to the screen
        print(c, oss);
        return oss.str();
    }

    // ============ Search & Count ============

    template <typename T>
    int find(const Container<T>& c, const T& value) {
        int index = 0;
        for (const auto& val : c) {
            if (val == value) return index;
            index++;
        }
        return -1;
    }

    template <typename T>
    int count(const Container<T>& c, const T& value) {
        int cnt = 0;
        for (const auto& val : c) {
            if (val == value) cnt++;
        }
        return cnt;
    }

    template <typename T>
    bool contains(const Container<T>& c, const T& value) {
        return find(c, value) != -1;
    }

    // ============ Aggregates ============

    template <typename T>
    T sum(const Container<T>& c) {
        // Value Initialization: Safely initializes to zero (if it's a number) or an empty string (if it's a string)
        T total = T(); 
        for (const auto& val : c) {
            total += val;
        }
        return total;
    }

    template <typename T>
    T min(const Container<T>& c) {
        if (c.isEmpty()) {
            throw std::underflow_error("Container is empty");
        }
        auto it = c.begin();
        // Uses Dereference (*) to extract the first value which will serve as the baseline for comparison
        T minimum = *it;
        ++it;
        for (; it != c.end(); ++it) {
            if (*it < minimum) minimum = *it;
        }
        return minimum;
    }

    template <typename T>
    T max(const Container<T>& c) {
        if (c.isEmpty()) {
            throw std::underflow_error("Container is empty");
        }
        auto it = c.begin();
        T maximum = *it;
        ++it;
        for (; it != c.end(); ++it) {
            if (*it > maximum) maximum = *it;
        }
        return maximum;
    }

    // ============ Modifications ============

    // Uses a generic type Func that allows passing a lambda, a regular function, or a function object
    template <typename T, typename Func>
    void transform(Container<T>& c, Func f) {
        for (auto it = c.begin(); it != c.end(); ++it) {
            f(*it);
        }
    }

    template <typename T, typename Pred>
    Container<T> filter(const Container<T>& c, Pred p) {
        Container<T> result;
        for (const auto& val : c) {
            // Pred is a function that returns a boolean (a condition for filtering)
            if (p(val)) {
                result.add(val);
            }
        }
        return result;
    }

    template <typename T>
    void reverse(Container<T>& c) {
        int left = 0;
        int right = c.getCount() - 1;
        // In-Place array reversal (without allocating additional memory)
        while (left < right) {
            T temp = c.get(left);
            c.get(left) = c.get(right);
            c.get(right) = temp;
            left++;
            right--;
        }
    }

} // namespace containers

#endif // ALGORITHMS_HPP