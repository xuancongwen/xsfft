/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include "xsfft.h"

int main(int argc, char *argv[])
{
    long signalLength = 100;
    short *timeDomain = (short *)calloc(sizeof(short), signalLength);
    short *freqDomain = (short *)calloc(sizeof(short), signalLength);

    srand(0);
    for (long signalIndex = 0; signalIndex < signalLength; ++signalIndex) {
        *(timeDomain + signalIndex) = (rand() % USHRT_MAX) - SHRT_MAX;  // Some (hopefully) gaussian noise
    }

    bool success = xsFFT(timeDomain, signalLength, freqDomain);
    
    puts(success ? "Success!\n" : "Fail...\n");
    
    for (long freqIndex = 0; freqIndex < signalLength; ++freqIndex) {
        std::cout << *(freqDomain + freqIndex) << "\t";
    }

    free(timeDomain);
    free(freqDomain);

    return success ? 0 : -1;
}
