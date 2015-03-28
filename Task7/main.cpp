#include <iostream>

#include <bigint.h>

int main()
{
    BigInt a, b;
    a = 1;
    for (int i = 1; i <= 200; ++i) {
        b = i;
        a = a * b;
    }

    std::cout << a << std::endl;
    return 0;
}

