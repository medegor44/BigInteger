#include <iostream>

#include "biginteger.h"

using namespace std;

int main()
{
    BigInteger a(1), b, c;

    cin >> a >> c;

    a = a + c;
    cout << a;

    return 0;
}
