/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "xsfft.h"

using namespace std;

int main(int argc, char *argv[])
{
    long dataLength = 100;
    xsComplex *data = new xsComplex[dataLength];

    srand(0);
    xsComplex *dataIterator = data;
    for(long signalIndex = 0; signalIndex < dataLength; ++signalIndex, ++dataIterator) {
        //dataIterator->set((rand() % USHRT_MAX) - SHRT_MAX, 0.0);
        //dataIterator->set(sin(2.0 * xsPI * (double)signalIndex), 0.0);
        dataIterator->set((double)signalIndex, 0.0);
        cout << dataIterator->real() << "\n";
    }

    xsCoerceDataRadix2(data, &dataLength);
    bool success = xsFFT(data, dataLength);
    
    if (success) {
        cout << "\n\nSuccess!\n\n";
    } else {
        cout << "\n\nFail...\n\n";
    }
    
    dataIterator = data;
    for(long freqIndex = 0; freqIndex < dataLength; ++freqIndex, ++dataIterator) {
        cout << dataIterator->real() << "\n";
    }
    
    puts("\n");

    free(data);

    return success ? 0 : -1;
}
