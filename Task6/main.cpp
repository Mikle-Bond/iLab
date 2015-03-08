#include <iostream>
#include "mystack.h"

using namespace std;

int main()
{
    MyStack first(10);

    for (int i = 10; i < 200; i += 10)
        first.push(i);
    first.toString();
    first.pop();
    cout << first.pop() << endl;
    int t = 0;
    cin >> t;
    first.push(t);
    first.toString();
    cout << "Hello World!" << endl;
    return 0;
}

