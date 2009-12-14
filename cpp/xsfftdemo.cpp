/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <iostream>
#include <cstdlib>

#include "xsfft.h"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned long dataLength = 100;
    int *rawData = (int *)calloc(dataLength, sizeof(int));
    for (unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, *(rawData + signalIndex) = signalIndex);
    
    xsComplex *data = xsAllocArray(rawData, dataLength);
    
    free(rawData);
    
    cout << "--------------------------Interpolation----------------------------------" << endl;
    
    data = xsInterpolateWithFactor2(data, &dataLength);
    for(unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        cout << (data + dataIndex)->real() << endl;
    }

    xsFreeArray(data);

    return 0;
}
