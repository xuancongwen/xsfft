CPPFLAGS= -O
CPP= g++

all: test fft ift

test: main.cpp xscomplex.cpp
	$(CPP) $(CPPFLAGS) xscomplex.cpp xsfft.cpp xsift.cpp main.cpp -o test

fft: fftmain.cpp xscomplex.cpp
	$(CPP) $(CPPFLAGS) xscomplex.cpp xsfft.cpp fftmain.cpp -o xsfft

ift: iftmain.cpp xscomplex.cpp
	$(CPP) $(CPPFLAGS) xscomplex.cpp xsift.cpp iftmain.cpp -o xsift

clean: cleantest cleanfft cleanift

cleantest:
	rm test

cleanfft:
	rm xsfft

cleanift:
	rm xsift
