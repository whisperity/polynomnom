#include "Polynomial.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

Polynomial::Polynomial()
{
    this->_performCleanup(); // Make the object into default state
    //cout << "Polynomial initialized." << endl;
    // Noop.
}

Polynomial::Polynomial(double coefficient)
{
    this->setMember(0, coefficient);
    this->_performCleanup();
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
    this->_performCleanup();
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
    this->_performCleanup();
    return *this;
}

double Polynomial::operator[] (const size_t index) const
{
    return getMember(index);
}

bool Polynomial::operator==(const Polynomial& poly) const
{
    return this->equals(poly);
}

bool Polynomial::operator!=(const Polynomial& poly) const
{
    return !this->equals(poly);
}

std::ostream& operator << (std::ostream& o, const Polynomial& poly)
{
    if (poly.isNull())
        return o << "nullPolynomial";
    else if (poly.isConstant())
        return o << poly.getMember(0) << "(constant)";

    bool firstCoeff = true;
    for (coefficientMap::const_iterator cit = poly.m_coefficients.cbegin();
        cit != poly.m_coefficients.cend(); ++cit)
    {
        // it->first: power
        // it->second: coefficient

        // Omit the members with 0 coefficient
        if (cit->second == 0) continue;

        if (!firstCoeff)
            o << " ";

        // Print the signum of the coefficient
        // (so it would neatly look as -5x^2 + 3x - 2)
        if (cit->second < 0)
            o << "- ";
        else if (cit->second > 0 && !firstCoeff)
            o << "+ ";

        // Only print the coefficient if it is not 1. The 1 multiplier can be omitted.
        if (fabs(cit->second) != 1)
            o << fabs(cit->second);

        // Don't print the power for the first-order member and don't print x for the constant member
        if (cit->first > 1)
            o << "x^" << cit->first;
        if (cit->first == 1)
            o << "x";

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

void Polynomial::setMember(const size_t index, const double coefficient)
{
    this->m_coefficients[index] = coefficient; // Add or reassign a member
    this->_performCleanup();
}

double Polynomial::at(const double t) const
{
    double result = 0;

    for (size_t power = 0; power <= this->degree(); ++power)
    {
        //cout << result << " += " << this->getMember(power) << " * " << t << "^" << power << endl;
        result += this->getMember(power) * (pow(t, power));
    }

    return result;
}

void Polynomial::add(const Polynomial& poly)
{
    //          2x^2 + 3x + 1
    // (+) x^3 + x^2 - 2x - 2
    // ----------------------
    //     x^3 +3x^2 +  x - 1
    //
    // So we have to member-by-member add the coefficients to get the added polynomial

    for (size_t p = 0; p <= max(this->degree(), poly.degree()); ++p)
        this->setMember(p, this->getMember(p) + poly.getMember(p));
}

void Polynomial::subtract(const Polynomial& poly)
{
    // Subtraction works just as so
    for (size_t p = 0; p <= max(this->degree(), poly.degree()); ++p)
        this->setMember(p, this->getMember(p) - poly.getMember(p));
}

void Polynomial::multiply(const Polynomial& poly)
{
    // If either is a nullpolynomial, the multiple is trivially a nullpolynomial
    if (this->isNull() || poly.isNull())
        this->m_coefficients.clear();
    // If both is a constant, the multiple is trivially the constants' multiple
    else if (this->isConstant() && poly.isConstant())
    {
        double multiple = this->getMember(0) * poly.getMember(0);

        this->m_coefficients.clear();
        this->setMember(0, multiple);
    }
    // If either polynomials is a constant one (but not both), we can still ease the multiplication
    else if (this->isConstant() || poly.isConstant())
    {
        // Select which polynomial is the constant and the more complex one;
        const Polynomial* constantOne = (this->isConstant() ? this : &poly);
        const Polynomial* complexOne = (!this->isConstant() ? this : &poly);
        Polynomial multiple;

        // Only multiply the coefficients of the complex polynomial by the given constant, storing it in this
        double constant = constantOne->leadingCoefficient();
        for (size_t i = 0; i <= complexOne->degree(); ++i)
        {
            double coeff = complexOne->getMember(i);
            if (coeff == 0) continue;

            multiple.setMember(i, coeff * constant);
        }

        // Let the multiplied polynomial be the current one
        *this = multiple;
    }
    // If both polynomials are complex ones, we do the multiplication by hand
    else
    {
        vector<double> multi_coefficients;
        multi_coefficients.resize(this->degree() + poly.degree() + 1); // Create space for the coefficients

        for (size_t i = 0; i <= this->degree(); ++i)
        {
            double left = this->getMember(i);
            if (left == 0) continue; // 0 * anything = 0

            for (size_t j = 0; j <= poly.degree(); ++j)
            {
                double right = poly.getMember(j);
                if (right == 0) continue; // anything * 0 = 0

                // Basically you have to multiply every member with every member...
                multi_coefficients.at(i+j) += left * right;
            }
        }

        // Set the calculated coefficients
        this->m_coefficients.clear();
        for (size_t i = 0; i < multi_coefficients.size(); ++i)
            this->setMember(i, multi_coefficients.at(i));
    }
}

bool Polynomial::divide(const Polynomial& divisor, Polynomial& quotient, Polynomial& remainder) const
{
    if (divisor.isNull())
        return false;

    if (divisor.degree() > this->degree())
    {
        remainder = *this;
        Polynomial quotient_null;
        quotient = quotient_null;
    }
    else
    // Degree of divisor is smaller or equal than divident
    {
        Polynomial dividend = *this; // Save out the current instance
        // f : g = q
        // f % g = r
        // f: dividend (this), g: divisor, q: quotient, r: remainder
        // The dividend is only initially 'this', it gets consumed as the division happens.

        size_t quotient_max_degree = dividend.degree() - divisor.degree();
        size_t quotient_member_degree = quotient_max_degree;
        // We can only divide further if there is something to divide.
        while (quotient_member_degree >= 0 && quotient_member_degree <= quotient_max_degree && !dividend.isNull())
        {
            /*cout << "-----------------------------" << endl;
            cout << "I'm running a division loop. Current degree of the quotient: " << quotient_member_degree << endl;
            cout << "(Maximum plausible degree of quotient: " << quotient_max_degree << ")" << endl;
            cout << "Dividend: " << dividend << endl;*/
            // Subtract the divisor's LC from the dividend's LC
            // (and so the powers), so that we get the LC of the quotient.
            /*cout << "deg(divident) = " << dividend.degree() << endl;
            cout << "lc(dividend) = " << dividend.leadingCoefficient() << endl;*/

            // After subtracting the LCs, we get the quotient's LC.
            // Using polynomial long division, we now multiply the quotient's LC by the divisor (-> getting a polynomial)
            // and thus, we subtract that from the dividend... and loop this whole shit.)

            // If the current member degree underflows, thus reaches a values higher than the maximum degree
            // We terminate the whole cycle because we reached the remainder.
            if (quotient_member_degree > quotient_max_degree)
                break;

            // Set the current member of the quotient to the quotient of the coefficients
            quotient.setMember(quotient_member_degree, dividend.leadingCoefficient() / divisor.leadingCoefficient());

            Polynomial multiplier;
            multiplier.setMember(quotient_member_degree, quotient.getMember(quotient_member_degree));

            /*cout << "Divisor: " << divisor << endl;*/
            Polynomial inner_multiple = divisor * multiplier;

            dividend = dividend - inner_multiple;

            /*cout << "Current quotient (across division operation): " << quotient << endl;
            cout << "Current multiplier: " << multiplier << endl;
            cout << "Multiplied dividend: (this will be subtracted) " << inner_multiple << endl;
            cout << "New dividend (after subtraction): " << dividend << endl;*/

            quotient_member_degree = dividend.degree() - divisor.degree();
        }

        // When the loop reaches its terminus, we divided everything we could.
        // Anything that remained in the dividend (after subtraction) is actually the remainder.
        remainder = dividend; // So assign it into its proper place.
    }
}

bool Polynomial::equals(const Polynomial& poly) const
{
    // Two polynomials are equal if their degree is equal and every coefficient is equal for every member.
    /* We could do it this way, but it's safer if we check without assuming the invariant for now...
    return this->m_coefficients.size() == poly.m_coefficients.size() &&
        equal(this->m_coefficients.cbegin(), this->m_coefficients.cend(), poly.m_coefficients.cbegin());
    */

    // Two polynomials equal if their degree is equal and every coefficient is equal for every member
    if (this->degree() != poly.degree())
        return false;

    bool is_equal = true; // Assume that it is equal
    for (size_t i = 0; i <= this->degree(); ++i) // The sizes are now equal
        is_equal = is_equal || (this->getMember(i) == poly.getMember(i));

    return is_equal;
}

bool Polynomial::isNull() const
{
    // A polynomial is a null-polynomial if every coefficient is zero.
    // Utilising the invariant, if we are nullpolynomial, the degree is zero and that 0th coefficient is zero.
    return (this->degree() == 0 && this->getMember(0) == 0);
}

bool Polynomial::isConstant() const
{
    // The polynomial is a constant one if there is only a constant (0th power) member
    return (this->degree() == 0 && this->getMember(0) != 0);
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
            if (cit->first > maxPower)
                maxPower = cit->first;
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

Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
    Polynomial ret = a;
    ret.add(b);

    return ret;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b)
{
    Polynomial ret = a;
    ret.subtract(b);

    return ret;
}

Polynomial operator*(const Polynomial& a, const Polynomial& b)
{
    Polynomial ret = a;
    ret.multiply(b);

    return ret;
}

Polynomial operator/(const Polynomial& a, const Polynomial& b)
{
    Polynomial q; // quotient
    Polynomial r; // remainder

    a.divide(b, q, r);

    return q;
}

Polynomial operator%(const Polynomial& a, const Polynomial& b)
{
    Polynomial q; // quotient
    Polynomial r; // remainder

    a.divide(b, q, r);

    return r;
}
