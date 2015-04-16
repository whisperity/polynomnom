#include "Polynomial.hpp"
#include <math.h>

using namespace std;

Polynomial::Polynomial()
{
    this->_performCleanup();
    //cout << "Polynomial initialized." << endl;
    // Noop.
}

/*Polynomial::Polynomial(const size_t coefficients)
{
    // Ez nem mûködik mivel a map-nak nincs alapból mérete.
    //this->m_coefficients.reserve(coefficients);
}*/

Polynomial::Polynomial(const Polynomial& poly)
{
    // Copy the map.
    this->m_coefficients = poly.m_coefficients;
}

#include <sstream>

Polynomial::~Polynomial()
{
    stringstream ss;
    ss << *this;

    cout << "The polynomial " << ss.str() << " was destructed." << endl;
}

const Polynomial& Polynomial::operator=(const Polynomial& poly)
{
    this->m_coefficients = poly.m_coefficients;
    return *this;
}

double Polynomial::operator[] (const size_t index) const
{
    return getMember(index);
}

/* DISABLED: cannot perform a cleanup this way! */
/*double& Polynomial::operator[] (const size_t index)
{
    setMember(index, )
}*/


/*Polynomial Polynomial::operator+(const Polynomial& poly)
{

}

/*Polynomial Polynomial::operator-(const Polynomial& poly)
{

}

/*bool Polynomial::operator==(const Polynomial& poly) const
{

}

/*bool Polynomial::operator!=(const Polynomial& poly) const
{

}*/

std::ostream& operator << (std::ostream& o, const Polynomial& poly)
{
    if (poly.isNull())
        return o << "nullpolynomial";

    bool firstCoeff = true;
    for (coefficientMap::const_iterator cit = poly.m_coefficients.cbegin();
        cit != poly.m_coefficients.cend(); ++cit)
    {
        // it->first: power
        // it->second: coefficient
        /*const size_t& power = it->first;
        const double& coefficient = it->second;*/

        // Omit the members with 0 coefficient
        //if (cit->second == 0) continue;

        if (!firstCoeff)
            o << " ";

        // Print the signum of the coefficient
        // (so it would neatly look as -5x^2 + 3x - 2)
        if (cit->first < 0)
            o << "-";
        else if (cit->first > 0 && !firstCoeff)
            o << "+";

        o << cit->second;

        // If the power is 0, it's the constant member, so don't print it
        if (cit->first != 0)
            o << "x^" << cit->first;

        if (firstCoeff) firstCoeff = false;
    }

    return o;
}

size_t Polynomial::degree() const
{
    return this->m_degree;
}

double Polynomial::getMember(const size_t index) const
{
    if (this->hasMember(index))
        return this->m_coefficients.at(index);
    else
        return .0; // Non-existant members are just not stored: they are mathematically there with 0 coefficient.
}

void Polynomial::setMember(const size_t index, double coefficient)
{
    this->m_coefficients[index] = coefficient; // Add or reassign a member
    this->_performCleanup();
}

double Polynomial::run(const double t) const
{
    double result = 0;

    for (size_t power = 0; power <= this->degree(); ++power)
    {
        cout << result << " += " << this->getMember(power) << " * " << t << "^" << power << endl;
        result += this->getMember(power) * (pow(t, power));
    }

    return result;
}

/*void Polynomial::add(const Polynomial& poly)
{

}

/*void Polynomial::subtract(const Polynomial& poly)
{

}

/*bool Polynomial::equals(const Polynomial& poly) const
{

}*/

bool Polynomial::isNull() const
{
    // A polynomial is a null-polynomial if every coefficient is zero.
    // Utilising the invariant, if we are nullpolynomial, the degree is zero and that 0th coefficient is zero.
    return (this->degree() == 0 && this->getMember(0) == 0);
}

void Polynomial::_performCleanup()
{
    // Cleanup consists of removing the 0 coefficient parts from the map
    size_t num_coefficients = 0;
    size_t removePowers[this->m_coefficients.size()];

    // And keeping the degree of the object the degree of the polynomial
    size_t maxPower = 0;

    // Get the 0 coefficient elements from the map
    for (coefficientMap::const_iterator cit = this->m_coefficients.cbegin();
        cit != this->m_coefficients.cend(); ++cit)
    {
        if (cit->second == 0)
            removePowers[num_coefficients++] = cit->first;
        else
        {
            if (cit->first > maxPower)
                maxPower = cit->first;
        }
    }

    // Remove the elements
    for (size_t i = 0; i < num_coefficients; ++i)
        this->m_coefficients.erase(removePowers[i]);

    this->m_degree = maxPower;
    return;
}

bool Polynomial::hasMember(const size_t index) const
{
    // This is basically the standard way of finding if the given power exists
    // The iterator becomes the end of the collection if the value is not found
    return this->m_coefficients.find(index) != this->m_coefficients.end();
}

/*Polynomial operator+(const Polynomial& a, const Polynomial& b)
{

}

/*Polynomial operator-(const Polynomial& a, const Polynomial& b)
{

}

/*Polynomial operator*(const Polynomial& a, const Polynomial& b)
{

}

/*Polynomial operator/(const Polynomial& a, const Polynomial& b)
{

}
*/
