#include "Point.hpp"
#include <cmath>
#include <iostream>

namespace Geometry {

double distance(Point point1, Point point2) {
    double diffX = point2.x - point1.x;
    double diffY = point2.y - point1.y;
    
    double sum = (diffX * diffX) + (diffY * diffY);
    
    return std::sqrt(sum);
}

void printPoint(Point point) {
    std::cout << "(" << point.x << "," << point.y << ")\n";
}

}