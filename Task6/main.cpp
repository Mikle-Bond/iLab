#include <iostream>
#include "mystack.h"

using namespace std;


void foo (int v)
{
    static MyStack glob (10);
    glob.push(v);
    if (v == 0) glob.toString();
}


int main()
{
    cout << "Enter main ()" << endl;

    MyStack first(10);
    MyStack *second = &first;

    // First fill the stack
    for (int i = 10; i < 80; i += 10)
        first.push(i);
    // Print it
    first.toString();


    second->pop();

    // Pop one element
    cout << first.pop() << endl;

    // Push user element
    int t = 0;
    cin >> t;
    first.push(t);

    // Print stack again
    first.toString();

    cout << "Hello World!" << endl;

    foo(4);
    foo(8);
    foo(16);
    foo(32);
    foo(55);
    foo(41);
    foo(0);

    return 0;
}

