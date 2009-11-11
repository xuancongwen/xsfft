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

///////////////////////////////////////////
// For a given value, find the next highest
// power of two
///////////////////////////////////////////
unsigned long xsNextPowerOfTwo(const unsigned long value);

///////////////////////////////////////////
// Coerces the incoming array into a radix
// 2 array in place.
///////////////////////////////////////////
void xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength);

////////////////////////////////////////////////
// FORWARD FAST FOURIER TRANSFORM
//     Performs the FFT in place.
////////////////////////////////////////////////
bool xsFFT(xsComplex *data, const unsigned long dataLength);

//////////////////////////////////////////////////////////
// INVERSE FAST FOURIER TRANSFORM
//     Perform the FFT in place.
//
//     The result is always scaled
//////////////////////////////////////////////////////////
bool xsIFFT(xsComplex *data, const unsigned long dataLength);

////////////////////////////////////////////////////
// Uses FFT interpolation to
// produce an upsampled data array in place.
// Each call will scale the number of data points
// up by a factor of 2.
////////////////////////////////////////////////////
void xsUpSample(xsComplex *data, unsigned long *dataLength);

#endif
