Polynom-Nom
===========

Synopsis
--------
*Polynom-Nom* is a C++ library, based mainly around implementing the concept of polynomials and various discrete mathematical phenomenon. The code was used to deepen my understanding in the field but most importantly to practice implementation in C++.

**Disclaimer!** This project is only a work for a University side-assignment and was **NOT** checked to be safe, fast or good enough for heavy calculations. For the real deal, you should use a real library, like [Givaro](http://givaro.forge.imag.fr).

Usage
-----
To use the library, you need to include the appropriate header in your translation unit.

Contribution
------------
Even though this project is not meant to be maintained after the assignment is done, contributions and feedback are welcome. Head over to the *Issues* page to contribute. Code contributions should follow the style the project is written by. 

Implementation details
----------------------

## Polynomials
> Implemented in **Polynomial.hpp**

The Polynomail class represents a [polynomial](http://en.wikipedia.org/wiki/Polynomial), that is, a mathematical expression consisting of a variable (usually **x**) and coefficients. An easy example polynomial is the quadratic function: `3x^2 + 4x - 9`.

The above expression can be initialised as a variable in the program as follows:

```c++
Polynomial<int> quad;
quad.setMember(2,  3);
quad.setMember(1,  4);
quad.setMember(0, -9);
```

`Polynomial<T>` is a class which coefficients are of type `T`. There are a few restrictions to this type template, though: polynomials can only exist "above" a [ring](http://en.wikipedia.org/wiki/Ring %28mathematics%29), that is algebraic structure. Without further going into advanced discrete mathematics, let's just a say a ring is something like the set of integer numbers: there is a `+` and `*` (addition and multiplication) operator on them.

To utilise the library, `T` must have the operators `+`, `-`, `*`, `/`, `+=`, `<`, `<=`, `>`, `>=`, `==`, `!=` defined and working on them. Casually, `-` is the inverse of `+` and `/` is the inverse of `*`.

### Member functions and operators
 * `degree()`: Returns the degree of the polynomial.
 * `isNull()`, `isConstant()`: Whether the polynomial is a null or a constant polynomial. **Caution!** Usually, null polynomials are described with the degree *minus infinity*, but that was decided to be extra hassle to implement. At any chance you see if your polynomial's degree is 0, check against these two boolean functions.
 * `at(t)`: Calculate the polynomial function's value if `t` in place of the indeterminate `x`. (This calculation uses [Horner's scheme](http://en.wikipedia.org/wiki/Horner's method).)
 * `getMember(i)`: Get the coefficient for the member which power is `i`.
 * `setMember(i, t)`: Set the coefficient to be `t` for the member which power is `i`. 
 * The `+`, `-`, `*`, `/` and `%` arithmetical operators are implemented
  - `/` and `%` refers to the results of [Polynomial long division](http://en.wikipedia.org/wiki/Polynomial long division), `/` creates the quotient, `%` creates the remainder.
  - For performance reasons, if you wish to calculate **both** the quotient and remainder of a polynomial division, you should use member function `divide()` instead. *(See below.)*
 * Of course, polynomials can be checked if they are equal (`==`, `!=`) and ordered (`<`, `<=`, `>`, `>=`). Ordering them is based on their degree, so a polynomial of less number of members (smaller degree) is considered *smaller*.
 * `<<`: Infeeding the polynomial into an output stream (for example `std::cout << poly;`) creates a textual representation.

#### Polynomial division
Calculating the quotient of a polynomial divided by another is a costly operation involving a lot of multiplicative routines. Using the `/` and `%` operators to calculate the quotient of remainder runs the whole lot of operation twice.

```c++
// Polynomial<T> a, b;
// ^ These are the polynomials we are going to divide
std::cout << "Quotient:  " << (a / b) << std::endl;
std::cout << "Remainder: " << (a % b) << std::endl;
```

The above operation can be simplified by using the `divide()` member functions:

```c++
// Polynomial<T> a, b;
// ^ The same. We are going to divide A by B.
Polynomial<T> q, r; // The quotient and the remainder.
a.divide(b, q, r);

std::cout << "Quotient:  " << q << std::endl;
std::cout << "Remainder: " << r << std::endl;
```

## The Euclidean Algorithm
> **EuclideanAlgorithm.hpp**

The [Euclidean algorithm](http://en.wikipedia.org/wiki/Euclidean algorithm) is used to calculate the [greatest common divisor](http://en.wikipedia.org/wiki/Greatest common divisor) of two numbers (*GCD*), and its extended version calculates the coefficients of a linear combination of the numbers to produce said *GCD*. If the numbers are `a` and `b`, the extended algorithm solves the equation `ax + by = gcd(a, b)` for `x` and `y`.

An implementation of the Euclidean algorithms are given for an arbitrary type of `T`. `T` must be algebraically from a [Euclidean domain](http://en.wikipedia.org/wiki/Euclidean ring), that is something where the Euclidean algorithm works. (Yeah...).

Loosely speaking, the `T` class should implement the operators `+`, `-`, `*`, `/` and `%`, it should be ordered (with the requirement of having divided two numbers, the remainder's some sort of value (for numbers: the absolute value, for polynomials: the degree) must be smaller than the divisor's said value) and have an additive and multiplicative identity (which there is, because `T` is from a ring).

Three functions are given:
 * `euclidean<T>(a, b)` calculates the greatest common divisor for `a` and `b`
 * `euclidean_lcm<T>(a, b)` calculates the [least common multiple](http://en.wikipedia.org/wiki/Least common multiple)
 * `extended_euclidean<T>(a, b)` solve the equation `ax + by = gcd(a, b)` by the extended euclidean algorithm
  - The function returns an `EEuclideanResult<T>` variable which contains five member properties: `a`, `b`, `x`, `y` and `gcd`, which are the respectively the variables of the above equation.

## Residue numbers, remainder rings, Zm
> **Residue.hpp**

`Zm` is the residue system created from the results of operation `mod m`. For example, `Z3` contains all the possible values of `mod 3`: 0, 1 and 2.

Calculations can also be done in a residue system (and polynomials can be created with coefficients being residue numbers!). By instantinating variables as `ResidueNum<M>` (where `M` is the modulus), the usual arithmetic, equation and ordering operators work in modulo.

> This `ResidueNum<M>` class is a good example of what a `T` should implement to be usable as a polynomial's coefficient type. Of couse, to create a polynomial with its coefficients being modulo 7, one should declare the variable as `Polynomial<ResidueNum<7>>`.

The arithmetical operation `a / b` (in the context of residue numbers) is used to solve the [linear congruence](http://en.wikipedia.org/wiki/Modular arithmetic#Congruence relation) `bx === a (mod M)` (where `===` represents the congruence relation).

Consider the following example:

```c++
ResidueNum<7> a(5), b(2);
std::cout << (a / b) << std::endl;
```

This will output `6`, because 2 multiplied by 6 is 12, 12 mod 7 is 5. It is to be noted that this congruence has no solutions modulo 6:

```c++
ResidueNum<6> a(5), b(2);
std::cout << (a / b) << std::endl;
```

Execution of this code will fail due to an exception, because you are not able to find a number which multiplies 2 to get an odd number as a result (namely 5). The whole mathematical system behind it is not part of this README.

## Rational numbers
> **To be developed.**

Technical details
-----------------
Because of the library being fully templated, `T` types must implement their additive and multiplicative identities and an absolute value function.
