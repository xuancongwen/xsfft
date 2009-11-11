/* 
 This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
 elements.  This function does not care how many elements are in the input file.
 */

#include <iostream>
#include <assert.h>

#include "xsfft.h"

using namespace std;

inline void testComplexNumbers();
inline void testFFTs();

int main(int argc, char *argv[])
{
    testComplexNumbers();
    testFFTs();
    
    cout << "All tests passed!" << endl;
    
    return 0;
}

inline void testComplexNumbers()
{
    // Test constructors
    assert(xsComplex().real() == 0.0 && xsComplex().imaginary() == 0.0);
    assert(xsComplex(1.0).real() == 1.0 && xsComplex(1.0).imaginary() == 0.0);
    assert(xsComplex(2.0, 3.0).real() == 2.0 && xsComplex(2.0, 3.0).imaginary() == 3.0);
    
    // Test ==
    xsComplex test = 5;
    assert(test == xsComplex(5.0, 0.0));
    assert(test == 5.0);
    assert(5.0 == test);
    
    // Test !=
    assert(test != xsComplex(5.0, 1.0));
    assert(test != 4.0);
    assert(4.0 != test);
    
    // Test magnitude()
    assert(xsComplex(3.0, 4.0).magnitude() == 5.0);
    assert(xsComplex(-3.0, 4.0).magnitude() == 5.0);
    assert(xsComplex(4.0, -3.0).magnitude() == 5.0);
    assert(xsComplex(-4.0, -3.0).magnitude() == 5.0);
    
    // Test norm()
    assert(xsComplex(1.0, 2.0).norm() == 5.0);
    assert(xsComplex(-1.0, 2.0).norm() == 5.0);
    
    // Test complex conjugal visits
    // ...I mean, conjugate()
    assert(xsComplex(1.0, 1.0).conjugate() == xsComplex(1.0, -1.0));
    assert(xsComplex(1.0, -1.0).conjugate() == xsComplex(1.0, 1.0));
    assert(xsComplex(-1.0, -1.0).conjugate() == xsComplex(-1.0, 1.0));

    // Test =
    assert(test == xsComplex(5.0, 0.0));
    
    // Test set()
    test.set(6.0, 9.0);
    assert(test == xsComplex(6.0, 9.0));
    
    // Test setReal()
    test.setReal(4.0);
    assert(test.real() == 4.0);
    
    // Test setImaginary()
    test.setImaginary(5.0);
    assert(test.imaginary() == 5.0);
    
    // Test +
    test.set(1.0, 1.0);
    xsComplex result = test + xsComplex(2.0, 2.0);
    assert(result == xsComplex(3.0, 3.0));
    
    result = test + 3;
    assert(result == xsComplex(4.0, 1.0));
    
    result = 4 + test;
    assert(result == xsComplex(5.0, 1.0));
    
    // Test -
    result = test - xsComplex(2.0, 2.0);
    assert(result == xsComplex(-1.0, -1.0));
    
    result = test - 2.0;
    assert(result == xsComplex(-1.0, 1.0));
    
    result = 1 - test;
    assert(result == xsComplex(0.0, -1.0));
    
    // Test *
    result = test * xsComplex(1.0, 1.0);
    assert(result == xsComplex(0.0, 2.0));
    
    result = test * 3.0;
    assert(result == xsComplex(3.0, 3.0));
    
    result = -3.0 * test;
    assert(result == xsComplex(-3.0, -3.0));
    
    // Test /
    result = test / xsComplex(1.0, 1.0);
    assert(result == xsComplex(1.0, 0.0));
    
    result = test / 2;
    assert(result == xsComplex(0.5, 0.5));
    
    result = 5 / test;
    assert(result == xsComplex(2.5, -2.5));
    
    // Test +=
    test.set(1.0, 1.0);
    result.set(3.0, 6.0);
    result += test;
    assert(result == xsComplex(4.0, 7.0));
    
    result += 3;
    assert(result == xsComplex(7.0, 7.0));
    
    // Test -=
    result -= test;
    assert(result == xsComplex(6.0, 6.0));
    
    result -= 3;
    assert(result == xsComplex(3.0, 6.0));
    
    // Test *=
    result *= test;
    assert(result == xsComplex(-3.0, 9.0));
    
    result *= 2;
    assert(result == xsComplex(-6, 18));
    
    // Test /=
    result /= test;
    assert(result == xsComplex(6, 12));
    
    result /= 6;
    assert(result == xsComplex(1, 2));
    
    cout << "Complex numbers tested and correct." << endl;
}

inline void testFFTs()
{
    
}
