#include "bigint.h"
#include <cstring>


BigInt::BigInt()
{
    max_size = 10000;
    size = 0;
    base = 10;
    data = new data_t [max_size];
    memset(data, 0, max_size * sizeof(data_t));
}

BigInt::~BigInt()
{
    delete [] data;
}


bool operator == (const BigInt &a, const BigInt &b)
{
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; ++i)
        if (a.data[i] != b.data[i]) return false;
    return true;
}

bool operator >= (const BigInt &a, const BigInt &b)
{
    if (a.size < b.size) {
        return false;
    } else if (a.size > b.size) {
        return true;
    } else {
        int i = a.size - 1;
        while (i >= 0 && a.data[i] == b.data[i]) {
            --i;
        }
        if (i >= 0 && a.data[i] < b.data[i])
            return false;
    }
    return true;
}

bool operator <= (const BigInt &a, const BigInt &b)
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
        if (i >= 0 && a.data[i] > b.data[i])
            return false;
    }
    return true;
}

bool operator > (const BigInt &a, const BigInt &b)
{
    if (a.size < b.size) {
        return false;
    } else if (a.size > b.size) {
        return true;
    } else {
        int i = a.size - 1;
        while (i >= 0 && a.data[i] == b.data[i]) {
            --i;
        }
        if (i >= 0 && a.data[i] > b.data[i])
            return true;
    }
    return false;
}

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


const BigInt operator + (const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp += a;
    temp += b;
    return temp;
}

const BigInt operator - (const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp += a;
    temp -= b;
    return temp;
}

BigInt& BigInt::operator += (const BigInt &b)
{
    int i = 0;
    data_t d = 0;
    data_t t = 0;
    while (i < size && i < b.size) {
        t = d + data[i] + b.data[i];
        d = t / base;
        data[i] = t % base;
        ++i;
    }
    while (i < b.size) {
        t = d + b.data[i];
        d = t / base;
        data[i] = t % base;
        ++i;
    }
    while (i < size) {
        t = d + data[size];
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

BigInt& BigInt::operator = (const BigInt &b)
{
    base = b.base;
    max_size = b.max_size;
    size = b.size;
    for (int i = 0; i < b.size; ++i)
        data[i] = b.data[i];
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
        t = d + data[size];
        if (t < 0) {
            d = -1;
            t += base;
        } else {
            d = 0;
        }
        data[i] = t % base;
        ++i;
    }
    if (0 == data[size-1])
        --size;
    return *this;
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

std::ostream& operator << (std::ostream &os, BigInt &b)
{
    for (int i = b.size - 1; i >= 0; --i)
        // printf("%02d",b.data[i]);
        std::cout << (int) b.data[i];
    std::cout << std::endl;
    return os;
}


const BigInt operator * (const BigInt &a, const BigInt &b)
{
    BigInt z;
    for (int i = 0; i < b.size; ++i) {
        int d = 0;
        for (int j = 0; j < a.size; ++j) {
            z.data[j + i] += a.data[j] * b.data[i];
            z.data[j + i] += d;
            d = z.data[j + i] / z.base;
            z.data[j + i] %= z.base;
        }
        if (d) {
            z.data[i + a.size] += d;
        }
    }
    z.size = a.size + b.size - 1;
    if (z.data[z.size]) ++z.size;
    return z;
}


void BigInt::dump ()
{
    for (int i = size-1; i >= 0; --i) {
        std::cout << (int) data[i] << " ";
    }
    std::cout << std::endl;
}
