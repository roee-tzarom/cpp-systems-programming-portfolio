/**
 * @file test.cpp
 * @brief Unit tests for Physics & Math Computation Engine using doctest
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
#include <fstream>

using namespace metaengine;

// ==================== TYPEINFO TESTS ====================

TEST_CASE("TypeInfo<int> - Full Specialization") {
    CHECK(std::string(TypeInfo<int>::name) == "int");
    CHECK(TypeInfo<int>::is_numeric == true);
    CHECK(TypeInfo<int>::is_pointer == false);
    CHECK(TypeInfo<int>::size == sizeof(int));
    CHECK(TypeInfo<int>::min_value == -2147483648);
    CHECK(TypeInfo<int>::max_value == 2147483647);
}

TEST_CASE("TypeInfo<int> - describe") {
    std::string desc = TypeInfo<int>::describe();
    CHECK(desc.find("int") != std::string::npos);
    CHECK(desc.find("numeric") != std::string::npos);
    CHECK(desc.find("4 bytes") != std::string::npos);
}

TEST_CASE("TypeInfo<double> - Full Specialization") {
    CHECK(std::string(TypeInfo<double>::name) == "double");
    CHECK(TypeInfo<double>::is_numeric == true);
    CHECK(TypeInfo<double>::is_pointer == false);
    CHECK(TypeInfo<double>::size == sizeof(double));
}

TEST_CASE("TypeInfo<double> - describe") {
    std::string desc = TypeInfo<double>::describe();
    CHECK(desc.find("double") != std::string::npos);
    CHECK(desc.find("floating-point") != std::string::npos);
}

TEST_CASE("TypeInfo<bool> - Full Specialization") {
    CHECK(std::string(TypeInfo<bool>::name) == "bool");
    CHECK(TypeInfo<bool>::is_numeric == false);
    CHECK(TypeInfo<bool>::is_pointer == false);
}

TEST_CASE("TypeInfo<std::string> - Full Specialization") {
    CHECK(std::string(TypeInfo<std::string>::name) == "string");
    CHECK(TypeInfo<std::string>::is_numeric == false);
    CHECK(TypeInfo<std::string>::is_pointer == false);
}

TEST_CASE("TypeInfo<int*> - Partial Specialization (Pointer)") {
    CHECK(std::string(TypeInfo<int*>::name) == "pointer");
    CHECK(TypeInfo<int*>::is_numeric == false);
    CHECK(TypeInfo<int*>::is_pointer == true);
    CHECK(TypeInfo<int*>::size == sizeof(int*));
}

TEST_CASE("TypeInfo<int*> - describe contains pointed type") {
    std::string desc = TypeInfo<int*>::describe();
    CHECK(desc.find("pointer to int") != std::string::npos);
}

TEST_CASE("TypeInfo<double*> - Partial Specialization") {
    CHECK(TypeInfo<double*>::is_pointer == true);
    std::string desc = TypeInfo<double*>::describe();
    CHECK(desc.find("pointer to double") != std::string::npos);
}

TEST_CASE("TypeInfo - Unknown Type (Primary Template)") {
    struct Foo {};
    CHECK(std::string(TypeInfo<Foo>::name) == "Unknown");
    CHECK(TypeInfo<Foo>::is_numeric == false);
    CHECK(TypeInfo<Foo>::is_pointer == false);
}

// ==================== MYSWAP TESTS ====================

TEST_CASE("mySwap<int> - XOR swap") {
    int a = 10, b = 20;
    mySwap(a, b);
    CHECK(a == 20);
    CHECK(b == 10);
}

TEST_CASE("mySwap<int> - Same values") {
    int a = 5, b = 5;
    mySwap(a, b);
    CHECK(a == 5);
    CHECK(b == 5);
}

TEST_CASE("mySwap<string> - Optimized swap") {
    std::string a = "hello", b = "world";
    mySwap(a, b);
    CHECK(a == "world");
    CHECK(b == "hello");
}

TEST_CASE("mySwap<bool> - Logical swap") {
    bool a = true, b = false;
    mySwap(a, b);
    CHECK(a == false);
    CHECK(b == true);
}

TEST_CASE("mySwap<bool> - Same values") {
    bool a = true, b = true;
    mySwap(a, b);
    CHECK(a == true);
    CHECK(b == true);
}

TEST_CASE("mySwap<int> - Negative values") {
    int a = -10, b = 20;
    mySwap(a, b);
    CHECK(a == 20);
    CHECK(b == -10);
}

TEST_CASE("mySwap<double> - Generic swap") {
    double a = 3.14, b = 2.71;
    mySwap(a, b);
    CHECK(a == doctest::Approx(2.71));
    CHECK(b == doctest::Approx(3.14));
}

TEST_CASE("mySwap<int> - XOR swap with zero") {
    int a = 0, b = 42;
    mySwap(a, b);
    CHECK(a == 42);
    CHECK(b == 0);
}

TEST_CASE("mySwap<string> - Empty strings") {
    std::string a = "", b = "test";
    mySwap(a, b);
    CHECK(a == "test");
    CHECK(b == "");
}

// ==================== FORMATTER TESTS ====================

TEST_CASE("Formatter<int> - format") {
    CHECK(Formatter<int>::format(42) == "42");
    CHECK(Formatter<int>::format(-5) == "-5");
    CHECK(Formatter<int>::format(0) == "0");
}

TEST_CASE("Formatter<int> - formatHex") {
    CHECK(Formatter<int>::formatHex(255) == "0xFF");
    CHECK(Formatter<int>::formatHex(0) == "0x0");
    CHECK(Formatter<int>::formatHex(16) == "0x10");
}

TEST_CASE("Formatter<double> - format") {
    CHECK(Formatter<double>::format(3.14159, 2) == "3.14");
    CHECK(Formatter<double>::format(3.14159, 4) == "3.1416");
    CHECK(Formatter<double>::format(0.0, 1) == "0.0");
}

TEST_CASE("Formatter<double> - formatScientific") {
    std::string result = Formatter<double>::formatScientific(123.0, 3);
    CHECK(result.find("1.230") != std::string::npos);
    CHECK(result.find("e") != std::string::npos);
}

TEST_CASE("Formatter<double> - formatWithLabel") {
    std::string result = Formatter<double>::formatWithLabel("pi", 3.14);
    CHECK(result.find("pi") != std::string::npos);
    CHECK(result.find("3.14") != std::string::npos);
}

TEST_CASE("Formatter<bool> - format") {
    CHECK(Formatter<bool>::format(true) == "true");
    CHECK(Formatter<bool>::format(false) == "false");
}

TEST_CASE("Formatter<bool> - formatYesNo") {
    CHECK(Formatter<bool>::formatYesNo(true) == "Yes");
    CHECK(Formatter<bool>::formatYesNo(false) == "No");
}

TEST_CASE("Formatter<bool> - formatOnOff") {
    CHECK(Formatter<bool>::formatOnOff(true) == "ON");
    CHECK(Formatter<bool>::formatOnOff(false) == "OFF");
}

TEST_CASE("Formatter<string> - format") {
    CHECK(Formatter<std::string>::format("Hello") == "\"Hello\"");
    CHECK(Formatter<std::string>::format("") == "\"\"");
}

TEST_CASE("Formatter<string> - formatUpper") {
    CHECK(Formatter<std::string>::formatUpper("Hello World") == "HELLO WORLD");
}

TEST_CASE("Formatter<string> - formatLower") {
    CHECK(Formatter<std::string>::formatLower("Hello World") == "hello world");
}

TEST_CASE("Formatter<string> - formatWithLabel") {
    std::string result = Formatter<std::string>::formatWithLabel("name", "Alice");
    CHECK(result.find("name") != std::string::npos);
    CHECK(result.find("Alice") != std::string::npos);
    CHECK(result.find("length: 5") != std::string::npos);
}

// ==================== DERIVATIVE TESTS ====================

TEST_CASE("Const - eval and toString") {
    CHECK(Const<5>::eval(0) == 5);
    CHECK(Const<5>::eval(100) == 5);
    CHECK(Const<0>::eval(42) == 0);
    CHECK(Const<5>::toString() == "5");
}

TEST_CASE("Var - eval and toString") {
    CHECK(Var::eval(0) == 0);
    CHECK(Var::eval(7) == 7);
    CHECK(Var::eval(-3) == -3);
    CHECK(Var::toString() == "x");
}

TEST_CASE("Add - eval and toString") {
    using E = Add<Var, Const<3>>;
    CHECK(E::eval(5) == 8);
    CHECK(E::eval(0) == 3);
    CHECK(E::toString() == "(x + 3)");
}

TEST_CASE("Mul - eval and toString") {
    using E = Mul<Var, Const<4>>;
    CHECK(E::eval(3) == 12);
    CHECK(E::eval(0) == 0);
    CHECK(E::toString() == "(x * 4)");
}

TEST_CASE("Power - eval and toString") {
    using E = Power<Var, 3>;
    CHECK(E::eval(2) == 8);
    CHECK(E::eval(3) == 27);
    CHECK(E::eval(0) == 0);
    CHECK(E::toString() == "(x^3)");
}

TEST_CASE("Power<Var, 1> - eval returns x") {
    using E = Power<Var, 1>;
    CHECK(E::eval(5) == 5);
    CHECK(E::eval(0) == 0);
    CHECK(E::eval(-3) == -3);
}

TEST_CASE("Power<E, 0> - eval returns 1") {
    using E = Power<Var, 0>;
    CHECK(E::eval(5) == 1);
    CHECK(E::eval(0) == 1);
}

// ==================== PHYSICS TESTS ====================

TEST_CASE("celsiusToFahrenheit") {
    constexpr double f = celsiusToFahrenheit(100.0);
    CHECK(f == doctest::Approx(212.0));

    constexpr double f2 = celsiusToFahrenheit(0.0);
    CHECK(f2 == doctest::Approx(32.0));

    constexpr double f3 = celsiusToFahrenheit(-40.0);
    CHECK(f3 == doctest::Approx(-40.0));
}

TEST_CASE("fahrenheitToCelsius") {
    constexpr double c = fahrenheitToCelsius(212.0);
    CHECK(c == doctest::Approx(100.0));

    constexpr double c2 = fahrenheitToCelsius(32.0);
    CHECK(c2 == doctest::Approx(0.0));
}

TEST_CASE("kmToMiles") {
    constexpr double m = kmToMiles(1.0);
    CHECK(m == doctest::Approx(0.621371));

    constexpr double marathon = kmToMiles(42.195);
    CHECK(marathon == doctest::Approx(26.2188).epsilon(0.01));
}

TEST_CASE("milesToKm") {
    constexpr double k = milesToKm(1.0);
    CHECK(k == doctest::Approx(1.60934));
}

TEST_CASE("degreesToRadians") {
    constexpr double r = degreesToRadians(180.0);
    CHECK(r == doctest::Approx(PI));

    constexpr double r2 = degreesToRadians(90.0);
    CHECK(r2 == doctest::Approx(PI / 2.0));

    constexpr double r3 = degreesToRadians(0.0);
    CHECK(r3 == doctest::Approx(0.0));
}

TEST_CASE("radiansToDegrees") {
    constexpr double d = radiansToDegrees(PI);
    CHECK(d == doctest::Approx(180.0));
}

TEST_CASE("kineticEnergy") {
    constexpr double ke = kineticEnergy(10.0, 5.0);
    CHECK(ke == doctest::Approx(125.0));

    constexpr double ke2 = kineticEnergy(0.0, 100.0);
    CHECK(ke2 == doctest::Approx(0.0));
}

TEST_CASE("potentialEnergy") {
    constexpr double pe = potentialEnergy(10.0, 20.0);
    CHECK(pe == doctest::Approx(10.0 * 9.80665 * 20.0));
}

TEST_CASE("massEnergy") {
    constexpr double e = massEnergy(1.0);
    CHECK(e == doctest::Approx(SPEED_OF_LIGHT * SPEED_OF_LIGHT));
}

TEST_CASE("freeFallDistance") {
    constexpr double d = freeFallDistance(0.0);
    CHECK(d == doctest::Approx(0.0));

    constexpr double d2 = freeFallDistance(1.0);
    CHECK(d2 == doctest::Approx(0.5 * GRAVITY));
}

TEST_CASE("power - constexpr") {
    constexpr double p1 = power(2.0, 3);
    CHECK(p1 == doctest::Approx(8.0));

    constexpr double p2 = power(5.0, 0);
    CHECK(p2 == doctest::Approx(1.0));

    constexpr double p3 = power(3.0, 2);
    CHECK(p3 == doctest::Approx(9.0));
}

TEST_CASE("absVal - constexpr") {
    constexpr double a1 = absVal(-5.0);
    CHECK(a1 == doctest::Approx(5.0));

    constexpr double a2 = absVal(3.0);
    CHECK(a2 == doctest::Approx(3.0));

    constexpr double a3 = absVal(0.0);
    CHECK(a3 == doctest::Approx(0.0));
}

// ==================== DECLTYPE TESTS ====================

TEST_CASE("add - mixed types") {
    auto r1 = add(3, 4.5);
    CHECK(r1 == doctest::Approx(7.5));

    auto r2 = add(3, 4);
    CHECK(r2 == 7);

    auto r3 = add(1.5, 2.5);
    CHECK(r3 == doctest::Approx(4.0));
}

TEST_CASE("multiply - mixed types") {
    auto r1 = multiply(3, 4);
    CHECK(r1 == 12);

    auto r2 = multiply(3, 4.0);
    CHECK(r2 == doctest::Approx(12.0));
}

TEST_CASE("maxOf - mixed types") {
    auto r1 = maxOf(3, 4.5);
    CHECK(r1 == doctest::Approx(4.5));

    auto r2 = maxOf(5, 3.2);
    CHECK(r2 == doctest::Approx(5.0));

    auto r3 = maxOf(3, 3);
    CHECK(r3 == 3);
}

TEST_CASE("minOf - mixed types") {
    auto r1 = minOf(3, 4.5);
    CHECK(r1 == doctest::Approx(3.0));

    auto r2 = minOf(5.5, 3);
    CHECK(r2 == doctest::Approx(3.0));
}

TEST_CASE("isAddResultFloating") {
    CHECK(isAddResultFloating<int, double>() == true);
    CHECK(isAddResultFloating<float, int>() == true);
    CHECK(isAddResultFloating<int, int>() == false);
    CHECK(isAddResultFloating<double, double>() == true);
}

TEST_CASE("isMulResultIntegral") {
    CHECK(isMulResultIntegral<int, int>() == true);
    CHECK(isMulResultIntegral<int, double>() == false);
    CHECK(isMulResultIntegral<short, int>() == true);
}

// ==================== STUDENT TEST FILE CHECK ====================

TEST_CASE("StudentTest - File exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases.");
}