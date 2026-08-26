#include "Utilities.hpp"
#include <span>
#include <cstddef>

namespace Utils {

Geometry::Point findClosestToOrigin(Geometry::Point* points, int size) {
    std::span<Geometry::Point> pointsSpan(points, static_cast<std::size_t>(size));
    Geometry::Point origin = {0.0, 0.0};
    
    Geometry::Point closest = pointsSpan[0];
    double minDist = Geometry::distance(origin, closest);

    for (std::size_t i = 1; i < pointsSpan.size(); i++) {
        double currentDist = Geometry::distance(origin, pointsSpan[i]);
        
        if (currentDist < minDist) {
            minDist = currentDist;
            closest = pointsSpan[i];
        }
    }

    return closest;
}

Geometry::Circle createCircle(double centerX, double centerY, double radius) { // NOLINT(bugprone-easily-swappable-parameters)
    Geometry::Point center_point = {centerX, centerY};
    Geometry::Circle new_circle = {center_point, radius};
    return new_circle;
}

double calculateAverage(const double* arr, int size) {
    if (size == 0) {
        return 0.0;
    }

    std::span<const double> arrSpan(arr, static_cast<std::size_t>(size));
    double sum = 0.0;
    
    for (std::size_t i = 0; i < arrSpan.size(); i++) {
        sum = sum + arrSpan[i];
    }

    return sum / size;
}

}