// This implementation of xsComplex is based on LibRow's implementation.
// See the original source here:
//
//      http://www.librow.com/articles/article-10
//
// The original code has been extensively modified.

#ifndef XS_COMPLEX
#define XS_COMPLEX

// Data structure
typedef struct _xsComplex {
    double real;
    double imaginary;
} xsComplex;

// Initialization
xsComplex xsComplexCreate();
xsComplex xsComplexFromComponents(const double real, const double imaginary);
xsComplex xsComplexFromReal(const double real);
xsComplex xsComplexFromImaginary(const double imaginary);
xsComplex xsComplexFromPolar(const double r, const double theta);
xsComplex xsComplexFromComplex(const xsComplex complex);

// Comparison
int xsComplexEqual(const xsComplex left, const xsComplex right);

// Computed values
xsComplex xsComplexConjugate(const xsComplex complex);
double xsComplexNorm(const xsComplex complex);
double xsComplexMagnitude(const xsComplex complex);
xsComplex xsComplexScale(xsComplex complex, const double scaleFactor);

// Commutative operations
xsComplex xsComplexSum(const xsComplex left, const xsComplex right);
xsComplex xsComplexProduct(const xsComplex left, const xsComplex right);

// Non-Commutative operations
xsComplex xsComplexDifference(const xsComplex minuend, const xsComplex subtrahend);
xsComplex xsComplexQuotient(const xsComplex dividend, const xsComplex divisor);
        
#endif
