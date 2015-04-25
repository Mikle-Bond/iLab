#include "bigint.h"
#include <cstring>

// Basic constructor
BigInt::BigInt()
{
//    max_size = 10000;
//    base = 10;
    size = 0;
    data = new data_t [max_size];
    memset(data, 0, max_size * sizeof(data_t));
}

// Copy-constructor
BigInt::BigInt(const BigInt &other)
{
    this->size = other.size;
    data = new data_t [max_size];
    for (int i = 0; i < max_size; ++i) {
        this->data[i] = other.data[i];
    }
}

// D-tor
BigInt::~BigInt()
{
    delete [] data;
}

// Basic swap
void swap (BigInt &a, BigInt &b)
{
    using std::swap;
    swap (a.size, b.size);
    swap (a.data, b.data);
    // everything else is equals
}

// Basic comporator for equalance
bool operator == (const BigInt &a, const BigInt &b)
{
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; ++i)
        if (a.data[i] != b.data[i]) return false;
    return true;
}

// Basic comporator
bool operator < (const BigInt &a, const BigInt &b)
{
    if (a.size > b.size) {
        return false;
    } else if (a.size < b.size) {
        return true;
    } else {
        int i = a.size - 1;
        while (i >= 0 && a.data[i] == b.data[i]) {
            --i;
        }
        if (i >= 0 && a.data[i] < b.data[i])
            return true;
    }
    return false;
}

// Relative comporators:

inline bool operator != (const BigInt &a, const BigInt &b)
{
    return !operator ==(a, b);
}

inline bool operator >= (const BigInt &a, const BigInt &b)
{
    return !operator < (b, a);
}

inline bool operator <= (const BigInt &a, const BigInt &b)
{
    return !operator > (a, b);
}

inline bool operator > (const BigInt &a, const BigInt &b)
{
    return operator < (b, a);
}

BigInt& BigInt::operator = (BigInt other)
{
    swap (*this, other);
    return *this;
}

BigInt& BigInt::operator += (const BigInt &other)
{
    int i = 0;
    data_t d = 0;
    data_t t = 0;
    while (i < size && i < other.size) {
        t = d + data[i] + other.data[i];
        d = t / base;
        data[i] = t % base;
        ++i;
    }
    while (i < other.size) {
        t = d + other.data[i];
        d = t / base;
        data[i] = t % base;
        ++i;
    }
    while (i < size) {
        t = d + data[i];
        d = t / base;
        data[i] = t % base;
        ++i;
    }
    size = i;
    if (d) {
        data[size] = d;
        ++size;
    }
    return *this;
}

BigInt& BigInt::operator -= (const BigInt &b)
{
    if (*this < b) {
        std::cout << "Unsigned only!" << std::endl;
        std::cout << "Subtraction fault" << std::endl
                  << std::endl;
        exit(1);
    }
    int i = 0;
    data_t d = 0;
    data_t t = 0;
    while (i < size && i < b.size) {
        t = d + data[i] - b.data[i];
        if (t < 0) {
            d = -1;
            t += base;
        } else {
            d = 0;
        }
        data[i] = t % base;
        ++i;
    }
    while (i < size) {
        t = d + data[i];
        if (t < 0) {
            d = -1;
            t += base;
        } else {
            d = 0;
        }
        data[i] = t % base;
        ++i;
    }
    while (size > 1 && 0 == data[size-1])
        --size;
    return *this;
}

BigInt& BigInt::operator *= (const BigInt &other)
{
    int i = 0;
    int j = 0;
    BigInt temp;
    // temp is probably bigger, so it should be
    // in the inside 'for'
    for (i = 0; i < other.size; ++i) {
        int d = 0;
        for (j = 0; j < size; ++j) {
            temp.data[j + i] += data[j] * other.data[i];
            temp.data[j + i] += d;
            d = temp.data[j + i] / base;
            temp.data[j + i] %= base;
        }
        if (d) {
            temp.data[i + size] += d;
        }
    }
    temp.size = size + other.size - 1;
    while (temp.data[temp.size]) ++temp.size;
    swap(temp, *this);
    return *this;
}

const BigInt operator + (BigInt a, const BigInt &b)
{
    a += b;
    return a;
}

const BigInt operator - (BigInt a, const BigInt &b)
{
    a -= b;
    return a;
}

const BigInt operator * (BigInt a, const BigInt &b)
{
    a *= b;
    return a;
}

BigInt::operator unsigned () const
{
    unsigned z = 0;
    for (int i = size - 1; i >= 0; --i) {
        z *= base;
        z += data[i];
    }
    return z;
}

std::ostream& operator << (std::ostream &os, const BigInt &b)
{
    for (int i = b.size - 1; i >= 0; --i)
        printf("%d",b.data[i]);
        // std::cout << (int) b.data[i];
//    std::cout << std::endl;
    return os;
}

std::istream& operator >> (std::istream &is, BigInt &b)
{
    int c = 0;
    int i = BigInt::max_size;
    while ((c = getchar()) <= '9' && c >= '0'
           && i > 0) {
        b.data[--i] = c - '0';
    }

    if (i < 0) is.setstate(std::ios::failbit); // TODO!

    b.size = BigInt::max_size - i;
    if (i > 0) {
        --i;
        int j = -1;
        while (j < b.size) {
            b.data[++j] = b.data[++i];
        }
        for (; j < BigInt::max_size; ++j)
            b.data[j] = 0;
    }
    return is;
}

void BigInt::dump ()
{
    for (int i = size-1; i >= 0; --i) {
        std::cout << (int) data[i] << " ";
    }
    std::cout << std::endl;

}
