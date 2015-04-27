#ifndef _RESIDUE_H
#define _RESIDUE_H

#include <vector>

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
        //template<long N>
        //friend ResidueNum<N> operator / (const ResidueNum<N>& a, const ResidueNum<N>& b);

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
        static const long m_modulo = M;
};

template<long M>
ResidueNum<M>::ResidueNum()
{
    this->m_number = 0;
}

template<long M>
ResidueNum<M>::ResidueNum(const long num)
{
    this->m_number = num;
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
    Residue r(a.m_modulo);

    ResidueNum<M> c(r.add(a.m_number, b.m_number));
    return c;
}

template<long M>
ResidueNum<M> operator - (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(a.m_modulo);

    ResidueNum<M> c(r.subtract(a.m_number, b.m_number));
    return c;
}

template<long M>
ResidueNum<M> operator * (const ResidueNum<M>& a, const ResidueNum<M>& b)
{
    Residue r(a.m_modulo);

    ResidueNum<M> c(r.multiply(a.m_number, b.m_number));
    return c;
}

/*template<long M>
ResidueNum<M> operator / (const ResidueNum<M>& a, const ResidueNum<M>& b)
{*/
    // There has to be some sort of a congruency solver here.
    // Consider 5 : 2 = ? (mod 7)
    // The answer is 6, because 6 * 2 = 12 ==congruent== 5 (mod 7).
    //
    // So basically, 2x === 5 (mod 7) needs a solution for x. The solution will be 6's congruence class.
/*}*/

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


// Declare the additive and multiplicative inverses for residue numbers
template<long M> struct id_multiplicative_exists<ResidueNum<M>> : id_multiplicative_known{};
template<long M> struct id_multiplicative<ResidueNum<M>> { static ResidueNum<M> const value; };
template<long M> ResidueNum<M> const id_multiplicative<ResidueNum<M>>::value = ResidueNum<M>(1);

template<long M> struct id_additive_exists<ResidueNum<M>> : id_additive_known{};
template<long M> struct id_additive<ResidueNum<M>> { static ResidueNum<M> const value; };
template<long M> ResidueNum<M> const id_additive<ResidueNum<M>>::value = ResidueNum<M>(0);

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
#endif // _RESIDUE_H