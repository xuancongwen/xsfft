#ifndef XS_FFT
#define XS_FFT

template <class T>
bool xsFFT(T *inElements, long inNumberOfElements, T *outFrequencyComponents);

long xsNextPowerOfTwo(long value);

#endif
