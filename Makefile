all: demo fft ift

demo: main.c
	g++ main.c -o test

fft: fftmain.c
	g++ fftmain.c -o xsfft

ift: iftmain.c
	g++ iftmain.c -o xsift

clean: cdemo cfft cift

cdemo: test
	rm test

cfft: xsfft
	rm xsfft

cift: xsift
	rm xsift
