#include <stdlib.h>

#include "xsfft.h"
#include "xscomplex.h"

const double xsPI = 3.14159265358979323846;

// Private structures

typedef struct {
    long length;
    xsComplex *data;
} xsDoubleArray;

// Private functions

xsDoubleArray _xsFormatData(double *elements, long elementsSize);
xsDoubleArray _xsFormatData(float *elements, long elementsSize);
xsDoubleArray _xsFormatData(long *elements, long elementsSize);
xsDoubleArray _xsFormatData(int *elements, long elementsSize);
xsDoubleArray _xsFormatData(short *elements, long elementsSize);
xsDoubleArray _xsFormatData(char *elements, long elementsSize);

void _xsFFTRecursive(xsComplex *inElements, long inNumberOfElements, xsComplex *outFrequencyComponents);

// Public Method Implementations

bool xsFFT(double *inElements, long inNumberOfElements, double *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
        
    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

bool xsFFT(float *inElements, long inNumberOfElements, float *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
    
    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

bool xsFFT(long *inElements, long inNumberOfElements, long *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }

    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

bool xsFFT(int *inElements, long inNumberOfElements, int *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
    
    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

bool xsFFT(short *inElements, long inNumberOfElements, short *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
    
    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

bool xsFFT(char *inElements, long inNumberOfElements, char *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
    
    xsDoubleArray formattedData = _xsFormatData(inElements, inNumberOfElements);
    
    xsComplex *outFrequencyComponentsComplex = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    _xsFFTRecursive(formattedData.data, formattedData.length, outFrequencyComponentsComplex);
    
    for(long index = 0; index < formattedData.length; ++index) {
        *(outFrequencyComponents + index) = (outFrequencyComponentsComplex + index)->magnitude();
    }
    
    free(outFrequencyComponentsComplex);
    free(formattedData.data);
    
    return true;
}

long xsNextPowerOfTwo(long value)
{
    long nextPowerOfTwo = 1;
    while (nextPowerOfTwo < value) {
        nextPowerOfTwo <<= 1;
    }
    
    return nextPowerOfTwo;
}


// Private Method Implementation

xsDoubleArray _xsFormatData(double *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

xsDoubleArray _xsFormatData(float *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

xsDoubleArray _xsFormatData(long *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

xsDoubleArray _xsFormatData(int *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

xsDoubleArray _xsFormatData(short *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

xsDoubleArray _xsFormatData(char *elements, long elementsSize)
{
    xsDoubleArray formattedData;
    formattedData.length = xsNextPowerOfTwo(elementsSize);
    formattedData.data = (xsComplex *)calloc(sizeof(xsComplex), formattedData.length);
    
    for(long index = 0; index < formattedData.length; ++index) {
        xsComplex *curElement = formattedData.data + index;
        curElement->real = *(elements + index);
        curElement->imaginary = 0.0;
    }
    
    return formattedData;
}

void _xsFFTRecursive(xsComplex *inElements, long inNumberOfElements, xsComplex *outFrequencyComponents)
{
    if (inNumberOfElements == 1) {
        *outFrequencyComponents = *inElements;
        return;
    }

    xsComplex *evenElements = (xsComplex *)calloc(inNumberOfElements / 2, sizeof(xsComplex));
    xsComplex *oddElements = (xsComplex *)calloc(inNumberOfElements / 2, sizeof(xsComplex));
    for(long index = 0; index < inNumberOfElements / 2; ++index) {
        *(evenElements + index) = *(inElements + (index * 2));
        *(oddElements + index) = *(inElements + (index * 2) + 1);
    }

    xsComplex *evenFrequencyComponents = (xsComplex *)calloc(inNumberOfElements / 2, sizeof(xsComplex));
    _xsFFTRecursive(evenElements, inNumberOfElements / 2, evenFrequencyComponents);

    xsComplex *oddFrequencyComponents = (xsComplex *)calloc(inNumberOfElements / 2, sizeof(xsComplex));
    _xsFFTRecursive(oddElements, inNumberOfElements / 2, oddFrequencyComponents);

    free(evenElements);
    free(oddElements);

    xsComplex twiddleConstant;
    twiddleConstant.initWithEulerIdentity(2.0 * xsPI / (double)inNumberOfElements);

    xsComplex twiddleFactor;
    twiddleFactor.real = 1.0;
    twiddleFactor.imaginary = 0.0;
    for(long frequencyIndex = 0; frequencyIndex < inNumberOfElements / 2; ++frequencyIndex) {
        xsComplex *lowerHalf = (outFrequencyComponents + frequencyIndex);
        xsComplex *bottomHalf = (outFrequencyComponents + frequencyIndex + inNumberOfElements / 2);
        
        xsComplex evenHalf = *(evenFrequencyComponents + frequencyIndex);
        xsComplex oddHalf = *(oddFrequencyComponents + frequencyIndex);

        *lowerHalf = evenHalf + twiddleFactor * oddHalf;
        *bottomHalf = evenHalf - twiddleFactor * oddHalf;
        
        twiddleFactor *= twiddleConstant;
    }

    free(evenFrequencyComponents);
    free(oddFrequencyComponents);
}
