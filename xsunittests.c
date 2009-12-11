/* 
 This contains testing for xsComplex and xsFFT.
 */

#include <stdio.h>
#include <assert.h>
#include "xsfft.h"

// Private methods to be tested

void _xsFormatInput(xsComplex *data, const unsigned long dataLength);
void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI);
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength);
xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength);


// Function prototypes

inline void testComplexNumbers();
inline void testFFTs();
inline void performTest(bool test, const char *testBehavior);


// Program entrypoint

int main(int argc, char *argv[])
{
    testComplexNumbers();
    testFFTs();
    
    cout << "All tests passed!" << endl;
    
    return 0;
}


// Test helper

inline void performTest(bool test, const char *testBehavior)
{
    cout << "Testing " << testBehavior << "...";
    assert(test);
    cout << "PASSED" << endl;
}


// Test implementations

inline void testComplexNumbers()
{
    cout << "Testing complex numbers..." << endl << endl;
        
    // Test constructors
    performTest(xsComplex().real() == 0.0 && xsComplex().imaginary() == 0.0, "default constructor");
    performTest(xsComplex(1.0).real() == 1.0 && xsComplex(1.0).imaginary() == 0.0, "real constructor");
    performTest(xsComplex(2.0, 3.0).real() == 2.0 && xsComplex(2.0, 3.0).imaginary() == 3.0, "vector constructor");
    
    // Test =
    xsComplex test = 8.0;
    performTest(test.real() == 8.0 && test.imaginary() == 0.0, "assignment");
    
    // Test ==
    test = 5;
    performTest(test == xsComplex(5.0, 0.0), "xsComplex == xsComplex");
    performTest(test == 5.0, "xsComplex == real");
    performTest(5.0 == test, "real == xsComplex");
    
    // Test !=
    performTest(test != xsComplex(5.0, 1.0), "xsComplex != xsComplex");
    performTest(test != 4.0, "xsComplex != real");
    performTest(4.0 != test, "real != xsComplex");
    
    // Test magnitude()
    performTest(xsComplex(3.0, 4.0).magnitude() == 5.0, "magnitude test #1");
    performTest(xsComplex(-3.0, 4.0).magnitude() == 5.0, "magnitude test #2");
    performTest(xsComplex(4.0, -3.0).magnitude() == 5.0, "magnitude test #3");
    performTest(xsComplex(-4.0, -3.0).magnitude() == 5.0, "magnitude test #4");
    
    // Test norm()
    performTest(xsComplex(1.0, 2.0).norm() == 5.0, "norm test #1");
    performTest(xsComplex(-1.0, 2.0).norm() == 5.0, "norm test #2");
    
    // Test complex conjugal visits
    // ...I mean, conjugate()
    performTest(xsComplex(1.0, 1.0).conjugate() == xsComplex(1.0, -1.0), "conjugate test #1");
    performTest(xsComplex(1.0, -1.0).conjugate() == xsComplex(1.0, 1.0), "conjugate test #2");
    performTest(xsComplex(-1.0, -1.0).conjugate() == xsComplex(-1.0, 1.0), "conjugate test #3");
    
    // Test set()
    test.set(6.0, 9.0);
    performTest(test == xsComplex(6.0, 9.0), "set()");
    
    // Test setReal()
    test.setReal(4.0);
    performTest(test.real() == 4.0, "setReal()");
    
    // Test setImaginary()
    test.setImaginary(5.0);
    performTest(test.imaginary() == 5.0, "setImaginary()");
    
    // Test +
    test.set(1.0, 1.0);
    xsComplex result = test + xsComplex(2.0, 2.0);
    performTest(result == xsComplex(3.0, 3.0), "xsComplex + xsComplex");
    
    result = test + 3;
    performTest(result == xsComplex(4.0, 1.0), "xsComplex + real");
    
    result = 4 + test;
    performTest(result == xsComplex(5.0, 1.0), "real + xsComplex");
    
    // Test -
    result = test - xsComplex(2.0, 2.0);
    performTest(result == xsComplex(-1.0, -1.0), "xsComplex - xsComplex");
    
    result = test - 2.0;
    performTest(result == xsComplex(-1.0, 1.0), "xsComplex - real");
    
    result = 1 - test;
    performTest(result == xsComplex(0.0, -1.0), "real - xsComplex");
    
    // Test *
    result = test * xsComplex(1.0, 1.0);
    performTest(result == xsComplex(0.0, 2.0), "xsComplex * xsComplex");
    
    result = test * 3.0;
    performTest(result == xsComplex(3.0, 3.0), "xsComplex * real");
    
    result = -3.0 * test;
    performTest(result == xsComplex(-3.0, -3.0), "real * xsComplex");
    
    // Test /
    result = test / xsComplex(1.0, 1.0);
    performTest(result == xsComplex(1.0, 0.0), "xsComplex / xsComplex");
    
    result = test / 2;
    performTest(result == xsComplex(0.5, 0.5), "xsComplex / real");
    
    result = 5 / test;
    performTest(result == xsComplex(2.5, -2.5), "real / xsComplex");
    
    // Test +=
    test.set(1.0, 1.0);
    result.set(3.0, 6.0);
    result += test;
    performTest(result == xsComplex(4.0, 7.0), "+= xsComplex");
    
    result += 3;
    performTest(result == xsComplex(7.0, 7.0), "+= real");
    
    // Test -=
    result -= test;
    performTest(result == xsComplex(6.0, 6.0), "-= xsComplex");
    
    result -= 3;
    performTest(result == xsComplex(3.0, 6.0), "-= real");
    
    // Test *=
    result *= test;
    performTest(result == xsComplex(-3.0, 9.0), "*= xsComplex");
    
    result *= 2;
    performTest(result == xsComplex(-6, 18), "*= real");
    
    // Test /=
    result /= test;
    performTest(result == xsComplex(6, 12), "/= xsComplex");
    
    result /= 6;
    performTest(result == xsComplex(1, 2), "/= real");
    
    cout << "Complex numbers tested and correct." << endl;
}

void _testInterpolation()
{
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);
    
    xsComplex *data = xsAllocArray(rawData, dataLength);
    
    free(rawData);
    
    cout << "--------------------------Interpolation----------------------------------" << endl;
    
    data = xsInterpolateWithFactor2(data, &dataLength);
    for(unsigned long dataIndex = 0; dataIndex < 100; dataIndex += 2) {
        performTest((unsigned long)((data + dataIndex)->real() + 0.5) == dataIndex / 2, "interpolation");
    }
    
    xsFreeArray(data);
}

inline void testFFTs()
{
    // Setup
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);    
    
    // Test xsNextPowerOfTwo()
    performTest(xsNextPowerOfTwo(100) == 128, "xsNextPowerOfTwo() #1");
    performTest(xsNextPowerOfTwo(128) == 128, "xsNextPowerOfTwo() #2");
    performTest(xsNextPowerOfTwo(129) == 256, "xsNextPowerOfTwo() #3");
    
    // Test xsAllocArray()
    xsComplex *data = xsAllocArray(rawData, dataLength);
    for (unsigned long index = 0; index < dataLength; ++index) {
        performTest(*(data + index) == xsComplex(index, 0.0), "xsAllocArray() tests");
    }
    
    // Test xsCoerceDataRadix2
    data = xsCoerceDataRadix2(data, &dataLength);
    performTest(dataLength == 128, "xsCoerceDataRadix2 new data size");
    for (unsigned long index = 0; index < dataLength; ++index) {
        if (index < 100) {
            performTest(*(data + index) == xsComplex(index, 0.0), "xsCoerceDataRadix2 new data original section");
        } else {
            performTest(*(data + index) == 0.0, "xsCoerceDataRadix2 new data padded section");
        }
    }
    
    xsFreeArray(data);
        
    // Interpolation
    _testInterpolation();
    
    cout << "FFT functions tested and correct." << endl;
}
