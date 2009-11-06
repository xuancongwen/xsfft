all: demo fft ift

demo: main.cpp xscomplex.cpp
	g++ main.cpp xscomplex.cpp xsfft.cpp xsift.cpp -o test

fft: fftmain.cpp xscomplex.cpp
	g++ fftmain.cpp xscomplex.cpp xsfft.cpp -o xsfft

ift: iftmain.cpp xscomplex.cpp
	g++ iftmain.cpp xscomplex.cpp xsift.cpp -o xsift

clean: cleantest cleanfft cleanift

cleantest:
	rm test

cleanfft:
	rm xsfft

cleanift:
	rm xsift
