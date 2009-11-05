template <class T>
class xsComplex
{
public:
    // Initialization
    xsComplex(const T real_part, const T imaginary_part);
    xsComplex(const xsComplex<T> &toCopy);

    ~xsComplex();

    // Addition
    xsComplex<T> operator+(const xsComplex<T> right);
    xsComplex<T> operator+=(const xsComplex<T> right);

    // Subtraction
    xsComplex<T> operator-(const xsComplex<T> right);
    xsComplex<T> operator-=(const xsComplex<T> right);

    // Multiplication
    xsComplex<T> operator*(const xsComplex<T> right);
    xsComplex<T> operator*=(const xsComplex<T> right);

    // Complex Conjugate
    xsComplex<T> conjugate();

private:
    T real;
    T imaginary;
};
