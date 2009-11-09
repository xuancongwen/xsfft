// This implementation of xsComplex is based on LibRow's implementation.
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
// 2 array.
///////////////////////////////////////////
void xsCoerceDataRadix2(xsComplex *data, long *dataLength);

////////////////////////////////////////////////
//     data         - both input data and output
//     dataLength   - length of input data
////////////////////////////////////////////////
bool xsFFT(xsComplex *data, const long dataLength);

//////////////////////////////////////////////////////////
// INVERSE FOURIER TRANSFORM
//     data         - both input data and output
//     dataLength   - length of both input data and result
//
//     The result is always scaled
//////////////////////////////////////////////////////////
bool xsIFFT(xsComplex *data, const long dataLength);

#endif
