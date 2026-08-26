/**
 * @file Stack.hpp
 * @brief Header file for the generic Stack class
 *
 * This file contains the template class Stack, an adapter over Container
 * that provides Last-In-First-Out (LIFO) data structure functionality.
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

    template <typename T>
    class Stack {
    private:
        // Adapter pattern (Composition instead of Inheritance): The stack doesn't "inherit" from the container but "holds" it
        Container<T> elements;

    public:
        // Default constructor, copy constructor, and assignment operator 
        // are implicitly handled correctly because Container manages its own memory.
        // Because the Container knows how to manage memory, the Rule of Zero applies to us (we don't need to write a destructor)
        Stack() = default;

        // ============ Core Operations ============
        void push(const T& item) {
            elements.add(item);
        }

        T pop() {
            if (elements.isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            int topIndex = elements.getCount() - 1;
            T topElement = elements.get(topIndex);
            elements.removeAt(topIndex);
            return topElement;
        }

        T& top() {
            if (elements.isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return elements.get(elements.getCount() - 1);
        }

        const T& top() const {
            if (elements.isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return elements.get(elements.getCount() - 1);
        }

        // ============ Getters & Utility ============
        int size() const {
            return elements.getCount();
        }

        bool isEmpty() const {
            return elements.isEmpty();
        }

        // ============ Iterator Methods ============
        // Iterates from bottom to top
        // Must use the word typename because Iterator is a type that depends on the template parameter (Dependent Type)
        typename Container<T>::Iterator begin() const {
            return elements.begin();
        }

        typename Container<T>::Iterator end() const {
            return elements.end();
        }
    };

} // namespace containers

#endif // STACK_HPP