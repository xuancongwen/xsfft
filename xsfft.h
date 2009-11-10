// The implementation of the Cooley-Tukey FFT is based on LibRow's implementation.
// See the original source here:
//
//      http://www.librow.com/articles/article-10
//
// The original code has been extensively modified.  For minimal memory use,
// xsFFT only supports in-place algorithms.

#ifndef XS_FFT
#define XS_FFT

#include "xscomplex.h"

extern const double xsPI;

///////////////////////////////////////////
// For a given value, find the next highest
// power of two
///////////////////////////////////////////
long xsNextPowerOfTwo(const long value);

///////////////////////////////////////////
// Coerces the incoming array into a radix
// 2 array in place.
///////////////////////////////////////////
void xsCoerceDataRadix2(xsComplex *data, long *dataLength);

////////////////////////////////////////////////
// FORWARD FAST FOURIER TRANSFORM
//     Performs the FFT in place.
////////////////////////////////////////////////
bool xsFFT(xsComplex *data, const long dataLength);

//////////////////////////////////////////////////////////
// INVERSE FAST FOURIER TRANSFORM
//     Perform the FFT in place.
//
//     The result is always scaled
//////////////////////////////////////////////////////////
bool xsIFFT(xsComplex *data, const long dataLength);

////////////////////////////////////////////////////
// Uses FFT interpolation to
// produce an upsampled data array in place.
// Each call will scale the number of data points
// up by a factor of 2.
////////////////////////////////////////////////////
void xsUpSample(xsComplex *data, long *dataLength);

#endif
