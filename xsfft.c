#include "xsfft.h"

// Private functions

long _xsPadShortInput(short *elements, long numberOfElements);
long _xsNextPowerOfTwo(long value);

// Public Method Implementations

bool xsShortFFTRecursive(short *inElements, long inNumberOfElements, short *outFrequencyComponents)
{
    if (!inElements) {
        return false;
    }
    if (!outFrequencyComponents) {
        return false;
    }
    if (inNumberOfElements == 1) {
        outFrequencyComponents = inElements;
        return true;
    }

    short *evenElements = calloc(inNumberOfElements / 2, sizeof(short));
    short *oddElements = calloc(inNumberOfElements / 2, sizeof(short));
    for (long index = 0; index < inNumberOfElements / 2; ++index) {
        *(evenElements + index) = *(inElements + (index * 2));
        *(oddElements + index) = *(inElements + (index * 2) + 1);
    }

    short *evenFrequencyComponents = xsShortFFTRecursive(evenElements, inNumberOfElements / 2);
    short *oddFrequencyComponents = xsShortFFTRecursive(oddElements, inNumberOfElements / 2);
    free(evenElements);
    free(oddElements);

    //TODO: What is omega?
    //TODO: What to do with complex number?
    double omega_n = 0.0;   // How to represent this factor? e^(2*pi*j/inNumberOfElements)
    for (long frequencyIndex = 0, double omega = 1.0; frequencyIndex < inNumberOfElements / 2; ++frequencyIndex, omega *= omega_n) {
        *(outFrequencyComponents + frequencyIndex) = *(evenFrequencyComponents + frequencyIndex) + omega * (*(oddFrequencyComponents + frequencyIndex));
        *(outFrequencyComponents + frequencyIndex + inNumberOfElements / 2) = *(evenFrequencyComponents + frequencyIndex) - omega * (*(oddFrequencyComponents + frequencyIndex));
    }
    
    return true;
}

// Private Method Implementation

long _xsPadShortInput(short *elements, long numberOfElements)
{
    int idealNumberOfElements = _xsNextPowerOfTwo(numberOfElements);
    elements = (short *)realloc(elements, idealNumberOfElements);

    for (long newIndex = numberOfElements; newIndex < idealNumberOfElements; ++newIndex) {
        *(elements + newIndex) = 0;
    }

    return idealNumberOfElements;
}

long _xsNextPowerOfTwo(long value)
{
    long nextPowerOfTwo = 1;
    while (nextPowerOfTwo < value) {
        nextPowerOfTwo <<= 1;
    }

    return nextPowerOfTwo;
}
