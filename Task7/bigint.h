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
    BigInt(const BigInt &other);
    template <typename T> BigInt(T other);
    ~BigInt();

    friend void swap (BigInt &a, BigInt &b);

    void dump ();

    BigInt& operator = (BigInt other);
    BigInt& operator += (const BigInt &other);
    BigInt& operator -= (const BigInt &other);
    BigInt& operator *= (const BigInt &other);

    friend const BigInt operator + (BigInt a, const BigInt &b);
    friend const BigInt operator - (BigInt a, const BigInt &b);
    friend const BigInt operator * (BigInt a, const BigInt &b);

    friend std::ostream& operator << (std::ostream &os, const BigInt &b);
    friend std::istream& operator >> (std::istream &is, BigInt &b);

    friend bool operator < (const BigInt &a, const BigInt &b);
    friend bool operator == (const BigInt &a, const BigInt &b);

    friend bool operator > (const BigInt &a, const BigInt &b);
    friend bool operator <= (const BigInt &a, const BigInt &b);
    friend bool operator >= (const BigInt &a, const BigInt &b);
    friend bool operator != (const BigInt &a, const BigInt &b);

    explicit operator unsigned () const;
private:
    // array of the data
    data_t *data;
    // base of notation [10 by default]
    static const data_t base = 10;
    // number of digits
    int size;
    // max number of digits
    static const int max_size = 10000;
};

// Conversion constructor
template <typename T>
BigInt::BigInt(T other)
{
    this->data = new data_t [max_size];
    this->size = 0;
    while (other > 0) {
        data[size] = other % base;
        other /= base;
        ++size;
    }
}

#endif
