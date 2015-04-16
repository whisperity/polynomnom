#include <string>
#include <iostream>
#include "Polynomial.hpp"

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;

    Polynomial a;

    cout << "a: " << a << endl;
    a.setMember(5, 12.5);
    cout << "a: " << a << endl;
    a.setMember(2, 3.4);
    cout << "a: " << a << endl;

    //cout << a.getMember(2) << "x^2 and " << a[5] << "x^5" << endl;

    a.setMember(2, 1);
    cout << "a: " << a << endl;

    a.setMember(2, 0);
    cout << "a: " << a << endl;

    Polynomial b;
    b.setMember(2, 4);
    b.setMember(1, 3);
    b.setMember(0, -5);
    cout << b << endl;
    cout << b.run(1) << endl;

    Polynomial c;
    cout << "deg(c): " << c.degree() << endl;
    if (c.isNull())
        cout << "c is null polynomial." << endl;
    else
        cout << "c is not a null polynomial." << endl;

    Polynomial d;
    d = b;
    cout << "d: " << d << endl;
    d.setMember(12, 3.14);
    cout << "d: " << d << endl;
    cout << "b: " << b << endl;

    Polynomial e(d);
    cout << "e: " << e << endl;

    return 0;
}
