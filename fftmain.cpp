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
    long signalLength = 128;
    xsComplex *data = (xsComplex *)calloc(signalLength, sizeof(xsComplex));

    srand(0);
    xsComplex *dataIterator = data;
    for(long signalIndex = 0; signalIndex < signalLength; ++signalIndex, ++dataIterator) {
        dataIterator = new xsComplex((rand() % USHRT_MAX) - SHRT_MAX, 0.0);  // Some (hopefully) gaussian noise
        //dataIterator = sin(2 * xsPI * signalIndex);
        //dataIterator = signalIndex;
        cout << dataIterator->real() << "\n";
    }

    bool success = xsFFT(data, signalLength);
    
    if (success) {
        cout << "\n\nSuccess!\n\n";
    } else {
        cout << "\n\nFail...\n\n";
    }
    
    dataIterator = data;
    for(long freqIndex = 0; freqIndex < signalLength; ++freqIndex) {
        cout << dataIterator->norm() << "\n";
    }
    
    puts("\n");

    free(data);

    return success ? 0 : -1;
}
