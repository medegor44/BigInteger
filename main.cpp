#include <iostream>

#include "biginteger.h"

using namespace std;

int main()
{
    BigInteger a, b;

    cin >> a >> b;

    auto c = a / b;

    cout << c;


    return 0;
}
