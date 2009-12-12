all: xscomplex.c xsfft.c xsfftdemo.c
	gcc -O xscomplex.c xsfft.c xsfftdemo.c -o xsfftdemo

tests: xscomplex.c xsfft.c xsunittests.c
	gcc -O xscomplex.c xsfft.c xsunittests.c -o xsunittests

clean:
	rm xsfftdemo
