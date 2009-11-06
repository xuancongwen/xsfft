all: test fft ift

test: main.cpp xscomplex.cpp
	g++ main.cpp xscomplex.cpp xsfft.cpp xsift.cpp -o test

fft: fftmain.cpp xscomplex.cpp
	g++ fftmain.cpp xsfft.cpp xscomplex.cpp -o xsfft

ift: iftmain.cpp xscomplex.cpp
	g++ iftmain.cpp xsift.cpp xscomplex.cpp -o xsift

clean: cleantest cleanfft cleanift

cleantest:
	rm test

cleanfft:
	rm xsfft

cleanift:
	rm xsift
