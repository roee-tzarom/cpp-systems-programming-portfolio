/**
 * @file StudentTest.cpp
 * @brief Exactly 20 original test cases using the generated AI data.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TypeInfo.hpp"
#include "MySwap.hpp"
#include "Formatter.hpp"
#include "Derivative.hpp"
#include "PhysicsUnits.hpp"
#include "DecltypeUtils.hpp"
#include <string>

using namespace metaengine;

// ==================== 1. Temperature Conversions ====================

TEST_CASE("Student 1: Celsius to Fahrenheit (0 -> 32)") {
    CHECK(celsiusToFahrenheit(0.0) == doctest::Approx(32.0));
}

TEST_CASE("Student 2: Celsius to Fahrenheit (100 -> 212)") {
    CHECK(celsiusToFahrenheit(100.0) == doctest::Approx(212.0));
}

TEST_CASE("Student 3: Fahrenheit to Celsius (32 -> 0)") {
    CHECK(fahrenheitToCelsius(32.0) == doctest::Approx(0.0));
}

TEST_CASE("Student 4: Fahrenheit to Celsius (-40 -> -40)") {
    CHECK(fahrenheitToCelsius(-40.0) == doctest::Approx(-40.0));
}

// ==================== 2. Distance Conversions & Scaling ====================

TEST_CASE("Student 5: Miles to Kilometers (1 -> 1.60934)") {
    CHECK(milesToKm(1.0) == doctest::Approx(1.60934).epsilon(0.0001));
}

TEST_CASE("Student 6: Kilometers to Miles (5 -> 3.10686)") {
    CHECK(kmToMiles(5.0) == doctest::Approx(3.10686).epsilon(0.0001));
}

TEST_CASE("Student 7: Meters to Kilometers using decltype multiply (1500 * 0.001 -> 1.5)") {
    CHECK(multiply(1500, 0.001) == doctest::Approx(1.5));
}

TEST_CASE("Student 8: Inches to Feet using decltype multiply (12 * 1/12 -> 1.0)") {
    CHECK(multiply(12, 1.0 / 12.0) == doctest::Approx(1.0));
}

// ==================== 3. String Formatting ====================

TEST_CASE("Student 9: Convert to Uppercase (hello world -> HELLO WORLD)") {
    CHECK(Formatter<std::string>::formatUpper("hello world") == "HELLO WORLD");
}

TEST_CASE("Student 10: Convert to Lowercase (AUTOMATION -> automation)") {
    CHECK(Formatter<std::string>::formatLower("AUTOMATION") == "automation");
}

TEST_CASE("Student 11: Convert to Lowercase (MiXeD CaSe -> mixed case)") {
    CHECK(Formatter<std::string>::formatLower("MiXeD CaSe") == "mixed case");
}

TEST_CASE("Student 12: Convert to Uppercase (edgeCASE123 -> EDGECASE123)") {
    CHECK(Formatter<std::string>::formatUpper("edgeCASE123") == "EDGECASE123");
}

// ==================== 4. Mathematical Operations (Powers & Abs) ====================

TEST_CASE("Student 13: Power (Base 2, Exponent 3 -> 8)") {
    CHECK(power(2.0, 3) == doctest::Approx(8.0));
}

TEST_CASE("Student 14: Power (Base 5, Exponent 0 -> 1)") {
    CHECK(power(5.0, 0) == doctest::Approx(1.0));
}

TEST_CASE("Student 15: DecltypeUtils add with 10 and -2 (10 + -2 = 8)") {
    CHECK(add(10, -2.0) == doctest::Approx(8.0));
}

TEST_CASE("Student 16: Absolute Value (-42 -> 42)") {
    CHECK(absVal(-42.0) == doctest::Approx(42.0));
}

TEST_CASE("Student 17: Absolute Value (3.14 -> 3.14)") {
    CHECK(absVal(3.14) == doctest::Approx(3.14));
}

// ==================== 5. Mathematical Operations (Maximum) ====================

TEST_CASE("Student 18: Find Maximum (-5.5, -2.2 -> -2.2)") {
    CHECK(maxOf(-5.5, -2.2) == doctest::Approx(-2.2));
}

TEST_CASE("Student 19: Find Maximum (-0.01, -0.10 -> -0.01)") {
    CHECK(maxOf(-0.01, -0.10) == doctest::Approx(-0.01));
}

TEST_CASE("Student 20: Find Maximum (-99.99, -99.98 -> -99.98)") {
    CHECK(maxOf(-99.99, -99.98) == doctest::Approx(-99.98));
}