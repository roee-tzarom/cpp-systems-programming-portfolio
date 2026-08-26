#pragma once
#include "Point.hpp"

namespace Geometry {

struct Circle {
    Point center;
    double radius;
};

// Calculate area of the circle
// TODO: Complete the code
double calculateArea(Circle circle);

// Calculate circumference of the circle
// TODO: Complete the code
double calculateCircumference(Circle circle);

// Check if a point is inside the circle
// TODO: Complete the code
bool isPointInside(Circle circle, Point point);

// Print circle - should output in format Circle: center=(x,y), radius=r
// TODO: Complete the code
void printCircle(Circle circle);

} // namespace Geometry