/**
 * @file Container.hpp
 * @brief Header file for the generic Container class
 *
 * This file contains the template class Container, a dynamic array
 * implementation that supports dynamic resizing, basic operations,
 * and an internal Iterator for range-based for loops.
 */

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>

namespace containers {

    template <typename T>
    class Container {
    private:
        T* data;
        int capacity;
        int count;

        void resize() {
            // Doubling the capacity by 2 ensures that the add operation remains O(1) on average (Amortized time)
            int newCapacity = capacity * 2;
            T* newData = new T[static_cast<size_t>(newCapacity)];
            for (int i = 0; i < count; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    public:
        // ============ Iterator Class ============
        // An internal class that allows us to use modern loops (for auto x : container)
        class Iterator {
        private:
            T* ptr;
        public:
            explicit Iterator(T* p) : ptr(p) {}

            // Returns a reference so we can not only read but also modify the value through the iterator
            T& operator*() {
                return *ptr;
            }

            Iterator& operator++() {
                ptr++;
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return ptr != other.ptr;
            }

            bool operator==(const Iterator& other) const {
                return ptr == other.ptr;
            }
        };

        // ============ Constructors & Destructor ============
        // explicit prevents the compiler from accidentally making strange conversions (like Container c = 4;)
        explicit Container(int initialCapacity = 4) : capacity(initialCapacity), count(0) {
            if (initialCapacity <= 0) {
                throw std::invalid_argument("Capacity must be positive");
            }
            data = new T[static_cast<size_t>(capacity)];
        }

        // Copy Constructor: A Deep Copy is mandatory because we are managing dynamic memory (a pointer)
        Container(const Container& other) : capacity(other.capacity), count(other.count) {
            data = new T[static_cast<size_t>(capacity)];
            for (int i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }

        ~Container() {
            delete[] data; // Frees the memory we allocated to prevent Memory Leaks
        }

        Container& operator=(const Container& other) {
            // Self-assignment check: critical to prevent a situation where we accidentally delete ourselves (e.g. c = c)
            if (this != &other) {
                delete[] data;
                capacity = other.capacity;
                count = other.count;
                data = new T[static_cast<size_t>(capacity)];
                for (int i = 0; i < count; ++i) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        // ============ Core Operations ============
        void add(const T& item) {
            if (count == capacity) {
                resize();
            }
            data[count++] = item;
        }

        // Returns a reference to allow modification (e.g.: c.get(0) = 5)
        T& get(int index) {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        // Const overload: automatically called when our object is defined as const
        const T& get(int index) const {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        void removeAt(int index) {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            // Shifts all elements after the index one step back to overwrite the deleted element
            for (int i = index; i < count - 1; ++i) {
                data[i] = data[i + 1];
            }
            count--;
        }

        // ============ Getters & Utility ============
        int getCount() const { return count; }
        int getCapacity() const { return capacity; }
        bool isEmpty() const { return count == 0; }
        void clear() { count = 0; } // Clears count but retains capacity

        // ============ Iterator Methods ============
        Iterator begin() const {
            return Iterator(data);
        }

        Iterator end() const {
            return Iterator(data + count); // Points to one place after the last element (as is customary in C++)
        }
    };

} // namespace containers

#endif // CONTAINER_HPP