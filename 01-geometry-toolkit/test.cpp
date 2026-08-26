#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define _USE_MATH_DEFINES
#include "doctest.h"
#include "Point.hpp"
#include "Circle.hpp"
#include "Utilities.hpp"
#include <cmath>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace Geometry;
using namespace Utils;

TEST_CASE("Point struct and functions") {
    SUBCASE("Point initialization") {
        Point p1 = {0, 0};
        CHECK(p1.x == 0);
        CHECK(p1.y == 0);
        
        Point p2 = {3.5, -2.5};
        CHECK(p2.x == 3.5);
        CHECK(p2.y == doctest::Approx(-2.5));
    }
    
    SUBCASE("Distance calculation") {
        Point origin = {0, 0};
        Point p3 = {3, 4};
        double dist = distance(origin, p3);
        CHECK(dist == doctest::Approx(5.0));
        
        // Test distance with negative coordinates
        Point p4 = {-3, -4};
        dist = distance(origin, p4);
        CHECK(dist == doctest::Approx(5.0));
        
        // Test self distance
        dist = distance(origin, origin);
        CHECK(dist == doctest::Approx(0.0));
    }
}

TEST_CASE("Circle struct and functions") {
    SUBCASE("Circle initialization") {
        Circle c1;
        c1.center = {0, 0};
        c1.radius = 5;
        CHECK(c1.center.x == 0);
        CHECK(c1.center.y == 0);
        CHECK(c1.radius == 5);
    }
    
    SUBCASE("Area calculation") {
        Circle c2;
        c2.center = {0, 0};
        c2.radius = 2;
        double area = calculateArea(c2);
        CHECK(area == doctest::Approx(M_PI * 4));
        
        // Edge case: zero radius
        Circle c3;
        c3.center = {0, 0};
        c3.radius = 0;
        area = calculateArea(c3);
        CHECK(area == doctest::Approx(0));
    }
    
    SUBCASE("Circumference calculation") {
        Circle c2;
        c2.center = {0, 0};
        c2.radius = 2;
        double circ = calculateCircumference(c2);
        CHECK(circ == doctest::Approx(2 * M_PI * 2));
        
        Circle c3;
        c3.center = {0, 0};
        c3.radius = 0;
        circ = calculateCircumference(c3);
        CHECK(circ == doctest::Approx(0));
    }
    
    SUBCASE("Point inside circle") {
        Circle c4;
        c4.center = {0, 0};
        c4.radius = 5;
        
        // Center point
        Point centerPoint = {0, 0};
        CHECK(isPointInside(c4, centerPoint));
        
        // Point on boundary (exactly radius distance away)
        Point boundaryPoint = {3, 4};
        CHECK(isPointInside(c4, boundaryPoint));
        
        // Point inside circle
        Point insidePoint = {2, 2};
        CHECK(isPointInside(c4, insidePoint));
        
        // Point outside circle
        Point outsidePoint = {4, 4};
        CHECK_FALSE(isPointInside(c4, outsidePoint));
    }
}

TEST_CASE("Utilities functions") {
    SUBCASE("findClosestToOrigin") {
        Point points[4] = {
            {3, 4},   // Distance = 5
            {1, 1},   // Distance = sqrt(2) ≈ 1.414
            {-2, 2},  // Distance = sqrt(8) ≈ 2.828
            {0, 5}    // Distance = 5
        };
        
        Point closest = findClosestToOrigin(points, 4);
        CHECK(closest.x == doctest::Approx(1));
        CHECK(closest.y == doctest::Approx(1));
        
        // Edge case: single point
        Point singlePoint[1] = {{7, 24}};
        closest = findClosestToOrigin(singlePoint, 1);
        CHECK(closest.x == doctest::Approx(7));
        CHECK(closest.y == doctest::Approx(24));
    }
    
    SUBCASE("createCircle") {
        Circle c1 = createCircle(0, 0, 1);
        CHECK(c1.center.x == 0);
        CHECK(c1.center.y == 0);
        CHECK(c1.radius == doctest::Approx(1.0));
        
        Circle c2 = createCircle(2, 3, 5);
        CHECK(c2.center.x == 2);
        CHECK(c2.center.y == 3);
        CHECK(c2.radius == 5);
    }
    
    SUBCASE("calculateAverage") {
        double arr1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
        double avg = calculateAverage(arr1, 5);
        CHECK(avg == doctest::Approx(3.0));
        
        // Edge cases
        double arr2[] = {7.5};
        avg = calculateAverage(arr2, 1);
        CHECK(avg == doctest::Approx(7.5));
        
        double arr3[] = {-1.0, -2.0, -3.0, -4.0, -5.0};
        avg = calculateAverage(arr3, 5);
        CHECK(avg == doctest::Approx(-3.0));
        
        double arr4[] = {-5.0, -2.5, 0.0, 2.5, 5.0};
        avg = calculateAverage(arr4, 5);
        CHECK(avg == doctest::Approx(0.0));
    }
}

TEST_CASE("Student custom tests file exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp file must be created by the student");
}