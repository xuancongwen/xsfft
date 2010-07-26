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

xsComplex *xsAllocArrayDouble(double *data, unsigned long dataLength);
xsComplex *xsAllocArrayFloat(float *data, unsigned long dataLength);
xsComplex *xsAllocArrayLong(long *data, unsigned long dataLength);
xsComplex *xsAllocArrayInt(int *data, unsigned long dataLength);
xsComplex *xsAllocArrayShort(short *data, unsigned long dataLength);
xsComplex *xsAllocArrayChar(char *data, unsigned long dataLength);

void xsFreeArray(xsComplex *data);

// Find the next power of two for a given number

unsigned long xsNextPowerOfTwo(const unsigned long value);

// Ensure power of 2 number of input

xsComplex *xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength);

// FFT and IFFT

int xsFFT(xsComplex *data, const unsigned long dataLength, const unsigned long maxFrequency);
int xsIFFT(xsComplex *data, const unsigned long dataLength, const unsigned long maxFrequency);

// Useful functions that utilize FFTs

xsComplex *xsInterpolateWithFactor2(xsComplex *data, unsigned long *dataLength);

#endif
