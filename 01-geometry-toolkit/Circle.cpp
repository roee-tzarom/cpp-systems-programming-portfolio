#include "Circle.hpp"
#include <cmath>
#include <iostream>

namespace Geometry {

const double PI_CONST = 3.141592653589793;
const double TWO = 2.0;

double calculateArea(Circle circle) {
    double currentRadius = circle.radius;
    return PI_CONST * std::pow(currentRadius, TWO);
}

double calculateCircumference(Circle circle) {
    double currentRadius = circle.radius;
    return TWO * PI_CONST * currentRadius;
}

bool isPointInside(Circle circle, Point point) {
    double dist = distance(circle.center, point);
    return dist <= circle.radius;
}

void printCircle(Circle circle) {
    std::cout << "Circle: center=(" << circle.center.x << "," << circle.center.y << "), radius=" << circle.radius << "\n";
}

}