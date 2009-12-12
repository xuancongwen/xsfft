#include <math.h>
#include "xscomplex.h"

// Comparison

int xsComplexEqual(const xsComplex lhs, const xsComplex rhs)
{
    return lhs.real == rhs.real && lhs.imaginary == rhs.imaginary;
}

//  Computed Values

xsComplex xsComplexConjugate(const xsComplex complex)
{
    xsComplex conjugate;
    conjugate.real = complex.real;
    conjugate.imaginary = -complex.imaginary;
    return conjugate;
}

double xsComplexNorm(const xsComplex complex)
{
    return complex.real * complex.real + complex.imaginary * complex.imaginary;
}

double xsComplexMagnitude(const xsComplex complex)
{
    return sqrt(xsComplexNorm(complex));
}

// Commutative operations

xsComplex xsComplexSum(const xsComplex lhs, const xsComplex rhs)
{
    xsComplex sum;
    sum.real = lhs.real + rhs.real;
    sum.imaginary = lhs.imaginary + rhs.imaginary;
    return sum;
}

xsComplex xsComplexProduct(const xsComplex lhs, const xsComplex rhs)
{
    xsComplex product;
    product.real = lhs.real * rhs.real - lhs.imaginary * rhs.imaginary;
    product.imaginary = lhs.real * rhs.imaginary + lhs.imaginary * rhs.real;
    return product;
}

// Non-Commutative operations

xsComplex xsComplexDifference(const xsComplex minuend, const xsComplex subtrahend)
{
    xsComplex difference;
    difference.real = minuend.real - subtrahend.real;
    difference.imaginary = minuend.imaginary - minuend.imaginary;
    return difference;
}

xsComplex xsComplexQuotient(const xsComplex dividend, const xsComplex divisor)
{
    const double denominator = divisor.real * divisor.real + divisor.imaginary * divisor.imaginary;
    xsComplex quotient;
    quotient.real = (dividend.real * divisor.real + dividend.imaginary * divisor.imaginary) / denominator;
    quotient.imaginary = (dividend.imaginary * divisor.real - dividend.real * divisor.imaginary) / denominator;
    return quotient;
}
