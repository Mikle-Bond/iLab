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
    BigInt a;
    BigInt b;

    while (1) {
        std::cin >> a;
        std::cout << a << std::endl;

        std::cin >> b;
        std::cout << b << std::endl;

        std::cout << a * b << std::endl;
    }

    return 0;
}

