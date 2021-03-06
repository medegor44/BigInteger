#ifndef BIGINTEGER
#define BIGINTEGER

#include <vector>
#include <cmath>
#include <ostream>
#include <istream>
#include <utility>
#include <cassert>
#include <utility>

using namespace std;

typedef long long int64;

class BigInteger
{
public:
    BigInteger(int n = 0);

    BigInteger operator *(int64_t n);

    BigInteger operator +(BigInteger another);
    BigInteger operator +(int64_t n);

    BigInteger operator -(BigInteger another);
    BigInteger operator -(int64_t n);

    BigInteger operator /(int64_t n);
    BigInteger operator %(int64_t n);
    BigInteger operator /(BigInteger another);
    BigInteger operator %(BigInteger another);

    BigInteger operator--(); // Префиксный
    BigInteger operator++();

    BigInteger operator--(int); // Постфиксный
    BigInteger operator++(int);

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
    int divShort(int64_t n);
    void addShort(int64 n, int startPos = 0);
    void mulShort(int64 n, int startPos = 0);
    pair<BigInteger, BigInteger> divBig(BigInteger another);
    const int64 base = 10000000000;
    int sign;
    vector<int64> number;
};

BigInteger abs(BigInteger bigInt);

ostream &operator <<(ostream &stream, BigInteger &bigInt);
istream &operator >>(istream &stream, BigInteger &bigInt);

#endif // BIGINTEGER

