#ifndef XS_COMPLEX
#define XS_COMPLEX

class xsComplex
{
public:
    // Initialization
    xsComplex();
    xsComplex(const double real_part, const double imaginary_part);
    xsComplex(const float real_part, const float imaginary_part);
    xsComplex(const long real_part, const long imaginary_part);
    xsComplex(const int real_part, const int imaginary_part);
    xsComplex(const short real_part, const short imaginary_part);
    xsComplex(const char real_part, const char imaginary_part);
    xsComplex(const xsComplex &toCopy);

    // Euler's Identity
    void initWithEulerIdentity(const double theta);
    void initWithEulerIdentity(const float theta);
    void initWithEulerIdentity(const long theta);
    void initWithEulerIdentity(const int theta);
    void initWithEulerIdentity(const short theta);
    void initWithEulerIdentity(const char theta);

    // Assignment
    xsComplex &operator=(const xsComplex &right);

    // Equality
    bool operator==(const xsComplex &right) const;
    bool operator!=(const xsComplex &right) const;

    // Addition
    const xsComplex operator+(const xsComplex &right) const;
    xsComplex &operator+=(const xsComplex &right);

    // Subtraction
    const xsComplex operator-(const xsComplex &right) const;
    xsComplex &operator-=(const xsComplex &right);

    // Multiplication
    const xsComplex operator*(const xsComplex &right) const;
    xsComplex &operator*=(const xsComplex &right);

    // Complex Conjugate
    xsComplex conjugate();
    
    // Magnitude
    double magnitude();

    // Public data
    double real;
    double imaginary;
};

#endif
