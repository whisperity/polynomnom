#ifndef _EUCLIDEAN_ALGO_H
#define _EUCLIDEAN_ALGO_H

#include "add_mult_identity.hpp"

template<typename T>
T euclidean(const T& a_orig, const T& b_orig)
{
    T a = a_orig;
    T b = b_orig;
    T c;

    // Swap the operands if needed
    if (a < b)
    {
        c = a;
        a = b;
        b = c;
    }

    c = a % b; // Get the first remainder
    while (c > id_additive<T>::value)
    {
        // While there is a remainder, always modulo the previous right-hand operand with the previous remainder.
        a = b;
        b = c;
        c = a % b;
    }

    // The last non-zero remainder is the GCD.
    return b;
}

template<typename T>
T euclidean_lcm(const T& a_orig, const T& b_orig)
{
    // The Euclidean algorithm can also be used to calculate least common multiple.
    T gcd = euclidean<T>(a_orig, b_orig);
    return (a_orig * b_orig) / gcd;
}

// Type for the 'ax + by = gcd' result of the extended Euclidean algorithm
template<typename T>
struct EEuclideanResult
{
    T gcd;
    T x; // the coefficient for a
    T a;
    T y; // the coefficient for b
    T b;
};

template<typename T>
EEuclideanResult<T> extended_euclidean(const T& a_orig, const T& b_orig)
{
    T a = a_orig;
    T b = b_orig;

    // Init step.
    // x0 := 1, y0 := 0     but we use the templated multiplicative-additive identity values here
    T x0 = id_multiplicative<T>::value;
    T y0 = id_additive<T>::value;

    T x1 = id_additive<T>::value;
    T y1 = id_multiplicative<T>::value;

    T xn = id_multiplicative<T>::value;
    T yn = id_multiplicative<T>::value;

    T q;
    T r = a % b;
    
    while (r > id_additive<T>::value)
    {
        // Apart from calculating the GCD, the extended euclidean algorithm also calculates a linear combination
        // of the two arguments which result in said GCD.
        q = a / b;
        xn = x0 - q * x1;
        yn = y0 - q * y1;

        x0 = x1; y0 = y1;
        x1 = xn; y1 = yn;

        a = b;
        b = r;
        r = a % b;
    }

    EEuclideanResult<T> result;
    result.gcd = b;
    result.a = a_orig;  result.b = b_orig;
    result.x = xn; result.y = yn;
    return result;
}

#endif // _EUCLIDEAN_ALGO_H
