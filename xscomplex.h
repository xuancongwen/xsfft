// This implementation of xsComplex is based on LibRow's implementation.
// See the original source here:
//
//      http://www.librow.com/articles/article-10
//
// The original code has been extensively modified.

#ifndef XS_COMPLEX
#define XS_COMPLEX


class xsComplex
{
public:
	//   Imaginary unity
	static const xsComplex i;
	static const xsComplex j;
    
	//   Initialization
	xsComplex();
	xsComplex(const double real, const double imaginary);
	xsComplex(const double theta);  // Euler initialization
    
	//   Assignment
	xsComplex &operator=(const xsComplex &toCopy);
    void set(const double real, const double imaginary);
    void setReal(const double real);
    void setImaginary(const double imaginary);
    
	//   Getters
	const double real() const;
	const double imaginary() const;
    
	//   Computed Values
	xsComplex conjugate() const;
	const double norm() const;
    const double magnitude() const;
    
	//   Overloaded Operators
	xsComplex operator+(const xsComplex &right) const;
	xsComplex operator-(const xsComplex &right) const;
	xsComplex operator*(const xsComplex &right) const;
	xsComplex operator/(const xsComplex &right) const;
    
	xsComplex &operator+=(const xsComplex &right);
	xsComplex &operator-=(const xsComplex &right);
	xsComplex &operator*=(const xsComplex &right);
	xsComplex &operator/=(const xsComplex &right);
    
    xsComplex &operator*=(const double right);
	xsComplex &operator/=(const double right);
    
	//   Comparison
	bool operator==(const xsComplex &right) const;
	bool operator!= (const xsComplex &right) const;
    
protected:
	double _real;
	double _imaginary;
};

#endif
