#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Point.hpp"
#include "Circle.hpp"
#include "Utilities.hpp"
#include <sstream>
#include <iostream>
#include <cmath>

using namespace Geometry;
using namespace Utils;

const double PI_TEST = 3.141592653589793;

// --- Tests for distance ---
TEST_CASE("1. distance between two positive points") {
    Point p1 = {0.0, 0.0};
    Point p2 = {3.0, 4.0};
    CHECK(distance(p1, p2) == doctest::Approx(5.0));
}

TEST_CASE("2. distance between the same point is zero") {
    Point p1 = {5.5, 5.5};
    CHECK(distance(p1, p1) == doctest::Approx(0.0));
}

TEST_CASE("3. distance with negative coordinates") {
    Point p1 = {-1.0, -1.0};
    Point p2 = {2.0, 3.0};
    CHECK(distance(p1, p2) == doctest::Approx(5.0));
}

// --- Tests for calculateArea ---
TEST_CASE("4. calculateArea with radius 1") {
    Circle c = {{0.0, 0.0}, 1.0};
    CHECK(calculateArea(c) == doctest::Approx(PI_TEST));
}

TEST_CASE("5. calculateArea with radius 0") {
    Circle c = {{2.0, 3.0}, 0.0};
    CHECK(calculateArea(c) == doctest::Approx(0.0));
}

TEST_CASE("6. calculateArea with larger radius") {
    Circle c = {{0.0, 0.0}, 2.0};
    CHECK(calculateArea(c) == doctest::Approx(4.0 * PI_TEST));
}

// --- Tests for calculateCircumference ---
TEST_CASE("7. calculateCircumference with radius 1") {
    Circle c = {{0.0, 0.0}, 1.0};
    CHECK(calculateCircumference(c) == doctest::Approx(2.0 * PI_TEST));
}

TEST_CASE("8. calculateCircumference with radius 0") {
    Circle c = {{5.0, 5.0}, 0.0};
    CHECK(calculateCircumference(c) == doctest::Approx(0.0));
}

TEST_CASE("9. calculateCircumference with radius 10") {
    Circle c = {{0.0, 0.0}, 10.0};
    CHECK(calculateCircumference(c) == doctest::Approx(20.0 * PI_TEST));
}

// --- Tests for isPointInside ---
TEST_CASE("10. isPointInside when point is exactly at center") {
    Circle c = {{1.0, 1.0}, 5.0};
    Point p = {1.0, 1.0};
    CHECK(isPointInside(c, p) == true);
}

TEST_CASE("11. isPointInside when point is strictly inside") {
    Circle c = {{0.0, 0.0}, 10.0};
    Point p = {3.0, 4.0};
    CHECK(isPointInside(c, p) == true);
}

TEST_CASE("12. isPointInside when point is exactly on the edge") {
    Circle c = {{0.0, 0.0}, 5.0};
    Point p = {3.0, 4.0};
    CHECK(isPointInside(c, p) == true);
}

TEST_CASE("13. isPointInside when point is outside") {
    Circle c = {{0.0, 0.0}, 2.0};
    Point p = {3.0, 3.0};
    CHECK(isPointInside(c, p) == false);
}

// --- Tests for createCircle ---
TEST_CASE("14. createCircle checks center coordinates") {
    Circle c = createCircle(2.5, 3.5, 10.0);
    CHECK(c.center.x == doctest::Approx(2.5));
    CHECK(c.center.y == doctest::Approx(3.5));
}

TEST_CASE("15. createCircle checks radius") {
    Circle c = createCircle(0.0, 0.0, 7.5);
    CHECK(c.radius == doctest::Approx(7.5));
}

TEST_CASE("16. createCircle with negative center coordinates") {
    Circle c = createCircle(-5.0, -10.0, 3.0);
    CHECK(c.center.x == doctest::Approx(-5.0));
}

// --- Tests for calculateAverage ---
TEST_CASE("17. calculateAverage with positive numbers") {
    double arr[] = {2.0, 4.0, 6.0}; // NOLINT
    CHECK(calculateAverage(arr, 3) == doctest::Approx(4.0));
}

TEST_CASE("18. calculateAverage with mixed numbers") {
    double arr[] = {-5.0, 0.0, 5.0}; // NOLINT
    CHECK(calculateAverage(arr, 3) == doctest::Approx(0.0));
}

TEST_CASE("19. calculateAverage with size 0 returns 0") {
    double arr[] = {1.0}; // NOLINT
    CHECK(calculateAverage(arr, 0) == doctest::Approx(0.0));
}

// --- Tests for findClosestToOrigin ---
TEST_CASE("20. findClosestToOrigin simple array") {
    Point arr[] = {{10.0, 10.0}, {1.0, 1.0}, {5.0, 5.0}}; // NOLINT
    Point closest = findClosestToOrigin(arr, 3);
    CHECK(closest.x == doctest::Approx(1.0));
}

// --- Tests for printing functions (Output Redirection) ---
TEST_CASE("21. printPoint output format") {
    Point p = {1.5, 2.5};
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    printPoint(p);

    std::cout.rdbuf(p_cout_streambuf); // Restore normal printing
    CHECK(oss.str() == "(1.5,2.5)\n");
}

TEST_CASE("22. printCircle output format") {
    Circle c = {{1.0, 2.0}, 3.0};
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    printCircle(c);

    std::cout.rdbuf(p_cout_streambuf); // Restore normal printing
    CHECK(oss.str() == "Circle: center=(1,2), radius=3\n");
}