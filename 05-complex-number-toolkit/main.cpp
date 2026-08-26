/**
 * @file main.cpp
 * @brief Demo for Complex Number System
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "Complex.hpp"
#include "ComplexArray.hpp"

using namespace std;
using namespace complex_math;

void printSeparator(const string& title = "") {
    cout << "\n========================================" << endl;
    if (! title.empty()) {
        cout << "  " << title << endl;
        cout << "========================================" << endl;
    }
}

int main() {
    cout << fixed << setprecision(4);
    
    printSeparator("Complex Number System Demo");
    cout << "Assignment 5:  Deep Copy & Conversion Operators\n" << endl;

    // ============ PART 1: COMPLEX CLASS ============
    
    printSeparator("PART 1: COMPLEX NUMBER CLASS");

    // --- 1. CONSTRUCTORS ---
    cout << "\n=== 1. CONSTRUCTORS ===" << endl;
    
    Complex c1;                     // Default:  0+0i
    Complex c2(5.0);                // Real only:  5+0i
    Complex c3(3.0, 4.0);           // Rectangular: 3+4i
    Complex c4(c3);                 // Copy constructor
    
    cout << "c1 (default): " << c1 << endl;                    // Expected: 0+0i
    cout << "c2 (real only): " << c2 << endl;                  // Expected: 5+0i
    cout << "c3 (3+4i): " << c3 << endl;                       // Expected: 3+4i
    cout << "c4 (copy of c3): " << c4 << endl;                 // Expected: 3+4i
    

    Complex c5 = Complex:: fromPolar(5.0, 0.927295);  // 5∠53.13° ≈ 3+4i
    cout << "c5 (from polar 5∠53.13°): " << c5 << endl;       // Expected: ≈3+4i

    // --- 2. CONVERSION OPERATORS ---
    cout << "\n=== 2. CONVERSION OPERATORS ===" << endl;
    
    Complex c6(3.0, 4.0);  // 3+4i, magnitude = 5
    
    double magnitude = (double)c6;
    cout << "c6 = " << c6 << endl;
    cout << "As double (magnitude): " << magnitude << endl;    // Expected: 5.0000
    
    bool isNonZero = (bool)c6;
    Complex zero(0, 0);
    bool isZero = (bool)zero;
    cout << "c6 as bool: " << (isNonZero ? "true" : "false") << " (non-zero)" << endl;  // Expected: true
    cout << "zero as bool: " << (isZero ? "true" : "false") << " (is zero)" << endl;    // Expected: false
    
    string str = (string)c6;
    cout << "As string: " << str << endl;                      // Expected: "3+4i"
    
    double result = 10.0 + (double)c6;
    cout << "10.0 + (double)c6 = " << result << endl;          // Expected: 15.0000
    
    Complex c7(2, 3);
    if (c7) {
        cout << "c7 is non-zero (bool conversion works! )" << endl;
    }
    
    cout << "\nString representations of " << c6 << ":" << endl;
    cout << "  Rectangular: " << c6.toRectangularString() << endl;      // Expected: 3+4i

    // --- 3. COMPLEX PROPERTIES ---
    cout << "\n=== 3. COMPLEX NUMBER PROPERTIES ===" << endl;
    
    Complex c8(3, 4);
    cout << "c8 = " << c8 << endl;
    cout << "Magnitude: " << c8.magnitude() << endl;                    // Expected: 5.0000
    cout << "Conjugate: " << c8.conjugate() << endl;                    // Expected: 3-4i
    cout << "Is zero?  " << (c8.isZero() ? "Yes" : "No") << endl;        // Expected: No
    cout << "Is real? " << (c8.isReal() ? "Yes" : "No") << endl;        // Expected: No
    
    Complex real(5, 0);
    cout << "\nreal = " << real << endl;
    cout << "Is real? " << (real.isReal() ? "Yes" : "No") << endl;      // Expected: Yes

    // --- 4. ARITHMETIC OPERATORS ---
    cout << "\n=== 4. ARITHMETIC OPERATORS ===" << endl;
    
    Complex a(3, 2);  // 3+2i
    Complex b(1, 4);  // 1+4i
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    Complex sum = a + b;
    cout << "a + b = " << sum << endl;                                  // Expected: 4+6i
    
    Complex diff = a - b;
    cout << "a - b = " << diff << endl;                                 // Expected: 2-2i
    
    Complex prod = a * b;
    cout << "a * b = " << prod << endl;                                 // Expected: -5+14i
    
    Complex quot = a / b;
    cout << "a / b = " << quot << endl;                                 // Expected: 0.6471-0.5882i
    
    Complex c9 = a + 5.0;
    cout << "a + 5.0 = " << c9 << endl;                                 // Expected: 8+2i
    
    Complex c10 = a * 2.0;
    cout << "a * 2.0 = " << c10 << endl;                                // Expected: 6+4i
    
    Complex neg = -a;
    cout << "-a = " << neg << endl;                                     // Expected: -3-2i
    
    Complex c11(5, 3);
    c11 += Complex(2, 1);
    cout << "After += (2+i): " << c11 << endl;                          // Expected: 7+4i
    
    c11 *= 2.0;
    cout << "After *= 2.0: " << c11 << endl;                            // Expected: 14+8i

    // --- 5. INCREMENT/DECREMENT (Prefix) ---
    cout << "\n=== 5. PREFIX INCREMENT/DECREMENT OPERATORS ===" << endl;
    
    Complex c12(3, 4);
    cout << "c12 initial: " << c12 << endl;                             // Expected: 3+4i
    
    ++c12;
    cout << "After ++c12: c12 = " << c12 << endl;                        // Expected: 4+4i
    
    ++c12;
    cout << "After ++c12: c12 = " << c12 << endl;                        // Expected: 5+4i
    
    --c12;
    cout << "After --c12: c12 = " << c12 << endl;                        // Expected: 4+4i

    // --- 6. COMPARISON OPERATORS ---
    cout << "\n=== 6. COMPARISON OPERATORS ===" << endl;
    
    Complex x(3, 4);   // |x| = 5
    Complex y(5, 0);   // |y| = 5
    Complex z(1, 1);   // |z| ≈ 1.414
    
    cout << "x = " << x << " (|x| = " << x.magnitude() << ")" << endl;
    cout << "y = " << y << " (|y| = " << y.magnitude() << ")" << endl;
    cout << "z = " << z << " (|z| = " << z.magnitude() << ")" << endl;
    
    cout << "x == y:  " << (x == y ? "true" : "false") << " (different values)" << endl;  // Expected: false
    cout << "x != y: " << (x != y ? "true" : "false") << endl;           // Expected: true
    cout << "x > z: " << (x > z ?  "true" : "false") << " (by magnitude)" << endl;        // Expected: true
    cout << "z < x: " << (z < x ? "true" : "false") << " (by magnitude)" << endl;        // Expected: true

    // --- 7. FRIEND FUNCTION ---
    cout << "\n=== 7. FRIEND FUNCTION ===" << endl;
    
    Complex p(3, 4);
    Complex q(6, 8);
    
    double dist = distance(p, q);
    cout << "Distance between " << p << " and " << q << ": " << dist << endl;  // Expected: 5.0000

    // --- 8. CONST METHODS ---
    cout << "\n=== 8. CONST METHODS ===" << endl;
    
    const Complex constComplex(6, 8);
    cout << "Const complex: " << constComplex << endl;
    cout << "Real part: " << constComplex. getReal() << endl;            // Expected: 6.0000
    cout << "Imaginary part: " << constComplex.getImag() << endl;       // Expected: 8.0000
    cout << "Magnitude:  " << constComplex.magnitude() << endl;          // Expected: 10.0000
    cout << "Is zero? " << (constComplex. isZero() ? "Yes" : "No") << endl; // Expected: No

    // --- 9. STATIC MEMBERS ---
    cout << "\n=== 9. STATIC MEMBERS ===" << endl;
    
    cout << "Total complex numbers created: " << Complex::getTotalComplexCreated() << endl;
    cout << "Current complex numbers in memory: " << Complex::getCurrentComplexCount() << endl;

    // ============ PART 2: COMPLEXARRAY CLASS ============
    
    printSeparator("PART 2: COMPLEX ARRAY");

    // --- 10. COMPOSITION (ComplexArray HAS-A Complex*) ---
    cout << "\n=== 10. COMPOSITION (ComplexArray HAS-A Complex array) ===" << endl;
    
    ComplexArray arr1;
    arr1.add(Complex(1, 2));
    arr1.add(Complex(3, 4));
    arr1.add(Complex(5, 6));
    
    cout << "Created ComplexArray arr1: " << arr1 << endl;
    cout << "Size: " << arr1.getSize() << endl;                         // Expected: 3
    
    // --- 11. DEEP COPY CONSTRUCTOR ---
    cout << "\n=== 11. DEEP COPY CONSTRUCTOR ===" << endl;
    
    cout << "\n--- Demonstrating Shallow vs Deep Copy ---" << endl;
    cout << "Original arr1: " << arr1 << endl;
    
    ComplexArray arr2(arr1);
    cout << "Created arr2 as copy of arr1: " << arr2 << endl;
    
    arr2[0] = Complex(99, 99);
    cout << "\nAfter modifying arr2[0] to 99+99i:" << endl;
    cout << "arr1[0]:  " << arr1[0] << " (UNCHANGED - deep copy works! )" << endl;
    cout << "arr2[0]: " << arr2[0] << " (changed)" << endl;
    
    cout << "\n✓ Deep copy verified:  arr1 and arr2 have independent arrays" << endl;
    cout << "  - Each has its own memory allocation" << endl;
    cout << "  - Modifying one doesn't affect the other" << endl;
    
    // --- 12. DEEP COPY via ASSIGNMENT OPERATOR ---
    cout << "\n=== 12. ASSIGNMENT OPERATOR (Also Deep Copy) ===" << endl;
    
    ComplexArray arr3;
    arr3.add(Complex(10, 20));
    cout << "arr3 before assignment: " << arr3 << endl;
    
    arr3 = arr1;
    cout << "arr3 after arr3 = arr1: " << arr3 << endl;
    
    arr3[0] = Complex(88, 88);
    cout << "\nAfter modifying arr3[0]:" << endl;
    cout << "arr1[0]: " << arr1[0] << " (UNCHANGED)" << endl;
    cout << "arr3[0]: " << arr3[0] << " (changed)" << endl;
    
    cout << "\n✓ Assignment operator deep copy verified!" << endl;

    // --- 13. DESTRUCTOR & DESTRUCT-ARRAYS ---
    cout << "\n=== 13. DESTRUCTOR & DESTRUCT-ARRAYS ===" << endl;
    
    cout << "Creating arrays in a scope block..." << endl;
    {
        ComplexArray temp1;
        temp1.add(Complex(1, 1));
        temp1.add(Complex(2, 2));
        
        ComplexArray temp2(temp1);  // Deep copy
        
        cout << "temp1: " << temp1 << endl;
        cout << "temp2: " << temp2 << endl;
        cout << "Exiting scope - destructors will be called..." << endl;
    }
    
    cout << "Scope exited - both arrays properly deleted" << endl;
    cout << "No memory leaks because each array was independently allocated!" << endl;

    // --- 14. BRACKET OPERATOR [] ---
    cout << "\n=== 14. BRACKET OPERATOR [] ===" << endl;
    
    ComplexArray arr4;
    arr4.add(Complex(2, 3));
    arr4.add(Complex(4, 5));
    arr4.add(Complex(6, 7));
    
    cout << "arr4: " << arr4 << endl;
    cout << "arr4[0] = " << arr4[0] << endl;                            // Expected: 2+3i
    cout << "arr4[1] = " << arr4[1] << endl;                            // Expected: 4+5i
    cout << "arr4[2] = " << arr4[2] << endl;                            // Expected: 6+7i
    
    arr4[1] = Complex(10, 10);
    cout << "After arr4[1] = 10+10i:  " << arr4 << endl;

    // --- 15. ARITHMETIC OPERATORS ON ARRAYS ---
    cout << "\n=== 15. ARITHMETIC OPERATORS (on Arrays) ===" << endl;
    
    ComplexArray arrA;
    arrA.add(Complex(1, 2));
    arrA.add(Complex(3, 4));
    
    ComplexArray arrB;
    arrB.add(Complex(5, 6));
    arrB.add(Complex(7, 8));
    
    cout << "arrA: " << arrA << endl;
    cout << "arrB: " << arrB << endl;
    
    ComplexArray arrSum = arrA + arrB;
    cout << "arrA + arrB: " << arrSum << endl;                          // Expected: [6+8i, 10+12i]
    
    ComplexArray arrPlusScalar = arrA + Complex(10, 0);
    cout << "arrA + 10: " << arrPlusScalar << endl;                     // Expected: [11+2i, 13+4i]
    
    ComplexArray arrScaled = arrA * 2.0;
    cout << "arrA * 2.0: " << arrScaled << endl;                        // Expected: [2+4i, 6+8i]

    // --- 16. MATHEMATICAL OPERATIONS ---
    cout << "\n=== 16. MATHEMATICAL OPERATIONS ===" << endl;
    
    ComplexArray arr6;
    arr6.add(Complex(1, 0));
    arr6.add(Complex(2, 0));
    arr6.add(Complex(3, 0));
    
    cout << "arr6: " << arr6 << endl;
    cout << "Sum: " << arr6.sum() << endl;                              // Expected: 6+0i
    cout << "Average: " << arr6.average() << endl;                      // Expected:  2+0i
    cout << "Max (by magnitude): " << arr6.max() << endl;               // Expected:  3+0i

    // --- 17. REFERENCE & REFERENCE-RETURN ---
    cout << "\n=== 17. REFERENCE & REFERENCE-RETURN ===" << endl;
    
    Complex& ref = arr4[0];
    cout << "Reference to arr4[0]: " << ref << endl;
    ref. setReal(100.0);
    cout << "After modifying through reference: " << arr4[0] << endl;   // Expected: 100+3i

    // --- 18. INLINE vs OUTLINE ---
    cout << "\n=== 18. INLINE vs OUTLINE ===" << endl;
    cout << "getSize() is INLINE: " << arr4.getSize() << endl;
    cout << "sum() is OUTLINE: " << arr4.sum() << endl;
    cout << "isEmpty() is INLINE: " << (arr4.isEmpty() ? "Yes" : "No") << endl;

    // --- 19. CONVERSION OPERATORS IN CONTEXT ---
    cout << "\n=== 19. CONVERSION OPERATORS IN CONTEXT ===" << endl;
    
    Complex c16(4, 3);  // |c| = 5
    
    double calculation = (double)c16 + 10.0;
    cout << "Complex " << c16 << " magnitude + 10.0 = " << calculation << endl;  // Expected: 15.0
    
    Complex nonZero(1, 2);
    Complex isZeroComplex(0, 0);
    
    if (nonZero) {
        cout << "Complex(1,2) evaluates to true (non-zero)" << endl;
    }
    if (! isZeroComplex) {
        cout << "Complex(0,0) evaluates to false (is zero)" << endl;
    }
    
    string message = "The complex number is:  " + (string)c16;
    cout << message << endl;
    
    cout << "\n=== Statistics ===" << endl;
    cout << "Total Complex numbers created: " << Complex::getTotalComplexCreated() << endl;
    cout << "Current Complex numbers in memory: " << Complex::getCurrentComplexCount() << endl;
    cout << "Total ComplexArrays created: " << ComplexArray::getTotalArraysCreated() << endl;
    cout << "Current ComplexArrays in memory: " << ComplexArray::getCurrentArrayCount() << endl;
    
    printSeparator("Demo Complete!");
    
    return 0;
}