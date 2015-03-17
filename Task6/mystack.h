#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstdlib>
#include <vector>
#include <cerrno>

#ifdef DBG
#define dout if(1)
#else
#define dout if(0)
#endif

template <typename st_elem_t>
class MyStack {
private:
    typedef int st_count_t;
    enum err_t {
        tea_cup = 0,                // no error
        out_of_range = EOVERFLOW,   // pop from empty stack
        ngtv_countr = EACCES,       // counter < 0
        no_data = EFAULT,           // st_data == NULL
        cant_create = ENOMEM,       // st_data == NULL

    };
public:
    MyStack ();
    ~MyStack ();

    void push (st_elem_t val);

    st_elem_t pop ();

    void toString (void);

private:

    err_t MyStackOk ();

    void err_switch(err_t errcode);

    std::vector<st_elem_t> *st_data;

    st_count_t st_counter;

    st_count_t st_size;
};

//=========================================================

template <typename st_elem_t>
MyStack<st_elem_t>::MyStack ():
    st_data (NULL),
    st_counter (0)
{
    st_data = new std::vector<st_elem_t>;
    if (st_data == NULL) err_switch(cant_create);

    dout std::cerr << "[INFO] Stack constructed: " << this << std::endl;
}

template <typename st_elem_t>
MyStack<st_elem_t>::~MyStack ()
{
    free(st_data);
    delete st_data;
    st_data = NULL;
    st_counter = -1;
    dout std::cerr << "[INFO] Stack deconstructed: " << this << std::endl;
}

template <typename st_elem_t>
void MyStack<st_elem_t>::push (st_elem_t val)
{
    MyStackOk();
    // if (st_counter > st_size) MyStack::err_switch(push_out);
    st_data->push_back(val);
    ++st_counter;
}

template <typename st_elem_t>
st_elem_t MyStack<st_elem_t>::pop ()
{
    MyStack::MyStackOk();
    if (!st_counter) MyStack::err_switch(out_of_range);
    st_elem_t ret = st_data->back();
    st_data->pop_back();
    --st_counter;
    return ret;
}

template <typename T>
typename MyStack<T>::err_t MyStack<T>::MyStackOk()
{
    if (this == NULL) MyStack<T>::err_switch(no_data);
    if (st_data == NULL) MyStack<T>::err_switch(no_data);
    if (st_counter < 0) MyStack<T>::err_switch(ngtv_countr);
    return tea_cup;
}

template <typename st_elem_t>
void MyStack<st_elem_t>::toString()
{
    int i = 0;
    MyStack::MyStackOk();

    std::cout << "[DUMP] Stack on " << this << std::endl;
    std::cout << "[DUMP] Counter: " << st_counter << std::endl;
    std::cout << "[DUMP] Max length: " << st_size << std::endl;
    if (st_counter >= 0)
        std::cout << "[DUMP] List of elements:" << std::endl;
    while (i < st_counter) {
        std::cout << "( " << i << " ) = " << (*st_data)[i] << std::endl;
        i++;
    }
    std::cout << "[DUMP] End of dump" << std::endl << std::endl;


}

template <typename st_elem_t>
void MyStack<st_elem_t>::err_switch(err_t errcode)
{
    if (errcode) errno = errcode;

    dout {
        switch (errcode) {

        case no_data:
            std::cerr << "[WARN] NULL pointer got" << std::endl;
            std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
            exit(1);
            break;

        case ngtv_countr:
            std::cerr << "[WARN] Counter can't be negative" << std::endl;
            std::cerr << "[DUMP] Counter: " << st_counter << std::endl;
            std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
            exit(1);
            break;

        case out_of_range:
            std::cerr << "[WARN] Push/pop access denied" << std::endl;
            std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
            exit(1);
            break;

        case cant_create:
            std::cerr << "[WARN] Data vector hasn't been created" << std::endl;
            std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
            exit(1);
            break;


        default:
            std::cerr << "[WARN] I dont know why you become here" << std::endl;
            break;
        }
    }
}


#endif // MYSTACK_H
