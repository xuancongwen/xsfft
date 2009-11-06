#include <stdlib.h>

#include "xsfft.h"
#include "xscomplex.h"

#define xsPI 3.14159265358979323846

// Private functions

long _xsNextPowerOfTwo(long value);

template <class T>
long _xsCoerceRad2Input(T *elements, long numberOfElements);

template <class T>
void _xsFFTRecursive(xsComplex<T> inElements[], long inNumberOfElements, xsComplex<T>  outFrequencyComponents[]);

template <class T>
void _xsCoerceComplex(T *inElements, long inNumberOfElements, xsComplex<T> *outElements);

// Public Method Implementations

bool xsShortFFT(short *inElements, long inNumberOfElements, short *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }

    _xsCoerceRad2Input<short>(inElements, inNumberOfElements);
    //_xsCoerceComplex();
    //_xsFFTRecursive();

    return true;
}

// Private Method Implementation

long _xsNextPowerOfTwo(long value)
{
    long nextPowerOfTwo = 1;
    while (nextPowerOfTwo < value) {
        nextPowerOfTwo <<= 1;
    }

    return nextPowerOfTwo;
}

template <class T>
long _xsCoerceRad2Input(T *elements, long numberOfElements)
{
    long idealNumberOfElements = _xsNextPowerOfTwo(numberOfElements);
    elements = (short *)realloc(elements, idealNumberOfElements);

    for (long newIndex = numberOfElements; newIndex < idealNumberOfElements; ++newIndex) {
        *(elements + newIndex) = (T)0;
    }

    return idealNumberOfElements;
}

template <class T>
void _xsCoerceComplex(T *inElements, long inNumberOfElements, xsComplex<T> *outElements)
{
    // outElements is already allocated, and MUST be the same size as inNumberOfElements
    for (long index = 0; index < inNumberOfElements; ++index) {
        *(outElements + index) = new xsComplex<T>(*(inElements + index), (T)0);
    }
}

template <class T>
void _xsFFTRecursive(xsComplex<T> *inElements, long inNumberOfElements, xsComplex<T> *outFrequencyComponents[])
{
    if (inNumberOfElements == 1) {
        outFrequencyComponents = inElements;
        return;
    }
    
    xsComplex<T> *evenElements = (xsComplex<T> *)calloc(inNumberOfElements / 2, sizeof(xsComplex<T>));
    xsComplex<T> *oddElements = (xsComplex<T> *)calloc(inNumberOfElements / 2, sizeof(xsComplex<T>));
    for (long index = 0; index < inNumberOfElements / 2; ++index) {
        *(evenElements + index) = *(inElements + (index * 2));
        *(oddElements + index) = *(inElements + (index * 2) + 1);
    }

    xsComplex<T> *evenFrequencyComponents;
    _xsFFTRecursive(evenElements, inNumberOfElements / 2, evenFrequencyComponents);

    xsComplex<T> *oddFrequencyComponents;
    _xsFFTRecursive(oddElements, inNumberOfElements / 2, oddFrequencyComponents);

    free(evenElements);
    free(oddElements);

    xsComplex<double> twiddleConstant;
    twiddleConstant.initWithEulerIdentity(2.0 * xsPI / (double)inNumberOfElements);
    
    xsComplex<double> twiddleFactor(1.0, 0.0);
    for (long frequencyIndex = 0; frequencyIndex < inNumberOfElements / 2; ++frequencyIndex) {
        *(outFrequencyComponents + frequencyIndex) = *(evenFrequencyComponents + frequencyIndex) + twiddleFactor * (*(oddFrequencyComponents + frequencyIndex));
        *(outFrequencyComponents + frequencyIndex + inNumberOfElements / 2) = *(evenFrequencyComponents + frequencyIndex) - twiddleFactor * (*(oddFrequencyComponents + frequencyIndex));
        twiddleFactor *= twiddleConstant;
    }
}
