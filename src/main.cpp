/*
* This must be built against the C++11 standard!
*/
#include <string>
#include <iostream>
#include "Polynomial.hpp"
#include "EuclideanAlgorithm.hpp"
#include "Residue.hpp"

using namespace std;

#include <ctime>
#include <cstdlib>
const float HI = 1000;
const float LO = -1000;
double ran()
{
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

int main2();
int main3();
int main()
{
    //cout << "Hello world!" << endl;
    srand(static_cast <unsigned> (time(0)));

    cout << endl;
    Polynomial<double> a;
    cout << "a: " << a << endl;
    a.setMember(5, 12.5);
    cout << "a: " << a << endl;
    a.setMember(2, 3.4);
    cout << "a: " << a << endl;

    cout << a.getMember(2) << "x^2 and " << a[5] << "x^5" << endl;

    a.setMember(2, 1);
    cout << "a: " << a << endl;

    a.setMember(2, 0);
    cout << "a: " << a << endl;

    cout << endl;
    Polynomial<double> b;
    b.setMember(2, 4);
    b.setMember(1, 3);
    b.setMember(0, -5);
    cout << "b: " << b << endl;
    cout << "b(1) = " << b.at(1) << endl;

    cout << endl;
    Polynomial<double> c;
    cout << "c: " << c << endl;
    cout << "deg(c): " << c.degree() << endl;
    if (c.isNull())
        cout << "c is null polynomial." << endl;
    else
        cout << "c is not a null polynomial." << endl;

    cout << endl;
    Polynomial<double> d;
    d = b;
    cout << "d=b; d: " << d << endl;
    d.setMember(12, 3.14);
    cout << "d: " << d << endl;
    cout << "b: " << b << endl;

    cout << endl;
    Polynomial<double> e(d);
    cout << "e: " << e << endl;

    cout << endl;
    Polynomial<double> f(5);
    cout << "f: " << f << endl;
    cout << "f(2) = " << f.at(2) << endl;
    f.setMember(1, 1);
    cout << "f: " << f << endl;
    cout << "f(2) = " << f.at(2) << endl;

    cout << endl;
    Polynomial<double> g;
    g.setMember(5, 1);
    g.setMember(4, -4.5);
    g.setMember(3, 2);
    g.setMember(2, -1);
    g.setMember(1, 1);
    g.setMember(0, -4);
    cout << "g: " << g << endl;
    cout << "deg(g): " << g.degree() << endl;

    cout << endl;
    Polynomial<double> h;
    for (int i = 0; i < 500; ++i)
        h.setMember(i, i);

    //cout << "h: " << h << endl;

    for(int i = 0; i <= 5; ++i)
        cout << "h(" << i << ") = " << h.at(i) << endl;

    cout << endl;
    Polynomial<double> j;
    for (int i = 0; i <= 25; ++i)
        j.setMember(i, ran());
    cout << "j: " << j << endl;

    double randomValue = ran();
    cout << "j(" << randomValue << ") = " << j.at(randomValue) << endl;

    cout << endl;
    Polynomial<double> x;
    x.setMember(2, 3);
    x.setMember(1,1);
    x.setMember(0, -2);

    Polynomial<double> y;
    y.setMember(3, 1);
    y.setMember(2, 1);
    y.setMember(1, 3);
    y.setMember(0, 4);

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    cout << endl;
    Polynomial<double> z = x;
    z.add(y);
    cout << "z := x" << endl;
    cout << "z.add(y)" << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    cout << endl;
    Polynomial<double> z1 = x;
    Polynomial<double> z2 = y;
    cout << "z1 := x                      z2 := y" << endl;
    cout << "z1.subtract(y) (x-y)         z2.subtract(x) (y-x)" << endl;
    z1.subtract(y);
    z2.subtract(x);
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z1: " << z1 << endl;
    cout << "z2: " << z2 << endl;

    cout << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "x + y: " << x+y << endl;
    cout << "y + x: " << y+x << endl;
    cout << "x - y: " << x-y << endl;
    cout << "y - x: " << y-x << endl;

    cout << endl;
    Polynomial<double> a1;
    a1.setMember(2, 2);
    a1.setMember(1, 25);
    a1.setMember(0, 2);

    Polynomial<double> a2 = a1;

    Polynomial<double> a3;
    a3.setMember(3, 2);
    a3.setMember(0, 4);

    cout << "a1: " << a1 << endl;
    cout << "a2: " << a2 << endl;
    cout << "a3: " << a3 << endl;
    cout << "deg(a1) = " << a1.degree() << "; deg(a2) = " << a2.degree() << "; deg(a3) = " << a3.degree() << endl;

    cout << "a1.equals(a2) = " << (a1.equals(a2) ? "true" : "false") << endl;
    cout << "a1 == a2 = " << (a1 == a2 ? "true" : "false") << endl;
    cout << "a2 == a3 = " << (a2 == a3 ? "true" : "false") << endl;
    cout << "a2 != a3 = " << (a2 != a3 ? "true" : "false") << endl;
    cout << "a1 != a3 = " << (a1 != a3 ? "true" : "false") << endl;

    cout << endl;
    Polynomial<double> p = a1+a2;
    cout << "p = a1 + a2: " << p << endl;

    cout << "a1 * a3: " << a1 * a3 << endl;

    cout << endl;
    Polynomial<double> q;
    q.setMember(4, 5);
    q.setMember(3, 3);

    Polynomial<double> r;
    r.setMember(2, 2);
    r.setMember(1, 3);

    cout << "(" << q << ") * (" << r << ") = " << q*r << endl;
    cout << "(" << r << ") * (" << q << ") = " << r*q << endl;
    cout << "(" << q << ") : (" << r << ") = " << q/r << endl;
    cout << "(" << r << ") : (" << q << ") = " << r/q << endl;

    cout << endl;
    Polynomial<double> te1, te2;
    te1.setMember(0, 2);
    te2.setMember(2, 0.5);
    cout << te1 << "\t*\t" << te2 << "\t=\t";
    cout << te1 * te2 << endl;

    Polynomial<double> s;
    s.setMember(2, 1);
    s.setMember(0, 3);

    Polynomial<double> t;
    t.setMember(0, 2);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "(" << s << ") * (" << t << ") = " << s*t << endl;
    cout << "(" << t << ") * (" << s << ") = " << t*s << endl;

    cout << "(" << s << ") : (" << t << ") = " << s/t << endl;
    cout << "(" << t << ") : (" << s << ") = " << t/s << endl;
    cout << "s%t = " << s%t << endl;
    cout << "t%s = " << t%s << endl;

    cout << endl;
    Polynomial<double> aa, bb;
    aa.setMember(100, 5); aa.setMember(2, 3);
    bb.setMember(200, 12); bb.setMember(6, 4);
    cout << aa << " * " << bb << " = " << aa*bb << endl;

    cout << endl;
    Polynomial<double> ab, ac;
    ab.setMember(0, 2);
    ac.setMember(0, 5);
    cout << ab << " * " << ac << " = " << ab*ac << endl;

    cout << endl;
    // Nagy Gábor diasorából a példa polinom.
    // 5x^4 + 2x - 3    :   2x^2 - 3x + 4
    cout << "Nagy Gábor" << endl;
    Polynomial<double> ngF, ngG, ngQ, ngR;
    ngF.setMember(4, 5); ngF.setMember(1, 2); ngF.setMember(0, -3);
    ngG.setMember(2, 2); ngG.setMember(1, -3); ngG.setMember(0, 4);
    ngQ.setMember(2, (double)5/2); ngQ.setMember(1, (double)15/4); ngQ.setMember(0, (double)5/8);
    ngR.setMember(1, (double)-89/8); ngR.setMember(0, (double)-11/2);
    cout << "ngF: " << ngF << endl;
    cout << "ngG: " << ngG << endl;
    cout << "ngQ: " << ngQ << endl;
    cout << "ngR: " << ngR << endl;
    cout << "(ngG * ngQ) + ngR: " << (ngG * ngQ) + ngR << endl;

    cout << "ngF : ngG = " << ngF / ngG << endl;
    cout << "ngF % ngG = " << ngF % ngG << endl;
    cout << "Quotient match? " << ((ngF / ngG) == ngQ) << "\tRemainder match? " << ((ngF % ngG) == ngR) << endl;

    // Ezt valahol wikipédián találtam asszem.
    cout << endl;
    Polynomial<double> rN, rD, rQ, rR;
    rN.setMember(0, -42); rN.setMember(1, 0); rN.setMember(2, -12); rN.setMember(3, 1);
    rD.setMember(0, -3); rD.setMember(1, 1); rD.setMember(2, 0); rD.setMember(3, 0);
    rQ.setMember(0, -27); rQ.setMember(1, -9); rQ.setMember(2, 1);
    rR.setMember(0, -123); rR.setMember(1, 0); rR.setMember(2, 0);

    cout << rN << endl;
    cout << rD << endl;
    cout << rQ << "\t" << rR << endl;
    cout << rR.degree() << "  " << rR.getMember(0) << endl;
    cout << (rD * rQ) + rR << endl;

    cout << "Q match? " << ((rN / rD) == rQ) << "\tR match? " << ((rN % rD) == rR) << endl;

    // Ezt is találtam valahol.
    cout << endl;
    Polynomial<double> wF, wG, wQ, wR;
    wF.setMember(3, 1); wF.setMember(2, -2); wF.setMember(0, -4);
    wG.setMember(1, 1); wG.setMember(0, -3);
    wQ.setMember(2, 1); wQ.setMember(1, 1); wQ.setMember(0, 3);
    wR.setMember(0, 5);

    cout << wF << endl;
    cout << wG << endl;
    cout << wQ << "\t" << wR << endl;
    cout << (wG * wQ) + wR << endl;
    cout << "Q match? " << ((wF / wG) == wQ) << "\tR match? " << ((wF % wG) == wR) << endl;

    cout << endl;
    Polynomial<double> c1, c2;
    c1.setMember(0, 10);
    c2.setMember(2, 2); c2.setMember(1, 5); c2.setMember(0, 2);

    cout << c1/c2 << endl;
    cout << c2/c1 << endl;
    
    // Test the euclidean algorithms
    cout << endl << endl;
    cout << "GCD(172, 62) = " << euclidean<int>(172, 62) << endl;
    cout << "LCM(172, 62) = " << euclidean_lcm<int>(172, 62) << endl;

    EEuclideanResult<int> res = extended_euclidean<int>(172, 62);
    cout << "GCD = A * X + B * Y" << endl;
    cout << "ExtendedEuclidean(172, 62) :== " << res.a << " * " << res.x << " + " << res.b << " * " << res.y << " = "
        << res.gcd << endl;
    cout << "Truly? " << (res.a*res.x + res.b*res.y == res.gcd ? "Yeah." : "Noope.") << endl;

    Polynomial<double> egy, ketto;
    egy.setMember(4, 1); egy.setMember(3, 1); egy.setMember(2, -3); egy.setMember(1, -4); egy.setMember(0, -1);
    ketto.setMember(3, 1); ketto.setMember(2, 1); ketto.setMember(1, -1); ketto.setMember(0, -1);
    cout << "gcd(" << egy << "  ;  " << ketto << ") = ";
    Polynomial<double> egyKettoGCD = euclidean<Polynomial<double>>(egy, ketto);
    cout << egyKettoGCD << endl;

    EEuclideanResult<Polynomial<double>> result = extended_euclidean<Polynomial<double>>(egy, ketto);
    cout << "ExtendedEuclidean(egy, ketto) :== [" << result.a << " * " << result.x << "] + [" << result.b << " * " << result.y << "] = "
        << result.gcd << endl;
    cout << "Truly? " << (result.a*result.x + result.b*result.y == result.gcd ? "Yeah." : "Noope.") << endl;

    main2();
    main3();

    cout << endl << "Type something to exit." << endl;
    std::string temp;
    std::cin >> temp;

    return 0;
}

int main2()
{
    cout << endl << endl;
    cout << "RESIDUE TESTING" << endl;
    cout << "---------------" << endl;

    Residue r(5);
    cout << "-1 mod 5: " << r.calcMod(-1) << endl;
    cout << "2 mod 5: " << r.calcMod(2) << endl;
    cout << "25 mod 5: " << r.calcMod(25) << endl;

    Residue q(3);
    cout << "-3 mod 3: " << q.calcMod(-3) << endl;

    ResidueNum<5> a(2);
    ResidueNum<5> b(4);
    cout << "2 + 4 = " << (a + b).number() << " (mod 5)" << endl;

    ResidueNum<10> c(5); ResidueNum<10> e(47);
    cout << "47 * 5 (mod 10) = " << (c * e).number() << endl;

    cout << id_multiplicative<ResidueNum<3>>::value << endl;
    cout << id_additive<ResidueNum<3>>::value << endl;

    // 47 is congruent to 7 (mod 10)
    cout << "5 < 47  <=>  5 < 7 : " << (c < e ? "Yea" : "Nay") << endl;

    ResidueNum<6> try1(28), try2(14);
    cout << try1.number() << " : " << try2.number() << " (mod 6) = " << (try1 / try2).number() << endl;

    // Solve 5 : 2 = ? (mod 7)
    ResidueNum<7> five(5), two(2);
    cout << "5 : 2 = " << (five / two).number() << " (mod 7), because" << endl;
    cout << "2*" << (five / two).number() << " == " << (five * two).number();
    cout << " == congruent == " << Residue(7).calcMod((five / two).number()) << " (mod 7)" << endl;
    cout << "Truly? " << (Residue(7).multiply((five / two).number(), 2) == 5 ? "Yeah." : "Nope.") << endl;

    cout << "2 : 5 = " << (two / five).number() << " (mod 7)" << endl;

    // Try to solve 5 : 2 = ? (mod 6).
    // This shouldn't give a result, but rather an exception.
    ResidueNum<6> otHAT(5), kettoHAT(2);
    cout << "5 : 2 = ";
    try
    {
        cout << (otHAT / kettoHAT).number() << endl;
    }
    catch (const exception& e)
    {
        cout << "ERROR! Operation unsolvable: " << endl << e.what() << endl;
    }

    // Példa az egyik gyakorlatról
    cout << endl << "p1 := x^4 + x^3 -3x^2 -4x -1" << endl << "p2 := x^3 + x^2 -x -1 \t\t\t (in Z3)" << endl;
    Polynomial<ResidueNum<3>> egy, ketto;
    egy.setMember(4, ResidueNum<3>(1)); egy.setMember(3, ResidueNum<3>(1)); egy.setMember(2, ResidueNum<3>(-3));
        egy.setMember(1, ResidueNum<3>(-4)); egy.setMember(0, ResidueNum<3>(-1));
    ketto.setMember(3, ResidueNum<3>(1)); ketto.setMember(2, ResidueNum<3>(1));
        ketto.setMember(1, ResidueNum<3>(-1)); ketto.setMember(0, ResidueNum<3>(-1));

    cout << "After simplification: " << endl;
    cout << "p1: " << egy << endl;
    cout << "p2: " << ketto << endl;

    cout << egy << " : " << ketto << " = " << (egy / ketto) << endl;
    cout << "\t\t\tr: " << (egy % ketto) << " \t (in Z3)" << endl;
    cout << "GCD(p1, p2) : " << euclidean<Polynomial<ResidueNum<3>>>(egy, ketto) << endl;

    // Példa a korábbi polinomokról, az a bizonyos 5x^4 + ... : 2x^2 + ... (Z7-ben)
    cout << endl << endl;
    Polynomial<ResidueNum<7>> o, k;
    o.setMember(4, ResidueNum<7>(5)); o.setMember(1, ResidueNum<7>(2)); o.setMember(0, ResidueNum<7>(-3));
    k.setMember(2, ResidueNum<7>(2)); k.setMember(1, ResidueNum<7>(-3)); k.setMember(0, ResidueNum<7>(4));

    cout << o << " : " << k << " (Z7) = " << (o / k) << endl;
    cout << "\t\tr: " << (o % k) << endl;

    // Try this also in Z6... this shouldn't have an answer just as how 5 : 2 (in Z6) does not hold.
    cout << endl;
    Polynomial<ResidueNum<6>> o2, k2;
    o2.setMember(4, ResidueNum<6>(5)); o2.setMember(1, ResidueNum<6>(2)); o2.setMember(0, ResidueNum<6>(-3));
    k2.setMember(2, ResidueNum<6>(2)); k2.setMember(1, ResidueNum<6>(-3)); k2.setMember(0, ResidueNum<6>(4));

    cout << o2 << " : " << k2 << " (Z6) = ";
    try
    {
        cout << (o2 / k2) << endl;
        cout << "\t\tr: " << (o2 % k2) << endl;
    }
    catch (const exception& e)
    {
        cout << "ERROR! Operation unsolvable: " << endl << e.what() << endl;
    }

    cout << endl;

    return 0;
}

#include "Rational.hpp"
void addTest(long aN, long aD, long bN, long bD, long eN, long eD, bool valueSet = true)
{
    Rational a(aN, aD), b(bN, bD), e(eN, eD);
    cout << "a: " << a << "\tb:" << b << "\t\t";
    if (valueSet)
        a += b;
    else
        a = a + b;
    cout << "a " << (valueSet ? "+=" : "+") << " b: " << a << "\t=?=\t" << e << "\t\t" << (a == e ? "Yeah." : "Nope :(") << endl;
}

void subTest(long aN, long aD, long bN, long bD, long eN, long eD, bool valueSet = true)
{
    Rational a(aN, aD), b(bN, bD), e(eN, eD);
    cout << "a: " << a << "\tb:" << b << "\t\t";
    if (valueSet)
        a -= b;
    else
        a = a - b;
    cout << "a " << (valueSet ? "-=" : "-") << " b: " << a << "\t=?=\t" << e << "\t\t" << (a == e ? "Yeah." : "Nope :(") << endl;
}

void mulTest(long aN, long aD, long bN, long bD, long eN, long eD, bool valueSet = true)
{
    Rational a(aN, aD), b(bN, bD), e(eN, eD);
    cout << "a: " << a << "\tb:" << b << "\t\t";
    if (valueSet)
        a *= b;
    else
        a = a * b;
    cout << "a " << (valueSet ? "*=" : "*") << " b: " << a << "\t=?=\t" << e << "\t\t" << (a == e ? "Yeah." : "Nope :(") << endl;
}

void divTest(long aN, long aD, long bN, long bD, long eN, long eD, bool valueSet = true)
{
    Rational a(aN, aD), b(bN, bD), e(eN, eD);
    cout << "a: " << a << "\tb:" << b << "\t\t";
    if (valueSet)
        a /= b;
    else
        a = a / b;
    cout << "a " << (valueSet ? "/=" : "/") << " b: " << a << "\t=?=\t" << e << "\t\t" << (a == e ? "Yeah." : "Nope :(") << endl;
}

int main3()
{
    cout << "RATIONAL TESTING" << endl;
    cout << "----------------" << endl;

    Rational a(4);
    Rational b(5, -4);
    Rational c(-5, 2);
    Rational d(-10, -20);
    cout << a << "\t" << b << "\t" << c << "\t" << d << endl;
    cout << a.real_value() << "\t" << b.real_value() << "\t" << c.real_value() << "\t" << d.real_value() << endl;

    cout << (Rational(1, 2, false) > Rational(2, 5, false)) << endl;

    cout << Rational(-4, 5).abs_value() << endl;

    addTest(1, 2, -2, 5, 1, 10); cout << endl;
    addTest(-4, 10, -6, 10, -10, 10); cout << endl;
    addTest(5, 11, 8, 13, 153, 143); cout << endl;
    addTest(-9, 2, 3, 7, -57, 14); cout << endl;

    addTest(1, 4, 3, 5, 17, 20);
    addTest(-1, 4, -3, 5, -17, 20);
    addTest(-1, 4, 3, 5, 7, 20);
    addTest(1, 4, -3, 5, -7, 20);

    cout << endl;
    subTest(2, 4, 1, 4, 1, 4);

    cout << endl;
    mulTest(2, 3, 4, 6, 4, 9);
    mulTest(2, 3, -4, 6, -4, 9);
    mulTest(-2, 3, 4, 6, -4, 9);
    mulTest(-2, 3, -4, 6, 4, 9);

    cout << endl;
    divTest(2, 3, 4, 6, 1, 1);
    divTest(-2, 3, 4, 6, -1, 1);
    divTest(2, 3, -4, 6, -1, 1);
    divTest(-2, 3, -4, 6, 1, 1);

    cout << endl << endl << "The same with the return new operators isntead of the in-place ones (so + instead of +=):" << endl;
    addTest(1, 2, -2, 5, 1, 10, false); cout << endl;
    addTest(-4, 10, -6, 10, -10, 10, false); cout << endl;
    addTest(5, 11, 8, 13, 153, 143, false); cout << endl;
    addTest(-9, 2, 3, 7, -57, 14, false); cout << endl;

    addTest(1, 4, 3, 5, 17, 20, false);
    addTest(-1, 4, -3, 5, -17, 20, false);
    addTest(-1, 4, 3, 5, 7, 20, false);
    addTest(1, 4, -3, 5, -7, 20, false);

    cout << endl;
    subTest(2, 4, 1, 4, 1, 4, false);

    cout << endl;
    mulTest(2, 3, 4, 6, 4, 9, false);
    mulTest(2, 3, -4, 6, -4, 9, false);
    mulTest(-2, 3, 4, 6, -4, 9, false);
    mulTest(-2, 3, -4, 6, 4, 9, false);

    cout << endl;
    divTest(2, 3, 4, 6, 1, 1, false);
    divTest(-2, 3, 4, 6, -1, 1, false);
    divTest(2, 3, -4, 6, -1, 1, false);
    divTest(-2, 3, -4, 6, 1, 1, false);

    cout << endl;
    cout << "Additive identity: " << id_additive<Rational>::value << "\tmultiplicative: " << id_multiplicative<Rational>::value << endl;

    // Test some rational-polynomials
    // (Previously these were tested with doubles.)
    // 5x^4 + 2x - 3    :   2x^2 - 3x + 4
    cout << "Nagy Gábor, now with rationals." << endl;
    Polynomial<Rational> ngF, ngG, ngQ, ngR;
    ngF.setMember(4, Rational(5)); ngF.setMember(1, Rational(2)); ngF.setMember(0, Rational(-3));
    ngG.setMember(2, Rational(2)); ngG.setMember(1, Rational(-3)); ngG.setMember(0, Rational(4));

    // Expected results:
    // Quotient: 5/2 x^2 + 15/4 x + 5/8
    // Remainder: -89/8 x - 11/2
    ngQ.setMember(2, Rational(5, 2)); ngQ.setMember(1, Rational(15, 4)); ngQ.setMember(0, Rational(5, 8));
    ngR.setMember(1, Rational(-89, 8)); ngR.setMember(0, Rational(-11, 2));
    cout << "ngF := " << ngF << endl;
    cout << "ngG := " << ngG << endl;
    cout << "ngQ := " << ngQ << endl;
    cout << "ngR := " << ngR << endl;
    cout << "(ngG * ngQ) + ngR = " << (ngG * ngQ) + ngR << endl;

    cout << "ngF : ngG = " << ngF / ngG << endl;
    cout << "ngF % ngG = " << ngF % ngG << endl;
    cout << "Quotient match? " << ((ngF / ngG) == ngQ) << "\tRemainder match? " << ((ngF % ngG) == ngR) << endl;

    //Polynomial<Rational> ngFp = ngF.derive();

    cout << "ngF': " << ngF.derive() << endl;
    cout << "ngG': " << ngG.derive() << endl;

    return 0;
}