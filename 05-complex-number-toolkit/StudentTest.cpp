#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "ComplexArray.hpp"
#include <stdexcept>

using namespace complex_math;

TEST_CASE("1. Complex: Division by difference of conjugates") {
    Complex testComplex(3.0, 4.0);
    Complex difference = testComplex - testComplex.conjugate();
    Complex resultComplex = testComplex / difference;
    CHECK(resultComplex.getReal() == doctest::Approx(0.5));
    CHECK(resultComplex.getImag() == doctest::Approx(-0.375));
}

TEST_CASE("2. Complex: Long operator chaining") {
    Complex firstComplex(1.0, 1.0);
    Complex secondComplex(2.0, 2.0);
    Complex thirdComplex(3.0, 3.0);
    Complex fourthComplex(4.0, 4.0);
    Complex fifthComplex(2.0, 0.0);
    Complex resultComplex = (firstComplex + secondComplex) * thirdComplex - (fourthComplex / fifthComplex);
    CHECK(resultComplex.getReal() == doctest::Approx(-2.0));
    CHECK(resultComplex.getImag() == doctest::Approx(16.0));
}

TEST_CASE("3. Complex: High power accumulation") {
    Complex baseComplex(1.1, 0.1);
    Complex resultComplex(1.0, 0.0);
    for(int index = 0; index < 10; ++index) {
        resultComplex = resultComplex * baseComplex;
    }
    CHECK(resultComplex.magnitude() > 1.0);
}

TEST_CASE("4. Complex: Normalization to unit circle") {
    Complex testComplex(3.0, 4.0);
    Complex normalizedComplex = testComplex / testComplex.magnitude();
    CHECK(normalizedComplex.magnitude() == doctest::Approx(1.0));
}

TEST_CASE("5. Complex: Division by near-zero complex number") {
    Complex normalComplex(1.0, 1.0);
    Complex nearZeroComplex(1e-9, 1e-9);
    Complex resultComplex = normalComplex / nearZeroComplex;
    CHECK(resultComplex.getReal() == doctest::Approx(1e9));
}

TEST_CASE("6. Complex: Sum with conjugate is pure real") {
    Complex testComplex(5.5, 7.3);
    Complex resultComplex = testComplex + testComplex.conjugate();
    CHECK(resultComplex.isReal() == true);
    CHECK(resultComplex.getReal() == doctest::Approx(11.0));
}

TEST_CASE("7. Complex: Product with conjugate is magnitude squared") {
    Complex testComplex(3.0, 4.0);
    Complex resultComplex = testComplex * testComplex.conjugate();
    CHECK(resultComplex.getReal() == doctest::Approx(25.0));
    CHECK(resultComplex.getImag() == doctest::Approx(0.0));
}

TEST_CASE("8. ComplexArray: Array multiplication by its own average") {
    ComplexArray targetArray;
    targetArray.add(Complex(2.0, 0.0));
    targetArray.add(Complex(4.0, 0.0));
    Complex averageValue = targetArray.average();
    for(int index = 0; index < targetArray.getSize(); ++index) {
        targetArray[index] = targetArray[index] * averageValue;
    }
    CHECK(targetArray[0].getReal() == doctest::Approx(6.0));
}

TEST_CASE("9. ComplexArray: Prefix sum generation") {
    ComplexArray originalArray;
    originalArray.add(Complex(1.0, 1.0));
    originalArray.add(Complex(2.0, 2.0));
    ComplexArray prefixArray;
    Complex currentSum(0.0, 0.0);
    for(int index = 0; index < originalArray.getSize(); ++index) {
        currentSum += originalArray[index];
        prefixArray.add(currentSum);
    }
    CHECK(prefixArray[1].getReal() == doctest::Approx(3.0));
}

TEST_CASE("10. ComplexArray: Dot product of two arrays") {
    ComplexArray firstArray;
    ComplexArray secondArray;
    firstArray.add(Complex(1.0, 0.0));
    secondArray.add(Complex(0.0, 1.0));
    Complex dotProductResult(0.0, 0.0);
    for(int index = 0; index < firstArray.getSize(); ++index) {
        dotProductResult += firstArray[index] * secondArray[index];
    }
    CHECK(dotProductResult.getImag() == doctest::Approx(1.0));
}

TEST_CASE("11. ComplexArray: Filter by magnitude threshold") {
    ComplexArray filterArray;
    filterArray.add(Complex(1.0, 0.0));
    filterArray.add(Complex(10.0, 0.0));
    for(int index = filterArray.getSize() - 1; index >= 0; --index) {
        if(filterArray[index].magnitude() < 5.0) {
            filterArray.remove(index);
        }
    }
    CHECK(filterArray.getSize() == 1);
}

TEST_CASE("12. ComplexArray: Array normalization by max element") {
    ComplexArray normalizeArray;
    normalizeArray.add(Complex(3.0, 4.0));
    normalizeArray.add(Complex(6.0, 8.0));
    Complex maximumElement = normalizeArray.max();
    for(int index = 0; index < normalizeArray.getSize(); ++index) {
        normalizeArray[index] /= maximumElement;
    }
    CHECK(normalizeArray[1].getReal() == doctest::Approx(1.0));
}

TEST_CASE("13. ComplexArray: Sorting array by magnitude") {
    ComplexArray sortingArray;
    sortingArray.add(Complex(10.0, 0.0));
    sortingArray.add(Complex(1.0, 0.0));
    if(sortingArray[1] < sortingArray[0]) {
        Complex temporaryComplex = sortingArray[0];
        sortingArray[0] = sortingArray[1];
        sortingArray[1] = temporaryComplex;
    }
    CHECK(sortingArray[0].getReal() == doctest::Approx(1.0));
}

TEST_CASE("14. ComplexArray: Conjugate manipulation and sum comparison") {
    ComplexArray conjugateArray;
    conjugateArray.add(Complex(1.0, 2.0));
    Complex originalSum = conjugateArray.sum();
    for(int index = 0; index < conjugateArray.getSize(); ++index) {
        conjugateArray[index] = conjugateArray[index].conjugate();
    }
    CHECK(conjugateArray.sum() == originalSum.conjugate());
}

TEST_CASE("15. ComplexArray: Stress test allocation and deletion") {
    ComplexArray stressArray;
    for(int index = 0; index < 1000; ++index) {
        stressArray.add(Complex(static_cast<double>(index), 0.0));
    }
    for(int index = 0; index < 999; ++index) {
        stressArray.remove(stressArray.getSize() - 1);
    }
    CHECK(stressArray.getSize() == 1);
}

TEST_CASE("16. ComplexArray: Polynomial evaluation") {
    ComplexArray coefficientsArray;
    coefficientsArray.add(Complex(1.0, 0.0));
    coefficientsArray.add(Complex(2.0, 0.0));
    Complex targetX(0.0, 1.0);
    Complex finalResult(0.0, 0.0);
    Complex currentPower(1.0, 0.0);
    for(int index = 0; index < coefficientsArray.getSize(); ++index) {
        finalResult += coefficientsArray[index] * currentPower;
        currentPower = currentPower * targetX;
    }
    CHECK(finalResult.getReal() == doctest::Approx(1.0));
    CHECK(finalResult.getImag() == doctest::Approx(2.0));
}

TEST_CASE("17. ComplexArray: Moving average simulation") {
    ComplexArray sourceArray;
    sourceArray.add(Complex(2.0, 0.0));
    sourceArray.add(Complex(4.0, 0.0));
    sourceArray.add(Complex(6.0, 0.0));
    ComplexArray movingAverageArray;
    for(int index = 1; index < sourceArray.getSize() - 1; ++index) {
        movingAverageArray.add((sourceArray[index - 1] + sourceArray[index] + sourceArray[index + 1]) / 3.0);
    }
    CHECK(movingAverageArray[0].getReal() == doctest::Approx(4.0));
}

TEST_CASE("18. ComplexArray: Mandelbrot sequence generation") {
    ComplexArray mandelbrotArray;
    Complex currentZ(0.0, 0.0);
    Complex constantC(0.5, 0.5);
    for(int index = 0; index < 5; ++index) {
        currentZ = currentZ * currentZ + constantC;
        mandelbrotArray.add(currentZ);
    }
    CHECK(mandelbrotArray.getSize() == 5);
}

TEST_CASE("19. ComplexArray: Array reversal and subtraction") {
    ComplexArray standardArray;
    standardArray.add(Complex(1.0, 0.0));
    standardArray.add(Complex(3.0, 0.0));
    ComplexArray reversedArray;
    reversedArray.add(standardArray[1]);
    reversedArray.add(standardArray[0]);
    ComplexArray differenceArray = standardArray + (reversedArray * -1.0);
    CHECK(differenceArray[0].getReal() == doctest::Approx(-2.0));
}

TEST_CASE("20. ComplexArray: Product of all elements") {
    ComplexArray productArray;
    productArray.add(Complex(2.0, 0.0));
    productArray.add(Complex(3.0, 0.0));
    Complex totalProduct(1.0, 0.0);
    for(int index = 0; index < productArray.getSize(); ++index) {
        totalProduct = totalProduct * productArray[index];
    }
    CHECK(totalProduct.getReal() == doctest::Approx(6.0));
}