all: xscomplex.cpp xsfft.cpp xsfftdemo.cpp
	g++ -O xscomplex.cpp xsfft.cpp xsfftdemo.cpp -o xsfftdemo

tests: xscomplex.cpp xsfft.cpp xsunittests.cpp
	g++ -O xscomplex.cpp xsfft.cpp xsunittests.cpp -o xsunittests

clean:
	rm xsfftdemo
