/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <stdio.h>
#include <stdlib.h>
#include "xsfft.h"

int main(int argc, char *argv[])
{
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);
    xsComplex *data = xsAllocArrayInt(rawData, dataLength);
    free(rawData);
    
    puts("--------------------------Interpolation----------------------------------\n");
    
    data = xsInterpolateWithFactor2(data, &dataLength);
    for(unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        printf("%f\n", (data + dataIndex)->real);
    }

    xsFreeArray(data);

    return 0;
}
