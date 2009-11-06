#ifndef XS_COMPLEX
#define XS_COMPLEX

template <class T>
class xsComplex
{
public:
    // Initialization
    xsComplex();
    xsComplex(T real_part, T imaginary_part);
    xsComplex(xsComplex<T> &toCopy);

    // Euler's Identity
    void initWithEulerIdentity(T theta);

    // Addition
    xsComplex<T> operator+(xsComplex<T> &right);
    xsComplex<T> operator+=(xsComplex<T> &right);

    // Subtraction
    xsComplex<T> operator-(xsComplex<T> &right);
    xsComplex<T> operator-=(xsComplex<T> &right);

    // Multiplication
    xsComplex<T> operator*(xsComplex<T> &right);
    xsComplex<T> operator*=(xsComplex<T> &right);

    // Complex Conjugate
    xsComplex<T> conjugate();

private:
    T real;
    T imaginary;
};

#endif
