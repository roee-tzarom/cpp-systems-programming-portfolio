/**
 * @file Queue.hpp
 * @brief Header file for the generic Queue class
 *
 * This file contains the template class Queue, an adapter over Container
 * that provides First-In-First-Out (FIFO) data structure functionality.
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

    template <typename T>
    class Queue {
    private:
        // Again using the Adapter Pattern to easily create a queue
        Container<T> elements;

    public:
        // Default constructor, copy constructor, and assignment operator 
        // are implicitly handled correctly because Container manages its own memory.
        Queue() = default;

        // ============ Core Operations ============
        void enqueue(const T& item) {
            elements.add(item);
        }

        T dequeue() {
            if (elements.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            // Removes the element from the beginning, the rest of the array "moves forward" thanks to the removeAt method
            T frontElement = elements.get(0);
            elements.removeAt(0);
            return frontElement;
        }

        T& front() {
            if (elements.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            return elements.get(0);
        }

        const T& front() const {
            if (elements.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            return elements.get(0);
        }

        T& back() {
            if (elements.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            // Checks who the last element that entered the queue is (for control purposes)
            return elements.get(elements.getCount() - 1);
        }

        const T& back() const {
            if (elements.isEmpty()) {
                throw std::underflow_error("Queue is empty");
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
        // Iterates from front to back
        typename Container<T>::Iterator begin() const {
            return elements.begin();
        }

        typename Container<T>::Iterator end() const {
            return elements.end();
        }
    };

} // namespace containers

#endif // QUEUE_HPP