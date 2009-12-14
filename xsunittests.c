/* 
 This contains testing for xsComplex and xsFFT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "xsfft.h"

// Private methods to be tested

void _xsFormatInput(xsComplex *data, const unsigned long dataLength);
void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI);
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength);
xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength);


// Function prototypes

void testComplexNumbers();
void testFFTs();
void performTest(int test, const char *testBehavior);


// Program entrypoint

int main(int argc, char *argv[])
{
    testComplexNumbers();
    testFFTs();
    
    puts("All test passed!\n");
    
    return 0;
}


// Test helper

void performTest(int test, const char *testBehavior)
{
    printf("Testing %s...", testBehavior);
    assert(test);
    puts("PASSED!");
}


// Test implementations

void testComplexNumbers()
{
    puts("[Complex Number Test]\n");
    
    // Test initialization
    xsComplex c1 = xsComplexCreate();
    xsComplex c2;
    xsComplex c3;
    performTest(c1.real == 0.0 && c1.imaginary == 0.0, "xsComplexCreate");
    c1 = xsComplexFromComponents(1.0, 2.0);
    performTest(c1.real == 1.0 && c1.imaginary == 2.0, "xsComplexFromComponents");
    c1 = xsComplexFromReal(5.0);
    performTest(c1.real == 5.0 && c1.imaginary == 0.0, "xsComplexFromReal");
    c1 = xsComplexFromImaginary(5.0);
    performTest(c1.real == 0.0 && c1.imaginary == 5.0, "xsComplexFromImaginary");
    c2 = xsComplexFromPolar(5.0, 0.523598775598299);
    performTest(c2.real > 4.330126 && c2.real < 4.330128 && c2.imaginary > 2.499999 && c2.imaginary < 2.500001, "xsComplexFromPolar");
    c2 = xsComplexCreate();
    c1 = xsComplexFromComplex(c2);
    performTest(c1.real == 0.0 && c1.imaginary == 0.0, "xsComplexFromComplex");
    
    // Test comparison
    c1 = xsComplexFromComponents(1.0, 2.0);
    c2 = xsComplexFromComponents(1.0, -2.0);
    c3 = xsComplexCreate();
    performTest(xsComplexEqual(c1, c1), "Equality");
    performTest(!xsComplexEqual(c1, c2), "In-equality");
    
    // Test computed values
    performTest(xsComplexEqual(xsComplexConjugate(c1), c2), "Complex conjugate");
    performTest(xsComplexNorm(c1) == 5.0, "Norm");
    c1.real = 3.0;
    c1.imaginary = 4.0;
    performTest(xsComplexMagnitude(c1) == 5.0, "Magnitude");
    
    // Test addition
    c2.real = 6.0;
    c2.imaginary = 8.0;
    c3 = xsComplexSum(c1, c1);
    performTest(xsComplexEqual(c3, c2), "Sum");
    
    // Test multiplication
    c1.real = 2.0;
    c1.imaginary = 3.0;
    c2.real = -5.0;
    c2.imaginary = 12.0;
    c3 = xsComplexProduct(c1, c1);
    performTest(xsComplexEqual(c3, c2), "Multiplication");
    
    // Test subtraction
    c1.real = 40.0;
    c1.imaginary = 40.0;
    c2.real = 0.0;
    c2.imaginary = 0.0;
    performTest(xsComplexEqual(xsComplexDifference(c1, c1), c2), "Subtraction");
    
    // Test division
    c1.real = 5.0;
    c1.imaginary = 0.0;
    c2.real = 1.0;
    c2.imaginary = 1.0;
    c1 = xsComplexQuotient(c1, c2);
    c3.real = 2.5;
    c3.imaginary = -2.5;
    performTest(xsComplexEqual(c1, c3), "Division");
    
    puts("Complex numbers tested and correct.\n");
}

void _testInterpolation()
{
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);
    xsComplex *data = xsAllocArrayInt(rawData, dataLength);
    free(rawData);
    
    puts("[Interpolation Tests]\n");
    
    data = xsInterpolateWithFactor2(data, &dataLength);
    for(unsigned long dataIndex = 0; dataIndex < 100; dataIndex += 2) {
        performTest((unsigned long)((data + dataIndex)->real + 0.5) == dataIndex / 2, "interpolation");
    }
    
    xsFreeArray(data);
}

void testFFTs()
{
    // Setup
    puts("[FFT Tests]\n");
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);    
    
    // Test xsNextPowerOfTwo()
    performTest(xsNextPowerOfTwo(100) == 128, "xsNextPowerOfTwo() #1");
    performTest(xsNextPowerOfTwo(128) == 128, "xsNextPowerOfTwo() #2");
    performTest(xsNextPowerOfTwo(129) == 256, "xsNextPowerOfTwo() #3");
    
    // Test xsAllocArray()
    xsComplex *data = xsAllocArrayInt(rawData, dataLength);
    for (unsigned long index = 0; index < dataLength; ++index) {
        xsComplex testAgainst = xsComplexFromReal(index);
        performTest(xsComplexEqual(*(data + index), testAgainst), "xsAllocArray() tests");
    }
    
    // Test xsCoerceDataRadix2
    data = xsCoerceDataRadix2(data, &dataLength);
    performTest(dataLength == 128, "xsCoerceDataRadix2 new data size");
    for (unsigned long index = 0; index < dataLength; ++index) {
        xsComplex comparator = xsComplexCreate();
        if (index < 100) {
            comparator = xsComplexFromReal(index);
        }
        performTest(xsComplexEqual(*(data + index), comparator), "xsCoerceDataRadix2 new data padded section");
    }
    
    xsFreeArray(data);
        
    // Interpolation
    _testInterpolation();
    
    puts("FFT functions tested and correct.");
}
