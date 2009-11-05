#include "xsfft.h"

// Private functions

long _xsPadShortInput(short *elements, long numberOfElements);

// Public Method Implementations

short *xsShortFFTIterative(short *elements, long numberOfElements);


// Private Method Implementation

long _xsPadShortInput(short *elements, long numberOfElements)
{
    int idealNumberOfElements = 2;
    while (idealNumberOfElements < numberOfElements) {
        idealNumberOfElements <<= 1;
    }

    elements = (short *)realloc(elements, idealNumberOfElements);

    for (long newIndex = numberOfElements; newIndex < idealNumberOfElements; ++newIndex) {
        *(elements + newIndex) = 0; // Pad the input with zeroes
    }

    return idealNumberOfElements;
}
