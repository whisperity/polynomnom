#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <algorithm>
#include <iosfwd>
#include <complex>
#include <cmath>

class Complex
{
    typedef std::complex<long double> inner;

    public:
        Complex();
        Complex(long double re);
        Complex(long double re, long double im);
        Complex(const inner& complex);
        Complex(const Complex& complex);

        long double re() const;
        long double im() const;
        
        friend Complex operator + (const Complex& a, const Complex& b);
        friend Complex operator - (const Complex& a, const Complex& b);
        friend Complex operator * (const Complex& a, const Complex& b);
        friend Complex operator / (const Complex& a, const Complex& b);
        friend Complex& operator += (Complex& cur, const Complex& a);
        friend Complex& operator -= (Complex& cur, const Complex& a);
        friend Complex& operator *= (Complex& cur, const Complex& a);
        friend Complex& operator /= (Complex& cur, const Complex& a);

        friend bool operator == (const Complex& a, const Complex& b);
        friend bool operator != (const Complex& a, const Complex& b);

        friend std::ostream& operator << (std::ostream& o, const Complex& cmplx);
    private:
        inner _complex;
};

Complex::Complex()
{
    this->_complex = inner(0, 0);
}

Complex::Complex(long double re)
{
    this->_complex = inner(re, 0);
}

Complex::Complex(long double re, long double im)
{
    this->_complex = inner(re, im);
}

Complex::Complex(const inner& complex)
{
    this->_complex = inner(complex);
}

Complex::Complex(const Complex& complex)
{
    this->_complex = inner(complex._complex);
}

long double Complex::re() const
{
    return this->_complex.real();
}

long double Complex::im() const
{
    return this->_complex.imag();
}

Complex& operator += (Complex& cur, const Complex& a)
{
    cur._complex += a._complex;
    return cur;
}

Complex& operator -= (Complex& cur, const Complex& a)
{
    cur._complex -= a._complex;
    return cur;
}

Complex& operator *= (Complex& cur, const Complex& a)
{
    cur._complex *= a._complex;
    return cur;
}

Complex& operator /= (Complex& cur, const Complex& a)
{
    cur._complex /= a._complex;
    return cur;
}

Complex operator + (const Complex& a, const Complex& b)
{
    Complex res = a;
    res += b;
    return res;
}

Complex operator - (const Complex& a, const Complex& b)
{
    Complex res = a;
    res -= b;
    return res;
}

Complex operator * (const Complex& a, const Complex& b)
{
    Complex res = a;
    res *= b;
    return res;
}

Complex operator / (const Complex& a, const Complex& b)
{
    Complex res = a;
    res /= b;
    return res;
}

bool operator == (const Complex& a, const Complex& b)
{
    return a._complex == b._complex;
}

bool operator != (const Complex& a, const Complex& b)
{
    return a._complex != b._complex;
}

std::ostream& operator << (std::ostream& o, const Complex& cmpl)
{
    // Write the complex number in algebraic form.

    if (cmpl.re() == 0 && cmpl.im() == 0)
        o << "0";
    else if (cmpl.re() != 0 && cmpl.im() != 0)
        o << cmpl.re() << " " << (cmpl.im() < 0 ? "-" : "+") << " " << abs(cmpl.im()) << "i";
    else if (cmpl.re() != 0 && cmpl.im() == 0)
        o << cmpl.re();
    else if (cmpl.re() == 0 && cmpl.im() != 0)
        o << cmpl.im() << "i";
    
    return o;
}

#ifdef _ADD_MULT_IDENTITY_H
// The additive identity is 0/1 (0), the multiplicative is 1/1 (1).
template<> struct id_multiplicative_exists<Complex> : id_multiplicative_known{};
template<> struct id_multiplicative<Complex> { static Complex const value; };
Complex const id_multiplicative<Complex>::value = // 1 + 0i
    Complex(id_multiplicative<long double>::value, id_additive<long double>::value);

template<> struct id_additive_exists<Complex> : id_additive_known{};
template<> struct id_additive<Complex> { static Complex const value; };
Complex const id_additive<Complex>::value = // 0 + 0i
    Complex(id_additive<long double>::value, id_additive<long double>::value);
#endif // _ADD_MULT_IDENTITY_H

#ifdef _POLYNOMIAL_H
template<>
std::ostream& operator << (std::ostream& o, const Polynomial<Complex>& poly)
{
    // Complex polynomials need to be written out a bit differently so we specialise the template here.

    if (poly.isNull())
        return o << "nullPolynomial";
    else if (poly.isConstant())
        return o << poly.getMember(0) << " (constant)";

    bool firstCoeff = true;
    for (Polynomial<Complex>::coefficientsMap::const_iterator cit = poly.m_coefficients.cbegin();
        cit != poly.m_coefficients.cend(); ++cit)
    {
        const long double re = cit->second.re();
        const long double im = cit->second.im();

        // Omit the members with 0 coefficient
        if (cit->second == id_additive<Complex>::value) continue;

        if (!firstCoeff)
            o << " ";

        // Printing the complex numbers is a bit tricky
        // If the complex number has both parts non-zero, it should be printed like: +(-6 - 8i)x^2
        // If either parts are zero, standard procedure applies: +4x and -6ix^3

        // Print the complex number making sure that the + and - signs are properly done.
        if (re != 0 && im != 0)
        {
            if (cit->first == 0)
            {
                if (!firstCoeff)
                    o << (re > 0 ? "+ " : "");

                if (re < 0)
                    o << "-";
                o << abs(re) << " " << (im > 0 ? "+ " : "- ") << abs(im) << "i";
            }
            else
            {
                if (!firstCoeff)
                    o << "+ ";
                o << "(" << re << " " << (im > 0 ? "+" : "-") << " " << abs(im) << "i)";
            }
        }
        else if (re != 0 && im == 0)
        {
            if (!firstCoeff)
                o << (re > 0 ? "+ " : "");

            if (re < 0)
                o << "- ";
            
            if (abs(re) != 1)
                o << abs(re);
        }
        else if (re == 0 && im != 0)
        {
            if (!firstCoeff)
                o << (im > 0 ? "+ " : "");

            if (im < 0)
                o << "- ";

            if (abs(im) != 1)
                o << abs(im);
            o << "i";
        }

        // Don't print the power for the first-order member and don't print x for the constant member
        if (cit->first > 1)
            o << "x^" << cit->first;
        if (cit->first == 1)
            o << "x";

        if (firstCoeff) firstCoeff = false;
    }

    return o;
}
#endif // _POLYNOMIAL_H

#endif // _COMPLEX_H