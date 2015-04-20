#include <string>
#include <iostream>
#include "Polynomial.hpp"

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;

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
    cout << "Quotient match? " << ((ngF / ngG) == ngQ) << "\tRemainders match? " << ((ngF % ngG) == ngR) << endl;

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

    return 0;
}
