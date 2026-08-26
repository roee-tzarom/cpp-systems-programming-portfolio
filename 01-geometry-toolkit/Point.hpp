#pragma once
#include <iostream>

namespace Geometry {

struct Point {
    double x;
    double y;
};

// Calculate distance between two points
// TODO: Complete the code
double distance(Point point1, Point point2);

// Print point - should output in format (x,y)
// TODO: Complete the code
void printPoint(Point point);

} // namespace Geometry