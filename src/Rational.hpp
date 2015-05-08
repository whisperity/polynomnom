#ifndef _RATIONAL_H
#define _RATIONAL_H

#include <algorithm>
#include <iosfwd>
#include "EuclideanAlgorithm.hpp"

class Rational
{
    public:
        Rational();
        // All whole numbers can be expressed as rational - their denominator is 1.
        Rational(long long numerator);
        Rational(long long numerator, long long denominator);
        Rational(unsigned long long numerator, unsigned long long denominator, bool negative);
        Rational(const Rational& frac);

        bool negative() const;
        unsigned long long numerator() const;
        unsigned long long denominator() const;

        Rational abs_value() const;
        long double real_value() const;

        friend Rational operator + (const Rational& a, const Rational& b);
        friend Rational operator - (const Rational& a, const Rational& b);
        friend Rational operator * (const Rational& a, const Rational& b);
        friend Rational operator / (const Rational& a, const Rational& b);
        friend Rational& operator += (Rational& cur, const Rational& a);
        friend Rational& operator -= (Rational& cur, const Rational& a);
        friend Rational& operator *= (Rational& cur, const Rational& a);
        friend Rational& operator /= (Rational& cur, const Rational& a);

        friend bool operator == (const Rational& a, const Rational& b);
        friend bool operator != (const Rational& a, const Rational& b);
        friend bool operator < (const Rational& a, const Rational& b);
        friend bool operator <= (const Rational& a, const Rational& b);
        friend bool operator > (const Rational& a, const Rational& b);
        friend bool operator >= (const Rational& a, const Rational& b);

        friend std::ostream& operator << (std::ostream& o, const Rational& frac);
    private:
        static void common_denominator(Rational cd[], const Rational& a, const Rational& b); // Hax.
        void _simplify();
        bool m_negative;
        unsigned long long m_numerator;
        unsigned long long m_denominator;
};

Rational::Rational()
{
    this->m_negative = false;
    this->m_numerator = 0;
    this->m_denominator = 1;
}

Rational::Rational(long long numerator)
{
    this->m_negative = (numerator < 0);
    this->m_numerator = abs(numerator);
    this->m_denominator = 1;
}

Rational::Rational(long long numerator, long long denominator)
{
    this->m_numerator = abs(numerator);
    this->m_denominator = abs(denominator);

    // A rational number is negative if either the numerator or the denominator is negative, but not both.
    this->m_negative = (numerator < 0) ^ (denominator < 0);
    this->_simplify();
}

Rational::Rational(unsigned long long numerator, unsigned long long denominator, bool negative)
{
    this->m_negative = negative;
    this->m_numerator = numerator;
    this->m_denominator = denominator;
    this->_simplify();
}

Rational::Rational(const Rational& frac)
{
    this->m_negative = frac.m_negative;
    this->m_numerator = frac.m_numerator;
    this->m_denominator = frac.m_denominator;
    this->_simplify();
}

bool Rational::negative() const
{
    return this->m_negative;
}

unsigned long long Rational::numerator() const
{
    return this->m_numerator;
}

unsigned long long Rational::denominator() const
{
    return this->m_denominator;
}

Rational Rational::abs_value() const
{
    Rational ret = *this;
    ret.m_negative = false;
    return ret;
}

long double Rational::real_value() const
{
    long double val = 1;
    val = val * this->m_numerator;
    val = val / this->m_denominator;
    if (this->m_negative)
        val = val * (-1);

    return val;
}

Rational& operator += (Rational& cur, const Rational& a)
{
    // a     c      a*d + b*c
    // -  +  -   =  ---------
    // b     d         b*d
    
    // First, put the two rationals on the common denominator
    Rational cd[2];
    Rational::common_denominator(cd, cur, a);

    // Shortcuts:
    const Rational& c = cd[0];
    const Rational& d = cd[1];

    // If the two rational's sign is the same, we just add the numerators and keep the sign
    if (c.m_negative == d.m_negative)
    {
        cur.m_numerator = c.m_numerator + d.m_numerator;
        cur.m_negative = c.m_negative;
    }
    else
    {

        // If the signs differ, we always subtract the bigger numerator from the smaller one.
        cur.m_numerator = std::max(c.m_numerator, d.m_numerator) - std::min(c.m_numerator, d.m_numerator);

        // The result negative if the absolute bigger (the rational which has a bigger absolute value) operand
        // of the addition was, in fact, negative.
        const Rational& negative_rational = ((c.m_negative && !d.m_negative) ? c : d);
        const Rational& positive_rational = ((c.m_negative && !d.m_negative) ? d : c);
        cur.m_negative = (negative_rational.abs_value() > positive_rational.abs_value());
    }

    cur.m_denominator = c.m_denominator; // The denominator is the common one
    cur._simplify();
    return cur;
}

Rational& operator -= (Rational& cur, const Rational& a)
{
    // Subtraction is basically adding the additive-inverse of the right-hand operand.
    Rational a_neg(a.m_numerator, a.m_denominator, !a.m_negative);
    cur += a_neg;
    return cur;
}

Rational& operator *= (Rational& cur, const Rational& a)
{
    // a/b * c/d = (a*c)/(b*d)
    // Result is negative if exactly one of the operands is negative.
    cur.m_numerator *= a.m_numerator;
    cur.m_denominator *= a.m_denominator;
    cur.m_negative ^= a.m_negative;

    cur._simplify();
    return cur;
}

Rational& operator /= (Rational& cur, const Rational& a)
{
    // Division is just multiplication with the multiplicative-inverse.
    Rational a_inv(a.m_denominator, a.m_numerator, a.m_negative);
    cur *= a_inv;
    return cur;
}

Rational operator + (const Rational& a, const Rational& b)
{
    Rational res = a;
    res += b;
    return res;
}

Rational operator - (const Rational& a, const Rational& b)
{
    Rational res = a;
    res -= b;
    return res;
}

Rational operator * (const Rational& a, const Rational& b)
{
    Rational res = a;
    res *= b;
    return res;
}

Rational operator / (const Rational& a, const Rational& b)
{
    Rational res = a;
    res /= b;
    return res;
}

bool operator == (const Rational& a, const Rational& b)
{
    if (a.m_negative == b.m_negative)
    {
        if (a.m_denominator == b.m_denominator)
            return (a.m_numerator == b.m_numerator);
        else
        {
            // Put numbers on the common denominator
            Rational cd[2];
            Rational::common_denominator(cd, a, b);
            
            // If two rationals are on the common denominator, equality happens if they have the same numerator as well.
            return (cd[0].m_numerator == cd[1].m_numerator);
        }
    }
    else
        return false;
}

bool operator != (const Rational& a, const Rational& b)
{
    return !(a == b);
}

bool operator > (const Rational& a, const Rational& b)
{
    // If either number is a negative and the other is positive - the positive one wins.
    if (a.m_negative && !b.m_negative)
        return false;
    else if (!a.m_negative && b.m_negative)
        return true;
    else
    {
        // If both is the same sign, put them on the common denominator.
        Rational cd[2];
        Rational::common_denominator(cd, a, b);

        if (cd[0].m_negative && cd[1].m_negative)
            // Two negatives: one with the smaller numerator wins.
            return (cd[0].m_numerator < cd[1].m_numerator);
        else
            // Two positives: one with the bigger numerator wins.
            return (cd[0].m_numerator > cd[1].m_numerator);
    }
}

bool operator >= (const Rational& a, const Rational& b)
{
    if (a.m_negative && !b.m_negative)
        return false;
    else if (!a.m_negative && b.m_negative)
        return true;
    else
    {
        // If both is the same sign, put them on the common denominator.
        Rational cd[2];
        Rational::common_denominator(cd, a, b);

        if (cd[0].m_negative && cd[1].m_negative)
            // Two negatives: one with the smaller numerator wins.
            return (cd[0].m_numerator <= cd[1].m_numerator);
        else
            // Two positives: one with the bigger numerator wins.
            return (cd[0].m_numerator >= cd[1].m_numerator);
    }
}

bool operator < (const Rational& a, const Rational& b)
{
    if (a.m_negative && !b.m_negative)
        return true;
    else if (!a.m_negative && b.m_negative)
        return false;
    else
    {
        // If both is the same sign, put them on the common denominator.
        Rational cd[2];
        Rational::common_denominator(cd, a, b);

        if (cd[0].m_negative && cd[1].m_negative)
            // Two negatives: one with the bigger numerator wins.
            return (cd[0].m_numerator > cd[1].m_numerator);
        else
            // Two positives: one with the smaller numerator wins.
            return (cd[0].m_numerator < cd[1].m_numerator);
    }
}

bool operator <= (const Rational& a, const Rational& b)
{
    if (a.m_negative && !b.m_negative)
        return true;
    else if (!a.m_negative && b.m_negative)
        return false;
    else
    {
        // If both is the same sign, put them on the common denominator.
        Rational cd[2];
        Rational::common_denominator(cd, a, b);

        if (cd[0].m_negative && cd[1].m_negative)
            // Two negatives: one with the bigger numerator wins.
            return (cd[0].m_numerator >= cd[1].m_numerator);
        else
            // Two positives: one with the smaller numerator wins.
            return (cd[0].m_numerator <= cd[1].m_numerator);
    }
}

std::ostream& operator << (std::ostream& o, const Rational& frac)
{
    o << (frac.m_negative ? "-" : "") << frac.m_numerator;
    if (frac.m_denominator != 1)
        o << "/" << frac.m_denominator;
    return o;
}

void Rational::common_denominator(Rational cd[], const Rational& a, const Rational& b)
{
    // Put the two rational upon the common denominator
    unsigned long long commonDenominator = a.m_denominator * b.m_denominator;
    Rational a_, b_;
    a_.m_numerator = a.m_numerator * b.m_denominator;
    b_.m_numerator = b.m_numerator * a.m_denominator;
    a_.m_denominator = commonDenominator;
    b_.m_denominator = commonDenominator;
    a_.m_negative = a.m_negative;
    b_.m_negative = b.m_negative;

    // Using std::pair would be nice...
    // Fucking hackfixes everywhere to prevent the copy constructor from firing and simplifying us.
    cd[0] = a_;
    cd[1] = b_;
}

void Rational::_simplify()
{
    // To simplify a rational number, we divide both the numerator and the denominator with their GCD.
    // So, for example, 25/100 could be just written as 5/20, that is 1/4.

    // If the numerator is zero, we don't simplify.
    if (this->m_numerator == 0)
        return;
    
    // If the denominator somehow becomes zero, we bail out
    if (this->m_denominator == 0)
    {
        std::stringstream errormessage;
        errormessage << (this->m_negative ? "-" : "") << this->m_numerator << "/" << this->m_denominator << ": division by zero";

        throw std::invalid_argument(errormessage.str());
    }

    unsigned long long gcd = euclidean<unsigned long long>(this->m_numerator, this->m_denominator);
    
    if (gcd > 1)
    { // If GCD is 1 there is nothing to simplify.
        this->m_numerator /= gcd;
        this->m_denominator /= gcd;
    }
}

#ifdef _ADD_MULT_IDENTITY_H
// The additive identity is 0/1 (0), the multiplicative is 1/1 (1).
template<> struct id_multiplicative_exists<Rational> : id_multiplicative_known{};
template<> struct id_multiplicative<Rational> { static Rational const value; };
Rational const id_multiplicative<Rational>::value = 
    Rational(id_multiplicative<unsigned long long>::value, id_multiplicative<unsigned long long>::value, false);

template<> struct id_additive_exists<Rational> : id_additive_known{};
template<> struct id_additive<Rational> { static Rational const value; };
Rational const id_additive<Rational>::value = 
    Rational(id_additive<unsigned long long>::value, id_multiplicative<unsigned long long>::value, false);
#endif // _ADD_MULT_IDENTITY_H

#ifdef _ABSVALUE_WRAPPER_H
// An absolute value exists in the type.
template<>
struct abs_value<Rational>
{
    static const bool known = true;
    static Rational abs(Rational val)
    {
        return val.abs_value();
    }
};
#endif // _ABSVALUE_WRAPPER_H

#endif // _RATIONAL_H