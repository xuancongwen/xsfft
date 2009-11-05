all: demo fft ift

demo: main.cpp complex.cpp
	g++ main.cpp complex.cpp -o test

fft: fftmain.cpp complex.cpp
	g++ fftmain.cpp complex.cpp -o xsfft

ift: iftmain.cpp complex.cpp
	g++ iftmain.cpp complex.cpp -o xsift

clean: cdemo cfft cift

cdemo: test
	rm test

cfft: xsfft
	rm xsfft

cift: xsift
	rm xsift
