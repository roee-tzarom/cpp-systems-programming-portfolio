/**
 * @file PhysicsUnits.hpp
 * @brief Compile-time physics and math computations using constexpr.
 *
 * This file provides a set of mathematical and physical conversion functions
 * and formulas that are evaluated entirely at compile-time, ensuring zero
 * runtime overhead for constant expressions.
 */

#pragma once

namespace metaengine {

// ============================================================================
// Constants
// ============================================================================

/** @brief Mathematical constant Pi */
constexpr double PI = 3.14159265358979323846;

/** @brief Speed of light in a vacuum (meters per second) */
constexpr double SPEED_OF_LIGHT = 299792458.0;

/** @brief Standard acceleration due to gravity on Earth (meters per second squared) */
constexpr double GRAVITY = 9.80665;

// ============================================================================
// Unit Conversions
// ============================================================================

/**
 * @brief Converts Celsius to Fahrenheit.
 * @param c Temperature in degrees Celsius.
 * @return Temperature in degrees Fahrenheit.
 */
// All functions here are constexpr - the compiler will pre-calculate them if we pass a constant value, saving work at runtime
constexpr double celsiusToFahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32.0;
}

/**
 * @brief Converts Fahrenheit to Celsius.
 * @param f Temperature in degrees Fahrenheit.
 * @return Temperature in degrees Celsius.
 */
constexpr double fahrenheitToCelsius(double f) {
    return (f - 32.0) * 5.0 / 9.0;
}

/**
 * @brief Converts Kilometers to Miles.
 * @param km Distance in kilometers.
 * @return Distance in miles.
 */
constexpr double kmToMiles(double km) {
    return km * 0.621371;
}

/**
 * @brief Converts Miles to Kilometers.
 * @param miles Distance in miles.
 * @return Distance in kilometers.
 */
constexpr double milesToKm(double miles) {
    return miles * 1.60934;
}

/**
 * @brief Converts Degrees to Radians.
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
constexpr double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

/**
 * @brief Converts Radians to Degrees.
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
constexpr double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

// ============================================================================
// Physics Formulas
// ============================================================================

/**
 * @brief Calculates kinetic energy.
 * @param mass Mass of the object in kilograms.
 * @param velocity Velocity of the object in meters per second.
 * @return Kinetic energy in Joules.
 */
constexpr double kineticEnergy(double mass, double velocity) {
    return 0.5 * mass * velocity * velocity;
}

/**
 * @brief Calculates potential energy.
 * @param mass Mass of the object in kilograms.
 * @param height Height of the object in meters.
 * @return Potential energy in Joules.
 */
constexpr double potentialEnergy(double mass, double height) {
    return mass * GRAVITY * height;
}

/**
 * @brief Calculates mass-energy equivalence (E = mc^2).
 * @param mass Mass of the object in kilograms.
 * @return Energy in Joules.
 */
constexpr double massEnergy(double mass) {
    return mass * SPEED_OF_LIGHT * SPEED_OF_LIGHT;
}

/**
 * @brief Calculates the distance of an object in free fall.
 * @param time Time elapsed in seconds.
 * @return Distance fallen in meters.
 */
constexpr double freeFallDistance(double time) {
    return 0.5 * GRAVITY * time * time;
}

// ============================================================================
// Math Utilities
// ============================================================================

/**
 * @brief Calculates the power of a base raised to an integer exponent.
 * Evaluated iteratively at compile-time.
 *
 * @param base The base value.
 * @param exp The integer exponent (assumed non-negative for this assignment).
 * @return The base raised to the power of exp.
 */
constexpr double power(double base, int exp) {
    double result = 1.0;
    // Starting from advanced C++ standards, it is allowed to use loops inside constexpr functions
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

/**
 * @brief Calculates the absolute value of a floating-point number.
 * @param value The input value.
 * @return The absolute value.
 */
constexpr double absVal(double value) {
    return value < 0 ? -value : value;
}

} // namespace metaengine