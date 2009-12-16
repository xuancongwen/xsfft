#include <math.h>
#include <stdlib.h>
#include "xsfft.h"

// Private functions

void _xsFormatInput(xsComplex *data, const unsigned long dataLength);
void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI);
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength);
xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength);


// Complex array creation/destruction

xsComplex *xsAllocArrayDouble(double *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = *(data + dataIndex);
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

xsComplex *xsAllocArrayFloat(float *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = (double)(*(data + dataIndex));
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

xsComplex *xsAllocArrayLong(long *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = (double)(*(data + dataIndex));
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

xsComplex *xsAllocArrayInt(int *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = (double)(*(data + dataIndex));
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

xsComplex *xsAllocArrayShort(short *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = (double)(*(data + dataIndex));
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

xsComplex *xsAllocArrayChar(char *data, unsigned long dataLength)
{
    xsComplex *newData = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        (newData + dataIndex)->real = (double)(*(data + dataIndex));
        (newData + dataIndex)->imaginary = 0.0;
    }
    
    return newData;
}

void xsFreeArray(xsComplex *data)
{
    free(data);
    data = NULL;
}


// Public method implementations

unsigned long xsNextPowerOfTwo(const unsigned long value)
{
    if (!(value & (value - 1))) {
        return value;
    }
    
    unsigned long nextPowerOfTwo = 1;
    while (nextPowerOfTwo < value) {
        nextPowerOfTwo <<= 1;
    }
    
    return nextPowerOfTwo;
}

xsComplex *xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength)
{
    unsigned long newLength = xsNextPowerOfTwo(*dataLength);
    if (newLength == *dataLength) {
        return data;
    }
    
    data = (xsComplex *)realloc(data, sizeof(xsComplex) * newLength);
    for (unsigned long index = *dataLength; index < newLength; ++index) {
        (data + index)->real = 0.0;
        (data + index)->imaginary = 0.0;
    }
    
    *dataLength = newLength;
    
    return data;
}

int xsFFT(xsComplex *data, const unsigned long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return 0;
    }
    
	_xsFormatInput(data, dataLength);
    _xsTransformHelper(data, dataLength, -xsPI);
    
	return 1;
}

int xsIFFT(xsComplex *data, const unsigned long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return 0;
    }
    
	_xsFormatInput(data, dataLength);
    _xsTransformHelper(data, dataLength, xsPI);
	_xsScaleIFFT(data, dataLength);
    
	return 1;
}


// Useful functions that utilize FFTs

xsComplex *xsInterpolateWithFactor2(xsComplex *data, unsigned long *dataLength)
{
    // Setup
    xsCoerceDataRadix2(data, dataLength);
    unsigned long oldLength = *dataLength;
    unsigned long newLength = oldLength << 1;
    
    // FFT
    xsFFT(data, oldLength);
    
    // Zero pad
    data = (xsComplex *)realloc(data, sizeof(xsComplex) * newLength);
    
    unsigned long rightHalfFirstIndex = 3 * oldLength / 2;
    unsigned long zeroPadFirstIndex = oldLength / 2;
    
    xsComplex center = *(data + zeroPadFirstIndex);
    (data + zeroPadFirstIndex)->real = center.real / 2.0;
    (data + zeroPadFirstIndex)->imaginary = center.imaginary / 2.0;
    
    (data + rightHalfFirstIndex)->real = center.real / 2.0;
    (data + rightHalfFirstIndex)->imaginary = center.imaginary / 2.0;
    
    for (unsigned long zeroPadIndex = 1; zeroPadIndex < oldLength / 2; ++zeroPadIndex) {
        *(data + rightHalfFirstIndex + zeroPadIndex) = *(data + zeroPadFirstIndex + zeroPadIndex);
        (data + zeroPadFirstIndex + zeroPadIndex)->real = 0.0;
        (data + zeroPadFirstIndex + zeroPadIndex)->imaginary = 0.0;
    }
    
    *dataLength = newLength;
    
    // Power has been halved at this point, we need to scale
    for (unsigned long index = 0; index < newLength; ++index) {
        (data + index)->real *= 2.0;
        (data + index)->imaginary *= 2.0;
    }
    
    // IFFT
    xsIFFT(data, newLength);
    
    return data;
}


// Private method implementations

void _xsFormatInput(xsComplex *data, const unsigned long dataLength)
{
	unsigned long target = 0;
	for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
		if (target > dataIndex) {
			xsComplex temp = *(data + target);
            *(data + target) = *(data + dataIndex);
			*(data + dataIndex) = temp;
		}
        
		unsigned long targetBitMask = dataLength;

		while (target & (targetBitMask >>= 1)) {
			target &= ~targetBitMask;
        }
		target |= targetBitMask;
	}
}

void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI)
{
    //   Perform butterflies...
	for (unsigned long step = 1; step < dataLength; step <<= 1) {
		double sine = sin(signedPI / (double)step * 0.5);
		xsComplex twiddleMultiplier = xsComplexFromComponents(-2.0 * sine * sine, sin(signedPI / (double)step));
		xsComplex twiddleFactor = xsComplexFromReal(1.0);
		for (unsigned long group = 0; group < step; ++group) {
			for (unsigned long pair = group; pair < dataLength; pair += (step << 1)) {
				unsigned long match = pair + step;
				xsComplex product = xsComplexProduct(twiddleFactor, *(data + match));
				*(data + match) = xsComplexDifference(*(data + pair), product);
                *(data + pair) = xsComplexSum(*(data + pair), product);
			}
            
			twiddleFactor = xsComplexSum(xsComplexProduct(twiddleMultiplier, twiddleFactor), twiddleFactor);
		}
	}
}

xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength)
{
    xsComplex *reversedCopy = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long index = 0; index < dataLength; ++index) {
        *(reversedCopy + (dataLength - index) - 1) = *(data + index);
    }
    
    return reversedCopy;
}


//   Scaling of inverse FFT result
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength)
{
	const double scaleFactor = 1.0 / (double)dataLength;
	//   Scale all data entries
	for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        *(data + dataIndex) = xsComplexScale(*(data + dataIndex), scaleFactor);
    }
}
