#ifndef _LAGRANGE_H
#define _LAGRANGE_H

#include <algorithm>
#include <vector>
#include "add_mult_identity.hpp"
#include "Polynomial.hpp"

// The template T here is just a wrapper for the internal polynomial's type.
// As so, the same restrictions apply.

// Lagrange interpolation creates a polynomial from a(n arbitrary) set of (Cj, Dj) pairs
// Which polynomial, when executed for its value at Cj, will result in Dj (for all Cj values).

template<typename T>
class Lagrange
{
    public:
        Lagrange<T>();
        void add(const T Ci, const T Di);
        void remove(const T Ci);
        bool get(const T Ci, T& Di) const;

        bool build();
        Polynomial<T> polynomial() const;

    private:
        // (Ci, Di) pairs
        std::vector<std::pair<T, T>> m_knownPairs;
        bool m_built;
        bool m_checkPassed;

        void _check(const Polynomial<T>& poly);
        Polynomial<T> m_interpolated;
};

template<typename T>
Lagrange<T>::Lagrange()
{
    this->m_knownPairs.clear();
    this->m_built = false;
    this->m_checkPassed = false;
    this->m_interpolated = Polynomial<T>();
}

template<typename T>
void Lagrange<T>::add(const T Ci, const T Di)
{
    // Check if the given Ci is already in the vector: if yes, remove it.
    typename std::vector<std::pair<T, T>>::const_iterator it =
        std::find_if(this->m_knownPairs.cbegin(), this->m_knownPairs.cend(),
            [&Ci](const std::pair<T, T>& thisPair)
            {
                return thisPair.first == Ci;
            }
    );

    if (it != this->m_knownPairs.cend())
        this->m_knownPairs.erase(it);
    
    this->m_knownPairs.push_back(std::pair<T, T>(Ci, Di));

    // Mark the interpolator changed
    this->m_built = false;
    this->m_checkPassed = false;
}

template<typename T>
void Lagrange<T>::remove(const T Ci)
{
    typename std::vector<std::pair<T, T>>::const_iterator it =
        std::find_if(this->m_knownPairs.cbegin(), this->m_knownPairs.cend(),
            [&Ci](const std::pair<T, T>& thisPair)
            {
                return thisPair.first == Ci;
            }
    );

    if (it != this->m_knownPairs.cend())
        this->m_knownPairs.erase(it);

    // Mark the change
    this->m_built = false;
    this->m_checkPassed = false;
}

template<typename T>
bool Lagrange<T>::get(const T Ci, T& Di) const
{
    // Get the Di for the Ci
    typename std::vector<std::pair<T, T>>::const_iterator it =
        std::find_if(this->m_knownPairs.cbegin(), this->m_knownPairs.cend(),
            [&Ci](const std::pair<T, T>& thisPair)
            {
                return thisPair.first == Ci;
            }
    );
    
    if (it != this->m_knownPairs.cend())
    {
        // Get the element pointed by the iterator and set the value to the return variable
        std::pair<T, T> elem = (*it);
        Di = elem.second;
        return true;
    }
    else
        return false;
}

template<typename T>
Polynomial<T> Lagrange<T>::polynomial() const
{ // Return the copy of the encapsulated polynomial only!
    if (this->m_built && this->m_checkPassed)
        return Polynomial<T>(this->m_interpolated);
    else
        return Polynomial<T>();
}

template<typename T>
bool Lagrange<T>::build()
{
    // Don't do anything if the polynomial was already built to conserve processing power
    if (this->m_built)
        return this->m_checkPassed;

    // The lagrange interpolation work as follows:
    // 1) We create N pieces of polynomials (li) for each Ci member.
    //    Each of these polynomials are created as the product of the "sub-polynomials" (x - Cj) / (Ci - Cj)
    //    (where i is the index of the current member and j the index of every other members)
    //
    // 2) After each of the polynomials are created, we create the full polynomial as the sum of
    //    Di * li for each (Ci, Di) pair.

    Polynomial<T> full;

    for (typename std::vector<std::pair<T, T>>::const_iterator it = this->m_knownPairs.cbegin();
        it != this->m_knownPairs.cend(); ++it)
    {
        T Ci = (*it).first;
        Polynomial<T> li(id_multiplicative<T>::value); // Make the polynomial default for multiplication

        // Create the sub-polynomials for the current index.
        for (typename std::vector<std::pair<T, T>>::const_iterator inner = this->m_knownPairs.cbegin();
            inner != this->m_knownPairs.cend(); ++inner)
        {
            T Cj = (*inner).first;
            if (Cj == Ci) continue; // Always skip the current member
            Polynomial<T> li_sub_numerator, li_sub_denominator;

            /*std::cout << "x - " << Cj << " / " << Ci << " - " << Cj << std::endl;*/
            // Create the numerator (x - Cj)
            li_sub_numerator.setMember(1, id_multiplicative<T>::value); // 1x
            li_sub_numerator.subtract(Polynomial<T>(Cj)); // - Cj

            // Create the denominator (Ci - Cj)
            li_sub_denominator.setMember(0, Ci - Cj);

            /*std::cout << li_sub_numerator << "/" << li_sub_denominator << std::endl;
            std::cout << std::endl;*/

            // Multiply the polynomial to li
            Polynomial<T> li_sub = li_sub_numerator / li_sub_denominator;
            li.multiply(li_sub);
        }

        std::cout << "l" << Ci << " = " <<  li << std::endl;
        std::cout << std::endl;

        // Add Di * li to the full polynomial.
        T Di = (*it).second;
        Polynomial<T> mult = Polynomial<T>(Di) * li;
        full.add(mult);
    }
    /*std::cout << full << std::endl;*/
    this->m_built = true;
    this->m_checkPassed = false;

    // Check the polynomial if its good.
    this->_check(full);

    if (this->m_checkPassed)
        this->m_interpolated = full;
    return this->m_checkPassed;
}

template<typename T>
void Lagrange<T>::_check(const Polynomial<T>& poly)
{
    // Check the built polynomial if its value for each Ci is exactly Di.
    // If the build was done right, it should be: Lagrange-interpolation
    // constructs a polynomial which SHOULD be Di at Ci.

    this->m_checkPassed = false;
    bool temp = true;
    for (typename std::vector<std::pair<T, T>>::const_iterator it = this->m_knownPairs.cbegin();
        it != this->m_knownPairs.cend(); ++it)
    {
        // (Ci, Di) pairs
        const std::pair<T, T> * thisPair = &(*it);
        
        temp &= (poly.at(thisPair->first) == thisPair->second);
    }

    this->m_checkPassed = temp;
}

#endif // _LAGRANGE_H