#include <math.h>
#include <stdlib.h>

#include "xsfft.h"

// Private functions

void _xsFormatInput(xsComplex *data, const unsigned long dataLength);
void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI);
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength);
xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength);


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

void xsCoerceDataRadix2(xsComplex *data, unsigned long *dataLength)
{
    unsigned long newLength = xsNextPowerOfTwo(*dataLength);
    if (newLength == *dataLength) {
        return;
    }
    
    data = (xsComplex *)realloc(data, sizeof(xsComplex) * newLength);
    xsComplex *dataIterator = (data + *dataLength);
    for (unsigned long index = *dataLength; index < newLength; ++index, ++dataIterator) {
        dataIterator->set(0.0, 0.0);
    }
    
    *dataLength = newLength;
}

bool xsFFT(xsComplex *data, const unsigned long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return false;
    }
    
	_xsFormatInput(data, dataLength);
    _xsTransformHelper(data, dataLength, -xsPI);
    
	return true;
}

bool xsIFFT(xsComplex *data, const unsigned long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return false;
    }
    
	_xsFormatInput(data, dataLength);
    _xsTransformHelper(data, dataLength, xsPI);
	_xsScaleIFFT(data, dataLength);
    
	return true;
}


// Useful functions that utilize FFTs

void xsInterpolateWithFactor2(xsComplex *data, unsigned long *dataLength)
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
    
    xsComplex center(*(data + zeroPadFirstIndex));
    *(data + zeroPadFirstIndex) = center / 2.0;
    *(data + rightHalfFirstIndex) = center / 2.0;
    
    for (unsigned long zeroPadIndex = 1; zeroPadIndex < oldLength / 2; ++zeroPadIndex) {
        *(data + rightHalfFirstIndex + zeroPadIndex) = *(data + zeroPadFirstIndex + zeroPadIndex);
        (data + zeroPadFirstIndex + zeroPadIndex)->set(0.0, 0.0);
    }
    
    *dataLength = newLength;
    
    // Power has been halved at this point, we need to scale
    for (unsigned long index = 0; index < newLength; ++index) {
        *(data + index) *= 2.0;
    }
    
    // IFFT
    xsIFFT(data, newLength);
}


// Private method implementations

void _xsFormatInput(xsComplex *data, const unsigned long dataLength)
{
	unsigned long target = 0;
	for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
		if (target > dataIndex) {
			xsComplex temp((data + target)->real(), (data + target)->imaginary());
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
		double sine = sin(signedPI / double(step) * 0.5);
		xsComplex twiddleMultiplier(-2.0 * sine * sine, sin(signedPI / double(step)));
		xsComplex twiddleFactor(1.0);
		for (unsigned long group = 0; group < step; ++group) {
			for (unsigned long pair = group; pair < dataLength; pair += (step << 1)) {
				unsigned long match = pair + step;
				xsComplex product(twiddleFactor * *(data + match));
				*(data + match) = *(data + pair) - product;
				*(data + pair) += product;
			}
            
			twiddleFactor = twiddleMultiplier * twiddleFactor + twiddleFactor;
		}
	}
}

xsComplex *_xsReverseCopy(xsComplex *data, const unsigned long dataLength)
{
    xsComplex *reversedCopy = (xsComplex *)calloc(dataLength, sizeof(xsComplex));
    
    for (unsigned long index = 0; index < dataLength; ++index) {
        (reversedCopy + (dataLength - index) - 1)->set((data + index)->real(), (data+index)->imaginary());
    }
    
    return reversedCopy;
}


//   Scaling of inverse FFT result
void _xsScaleIFFT(xsComplex *data, const unsigned long dataLength)
{
	const double scaleFactor = 1.0 / double(dataLength);
	//   Scale all data entries
	for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        *(data + dataIndex) *= scaleFactor;
    }
}
