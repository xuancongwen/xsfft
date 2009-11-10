all: xscomplex.cpp xsfft.cpp xsfftdemo.cpp
	g++ -O xscomplex.cpp xsfft.cpp xsfftdemo.cpp -o xsfftdemo

clean:
	rm xsfftdemo
