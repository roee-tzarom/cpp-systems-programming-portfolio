#include "Complex.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace complex_math {

    int Complex::totalComplexCreated = 0;
    int Complex::currentComplexCount = 0;

    constexpr double ZERO_VALUE = 0.0;
    constexpr double ONE_VALUE = 1.0;

    Complex::Complex() : real(ZERO_VALUE), imag(ZERO_VALUE) {
        totalComplexCreated++;
        currentComplexCount++;
    }

    Complex::Complex(double realValue) : real(realValue), imag(ZERO_VALUE) {
        totalComplexCreated++;
        currentComplexCount++;
    }

    Complex::Complex(double realValue, double imaginaryValue) : real(realValue), imag(imaginaryValue) {
        totalComplexCreated++;
        currentComplexCount++;
    }

    Complex::Complex(const Complex& otherComplex) : real(otherComplex.real), imag(otherComplex.imag) {
        totalComplexCreated++;
        currentComplexCount++;
    }

    Complex::~Complex() {
        currentComplexCount--;
    }

    Complex& Complex::operator=(const Complex& otherComplex) {
        if (this != &otherComplex) {
            this->real = otherComplex.real;
            this->imag = otherComplex.imag;
        }
        return *this;
    }

    double Complex::getReal() const { return real; }
    
    double Complex::getImag() const { return imag; }
    
    void Complex::setReal(double realValue) { real = realValue; }
    
    void Complex::setImag(double imaginaryValue) { imag = imaginaryValue; }

    double Complex::magnitude() const {
        return std::hypot(real, imag);
    }

    Complex Complex::conjugate() const {
        return Complex(real, -imag);
    }

    bool Complex::isZero() const {
        return (real == ZERO_VALUE && imag == ZERO_VALUE);
    }

    bool Complex::isReal() const {
        return (imag == ZERO_VALUE);
    }

    Complex::operator double() const {
        return magnitude();
    }

    Complex::operator bool() const {
        return !isZero();
    }

    std::string Complex::toRectangularString() const {
        std::ostringstream outputStream;
        outputStream << real;
        if (imag >= ZERO_VALUE) {
            outputStream << "+";
        }
        outputStream << imag << "i";
        return outputStream.str();
    }

    Complex::operator std::string() const {
        return toRectangularString();
    }

    Complex Complex::operator+(const Complex& otherComplex) const {
        return Complex(real + otherComplex.real, imag + otherComplex.imag);
    }

    Complex Complex::operator-(const Complex& otherComplex) const {
        return Complex(real - otherComplex.real, imag - otherComplex.imag);
    }

    Complex Complex::operator*(const Complex& otherComplex) const {
        return Complex(real * otherComplex.real - imag * otherComplex.imag,
                       real * otherComplex.imag + imag * otherComplex.real);
    }

    Complex Complex::operator/(const Complex& otherComplex) const {
        double denominator = otherComplex.real * otherComplex.real + otherComplex.imag * otherComplex.imag;
        if (denominator == ZERO_VALUE) {
            throw std::invalid_argument("Division by zero");
        }
        return Complex((real * otherComplex.real + imag * otherComplex.imag) / denominator,
                       (imag * otherComplex.real - real * otherComplex.imag) / denominator);
    }

    Complex Complex::operator+(double scalarValue) const {
        return Complex(real + scalarValue, imag);
    }

    Complex Complex::operator-(double scalarValue) const {
        return Complex(real - scalarValue, imag);
    }

    Complex Complex::operator*(double scalarValue) const {
        return Complex(real * scalarValue, imag * scalarValue);
    }

    Complex Complex::operator/(double scalarValue) const {
        if (scalarValue == ZERO_VALUE) {
            throw std::invalid_argument("Division by zero");
        }
        return Complex(real / scalarValue, imag / scalarValue);
    }

    Complex Complex::operator-() const {
        return Complex(-real, -imag);
    }

    Complex& Complex::operator+=(const Complex& otherComplex) {
        real += otherComplex.real;
        imag += otherComplex.imag;
        return *this;
    }

    Complex& Complex::operator-=(const Complex& otherComplex) {
        real -= otherComplex.real;
        imag -= otherComplex.imag;
        return *this;
    }

    Complex& Complex::operator*=(const Complex& otherComplex) {
        double newReal = real * otherComplex.real - imag * otherComplex.imag;
        double newImag = real * otherComplex.imag + imag * otherComplex.real;
        real = newReal;
        imag = newImag;
        return *this;
    }

    Complex& Complex::operator/=(const Complex& otherComplex) {
        Complex result = *this / otherComplex;
        *this = result;
        return *this;
    }

    Complex& Complex::operator+=(double scalarValue) {
        real += scalarValue;
        return *this;
    }

    Complex& Complex::operator-=(double scalarValue) {
        real -= scalarValue;
        return *this;
    }

    Complex& Complex::operator*=(double scalarValue) {
        real *= scalarValue;
        imag *= scalarValue;
        return *this;
    }

    Complex& Complex::operator/=(double scalarValue) {
        if (scalarValue == ZERO_VALUE) {
            throw std::invalid_argument("Division by zero");
        }
        real /= scalarValue;
        imag /= scalarValue;
        return *this;
    }

    Complex& Complex::operator++() {
        real += ONE_VALUE;
        return *this;
    }

    Complex Complex::operator++(int) {
        Complex temp = *this;
        ++(*this);
        return temp;
    }

    Complex& Complex::operator--() {
        real -= ONE_VALUE;
        return *this;
    }

    Complex Complex::operator--(int) {
        Complex temp = *this;
        --(*this);
        return temp;
    }

    bool Complex::operator==(const Complex& otherComplex) const {
        return (real == otherComplex.real && imag == otherComplex.imag);
    }

    bool Complex::operator!=(const Complex& otherComplex) const {
        return !(*this == otherComplex);
    }

    bool Complex::operator<(const Complex& otherComplex) const {
        return this->magnitude() < otherComplex.magnitude();
    }

    bool Complex::operator>(const Complex& otherComplex) const {
        return this->magnitude() > otherComplex.magnitude();
    }

    int Complex::getTotalComplexCreated() {
        return totalComplexCreated;
    }

    int Complex::getCurrentComplexCount() {
        return currentComplexCount;
    }

    Complex Complex::fromPolar(double radius, double thetaAngle) {
        return Complex(radius * std::cos(thetaAngle), radius * std::sin(thetaAngle));
    }

    double distance(const Complex& firstComplex, const Complex& secondComplex) {
        return std::hypot(firstComplex.real - secondComplex.real, firstComplex.imag - secondComplex.imag);
    }

    std::ostream& operator<<(std::ostream& outStream, const Complex& complexNumber) {
        outStream << complexNumber.toRectangularString();
        return outStream;
    }

}