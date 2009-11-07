#include <math.h>

#include "xscomplex.h"

// Initialization
 
xsComplex::xsComplex()
{
    this->real = 0.0;
    this->imaginary = 0.0;
}

xsComplex::xsComplex(const long real_part, const long imaginary_part)
{
    this->real = (double)real_part;
    this->imaginary = (double)real_part;
}

xsComplex::xsComplex(const int real_part, const int imaginary_part)
{
    this->real = (double)real_part;
    this->imaginary = (double)real_part;
}

xsComplex::xsComplex(const short real_part, const short imaginary_part)
{
    this->real = (double)real_part;
    this->imaginary = (double)real_part;
}

xsComplex::xsComplex(const char real_part, const char imaginary_part)
{
    this->real = (double)real_part;
    this->imaginary = (double)real_part;
}

xsComplex::xsComplex(const xsComplex &toCopy)
{
    this->real = toCopy.real;
    this->imaginary = toCopy.imaginary;
}

// Euler's Identity

void xsComplex::initWithEulerIdentity(const double theta)
{
    this->real = cos(theta);
    this->imaginary = sin(theta);
}

void xsComplex::initWithEulerIdentity(const float theta)
{
    this->real = cos((double)theta);
    this->imaginary = sin((double)theta);
}

void xsComplex::initWithEulerIdentity(const long theta)
{
    this->real = cos((double)theta);
    this->imaginary = sin((double)theta);
}

void xsComplex::initWithEulerIdentity(const int theta)
{
    this->real = cos((double)theta);
    this->imaginary = sin((double)theta);
}

void xsComplex::initWithEulerIdentity(const short theta)
{
    this->real = cos((double)theta);
    this->imaginary = sin((double)theta);
}

void xsComplex::initWithEulerIdentity(const char theta)
{
    this->real = cos((double)theta);
    this->imaginary = sin((double)theta);
}

// Assignment

xsComplex &xsComplex::operator=(const xsComplex &right)
{
    if (this == &right) {
        return *this;
    }
    
    this->real = right.real;
    this->imaginary = right.imaginary;
    
    return *this;
}

// Equality

bool xsComplex::operator==(const xsComplex &right) const
{
    return this->real == right.real && this->imaginary == right.imaginary;
}

bool xsComplex::operator!=(const xsComplex &right) const
{
    return !(*this == right);
}

// Addition

const xsComplex xsComplex::operator+(const xsComplex &right) const
{
    xsComplex sum = *this;
    sum.real += right.real;
    sum.imaginary += right.imaginary;
    return sum;
}

xsComplex &xsComplex::operator+=(const xsComplex &right)
{
    this->real += right.real;
    this->imaginary += right.imaginary;
    return *this;
}

// Subtraction

const xsComplex xsComplex::operator-(const xsComplex &right) const
{
    xsComplex difference = *this;
    difference.real -= right.real;
    difference.imaginary -= right.imaginary;
    return difference;
}

xsComplex &xsComplex::operator-=(const xsComplex &right)
{
    this->real -= right.real;
    this->imaginary -= right.real;
    return *this;
}

// Multiplication

const xsComplex xsComplex::operator*(const xsComplex &right) const
{
    xsComplex product = *this;
    product.real = this->real * right.real - this->imaginary * right.imaginary;
    product.imaginary = this->real * right.imaginary + this->imaginary * right.real;
    return product;
}

xsComplex &xsComplex::operator*=(const xsComplex &right)
{
    this->real = this->real * right.real - this->imaginary * right.imaginary;
    this->imaginary = this->real * right.imaginary + this->imaginary * right.real;
    return *this;
}

// Conjugate

xsComplex xsComplex::conjugate()
{
    xsComplex complexConjugate(this->real, -(this->imaginary));
    return complexConjugate;
}

// Magnitude

double xsComplex::magnitude()
{
    return sqrt(this->real * this->real + this->imaginary * this->imaginary);
}
