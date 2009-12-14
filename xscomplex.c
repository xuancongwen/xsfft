#include <math.h>
#include "xscomplex.h"

// Initialization

xsComplex xsComplexCreate()
{
    return xsComplexFromComponents(0.0, 0.0);
}

xsComplex xsComplexFromComponents(const double real, const double imaginary)
{
    xsComplex newComplex;
    newComplex.real = real;
    newComplex.imaginary = imaginary;
    return newComplex;
}

xsComplex xsComplexFromReal(const double real)
{
    return xsComplexFromComponents(real, 0.0);
}

xsComplex xsComplexFromImaginary(const double imaginary)
{
    return xsComplexFromComponents(0.0, imaginary);
}

xsComplex xsComplexFromPolar(const double r, const double theta)
{
    return xsComplexFromComponents(r * cos(theta), r * sin(theta));
}

xsComplex xsComplexFromComplex(const xsComplex complex)
{
    return xsComplexFromComponents(complex.real, complex.imaginary);
}

// Comparison

int xsComplexEqual(const xsComplex lhs, const xsComplex rhs)
{
    return lhs.real == rhs.real && lhs.imaginary == rhs.imaginary;
}

// Computed Values

xsComplex xsComplexConjugate(const xsComplex complex)
{
    return xsComplexFromComponents(complex.real, -complex.imaginary);
}

double xsComplexNorm(const xsComplex complex)
{
    return complex.real * complex.real + complex.imaginary * complex.imaginary;
}

double xsComplexMagnitude(const xsComplex complex)
{
    return sqrt(xsComplexNorm(complex));
}

xsComplex xsComplexScale(xsComplex complex, const double scaleFactor)
{
    return xsComplexFromComponents(complex.real * scaleFactor, complex.imaginary * scaleFactor);
}

// Commutative operations

xsComplex xsComplexSum(const xsComplex lhs, const xsComplex rhs)
{
    return xsComplexFromComponents(lhs.real + rhs.real, lhs.imaginary + rhs.imaginary);
}

xsComplex xsComplexProduct(const xsComplex lhs, const xsComplex rhs)
{
    return xsComplexFromComponents(lhs.real * rhs.real - lhs.imaginary * rhs.imaginary, lhs.real * rhs.imaginary + lhs.imaginary * rhs.real);
}

// Non-Commutative operations

xsComplex xsComplexDifference(const xsComplex minuend, const xsComplex subtrahend)
{
    return xsComplexFromComponents(minuend.real - subtrahend.real, minuend.imaginary - subtrahend.imaginary);
}

xsComplex xsComplexQuotient(const xsComplex dividend, const xsComplex divisor)
{
    const double denominator = divisor.real * divisor.real + divisor.imaginary * divisor.imaginary;
    return xsComplexFromComponents((dividend.real * divisor.real + dividend.imaginary * divisor.imaginary) / denominator, (dividend.imaginary * divisor.real - dividend.real * divisor.imaginary) / denominator);
}
