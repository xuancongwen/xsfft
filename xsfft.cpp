#include <math.h>

#include "xsfft.h"

const double xsPI = 3.14159265358979323846;

// Private functions

void _xsFormatInput(xsComplex *const data, const long dataLength);
void _xsFFTHelper(xsComplex *const data, const long dataLength);
void _xsIFFTHelper(xsComplex *const data, const long dataLength);
void _xsScaleIFFT(xsComplex *const data, const long dataLength);


// Public method implementations

long xsNextPowerOfTwo(long value)
{
    long nextPowerOfTwo = 1;
    while (nextPowerOfTwo < value) {
        nextPowerOfTwo <<= 1;
    }
    
    return nextPowerOfTwo;
}

bool xsFFT(xsComplex *const data, const long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return false;
    }
    
	_xsFormatInput(data, dataLength);
	_xsFFTHelper(data, dataLength);
    
	return true;
}

bool xsIFFT(xsComplex *const data, const long dataLength)
{
	if (!data || dataLength < 1 || dataLength & (dataLength - 1)) {
        return false;
    }
    
	_xsFormatInput(data, dataLength);
	_xsIFFTHelper(data, dataLength);
	_xsScaleIFFT(data, dataLength);
    
	return true;
}


// Private method implementations

void _xsFormatInput(xsComplex *const data, const long dataLength)
{
	long target = 0;
	for (unsigned int dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
		if (target > dataIndex) {
			xsComplex temp(*(data + target));
			*(data + target) = *(data + dataIndex);
			*(data + dataIndex) = temp;
		}
		long targetBitMask = dataLength;

		while (target & (targetBitMask >>= 1)) {
			target &= targetBitMask;
        }
		target |= targetBitMask;
	}
}

void _xsFFTHelper(xsComplex *const data, const long dataLength)
{
	//   Perform butterflies...
	for (long step = 1; step < dataLength; step <<= 1) {
		//   Jump to the next entry of the same transform factor
		long Jump = step << 1;
		//   Angle increment
		double delta = xsPI / double(step);
		//   Auxiliary sin(delta / 2)
		double Sine = sin(delta * .5);
		//   Multiplier for trigonometric recurrence
		xsComplex Multiplier(-2.0 * Sine * Sine, sin(delta));
		//   Start value for transform factor, fi = 0
		xsComplex Factor(1.0);
		//   Iteration through groups of different transform factor
		for (long Group = 0; Group < step; ++Group) {
			//   Iteration within group 
			for (long Pair = Group; Pair < dataLength; Pair += Jump) {
				//   Match position
				long Match = Pair + step;
				//   Second term of two-point transform
				xsComplex Product(Factor * data[Match]);
				//   Transform for fi + pi
				data[Match] = data[Pair] - Product;
				//   Transform for fi
				data[Pair] += Product;
			}
			//   Successive transform factor via trigonometric recurrence
			Factor = Multiplier * Factor + Factor;
		}
	}
}

void _xsIFFTHelper(xsComplex *const data, const long dataLength)
{
    //   Perform butterflies...
	for (long step = 1; step < dataLength; step <<= 1) {
		//   Jump to the next entry of the same transform factor
		long Jump = step << 1;
		//   Angle increment
		double delta = -xsPI / double(step);
		//   Auxiliary sin(delta / 2)
		double Sine = sin(delta * .5);
		//   Multiplier for trigonometric recurrence
		xsComplex Multiplier(-2.0 * Sine * Sine, sin(delta));
		//   Start value for transform factor, fi = 0
		xsComplex Factor(1.0);
		//   Iteration through groups of different transform factor
		for (long Group = 0; Group < step; ++Group) {
			//   Iteration within group 
			for (long Pair = Group; Pair < dataLength; Pair += Jump) {
				//   Match position
				unsigned int Match = Pair + step;
				//   Second term of two-point transform
				xsComplex Product(Factor * data[Match]);
				//   Transform for f_i + p_i
				data[Match] = data[Pair] - Product;
				//   Transform for fi
				data[Pair] += Product;
			}
			//   Successive transform factor via trigonometric recurrence
			Factor = Multiplier * Factor + Factor;
		}
	}
}

//   Scaling of inverse FFT result
void _xsScaleIFFT(xsComplex *const data, const long dataLength)
{
	const double scaleFactor = 1.0 / double(dataLength);
	//   Scale all data entries
	for (long dataPosition = 0; dataPosition < dataLength; ++dataPosition) {
        *(data + dataPosition) *= scaleFactor;
    }
}
