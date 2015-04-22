#include <iostream>

#include <bigint.h>

BigInt sum ()
{
    BigInt result;
    BigInt a, b;
//    BigInt temp;


    a = 5;
    b = 6;

//    std::cout << "Before: " << a << " " << b << " " << result << std::endl;

    return ((result += a) += b);

//    std::cout << "After: " << a << " " << b << " " << result << std::endl;

//    temp.dump();

//    return temp;
}

int main()

{
    BigInt test;
//    a = 1;
//    for (int i = 1; i <= 200; ++i) {
//        b = i;
//        a = a * b;
//    }

//    std::cout << a << std::endl;
    test = sum ();

    test.dump();

    std::cout << test << std::endl;

    return 0;
}

