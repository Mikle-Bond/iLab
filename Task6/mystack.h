#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstdlib>

class MyStack {
private:
    typedef int st_elem_t;
    typedef int st_count_t;
    enum err_t {
        tea_cup,            // no error
        no_pop,             // pop from empty stack
        push_out,           // push out of range
        no_stack,           // stack NULL pointer
        ngtv_countr,        // counter < 0
    };
public:
    // stack with max_len limit
    MyStack (st_count_t max_len);
    ~MyStack ();

    // push val to the stack
    void push (st_elem_t val);
    // recive one element
    st_elem_t pop ();
    // print current state of the stack
    void toString (void);
private:
    MyStack (); // only stack with limits (for now)

    // check the curren state
    err_t MyStackOk ();
    // in error case drop down WHOLE program
    void emergencyExit(err_t errcode);

    // the stack
    st_elem_t *st_data;
    // number of elements in stack
    st_count_t st_counter;
    // stack size
    st_count_t st_size;
};

#endif // MYSTACK_H
