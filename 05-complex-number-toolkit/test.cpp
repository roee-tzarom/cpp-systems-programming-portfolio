/**
 * @file test.cpp
 * @brief Unit tests for Complex Number System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "ComplexArray.hpp"
#include <fstream>

using namespace complex_math;

// ==================== COMPLEX CLASS TESTS ====================

TEST_CASE("Complex - Constructors") {
    Complex c1;
    CHECK(c1.getReal() == 0.0);
    CHECK(c1.getImag() == 0.0);
    
    Complex c2(5.0);
    CHECK(c2.getReal() == 5.0);
    CHECK(c2.getImag() == 0.0);
    
    Complex c3(3.0, 4.0);
    CHECK(c3.getReal() == 3.0);
    CHECK(c3.getImag() == 4.0);
    
    Complex c4(c3);
    CHECK(c4.getReal() == 3.0);
    CHECK(c4.getImag() == 4.0);
}

TEST_CASE("Complex - Conversion Operators") {
    Complex c(3.0, 4.0);  // |c| = 5
    
    SUBCASE("Convert to double (magnitude)") {
        double d = (double)c;
        CHECK(d == doctest::Approx(5.0));
    }
    
    SUBCASE("Convert to bool - non-zero") {
        bool b = (bool)c;
        CHECK(b == true);
    }
    
    SUBCASE("Convert to bool - zero") {
        Complex zero(0, 0);
        bool b = (bool)zero;
        CHECK(b == false);
    }
    
    SUBCASE("Convert to string") {
        std::string s = (std::string)c;
        CHECK(s == "3+4i");
    }
    
    SUBCASE("Use in conditional") {
        Complex nonZero(1, 2);
        if (nonZero) {
            CHECK(true);  // Should reach here
        } else {
            CHECK(false);  // Should not reach here
        }
    }
    
    SUBCASE("Use in arithmetic with conversion") {
        double result = 10.0 + (double)c;  // 10 + 5
        CHECK(result == doctest:: Approx(15.0));
    }
}

TEST_CASE("Complex - Properties") {
    Complex c(3.0, 4.0);
    
    CHECK(c.magnitude() == doctest::Approx(5.0));
    
    Complex conj = c.conjugate();
    CHECK(conj.getReal() == 3.0);
    CHECK(conj.getImag() == -4.0);
    
    CHECK_FALSE(c.isZero());
    CHECK_FALSE(c.isReal());
    
    Complex realNum(5, 0);
    CHECK(realNum.isReal());
}

TEST_CASE("Complex - Arithmetic Operators") {
    Complex a(3, 2);
    Complex b(1, 4);
    
    SUBCASE("Addition") {
        Complex sum = a + b;
        CHECK(sum.getReal() == 4.0);
        CHECK(sum. getImag() == 6.0);
        
        Complex sum2 = a + 5.0;
        CHECK(sum2.getReal() == 8.0);
        CHECK(sum2.getImag() == 2.0);
    }
    
    SUBCASE("Subtraction") {
        Complex diff = a - b;
        CHECK(diff.getReal() == 2.0);
        CHECK(diff.getImag() == -2.0);
    }
    
    SUBCASE("Multiplication") {
        Complex prod = a * b;
        // (3+2i)(1+4i) = 3 + 12i + 2i + 8i² = 3 + 14i - 8 = -5 + 14i
        CHECK(prod.getReal() == doctest::Approx(-5.0));
        CHECK(prod.getImag() == doctest::Approx(14.0));
    }
    
    SUBCASE("Division") {
        Complex quot = a / b;
        // (3+2i)/(1+4i) = (3+2i)(1-4i) / (1+16) = (3-12i+2i+8) / 17 = (11-10i)/17
        CHECK(quot.getReal() == doctest::Approx(11.0/17.0).epsilon(0.001));
        CHECK(quot.getImag() == doctest::Approx(-10.0/17.0).epsilon(0.001));
    }
    
    SUBCASE("Division by zero throws") {
        Complex zero(0, 0);
        CHECK_THROWS_AS(a / zero, std::invalid_argument);
    }
    
    SUBCASE("Unary negation") {
        Complex neg = -a;
        CHECK(neg. getReal() == -3.0);
        CHECK(neg.getImag() == -2.0);
    }
}

TEST_CASE("Complex - Increment/Decrement") {
    Complex c(3, 4);
    
    ++c;
    CHECK(c.getReal() == 4.0);  // Incremented
    
    ++c;
    CHECK(c.getReal() == 5.0);  // Incremented again
    
    --c;
    CHECK(c.getReal() == 4.0);  // Decremented
    
    --c;
    CHECK(c.getReal() == 3.0);  // Decremented again
}

TEST_CASE("Complex - Comparison Operators") {
    Complex a(3, 4);  // |a| = 5
    Complex b(5, 0);  // |b| = 5
    Complex c(1, 1);  // |c| ≈ 1.414
    
    CHECK(a != b);  // Different values
    CHECK(a > c);   // By magnitude
    CHECK(c < a);
}

TEST_CASE("Complex - Compound Assignment") {
    Complex c(3, 2);
    
    c += Complex(1, 4);
    CHECK(c.getReal() == 4.0);
    CHECK(c.getImag() == 6.0);
    
    c -= Complex(1, 1);
    CHECK(c.getReal() == 3.0);
    CHECK(c.getImag() == 5.0);
    
    c *= 2.0;
    CHECK(c. getReal() == 6.0);
    CHECK(c.getImag() == 10.0);
}

TEST_CASE("Complex - Static Members") {
    int initial = Complex::getTotalComplexCreated();
    
    Complex c1(1, 2);
    Complex c2(3, 4);
    
    CHECK(Complex::getTotalComplexCreated() == initial + 2);
}

TEST_CASE("Complex - Friend Function") {
    Complex c1(3, 4);
    Complex c2(6, 8);
    
    double dist = distance(c1, c2);
    CHECK(dist == doctest::Approx(5.0));
}

TEST_CASE("Complex - Polar Form") {
    Complex c = Complex:: fromPolar(5.0, 0.927295);  // 5∠53.13° ≈ 3+4i
    CHECK(c.getReal() == doctest::Approx(3.0).epsilon(0.01));
    CHECK(c.getImag() == doctest::Approx(4.0).epsilon(0.01));
}

// ==================== COMPLEXARRAY CLASS TESTS ====================

TEST_CASE("ComplexArray - Constructors") {
    ComplexArray arr1;
    CHECK(arr1.getSize() == 0);
    CHECK(arr1.isEmpty());
    
    ComplexArray arr2(20);
    CHECK(arr2.getCapacity() == 20);
}

TEST_CASE("ComplexArray - Add Elements (Composition)") {
    ComplexArray arr;
    arr.add(Complex(1, 2));
    arr.add(Complex(3, 4));
    
    CHECK(arr.getSize() == 2);
    CHECK_FALSE(arr.isEmpty());
}

TEST_CASE("ComplexArray - Deep Copy Constructor") {
    ComplexArray arr1;
    arr1.add(Complex(1, 2));
    arr1.add(Complex(3, 4));
    arr1.add(Complex(5, 6));
    
    // Create deep copy
    ComplexArray arr2(arr1);
    
    SUBCASE("Copy has same values") {
        CHECK(arr2.getSize() == arr1.getSize());
        CHECK(arr2[0] == arr1[0]);
        CHECK(arr2[1] == arr1[1]);
        CHECK(arr2[2] == arr1[2]);
    }
    
    SUBCASE("Deep copy - modifications are independent") {
        // Modify arr2
        arr2[0] = Complex(99, 99);
        
        // arr1 should be UNCHANGED
        CHECK(arr1[0].getReal() == 1.0);
        CHECK(arr1[0].getImag() == 2.0);
        
        // arr2 should be CHANGED
        CHECK(arr2[0].getReal() == 99.0);
        CHECK(arr2[0].getImag() == 99.0);
    }
    
    SUBCASE("Deep copy - arrays are independent") {
        arr2. add(Complex(7, 8));
        
        CHECK(arr1.getSize() == 3);  // Original unchanged
        CHECK(arr2.getSize() == 4);  // Copy changed
    }
}

TEST_CASE("ComplexArray - Assignment Operator (Deep Copy)") {
    ComplexArray arr1;
    arr1.add(Complex(10, 20));
    arr1.add(Complex(30, 40));
    
    ComplexArray arr2;
    arr2.add(Complex(1, 1));
    
    // Assignment (deep copy)
    arr2 = arr1;
    
    SUBCASE("Copy has same values") {
        CHECK(arr2.getSize() == 2);
        CHECK(arr2[0] == arr1[0]);
        CHECK(arr2[1] == arr1[1]);
    }
    
    SUBCASE("Deep copy - modifications independent") {
        arr2[0] = Complex(88, 88);
        
        CHECK(arr1[0].getReal() == 10.0);  // Original unchanged
        CHECK(arr2[0].getReal() == 88.0);  // Copy changed
    }
    
    SUBCASE("Self-assignment") {
        arr1 = arr1;  // Should handle gracefully
        CHECK(arr1.getSize() == 2);
        CHECK(arr1[0]. getReal() == 10.0);
    }
}

TEST_CASE("ComplexArray - Destructor (Destruct-Arrays)") {
    int initialCount = ComplexArray::getCurrentArrayCount();
    
    {
        ComplexArray temp;
        temp.add(Complex(1, 2));
        temp.add(Complex(3, 4));
        
        CHECK(ComplexArray::getCurrentArrayCount() == initialCount + 1);
    }  // Destructor called here
    
    CHECK(ComplexArray:: getCurrentArrayCount() == initialCount);
}

TEST_CASE("ComplexArray - Bracket Operator []") {
    ComplexArray arr;
    arr.add(Complex(2, 3));
    arr.add(Complex(4, 5));
    arr.add(Complex(6, 7));
    
    CHECK(arr[0].getReal() == 2.0);
    CHECK(arr[1].getReal() == 4.0);
    CHECK(arr[2].getReal() == 6.0);
    
    // Modify through bracket operator
    arr[1] = Complex(10, 10);
    CHECK(arr[1].getReal() == 10.0);
    CHECK(arr[1].getImag() == 10.0);
}

TEST_CASE("ComplexArray - Arithmetic Operators") {
    ComplexArray arr1;
    arr1.add(Complex(1, 2));
    arr1.add(Complex(3, 4));
    
    ComplexArray arr2;
    arr2.add(Complex(5, 6));
    arr2.add(Complex(7, 8));
    
    SUBCASE("Element-wise addition") {
        ComplexArray sum = arr1 + arr2;
        CHECK(sum[0].getReal() == 6.0);
        CHECK(sum[0].getImag() == 8.0);
        CHECK(sum[1].getReal() == 10.0);
        CHECK(sum[1].getImag() == 12.0);
    }
    
    SUBCASE("Add scalar to all") {
        ComplexArray result = arr1 + Complex(10, 0);
        CHECK(result[0].getReal() == 11.0);
        CHECK(result[1].getReal() == 13.0);
    }
    
    SUBCASE("Multiply by scalar") {
        ComplexArray result = arr1 * 2.0;
        CHECK(result[0].getReal() == 2.0);
        CHECK(result[0].getImag() == 4.0);
    }
}

TEST_CASE("ComplexArray - Mathematical Operations") {
    ComplexArray arr;
    arr.add(Complex(1, 0));
    arr.add(Complex(2, 0));
    arr.add(Complex(3, 0));
    
    Complex sum = arr. sum();
    CHECK(sum.getReal() == 6.0);
    
    Complex avg = arr.average();
    CHECK(avg.getReal() == doctest::Approx(2.0));
    
    Complex maxVal = arr.max();
    CHECK(maxVal.getReal() == 3.0);
}

TEST_CASE("ComplexArray - Remove Element") {
    ComplexArray arr;
    arr.add(Complex(1, 1));
    arr.add(Complex(3, 3));
    
    arr.remove(0);
    CHECK(arr.getSize() == 1);
    CHECK(arr[0].getReal() == 3.0);
}

TEST_CASE("ComplexArray - Find and Contains") {
    ComplexArray arr;
    arr.add(Complex(1, 2));
    arr.add(Complex(3, 4));
    arr.add(Complex(5, 6));
    
    int index = arr.find(Complex(3, 4));
    CHECK(index == 1);
    
    CHECK(arr.contains(Complex(5, 6)));
    CHECK_FALSE(arr.contains(Complex(99, 99)));
}

TEST_CASE("ComplexArray - Comparison Operators") {
    ComplexArray arr1;
    arr1.add(Complex(1, 2));
    arr1.add(Complex(3, 4));
    
    ComplexArray arr2;
    arr2.add(Complex(1, 2));
    arr2.add(Complex(3, 4));
    
    ComplexArray arr3;
    arr3.add(Complex(5, 6));
    
    CHECK(arr1 == arr2);
    CHECK(arr1 != arr3);
}

TEST_CASE("ComplexArray - Resize") {
    ComplexArray arr(2);  // Initial capacity 2
    
    arr.add(Complex(1, 1));
    arr.add(Complex(2, 2));
    CHECK(arr.getCapacity() == 2);
    
    arr.add(Complex(3, 3));  // Triggers resize
    CHECK(arr.getCapacity() == 4);
    CHECK(arr. getSize() == 3);
}

TEST_CASE("ComplexArray - Clear") {
    ComplexArray arr;
    arr.add(Complex(1, 2));
    arr.add(Complex(3, 4));
    
    arr.clear();
    CHECK(arr.getSize() == 0);
    CHECK(arr.isEmpty());
}

// ==================== INTEGRATION TESTS ====================

TEST_CASE("Integration - Complex with Array") {
    ComplexArray arr;
    
    // Add complex numbers
    arr.add(Complex(3, 4));
    arr.add(Complex(1, 2));
    arr.add(Complex(5, 0));
    
    // Use conversion operators
    double firstMag = (double)arr[0];
    CHECK(firstMag == doctest:: Approx(5.0));
    
    // Use arithmetic
    ComplexArray scaled = arr * 2.0;
    CHECK(scaled[0]. getReal() == 6.0);
    
    // Deep copy
    ComplexArray copy(arr);
    copy[0] = Complex(99, 99);
    CHECK(arr[0].getReal() == 3.0);  // Original unchanged
}

TEST_CASE("Integration - Conversion in Expressions") {
    Complex c(3, 4);
    
    // Use in arithmetic
    double result = (double)c + 10.0;
    CHECK(result == doctest::Approx(15.0));
    
    // Use in conditional
    if (c) {
        CHECK(true);
    }
    
    // Convert to string
    std::string s = (std::string)c;
    CHECK(s == "3+4i");
}

// ==================== STUDENT TEST FILE CHECK ====================

TEST_CASE("StudentTest - File exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases.");
}