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

// Find the next power of two for a given number

unsigned long xsNextPowerOfTwo(const unsigned long value);

// Ensure power of 2 number of input

void xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength);

// FFT and IFFT

bool xsFFT(xsComplex *data, const unsigned long dataLength);
bool xsIFFT(xsComplex *data, const unsigned long dataLength);

// Useful functions that utilize FFTs

void xsInterpolateWithFactor2(xsComplex *data, unsigned long *dataLength); // Upsamples to the next power of two elements

#endif
