#include "ComplexArray.hpp"
#include <stdexcept>

namespace complex_math {

    int ComplexArray::totalArraysCreated = 0;
    int ComplexArray::currentArrayCount = 0;

    void ComplexArray::resize() {
        int newCapacity = capacity * 2;
        if (newCapacity == 0) {
            newCapacity = 2;
        }

        Complex* newData = new Complex[static_cast<size_t>(newCapacity)];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    ComplexArray::ComplexArray() : data(nullptr), capacity(0), size(0) {
        totalArraysCreated++;
        currentArrayCount++;
    }

    ComplexArray::ComplexArray(int initialCapacity) 
        : capacity(initialCapacity > 0 ? initialCapacity : 2), size(0) {
        data = new Complex[static_cast<size_t>(capacity)];
        totalArraysCreated++;
        currentArrayCount++;
    }

    ComplexArray::ComplexArray(const ComplexArray& otherArray) 
        : capacity(otherArray.capacity), size(otherArray.size) {
        
        if (capacity > 0) {
            data = new Complex[static_cast<size_t>(capacity)];
            for (int i = 0; i < size; ++i) {
                data[i] = otherArray.data[i];
            }
        } else {
            data = nullptr;
        }

        totalArraysCreated++;
        currentArrayCount++;
    }

    ComplexArray& ComplexArray::operator=(const ComplexArray& otherArray) {
        if (this != &otherArray) {
            delete[] data;
            
            capacity = otherArray.capacity;
            size = otherArray.size;
            
            if (capacity > 0) {
                data = new Complex[static_cast<size_t>(capacity)];
                for (int i = 0; i < size; ++i) {
                    data[i] = otherArray.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    ComplexArray::~ComplexArray() {
        delete[] data;
        currentArrayCount--;
    }

    void ComplexArray::add(const Complex& complexElement) {
        if (size == capacity) {
            resize();
        }
        data[size] = complexElement;
        size++;
    }

    void ComplexArray::remove(int targetIndex) {
        if (targetIndex < 0 || targetIndex >= size) {
            return;
        }
        for (int i = targetIndex; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void ComplexArray::clear() {
        size = 0;
    }

    int ComplexArray::find(const Complex& complexElement) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == complexElement) {
                return i;
            }
        }
        const int notFoundIndex = -1;
        return notFoundIndex;
    }

    bool ComplexArray::contains(const Complex& complexElement) const {
        const int notFoundIndex = -1;
        return find(complexElement) != notFoundIndex;
    }

    Complex ComplexArray::sum() const {
        Complex totalValue(0.0, 0.0);
        for (int i = 0; i < size; ++i) {
            totalValue += data[i];
        }
        return totalValue;
    }

    Complex ComplexArray::average() const {
        if (size == 0) {
            return Complex(0.0, 0.0);
        }
        return sum() / static_cast<double>(size);
    }

    Complex ComplexArray::max() const {
        if (size == 0) {
            return Complex(0.0, 0.0);
        }
        int maxIndex = 0;
        for (int i = 1; i < size; ++i) {
            if (data[i] > data[maxIndex]) {
                maxIndex = i;
            }
        }
        return data[maxIndex];
    }

    Complex& ComplexArray::operator[](int targetIndex) {
        if (targetIndex < 0 || targetIndex >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[targetIndex];
    }

    const Complex& ComplexArray::operator[](int targetIndex) const {
        if (targetIndex < 0 || targetIndex >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[targetIndex];
    }

    ComplexArray ComplexArray::operator+(const ComplexArray& otherArray) const {
        int newCapacity = (size > otherArray.size) ? size : otherArray.size;
        ComplexArray resultArray(newCapacity);
        
        for (int i = 0; i < size && i < otherArray.size; ++i) {
            resultArray.add(data[i] + otherArray.data[i]);
        }
        return resultArray;
    }

    ComplexArray ComplexArray::operator+(const Complex& scalarComplex) const {
        ComplexArray resultArray(capacity);
        for (int i = 0; i < size; ++i) {
            resultArray.add(data[i] + scalarComplex);
        }
        return resultArray;
    }

    ComplexArray ComplexArray::operator*(double scalarValue) const {
        ComplexArray resultArray(capacity);
        for (int i = 0; i < size; ++i) {
            resultArray.add(data[i] * scalarValue);
        }
        return resultArray;
    }

    bool ComplexArray::operator==(const ComplexArray& otherArray) const {
        if (size != otherArray.size) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (data[i] != otherArray.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool ComplexArray::operator!=(const ComplexArray& otherArray) const {
        return !(*this == otherArray);
    }

    int ComplexArray::getTotalArraysCreated() { return totalArraysCreated; }
    int ComplexArray::getCurrentArrayCount() { return currentArrayCount; }

    std::ostream& operator<<(std::ostream& outStream, const ComplexArray& complexArray) {
        outStream << "[";
        for (int i = 0; i < complexArray.size; ++i) {
            outStream << complexArray.data[i];
            if (i < complexArray.size - 1) {
                outStream << ", ";
            }
        }
        outStream << "]";
        return outStream;
    }

}