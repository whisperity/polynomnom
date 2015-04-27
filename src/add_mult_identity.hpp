#ifndef _ADD_MULT_IDENTITY_H
#define _ADD_MULT_IDENTITY_H

// Check is a given type happens to have a multiplicative identity, and if so, return it.
// This is implemented here for basic arithmetic types.

// Indicate that we know or do not know the multiplicative identity

struct id_multiplicative_known
{
	static const bool value = true;
};

struct id_multiplicative_unknown
{
	static const bool value = false;
};


// By default, arbitrary types' MIs are unknown and undefined.

template<typename _T>
struct id_multiplicative_exists : id_multiplicative_unknown
{
};

// Defining an empty struct we make sure error message happens for types unknown

template<typename _T>
struct id_multiplicative
{
};

// Shortcut for arithmetic integral types where the MI is 1.

template<typename _T>
struct id_multiplicative_integral
{
	static const _T value = 1;
};


// Specialise the template, because we know the multiplicative inverse for arithmetic types
// Existance

template<> struct id_multiplicative_exists<char> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<unsigned char> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<signed char> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<wchar_t> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<unsigned short> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<signed short> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<unsigned int> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<signed int> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<unsigned long> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<signed long> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<unsigned long long> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<signed long long> : id_multiplicative_known{};

template<> struct id_multiplicative_exists<float> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<double> : id_multiplicative_known{};
template<> struct id_multiplicative_exists<long double> : id_multiplicative_known{};

// Value

template<> struct id_multiplicative<char> : id_multiplicative_integral<char>{};
template<> struct id_multiplicative<unsigned char> : id_multiplicative_integral<unsigned char>{};
template<> struct id_multiplicative<signed char> : id_multiplicative_integral<signed char>{};
template<> struct id_multiplicative<wchar_t> : id_multiplicative_integral<wchar_t>{};
template<> struct id_multiplicative<unsigned short> : id_multiplicative_integral<unsigned short>{};
template<> struct id_multiplicative<signed short> : id_multiplicative_integral<signed short>{};
template<> struct id_multiplicative<unsigned int> : id_multiplicative_integral<unsigned int>{};
template<> struct id_multiplicative<signed int> : id_multiplicative_integral<signed int>{};
template<> struct id_multiplicative<unsigned long> : id_multiplicative_integral<unsigned long>{};
template<> struct id_multiplicative<signed long> : id_multiplicative_integral<signed long>{};
template<> struct id_multiplicative<unsigned long long> : id_multiplicative_integral<unsigned long long>{};
template<> struct id_multiplicative<signed long long> : id_multiplicative_integral<signed long long>{};

template<> struct id_multiplicative<float> { static float const value; };
template<> struct id_multiplicative<double> { static double const value; };
template<> struct id_multiplicative<long double> { static long double const value; };

float const id_multiplicative<float>::value = 1.0;
double const id_multiplicative<double>::value = 1.0;
long double const id_multiplicative<long double>::value = 1.0;

// ------------------------
// Do the same for additive identity

struct id_additive_known
{
    static const bool value = true;
};

struct id_additive_unknown
{
    static const bool value = false;
};

template<typename _T>
struct id_additive_exists : id_additive_unknown
{
};

template<typename _T>
struct id_additive
{
};

template<typename _T>
struct id_additive_integral
{
    static const _T value = 0;
};

template<> struct id_additive_exists<char> : id_additive_known{};
template<> struct id_additive_exists<unsigned char> : id_additive_known{};
template<> struct id_additive_exists<signed char> : id_additive_known{};
template<> struct id_additive_exists<wchar_t> : id_additive_known{};
template<> struct id_additive_exists<unsigned short> : id_additive_known{};
template<> struct id_additive_exists<signed short> : id_additive_known{};
template<> struct id_additive_exists<unsigned int> : id_additive_known{};
template<> struct id_additive_exists<signed int> : id_additive_known{};
template<> struct id_additive_exists<unsigned long> : id_additive_known{};
template<> struct id_additive_exists<signed long> : id_additive_known{};
template<> struct id_additive_exists<unsigned long long> : id_additive_known{};
template<> struct id_additive_exists<signed long long> : id_additive_known{};

template<> struct id_additive_exists<float> : id_additive_known{};
template<> struct id_additive_exists<double> : id_additive_known{};
template<> struct id_additive_exists<long double> : id_additive_known{};

template<> struct id_additive<char> : id_additive_integral<char>{};
template<> struct id_additive<unsigned char> : id_additive_integral<unsigned char>{};
template<> struct id_additive<signed char> : id_additive_integral<signed char>{};
template<> struct id_additive<wchar_t> : id_additive_integral<wchar_t>{};
template<> struct id_additive<unsigned short> : id_additive_integral<unsigned short>{};
template<> struct id_additive<signed short> : id_additive_integral<signed short>{};
template<> struct id_additive<unsigned int> : id_additive_integral<unsigned int>{};
template<> struct id_additive<signed int> : id_additive_integral<signed int>{};
template<> struct id_additive<unsigned long> : id_additive_integral<unsigned long>{};
template<> struct id_additive<signed long> : id_additive_integral<signed long>{};
template<> struct id_additive<unsigned long long> : id_additive_integral<unsigned long long>{};
template<> struct id_additive<signed long long> : id_additive_integral<signed long long>{};

template<> struct id_additive<float> { static float const value; };
template<> struct id_additive<double> { static double const value; };
template<> struct id_additive<long double> { static long double const value; };

float const id_additive<float>::value = 0.0;
double const id_additive<double>::value = 0.0;
long double const id_additive<long double>::value = 0.0;

#endif // _ADD_MULT_IDENTITY_H