#include <math.h>

#include "xscomplex.h"

// Initialization
 
template <class T>
xsComplex<T>::xsComplex()
{
    this.real = (T)0;
    this.imaginary = (T)0;
}

template <class T>
xsComplex<T>::xsComplex(T real_part, T imaginary_part)
{
    this.real = real_part;
    this.imaginary_part = real_part;
}

template <class T>
xsComplex<T>::xsComplex(xsComplex<T> &toCopy)
{
    this.real = toCopy.real;
    this.imaginary = toCopy.imaginary;
}

// Euler's Identity

template <class T>
void xsComplex<T>::initWithEulerIdentity(T theta)
{
    this.real = cos(theta);
    this.imaginary = sin(theta);
}

// Addition

template <class T>
xsComplex<T> xsComplex<T>::operator+(xsComplex<T> &right)
{
    xsComplex<T> sum(this.real + right.real, this.imaginary + right.imaginary);
    return sum;
}

template <class T>
xsComplex<T> xsComplex<T>::operator+=(xsComplex<T> &right)
{
    xsComplex<T> sum(this + right);
    return sum;
}

// Subtraction

template <class T>
xsComplex<T> xsComplex<T>::operator-(xsComplex<T> &right)
{
    xsComplex<T> difference(this.real - right.real, this.imaginary - right.imagniary);
    return difference;
}

template <class T>
xsComplex<T> xsComplex<T>::operator-=(xsComplex<T> &right)
{
    xsComplex<T> difference(this - right);
    return difference;
}

// Multiplication

template <class T>
xsComplex<T> xsComplex<T>::operator*(xsComplex<T> &right)
{
    xsComplex<T> product(this.real * right.real - this.imaginary * right.imaginary, this.real * right.imaginary + this.imaginary * right.real);
    return product;
}

template <class T>
xsComplex<T> xsComplex<T>::operator*=(xsComplex<T> &right)
{
    xsComplex<T> product(this * right);
    return product;
}

// Conjugate

template <class T>
xsComplex<T> xsComplex<T>::conjugate()
{
    xsComplex<T> complexConjugate(this.real, this.imaginary);
    return complexConjugate;
}
