#include "complex.h"

template <class T>
xsComplex<T>::xsComplex(const T real_part, const T imaginary_part)
    :real(real_part), imaginary(imaginary_part)
{
}

template <class T>
xsComplex<T>::xsComplex(const xsComplex<T> &toCopy)
    :real(toCopy.real), imaginary(toCopy.imaginary)
{
}

template <class T>
xsComplex<T>::~xsComplex()
{
}

// Addition

template <class T>
xsComplex<T> xsComplex<T>::operator+(const xsComplex<T> right)
{
    xsComplex<T> sum(this.real + right.real, this.imaginary + right.imaginary);
    return sum;
}

template <class T>
xsComplex<T> xsComplex<T>::operator+=(const xsComplex<T> right)
{
    xsComplex<T> sum(this + right);
    return sum;
}

// Subtraction

template <class T>
xsComplex<T> xsComplex<T>::operator-(const xsComplex<T> right)
{
    xsComplex<T> difference(this.real - right.real, this.imaginary - right.imagniary);
    return difference;
}

template <class T>
xsComplex<T> xsComplex<T>::operator-=(const xsComplex<T> right)
{
    xsComplex<T> difference(this - right);
    return difference;
}

// Multiplication

template <class T>
xsComplex<T> xsComplex<T>::operator*(const xsComplex<T> right)
{
    xsComplex<T> product(this.real * right.real - this.imaginary * right.imaginary, this.real * right.imaginary + this.imaginary * right.real);
    return product;
}

template <class T>
xsComplex<T> xsComplex<T>::operator*=(const xsComplex<T> right)
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
