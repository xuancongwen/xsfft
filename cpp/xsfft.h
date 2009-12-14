// The implementation of the Cooley-Tukey FFT is based on LibRow's implementation.
// See the original source here:
//
//      http://www.librow.com/articles/article-10
//
// The original code has been extensively modified.  For minimal memory use,
// xsFFT only supports in-place algorithms.

#ifndef XS_FFT
#define XS_FFT

#define xsPI 3.14159265358979323846

#include "xscomplex.h"

// Complex array creation/destruction

xsComplex *xsAllocArray(double *data, unsigned long dataLength);
xsComplex *xsAllocArray(float *data, unsigned long dataLength);
xsComplex *xsAllocArray(long *data, unsigned long dataLength);
xsComplex *xsAllocArray(int *data, unsigned long dataLength);
xsComplex *xsAllocArray(short *data, unsigned long dataLength);
xsComplex *xsAllocArray(char *data, unsigned long dataLength);

void xsFreeArray(xsComplex *data);

// Find the next power of two for a given number

unsigned long xsNextPowerOfTwo(const unsigned long value);

// Ensure power of 2 number of input

xsComplex *xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength);

// FFT and IFFT

bool xsFFT(xsComplex *data, const unsigned long dataLength);
bool xsIFFT(xsComplex *data, const unsigned long dataLength);

// Useful functions that utilize FFTs

xsComplex *xsInterpolateWithFactor2(xsComplex *data, unsigned long *dataLength);

#endif
