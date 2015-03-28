#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

/*
 * Unsigned integers only!
 */

class BigInt
{
private:
    typedef char data_t;
public:
    BigInt();
    ~BigInt();
    void dump ();

    friend bool operator == (const BigInt &a, const BigInt &b);
    friend bool operator <= (const BigInt &a, const BigInt &b);
    friend bool operator >= (const BigInt &a, const BigInt &b);
    friend bool operator < (const BigInt &a, const BigInt &b);
    friend bool operator > (const BigInt &a, const BigInt &b);
    friend const BigInt operator + (const BigInt &a, const BigInt &b);
    friend const BigInt operator - (const BigInt &a, const BigInt &b);
    friend const BigInt operator * (const BigInt &a, const BigInt &b);
    friend std::ostream& operator << (std::ostream &os, BigInt &b);


    BigInt& operator += (const BigInt &b);
    BigInt& operator -= (const BigInt &b);
    BigInt& operator = (const BigInt &b);
    template <typename T> BigInt& operator = (const T &b);

    operator unsigned () const;
private:
    // array of the data
    data_t *data;
    // base of notation [10 by default]
    data_t base;
    // number of digits
    int size;
    // max number of digits
    int max_size;
};

/*
template <typename T>
BigInt& operator += (BigInt &a, const T &b)
{
    T z = b;
    data_t d = 0;
    data_t t = 0;
    while (z > 0) {
        t = d + data[size] + z % base;
        d = t / base;
        data[size] = t % base;
        z /= base;
        ++size;
    }
    return a;
}
*/

template <typename T>
BigInt& BigInt::operator = (const T &b)
{
    size = 0;
    T z = b;
    while (z > 0) {
        data[size] = z % base;
        z /= base;
        ++size;
    }
    return *this;
}

#endif // BIGINT_H
