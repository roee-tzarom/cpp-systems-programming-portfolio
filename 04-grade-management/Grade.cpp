#include "Grade.hpp"
#include <iomanip>

namespace grading {

    int Grade::totalGradesCreated = 0;

    void Grade::bound() {
        const double maxGrade = 100.0;
        const double minGrade = 0.0;
        if (value > maxGrade) {
            value = maxGrade;
        }
        if (value < minGrade) {
            value = minGrade;
        }
    }

    Grade::Grade(double val) : value(val) {
        bound();
        totalGradesCreated++;
    }

    Grade Grade::operator+(const Grade& other) const {
        return Grade(this->value + other.value);
    }

    Grade Grade::operator-(const Grade& other) const {
        return Grade(this->value - other.value);
    }

    Grade Grade::operator*(const Grade& other) const {
        return Grade(this->value * other.value);
    }

    Grade Grade::operator/(const Grade& other) const {
        const double zeroVal = 0.0;
        if (other.value == zeroVal) {
            return Grade(zeroVal);
        }
        return Grade(this->value / other.value);
    }

    Grade Grade::operator+(double num) const {
        return Grade(this->value + num);
    }

    Grade operator+(double num, const Grade& grade) {
        return Grade(num + grade.value);
    }

    Grade Grade::operator-(double num) const {
        return Grade(this->value - num);
    }

    Grade Grade::operator*(double num) const {
        return Grade(this->value * num);
    }

    Grade operator*(double num, const Grade& grade) {
        return Grade(num * grade.value);
    }

    Grade Grade::operator/(double num) const {
        const double zeroVal = 0.0;
        if (num == zeroVal) {
            return Grade(zeroVal);
        }
        return Grade(this->value / num);
    }

    Grade& Grade::operator+=(const Grade& other) {
        this->value += other.value;
        bound();
        return *this;
    }

    Grade& Grade::operator-=(const Grade& other) {
        this->value -= other.value;
        bound();
        return *this;
    }

    Grade& Grade::operator*=(const Grade& other) {
        this->value *= other.value;
        bound();
        return *this;
    }

    Grade& Grade::operator/=(const Grade& other) {
        const double zeroVal = 0.0;
        if (other.value != zeroVal) {
            this->value /= other.value;
            bound();
        }
        return *this;
    }

    Grade& Grade::operator+=(double num) {
        this->value += num;
        bound();
        return *this;
    }

    Grade& Grade::operator-=(double num) {
        this->value -= num;
        bound();
        return *this;
    }

    Grade& Grade::operator*=(double num) {
        this->value *= num;
        bound();
        return *this;
    }

    Grade& Grade::operator/=(double num) {
        const double zeroVal = 0.0;
        if (num != zeroVal) {
            this->value /= num;
            bound();
        }
        return *this;
    }

    bool Grade::operator==(const Grade& other) const {
        return this->value == other.value;
    }

    bool Grade::operator!=(const Grade& other) const {
        return !(*this == other);
    }

    bool Grade::operator<(const Grade& other) const {
        return this->value < other.value;
    }

    bool Grade::operator>(const Grade& other) const {
        return this->value > other.value;
    }

    bool Grade::operator<=(const Grade& other) const {
        return this->value <= other.value;
    }

    bool Grade::operator>=(const Grade& other) const {
        return this->value >= other.value;
    }

    Grade& Grade::operator++() {
        const double inc = 1.0;
        this->value += inc;
        bound();
        return *this;
    }

    Grade Grade::operator++(int) {
        Grade temp = *this;
        ++(*this);
        return temp;
    }

    Grade& Grade::operator--() {
        const double dec = 1.0;
        this->value -= dec;
        bound();
        return *this;
    }

    Grade Grade::operator--(int) {
        Grade temp = *this;
        --(*this);
        return temp;
    }

    Grade::operator int() const {
        return static_cast<int>(value);
    }

    Grade::operator double() const {
        return value;
    }

    Grade::operator std::string() const {
        const double gradeA = 90.0;
        const double gradeB = 80.0;
        const double gradeC = 70.0;
        const double gradeD = 60.0;
        if (value >= gradeA) {
            return "A";
        }
        if (value >= gradeB) {
            return "B";
        }
        if (value >= gradeC) {
            return "C";
        }
        if (value >= gradeD) {
            return "D";
        }
        return "F";
    }

    double Grade::getScore() const {
        return value;
    }

    void Grade::setScore(double newScore) {
        value = newScore;
        bound();
    }

    std::string Grade::getLetterGrade() const {
        return static_cast<std::string>(*this);
    }

    bool Grade::isPassing() const {
        return value >= PASSING_GRADE;
    }

    double Grade::getGPAPoints() const {
        const double gpaA = 4.0;
        const double gpaB = 3.0;
        const double gpaC = 2.0;
        const double gpaD = 1.0;
        const double gpaF = 0.0;
        std::string letter = getLetterGrade();
        if (letter == "A") {
            return gpaA;
        }
        if (letter == "B") {
            return gpaB;
        }
        if (letter == "C") {
            return gpaC;
        }
        if (letter == "D") {
            return gpaD;
        }
        return gpaF;
    }

    std::ostream& operator<<(std::ostream& outStream, const Grade& grade) {
        std::ios_base::fmtflags oldFlags = outStream.flags();
        outStream << std::fixed << std::setprecision(2) << grade.value 
           << " (" << grade.getLetterGrade() << ")";
        outStream.flags(oldFlags);
        return outStream;
    }

    int Grade::getTotalGradesCreated() {
        return totalGradesCreated;
    }

    double Grade::getPassingGrade() {
        return PASSING_GRADE;
    }

}