/**
 * @file Derivative.hpp
 * @brief Symbolic differentiation engine using template metaprogramming.
 *
 * This file constructs compile-time mathematical expression trees and
 * evaluates their symbolic derivatives. It uses templates to represent
 * variables, constants, addition, multiplication, and powers.
 */

#pragma once

#include <string>

namespace metaengine {

// ============================================================================
// 1. Expression Nodes
// ============================================================================

/**
 * @brief Represents a mathematical constant N.
 * @tparam N The integer value of the constant.
 */
template <int N>
struct Const {
    /**
     * @brief Evaluates the constant.
     * @param x The runtime value of the variable (ignored for constants).
     * @return The constant value N.
     */
    // The value N is already known at compile time (non-type template parameter), so we simply return it
    static double eval(double /*x*/) { return N; }
    
    /**
     * @brief Returns the string representation of the constant.
     * @return std::string The constant as a string.
     */
    static std::string toString() { return std::to_string(N); }
};

/**
 * @brief Represents the mathematical variable 'x'.
 */
struct Var {
    /**
     * @brief Evaluates the variable.
     * @param x The runtime value of the variable.
     * @return The value x.
     */
    static double eval(double x) { return x; }
    
    /**
     * @brief Returns the string representation of the variable.
     * @return std::string "x".
     */
    static std::string toString() { return "x"; }
};

/**
 * @brief Represents the addition of two mathematical expressions.
 * @tparam L The left-hand side expression type.
 * @tparam R The right-hand side expression type.
 */
template <typename L, typename R>
struct Add {
    /**
     * @brief Evaluates the sum of both expressions.
     * @param x The runtime value of the variable.
     * @return The sum.
     */
    static double eval(double x) { return L::eval(x) + R::eval(x); }
    
    /**
     * @brief Returns the string representation of the addition.
     * @return std::string Formatted as "(L + R)".
     */
    static std::string toString() { 
        return "(" + L::toString() + " + " + R::toString() + ")"; 
    }
};

/**
 * @brief Represents the multiplication of two mathematical expressions.
 * @tparam L The left-hand side expression type.
 * @tparam R The right-hand side expression type.
 */
template <typename L, typename R>
struct Mul {
    /**
     * @brief Evaluates the product of both expressions.
     * @param x The runtime value of the variable.
     * @return The product.
     */
    static double eval(double x) { return L::eval(x) * R::eval(x); }
    
    /**
     * @brief Returns the string representation of the multiplication.
     * @return std::string Formatted as "(L * R)".
     */
    static std::string toString() { 
        return "(" + L::toString() + " * " + R::toString() + ")"; 
    }
};

/**
 * @brief Represents an expression raised to an integer power.
 * @tparam E The base expression type.
 * @tparam N The integer exponent.
 */
template <typename E, int N>
struct Power {
    /**
     * @brief Evaluates the expression raised to the power N.
     * @param x The runtime value of the variable.
     * @return The calculated power.
     */
    static double eval(double x) {
        double base = E::eval(x);
        double result = 1.0;
        for (int i = 0; i < N; ++i) {
            result *= base;
        }
        return result;
    }
    
    /**
     * @brief Returns the string representation of the power expression.
     * @return std::string Formatted as "(E^N)".
     */
    static std::string toString() { 
        return "(" + E::toString() + "^" + std::to_string(N) + ")"; 
    }
};

// --- Partial Specializations for Power Edge Cases ---

/**
 * @brief Specialization for E^0 (any expression to the power of 0 is 1).
 * @tparam E The base expression type.
 */
// Partial specialization for the edge case: anything to the power of 0 always returns 1
template <typename E>
struct Power<E, 0> {
    static double eval(double /*x*/) { return 1.0; }
    static std::string toString() { return "(" + E::toString() + "^0)"; }
};

/**
 * @brief Specialization for x^1 (Var to the power of 1 is just x).
 */
// Full specialization: x to the power of 1 remains just x
template <>
struct Power<Var, 1> {
    static double eval(double x) { return x; }
    static std::string toString() { return "(x^1)"; }
};


// ============================================================================
// 2. Symbolic Derivative Engine
// ============================================================================

// Forward declaration of the Derive struct
template <typename Expr>
struct Derive;

/** * @brief Type alias helper to easily get the derivative type of an expression.
 * This simplifies the syntax from 'typename Derive<T>::type' to 'Derivative<T>'.
 */
template <typename Expr>
using Derivative = typename Derive<Expr>::type;

/**
 * @brief Derivative of a Constant (d/dx [N] = 0).
 */
template <int N>
struct Derive<Const<N>> {
    using type = Const<0>; // The derivative of a constant number is always 0
};

/**
 * @brief Derivative of a Variable (d/dx [x] = 1).
 */
template <>
struct Derive<Var> {
    using type = Const<1>; // The derivative of x with respect to x is always 1
};

/**
 * @brief Derivative of an Addition (Sum Rule: d/dx [f + g] = f' + g').
 */
template <typename L, typename R>
struct Derive<Add<L, R>> {
    using type = Add<Derivative<L>, Derivative<R>>;
};

/**
 * @brief Derivative of a Multiplication (Product Rule: d/dx [f * g] = f'g + fg').
 */
template <typename L, typename R>
struct Derive<Mul<L, R>> {
    // Implements the product rule: first derived times second normal + first normal times second derived
    using type = Add<Mul<Derivative<L>, R>, Mul<L, Derivative<R>>>;
};

} // namespace metaengine