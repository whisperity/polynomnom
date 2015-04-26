#ifndef _ABSVALUE_WRAPPER_H
#define _ABSVALUE_WRAPPER_H

#include <cmath>

// Gets the absolute value for a given type

// By default, we don't know the absolute value for an arbitrary type.

template<class _T>
struct abs_value
{
    static const bool known = false;
};

// But we know for arithmetic ones, providing a wrapper over fabs or abs.

template<class _T>
struct abs_value_integral
{
    static const bool known = true;
    static _T abs(_T val) { return ::abs(val); }
    //                             ^ ::, because we call the top-level abs function (from cmath header) instead of the current one
};

template<class _T>
struct abs_value_floating
{
    static const bool known = true;
    static _T abs(_T val) { return fabs(val); }
};

// Wrap over the types

template<> struct abs_value<char> : abs_value_integral<char>{};
template<> struct abs_value<unsigned char> : abs_value_integral<unsigned char>{};
template<> struct abs_value<signed char> : abs_value_integral<signed char>{};
template<> struct abs_value<wchar_t> : abs_value_integral<wchar_t>{};
template<> struct abs_value<unsigned short> : abs_value_integral<unsigned short>{};
template<> struct abs_value<signed short> : abs_value_integral<signed short>{};
template<> struct abs_value<unsigned int> : abs_value_integral<unsigned int>{};
template<> struct abs_value<signed int> : abs_value_integral<signed int>{};
template<> struct abs_value<unsigned long> : abs_value_integral<unsigned long>{};
template<> struct abs_value<signed long> : abs_value_integral<signed long>{};
template<> struct abs_value<unsigned long long> : abs_value_integral<unsigned long long>{};
template<> struct abs_value<signed long long> : abs_value_integral<signed long long>{};

template<> struct abs_value<float> : abs_value_floating<float>{};
template<> struct abs_value<double> : abs_value_floating<double>{};
template<> struct abs_value<long double> : abs_value_floating<long double>{};

#endif // _ABSVALUE_WRAPPER_H