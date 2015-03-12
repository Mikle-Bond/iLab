#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstdlib>

template <typename st_elem_t>
class MyStack {
private:
    typedef int st_count_t;
    enum err_t {
        tea_cup,            // no error
        no_pop,             // pop from empty stack
        push_out,           // push out of range
        no_stack,           // stack NULL pointer
        ngtv_countr,        // counter < 0
        no_class,           // this == NULL
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

//=========================================================

template <typename st_elem_t>
MyStack<st_elem_t>::MyStack (st_count_t max_len):
    st_data (NULL),
    st_counter (0),
    st_size (max_len)
{
    if (max_len < 0) exit(1);
    st_data = (st_elem_t *)calloc(sizeof(st_elem_t), max_len);
    std::cerr << "[INFO] Stack constructed: " << this << std::endl;
}

template <typename st_elem_t>
MyStack<st_elem_t>::~MyStack ()
{
    free(st_data);
    st_data = NULL;
    st_counter = -1;
    std::cerr << "[INFO] Stack deconstructed: " << this << std::endl;
}

template <typename st_elem_t>
void MyStack<st_elem_t>::push (st_elem_t val)
{
    MyStackOk();
    if (st_counter > st_size) MyStack::emergencyExit(push_out);
    st_data[st_counter++] = val;
}

template <typename st_elem_t>
st_elem_t MyStack<st_elem_t>::pop ()
{
    MyStack::MyStackOk();
    if (!st_counter) MyStack::emergencyExit(no_pop);
    st_elem_t ret = st_data[--st_counter];
    return ret;
}

template <typename T>
typename MyStack<T>::err_t MyStack<T>::MyStackOk()
{
    if (this == NULL) MyStack<T>::emergencyExit(no_class);
    if (st_data == NULL) MyStack<T>::emergencyExit(no_stack);
    if (st_counter < 0) MyStack<T>::emergencyExit(ngtv_countr);
    return tea_cup;
}

template <typename st_elem_t>
void MyStack<st_elem_t>::toString()
{
    int i = 0;
    MyStack::MyStackOk();

    std::cerr << "[DUMP] Stack on " << this << std::endl;
    std::cerr << "[DUMP] Counter: " << st_counter << std::endl;
    std::cerr << "[DUMP] Max length: " << st_size << std::endl;
    if (st_counter >= 0)
        std::cerr << "[DUMP] List of elements:" << std::endl;
    while (i < st_counter) {
        std::cerr << "( " << i << " ) = " << st_data[i] << std::endl;
        i++;
    }
    std::cerr << "[DUMP] End of dump" << std::endl << std::endl;


}

template <typename st_elem_t>
void MyStack<st_elem_t>::emergencyExit(err_t errcode)
{
    switch (errcode) {

    case no_stack:
        std::cerr << "[WARN] Empty stack (NULL pointer)" << std::endl;
        std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
        exit(1);
        break;

    case ngtv_countr:
        std::cerr << "[WARN] Counter can't be negative" << std::endl;
        std::cerr << "[DUMP] Counter: " << st_counter << std::endl;
        std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
        exit(1);
        break;

    case push_out:
        std::cerr << "[WARN] Push to filled up stack" << std::endl;
        MyStack::toString();
        exit(1);
        break;

    case no_pop:
        std::cerr << "[WARN] Pop from empty stack" << std::endl;
        std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
        exit(1);
        break;

    case no_class:
        std::cerr << "[WARN] NULL pointer is not a class" << std::endl;
        std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
        exit(1);


    default:

        std::cerr << "[WARN] I dont know how you become here" << std::endl;
        break;
    }
}


#endif // MYSTACK_H
