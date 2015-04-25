#include <iostream>

#include <bigint.h>

BigInt sum ()
{
    BigInt result;
    BigInt a, b;

    a = 5;
    b = 6;

    result = a + b;

    return result;
}

int main()

{
    BigInt b;

    while (1) {
        std::cin >> b;
        std::cout << b << std::endl;

        std::cout << 5 * b << std::endl;
    }

    return 0;
}

