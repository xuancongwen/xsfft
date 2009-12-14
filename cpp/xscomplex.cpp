#include <math.h>

#include "xscomplex.h"

//  Imaginary unity constants
const xsComplex xsComplex::i(0.0, 1.0);
const xsComplex xsComplex::j(0.0, 1.0);

//  Initialization

xsComplex::xsComplex()
:_real(0.0), _imaginary(0.0)
{
}

xsComplex::xsComplex(double real, double imaginary)
:_real(real), _imaginary(imaginary)
{
}

xsComplex::xsComplex(double real)
:_real(real), _imaginary(0.0)
{
}


//  Getters

const double xsComplex::real() const
{ 
    return _real;
}

const double xsComplex::imaginary() const
{ 
    return _imaginary;
}


//  Setters

xsComplex &xsComplex::operator=(const double real)
{
    _real = real;
    _imaginary = 0.0;
    
    return *this;
}

void xsComplex::set(const double real, const double imaginary)
{
    _real = real;
    _imaginary = imaginary;
}

void xsComplex::setReal(const double real)
{
    _real = real;
}

void xsComplex::setImaginary(const double imaginary)
{
    _imaginary = imaginary;
}


//  Computed Values

xsComplex xsComplex::conjugate() const
{
    return xsComplex(_real, -_imaginary);
}

const double xsComplex::norm() const
{
    return _real * _real + _imaginary * _imaginary;
}

const double xsComplex::magnitude() const
{
    return sqrt(norm());
}


//  Overloaded Operators

xsComplex xsComplex::operator+(const xsComplex &right) const
{
    return xsComplex(_real + right._real, _imaginary + right._imaginary);
}

xsComplex xsComplex::operator-(const xsComplex &right) const
{
    return xsComplex(_real - right._real, _imaginary - right._imaginary);
}

xsComplex xsComplex::operator*(const xsComplex &right) const
{
    return xsComplex(_real * right._real - _imaginary * right._imaginary, _real * right._imaginary + _imaginary * right._real);
}

xsComplex xsComplex::operator/(const xsComplex &right) const
{
    const double denominator = right._real * right._real + right._imaginary * right._imaginary;
    return xsComplex((_real *  right._real + _imaginary *  right._imaginary) / denominator, (_imaginary * right._real - _real * right._imaginary) / denominator);
}

xsComplex xsComplex::operator+(const double right) const
{
    return xsComplex(_real + right, _imaginary);
}

xsComplex xsComplex::operator-(const double right) const
{
    return xsComplex(_real - right, _imaginary);
}

xsComplex xsComplex::operator*(const double right) const
{
    return xsComplex(_real * right, _imaginary * right);
}

xsComplex xsComplex::operator/(const double right) const
{
    return xsComplex(_real / right, _imaginary / right);
}

xsComplex &xsComplex::operator+=(const xsComplex &right)
{
    _real += right._real;
    _imaginary += right._imaginary;
    return *this;
}

xsComplex &xsComplex::operator-=(const xsComplex &right)
{
    _real -= right._real;
    _imaginary -= right._imaginary;
    return *this;
}

xsComplex &xsComplex::operator*=(const xsComplex &right)
{
    const double temp = _real;
    _real = _real * right._real - _imaginary * right._imaginary;
    _imaginary = _imaginary * right._real + temp * right._imaginary;
    return *this;
}

xsComplex &xsComplex::operator/=(const xsComplex &right)
{
    const double denominator = right._real * right._real + right._imaginary * right._imaginary;
    const double temp = _real;
    _real = (_real * right._real + _imaginary * right._imaginary) / denominator;
    _imaginary = (_imaginary * right._real - temp * right._imaginary) / denominator;
    return *this;
}

xsComplex &xsComplex::operator+=(const double right)
{
    _real += right;
    return *this;
}

xsComplex &xsComplex::operator-=(const double right)
{
    _real -= right;
    return *this;
}

xsComplex &xsComplex::operator*=(const double right)
{
    _real *= right;
    _imaginary *= right;
    return *this;
}

xsComplex &xsComplex::operator/=(const double right)
{
    _real /= right;
    _imaginary /= right;
    return *this;
}

xsComplex operator+(const double left, const xsComplex &right)
{
    return xsComplex(left + right._real, right._imaginary);
}

xsComplex operator-(const double left, const xsComplex &right)
{
    return xsComplex(left - right._real, -right._imaginary);
}

xsComplex operator*(const double left, const xsComplex &right)
{
    return xsComplex(left * right._real, left * right._imaginary);
}

xsComplex operator/(const double left, const xsComplex &right)
{
    const double denominator = right._real * right._real + right._imaginary * right._imaginary;
    return xsComplex(left * right._real / denominator, -left * right._imaginary / denominator);
}


//  Comparison

bool xsComplex::operator==(const xsComplex &right) const
{
    return _real == right._real && _imaginary == right._imaginary;
}

bool xsComplex::operator!=(const xsComplex &right) const
{
    return _real != right._real || _imaginary != right._imaginary;
}

bool xsComplex::operator==(const double right) const
{
    return _real == right && _imaginary == 0.0;
}

bool xsComplex::operator!=(const double right) const
{
    return _real != right || _imaginary != 0.0;
}

bool operator==(const double left, const xsComplex &right)
{
    return left == right._real && right._imaginary == 0.;
}

bool operator!=(const double left, const xsComplex &right)
{
    return left != right._real || right._imaginary != 0.;
}
