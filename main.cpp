#include <iostream>

#include "biginteger.h"

using namespace std;

int main()
{
    BigInteger a;
    int n;

    cin >> a >> n;

    a = a + n;
    cout << a;

    return 0;
}
