#ifndef XS_FFT
#define XS_FFT

extern const double xsPI;

bool xsFFT(double *inElements, long inNumberOfElements, double *outFrequencyComponents);
bool xsFFT(float *inElements, long inNumberOfElements, float *outFrequencyComponents);
bool xsFFT(long *inElements, long inNumberOfElements, long *outFrequencyComponents);
bool xsFFT(int *inElements, long inNumberOfElements, int *outFrequencyComponents);
bool xsFFT(short *inElements, long inNumberOfElements, short *outFrequencyComponents);
bool xsFFT(char *inElements, long inNumberOfElements, char *outFrequencyComponents);

long xsNextPowerOfTwo(long value);

#endif
