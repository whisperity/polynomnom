#ifndef _RESIDUE_H
#define _RESIDUE_H

#include <stdexcept>
#include <sstream>
#include <vector>
#include "EuclideanAlgorithm.hpp"

class Residue
{
    public:
        // Create a residue class for the given modulo
        Residue(const long mod);

        long modulo() const;

        // Do +, - and * operation in the residue class
        long add(const long& a, const long& b) const;
        long subtract(const long& a, const long& b) const;
        long multiply(const long& a, const long& b) const;

        // Calculate the modulo of the given number in the residue class
        long calcMod(const long& a) const;

    private:
        long m_modulo;
};

Residue::Residue(const long mod)
{
    this->m_modulo = mod;
}

long Residue::modulo() const
{
    return this->m_modulo;
}

// Addition (subtraction) and multiplication is compatible with the equivalence classes
long Residue::add(const long& a, const long& b) const
{
    return this->calcMod(a + b);
}

long Residue::subtract(const long& a, const long& b) const
{
    return this->calcMod(a - b);
}

long Residue::multiply(const long& a, const long& b) const
{
    return this->calcMod(a * b);
}

long Residue::calcMod(const long& a) const
{
    // Calculate the modulo for the given number
    return (a % this->m_modulo + this->m_modulo) % this->m_modulo;
}

// Represent a number in a residue/congruence system
// M is the modulo
template<long M>
class ResidueNum
{
    public:
        ResidueNum<M>();
        ResidueNum<M>(const long num);
        ResidueNum<M>(const ResidueNum<M>& num);

        long number() const;

        template<long N>
        friend ResidueNum<N> operator + (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend ResidueNum<N> operator - (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend ResidueNum<N> operator * (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend ResidueNum<N> operator / (const ResidueNum<N>& a_orig, const ResidueNum<N>& b_orig);

        // This is needed for ResidueNum<> to work in Polynomial<> context
        template<long N>
        friend ResidueNum<N>& operator += (ResidueNum<N>& current, const ResidueNum<N>& add);

        template<long N>
        friend bool operator < (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend bool operator <= (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend bool operator > (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend bool operator >= (const ResidueNum<N>& a, const ResidueNum<N>& b);


        template<long N>
        friend bool operator == (const ResidueNum<N>& a, const ResidueNum<N>& b);
        template<long N>
        friend bool operator != (const ResidueNum<N>& a, const ResidueNum<N>& b);

        template<typename U>
        friend std::ostream& operator << (std::ostream& o, const Polynomial<U>& poly);
    private:
        long m_number;
        //static const long m_modulo = M;
};

template<long M>
ResidueNum<M>::ResidueNum()
{
    this->m_number = 0;
}

template<long M>
ResidueNum<M>::ResidueNum(const long num)
{
    Residue r(M);
    this->m_number = r.calcMod(num);
}

template<long M>
ResidueNum<M>::ResidueNum(const ResidueNum<M>& num)
{
    this->m_number = num.m_number;
}

template<long M>
long ResidueNum<M>::number() const
{
    return this->m_number;
}

template<long M>
ResidueNum<M> operator + (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);

    ResidueNum<M> c(r.add(a.m_number, b.m_number));
    return c;
}

template<long M>
ResidueNum<M> operator - (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);

    ResidueNum<M> c(r.subtract(a.m_number, b.m_number));
    return c;
}

template<long M>
ResidueNum<M> operator * (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);

    ResidueNum<M> c(r.multiply(a.m_number, b.m_number));
    return c;
}

template<long M>
ResidueNum<M> operator / (const ResidueNum<M>& a_orig, const ResidueNum<M>& b_orig)
{
    // Consider 5 : 2 = ? (mod 7)
    // (So we call the / operator as 5/2 (on ResidueNum<7>).
    // The answer is 6, because 6 * 2 = 12 ==congruent== 5 (mod 7).
    //
    // So basically, 2x === 5 (mod 7) needs a solution for x. The solution will be 6's congruence class.
    //               bx === a (mod m)

    // Reduce a and b mod m if they are not.
    Residue modOp(M);
    
    // Swap the operands because 5/2 actually means solving 2x === 5 (mod M)
    ResidueNum<M> a(modOp.calcMod(b_orig.number()));
    ResidueNum<M> b(modOp.calcMod(a_orig.number()));

    // Use extended euclidean algorithm to find solutions p and q for
    // a * p + m * q = gcd(a, m)
    EEuclideanResult<long> eer = extended_euclidean<long>(a.number(), M);
    // The result's X member is our 'p' variable for this operation.

    // If gcd(a, M) does not divide b then there are no solutions
    if (b.number() % eer.gcd != 0)
    {
        std::stringstream errormessage;
        errormessage << "gcd(" << eer.a << ", " << M << ") = " << eer.gcd;
        errormessage << " does not divide right-hand operand (b) " << b.number() << " -> no solutions.";

        throw std::invalid_argument(errormessage.str());
    }

    // The solution is given by the formula
    //          b * p
    // x0 = -------------  (mod m)
    //       gcd(a, m)
    long x0 = (b.number() * eer.x) / eer.gcd;

    // Normalise the result to be a positive number
    long result_Num = modOp.calcMod(x0);
    return ResidueNum<M>(result_Num);
}

template<long M>
ResidueNum<M>& operator += (ResidueNum<M>& current, const ResidueNum<M>& add)
{
    Residue r(M);

    ResidueNum<M> c(r.add(current.m_number, add.m_number));
    current = c;
    return current;
}

template<long M>
bool operator < (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) < r.calcMod(b.m_number);
}

template<long M>
bool operator <= (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) <= r.calcMod(b.m_number);
}

template<long M>
bool operator > (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) > r.calcMod(b.m_number);
}

template<long M>
bool operator >= (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) >= r.calcMod(b.m_number);
}

template<long M>
bool operator == (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) == r.calcMod(b.m_number);
}

template<long M>
bool operator != (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(M);
    return r.calcMod(a.m_number) != r.calcMod(b.m_number);
}

template<long M>
std::ostream& operator << (std::ostream& o, const ResidueNum<M>& num)
{
    o << num.number();
    return o;
}

#ifdef _ADD_MULT_IDENTITY_H
// Declare the additive and multiplicative inverses for residue numbers
template<long M> struct id_multiplicative_exists<ResidueNum<M>> : id_multiplicative_known{};
template<long M> struct id_multiplicative<ResidueNum<M>> { static ResidueNum<M> const value; };
template<long M> ResidueNum<M> const id_multiplicative<ResidueNum<M>>::value = ResidueNum<M>(1);

template<long M> struct id_additive_exists<ResidueNum<M>> : id_additive_known{};
template<long M> struct id_additive<ResidueNum<M>> { static ResidueNum<M> const value; };
template<long M> ResidueNum<M> const id_additive<ResidueNum<M>>::value = ResidueNum<M>(0);
#endif // _ADD_MULT_IDENTITY_H

#ifdef _ABSVALUE_WRAPPER_H
// Declare the absolute value function for residue numbers.
template<long M>
struct abs_value<ResidueNum<M>>
{
    static const bool known = true;
    static ResidueNum<M> abs(ResidueNum<M> val)
    {
        Residue r(M);
        long num = r.calcMod(val.number());
        ResidueNum<M> n(num);
        return n;
    }
};
#endif // _ABSVALUE_WRAPPER_H
#endif // _RESIDUE_H