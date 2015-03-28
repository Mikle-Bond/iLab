#define DBG

#include <iostream>
#include "mystack.h"

using namespace std;


void foo (int v)
{
    static MyStack<int> glob;
    glob.push(v);
    if (v == 0) glob.dump();
}


int main()
{
    cout << "Enter main ()" << endl;

    MyStack<float> first;
    MyStack<float> *second = &first;

    // First fill the stack
    for (int i = 10; i < 8000; i += 10)
        first.push(i);
    // Print it
    first.dump();


    second->pop();

    // Pop one element
    cout << first.pop() << endl;

    // Push user element
    int t = 0;
    cin >> t;
    first.push(t);

    // Print stack again
    first.dump();

    cout << "Hello World!" << endl;

    foo(4);
    foo(8);
    foo(16);
    foo(32);
    foo(55);
    foo(41);
    foo(0);

    MyStack<string> str_s(10);
    string temp = "abcd";
    str_s.push(temp);
    str_s.dump();

    return 0;
}

