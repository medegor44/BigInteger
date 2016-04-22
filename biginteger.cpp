#include "biginteger.h"

#include <iomanip>
#include <cctype>

BigInteger::BigInteger(int n)
{
    sign = (n == 0 ? 1 : n / abs(n));
    number.push_back(labs(n));
}

BigInteger BigInteger::operator +(BigInteger another)
{
    BigInteger tmpInt = *this;

    if (tmpInt.sign < 0) {
        if (another.sign > 0)
            return another - abs(tmpInt);
        else {
            BigInteger res = abs(tmpInt) + abs(another);
            res.sign = -1;
            return res;
        }
    } else {
        if (another.sign < 0)
            return tmpInt - abs(another);
    }

    if (another > tmpInt)
        swap(another, tmpInt);

//    for (int64 i = 0; i < another.number.size(); i++)
//        tmpInt.addShort(another.number[i], i);

    int64 carrige = 0;
    for (int64 i = 0; i < another.number.size() || carrige; i++) {
        tmpInt.number[i] +=
                ((i < another.number.size() ? another.number[i] : 0) + carrige);
        carrige = tmpInt.number[i] / base;
        tmpInt.number[i] %= base;
    }

    return tmpInt;
}

BigInteger BigInteger::operator =(const BigInteger &another)
{
    this->number = another.number;
    this->sign = another.sign;

    return *this;
}

bool BigInteger::operator ==(BigInteger &another)
{
    return this->sign == another.sign && this->number == another.number;
}

bool BigInteger::operator >(BigInteger &another)
{
    if (this->sign != another.sign)
        return this->sign > another.sign;

    if (this->number.size() != another.number.size())
        return (this->sign > 0) == (this->number.size() > another.number.size());

    for (int64 i = (int64)number.size() - 1; i >= 0; i--)
        if (this->number[i] != another.number[i])
            return (this->sign > 0) == (this->number[i] > another.number[i]);

    return false;
}

bool BigInteger::operator !=(BigInteger &another)
{
    return !(*this == another);
}

bool BigInteger::operator <=(BigInteger &another)
{
    return !(*this > another);
}

int BigInteger::divShort(int64_t n)
{
    assert(n != 0);

    int sign = this->sign * (n / abs(n));
    int oldSign = this->sign;

    n = abs(n);
    this->sign = 1;

    unsigned long long r = 0;

    for (int64 i = number.size() - 1; i >= 0; i--) {
        r = r * base + number[i];
        number[i] = r / n;
        r %= n;
    }

    this->sign = sign;

    while (number.size() > 1 && number.back() == 0)
        number.pop_back();

    return r * oldSign;
}

bool BigInteger::operator <(BigInteger &another)
{
    return *this <= another && *this != another;
}

bool BigInteger::operator >=(BigInteger &another)
{
    return *this > another || *this == another;
}

void BigInteger::addShort(int64 n, int startPos)
{
    int len = number.size();
    int64 carrige = n;
    for (int i = startPos; carrige != 0; i++) {
        number[i] += carrige;
        carrige = number[i] / base;
        number[i] %= base;

        if (i >= len - 1 && carrige != 0)
            number.push_back(0);
    }
}

pair<BigInteger, BigInteger> BigInteger::divBig(BigInteger another)
{
    BigInteger res(0);
    BigInteger t;
    t.number.clear();

    for (int i = another.number.size() - 1; i >= 0; i--) {
        t.number.push_back(0);
        t.number[0] = number[i];

        uint16_t left = 0;
        int64_t right = base - 1;
        uint64_t x = 0;

        while (left <= right) {
            int64_t m = (left + right) / 2;
            BigInteger n = another * m;
            if (n <= t) {
                x = m;
                left = m + 1;
            } else
                right = m - 1;
        }

        res.number[i] = x;
        t = t - another * x;
    }

    while (res.number.back() == 0)
        res.number.pop_back();

    return make_pair(res, t);
}

BigInteger BigInteger::operator +(int64_t n)
{
    BigInteger tmpInt = *this;

    return tmpInt + BigInteger(n);
}

void BigInteger::mulShort(int64_t n, int startPos)
{
    if (n == 0) {
        number.clear();
        number.push_back(0);
        return;
    }
    int64 carrige = 0;
    int64 i = startPos;

    do {
        number[i] = number[i] * n + carrige;
        carrige = number[i] / base;
        number[i] %= base;
        i++;
    } while (i < number.size());

    if (carrige != 0)
        number.push_back(carrige);
}

BigInteger BigInteger::operator *(int64_t n)
{
    BigInteger tmpInt = *this;
    tmpInt.sign *= (n == 0 ? 1 : n / abs(n));

    tmpInt.mulShort(n);

    return tmpInt;
}

BigInteger BigInteger::operator -(BigInteger another)
{
    BigInteger tmpInt = *this;

    if (tmpInt == another)
        return BigInteger(0);

    if (tmpInt.sign < 0) {
        if (another.sign < 0)
            return abs(another) - abs(tmpInt);
        else {
            BigInteger res = abs(tmpInt) + another;
            res.sign = -1;
            return res;
        }
    } else {
        if (another.sign < 0)
            return tmpInt + abs(another);
    }

    if (tmpInt < another) {
        swap(tmpInt, another);
        tmpInt.sign = -1;
    }


    for (int64 i = 0; i < tmpInt.number.size(); i++) {
        tmpInt.number[i] -= (i < another.number.size() ? another.number[i] : 0);
        if (tmpInt.number[i] < 0) {
            tmpInt.number[i] += base;
            tmpInt.number[i + 1] -= 1;
        }
    }

    return tmpInt;
}

BigInteger BigInteger::operator -(int64_t n)
{
    return (*this) - BigInteger(n);
}

BigInteger BigInteger::operator /(int64_t n)
{
    auto tmpInt = *this;
    tmpInt.divShort(n);
    return tmpInt;
}

BigInteger BigInteger::operator %(int64_t n)
{
    auto tmpInt = *this;
    return tmpInt.divShort(n);
}

BigInteger BigInteger::operator /(BigInteger another)
{/*
    BigInteger res(0);
    BigInteger t;
    t.number.clear();

    for (int i = another.number.size() - 1; i >= 0; i--) {
        t.number.push_back(0);
        t.number[0] = number[i];

        uint16_t left = 0;
        int64_t right = base - 1;
        uint64_t x = 0;

        while (left <= right) {
            int64_t m = (left + right) / 2;
            BigInteger n = another * m;
            if (n <= t) {
                x = m;
                left = m + 1;
            } else
                right = m - 1;
        }

        res.number[i] = x;
        t = t - another * x;
    }

    while (res.number.back() == 0)
        res.number.pop_back();

    return res;*/

    return divBig(another).first;
}

BigInteger BigInteger::operator %(BigInteger another)
{
    return divBig(another).second;
}

BigInteger BigInteger::operator--()
{
    (*this) = (*this) - 1;
    return *this;
}

BigInteger BigInteger::operator++()
{
    (*this) = (*this) + 1;
    return *this;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger tmp = *this;
    (*this) = (*this) - 1;

    return tmp;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger tmp = *this;
    (*this) = (*this) + 1;

    return tmp;
}

ostream &operator <<(ostream &stream, BigInteger &bigInt)
{
    int64 len = bigInt.number.size();

    if (bigInt.sign < 0 && len != 0)
        stream << '-';

    stream << (len == 0 ? 0 : bigInt.number[len - 1]);

    for (int64_t i = len - 2; i >= 0; i--)
        stream << setw(10) << setfill('0') << bigInt.number[i];

    return stream;
}

istream &operator >>(istream &stream, BigInteger &bigInt)
{
    char c;
    bigInt = bigInt * 0;
    bool isRead = false;
    bool readNumbers = false;

    while ((c = stream.get())) {
        if (!isdigit(c) && c != '-') {
            if (isRead)
                break;
            else
                continue;
        }

        isRead = true;

        if (c == '-') {
            bigInt.sign = -1;
            if (readNumbers)
                break;
            continue;
        }

        bigInt = bigInt * 10 + (bigInt.sign * (c - '0'));
        readNumbers = true;
    }

    return stream;
}

BigInteger abs(BigInteger bigInt)
{
    bigInt.sign = 1;
    return bigInt;
}
