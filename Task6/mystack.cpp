#include "mystack.h"
#include <iostream>
#include <cstdlib>

MyStack::MyStack (st_count_t max_len):
    st_data (NULL),
    st_counter (0),
    st_size (max_len)
{
    if (max_len < 0) exit(1);
    st_data = (st_elem_t *)calloc(sizeof(st_elem_t), max_len);
    std::cerr << "[INFO] Stack constructed: " << this << std::endl;
}

MyStack::~MyStack ()
{
    free(st_data);
    st_data = NULL;
    st_counter = -1;
    std::cerr << "[INFO] Stack deconstructed: " << this << std::endl;
}

void MyStack::push (st_elem_t val)
{
    MyStackOk();
    if (st_counter > st_size) MyStack::emergencyExit(push_out);
    st_data[st_counter++] = val;
}

MyStack::st_elem_t MyStack::pop ()
{
    MyStack::MyStackOk();
    if (!st_counter) MyStack::emergencyExit(no_pop);
    st_elem_t ret = st_data[--st_counter];
    return ret;
}

MyStack::err_t MyStack::MyStackOk()
{
    if (this == NULL) MyStack::emergencyExit(no_class);
    if (st_data == NULL) MyStack::emergencyExit(no_stack);
    if (st_counter < 0) MyStack::emergencyExit(ngtv_countr);
    return tea_cup;
}

void MyStack::toString()
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

void MyStack::emergencyExit(err_t errcode)
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

