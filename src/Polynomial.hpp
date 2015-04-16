#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include <cstddef>
#include <iostream>
#include <map>

typedef std::map<size_t, double, std::greater<size_t>> coefficientMap;

class Polynomial
{
    public:
        /* Constructors */
        // Default constructor
        Polynomial();

        // Default constructor with initial coefficient length provided
        //Polynomial(const size_t coefficients);

        // Copy constructor from another polynom
        Polynomial(const Polynomial& poly);

        /* Destructor */
        ~Polynomial();

        /* Operators */
        // Assignment operator
        const Polynomial& operator = (const Polynomial& poly);

        // Subscript getter operator to get an nth coefficient
        double operator [] (const size_t index) const;
        /*double operator [] (const size_t index) const;
        double& operator [] (const size_t index);*/

        // Add and subtract operator
        Polynomial operator + (const Polynomial& poly);
        Polynomial operator - (const Polynomial& poly);

        // Équalité, inéqualité
        bool operator == (const Polynomial& poly) const;
        bool operator != (const Polynomial& poly) const;

        // Printing operator
        friend std::ostream& operator << (std::ostream& o, const Polynomial& poly);

        /* Member functions */
        // Get the degree
        size_t degree() const;

        // Get the nth coefficient
        double getMember(const size_t index) const;

        // Set the nth coefficient
        void setMember(const size_t index, const double coefficient);

        // Calculate the polynomial function's value for variable 't'
        double run(const double t) const;

        // Add and subtract a polynomial from the current
        void add(const Polynomial& poly);
        void subtract(const Polynomial& poly);

        // Equalité
        bool equals(const Polynomial& poly) const;

        // Get if the polynomial is a nullpolynomial (that is: every coefficient is zero)
        bool isNull() const;

    private:
        // Array for coefficients
        // (First part of the pair is the power of the indeterminate,
        // the second part is the coefficient.)
        coefficientMap m_coefficients;

        // Degree of the polynomial
        size_t m_degree;

        // Determine if there is an indeterminate of the given power index
        bool hasMember(const size_t index) const;

        // Internal cleanup function.
        void _performCleanup();
};

/* Operators between two instances */
Polynomial operator + (const Polynomial& a, const Polynomial& b);
Polynomial operator - (const Polynomial& a, const Polynomial& b);
Polynomial operator * (const Polynomial& a, const Polynomial& b);
Polynomial operator / (const Polynomial& a, const Polynomial& b);

#endif // _POLYNOMIAL_H
