all: fft ift demo

demo: main.c
	g++ main.c -o demo

fft: fftmain.c
	g++ fftmain.c -o xsfft

ift: iftmain.c
	g++ iftmain.c -o xsift
