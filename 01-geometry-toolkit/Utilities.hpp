#pragma once
#include "Point.hpp"
#include "Circle.hpp"

namespace Utils {

// Function that takes an array of points and returns the point closest to the origin
// TODO: Complete the code
Geometry::Point findClosestToOrigin(Geometry::Point* points, int size);

// Function that creates a circle with given center and radius
// TODO: Complete the code
Geometry::Circle createCircle(double centerX, double centerY, double radius);

// Function that takes a double array and returns the average
// TODO: Complete the code
double calculateAverage(const double* arr, int size);

} // namespace Utils