#ifndef BIGINTEGER
#define BIGINTEGER

#include <vector>
#include <cmath>
#include <ostream>
#include <istream>

using namespace std;

typedef long long int64;

class BigInteger
{
public:
    BigInteger(int n = 0);
    BigInteger operator +(int n);
    BigInteger operator *(int n);
    BigInteger operator +(BigInteger another);
    BigInteger operator -(BigInteger another);
    BigInteger operator =(const BigInteger &another);


    bool operator == (BigInteger &another);
    bool operator != (BigInteger &another);
    bool operator > (BigInteger &another);
    bool operator < (BigInteger &another);
    bool operator >= (BigInteger &another);
    bool operator <= (BigInteger &another);

    friend ostream &operator <<(ostream &stream, BigInteger &bigInt);
    friend istream &operator >>(istream &stream, BigInteger &bigInt);
    friend BigInteger abs(BigInteger bigInt);

private:
    void addShort(int64 n, int startPos = 0);
    void mulShort(int64 n, int startPos = 0);
    const int64 base = 10000000000;
    int sign;
    vector<int64> number;
};

BigInteger abs(BigInteger bigInt);

ostream &operator <<(ostream &stream, BigInteger &bigInt);
istream &operator >>(istream &stream, BigInteger &bigInt);

#endif // BIGINTEGER

