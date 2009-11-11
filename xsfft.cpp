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


// Private method implementations

void _xsFormatInput(xsComplex *data, const unsigned long dataLength)
{
	unsigned long target = 0;
	for (unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
		if (target > dataIndex) {
			xsComplex temp((data + target)->real(), (data + target)->imaginary());
            (data + target)->set((data + dataIndex)->real(), (data + dataIndex)->imaginary());
			(data + dataIndex)->set(temp.real(), temp.imaginary());
		}
        
		unsigned long targetBitMask = dataLength;

		while (target & (targetBitMask >>= 1)) {
			target &= targetBitMask;
        }
		target |= targetBitMask;
	}
}

void _xsTransformHelper(xsComplex *data, const unsigned long dataLength, const double signedPI)
{
    //   Perform butterflies...
	for (unsigned long step = 1; step < dataLength; step <<= 1) {
		double Sine = sin(signedPI / double(step) * 0.5);
		//   Twiddle Constant
		xsComplex twiddleMultiplier(-2.0 * Sine * Sine, sin(signedPI / double(step)));
		//   Start value for transform factor
		xsComplex twiddleFactor(1.0);
		//   Iteration through groups of different transform factor
		for (unsigned long Group = 0; Group < step; ++Group) {
			//   Iteration within group 
			for (unsigned long Pair = Group; Pair < dataLength; Pair += (step << 1)) {
				//   Match position
				unsigned long Match = Pair + step;
				//   Second term of two-point transform
				xsComplex Product(twiddleFactor * data[Match]);
				//   Transform for fi + pi
				data[Match] = data[Pair] - Product;
				//   Transform for fi
				data[Pair] += Product;
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
	for (unsigned long dataPosition = 0; dataPosition < dataLength; ++dataPosition) {
        *(data + dataPosition) *= scaleFactor;
    }
}
