/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "xsfft.h"

int main(int argc, char *argv[])
{
    long signalLength = 100;
    double *timeDomain = (double *)calloc(sizeof(double), signalLength);
    double *freqDomain = (double *)calloc(sizeof(double), signalLength);

    srand(0);
    for(long signalIndex = 0; signalIndex < signalLength; ++signalIndex) {
        *(timeDomain + signalIndex) = (rand() % USHRT_MAX) - SHRT_MAX;  // Some (hopefully) gaussian noise
        //*(timeDomain + signalIndex) = sin(2 * xsPI * signalIndex);
        //*(timeDomain + signalIndex) = signalIndex;
        printf("%lf\t", *(timeDomain + signalIndex));
    }

    bool success = xsFFT(timeDomain, signalLength, freqDomain);
    
    puts(success ? "\n\nSuccess!\n\n" : "\n\nFail...\n\n");
    
    for(long freqIndex = 0; freqIndex < signalLength; ++freqIndex) {
        printf("%lf\t", *(freqDomain + freqIndex));
    }
    
    puts("\n");

    free(timeDomain);
    free(freqDomain);

    return success ? 0 : -1;
}
