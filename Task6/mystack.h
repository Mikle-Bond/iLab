#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>


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
        EPOINTER,                   // this == NULL
        EEMPTY,                     // pop from empty stack
        ECOUNTER,                   // counter < 0
        EMEMOUT,                    // st_data == NULL
        EGTMAX,                     // overflow max elements
        EPARAM,                     // invalid parameters
    };

public:
    MyStack ();
    MyStack (int max_size);
    ~MyStack ();

    int push (st_elem_t val);
    st_elem_t pop ();

    void dump (void);

    st_count_t get_counter ();
    st_count_t get_size ();
    err_t get_errno ();

private:
    st_elem_t *st_data = NULL;
    st_count_t st_counter;
    st_count_t st_size = 16;

    err_t error_n;
    void drop(err_t errcode);

    err_t is_not_OK ();
    int d_resize ();
};

//=========================================================


template <typename st_elem_t>
MyStack<st_elem_t>::MyStack ()
{
    st_counter = 0;

    st_data = new st_elem_t [st_size];
    if (st_data == NULL) {
        error_n = EMEMOUT;
    }

    dout std::cerr << "[INFO] Autosized stack constructed: " << this << std::endl;
}


template <typename st_elem_t>
MyStack<st_elem_t>::MyStack(int max_size)
{
    st_counter = 0;
    st_size = max_size;

    if (st_size < 0) {
        // errno = EINVAL;
        drop (EPARAM);
    } else {
        st_data = new st_elem_t [st_size];
        if (st_data == NULL) {
            error_n = EMEMOUT;
        }

        dout std::cerr << "[INFO] Stack constructed: " << this << "\n" <<
                          "[INFO] Size: " << st_size << "\n";
    }
}


template <typename st_elem_t>
MyStack<st_elem_t>::~MyStack ()
{
    delete [] st_data;
    st_data = NULL;
    st_counter = -1;
    st_size = -1;
    dout std::cerr << "[INFO] Stack deconstructed: " << this << std::endl;
}


template <typename st_elem_t>
int MyStack<st_elem_t>::push (st_elem_t val)
{
    if (is_not_OK())
        return -1;
    if (st_counter > st_size &&
            d_resize())
        return -1;

    st_data[st_counter++] = val;
    return 0;
}


template <typename st_elem_t>
st_elem_t MyStack<st_elem_t>::pop ()
{
    if (is_not_OK())
        return -1;
    if (0 == st_counter) {
        drop(EEMPTY);
        return -1;
    }

    st_elem_t ret = st_data[--st_counter];
    return ret;
}


template <typename T>
typename MyStack<T>::err_t MyStack<T>::is_not_OK()
{
    err_t ret = tea_cup;
    if (this == NULL)
        ret = EPOINTER;
    else if (st_counter < 0)
        ret = ECOUNTER;
    else if (st_counter > st_size + 1)
        ret = ECOUNTER;
    else if (st_data == NULL)
        ret = EMEMOUT;

    MyStack<T>::drop(ret);
    return ret;
}


template <typename st_elem_t>
void MyStack<st_elem_t>::dump()
{
    int i = 0;
    if (MyStack::is_not_OK()) return;

    std::cout << "[DUMP] Stack on " << this << std::endl <<
                 "[DUMP] Counter: " << st_counter << std::endl <<
                 "[DUMP] Max length: " << st_size << std::endl;
    if (st_counter > 0)
        std::cout << "[DUMP] List of elements:" << std::endl;
    while (i < st_counter) {
        std::cout << "( " << i << " ) = " << st_data[i] << std::endl;
        ++i;
    }
    std::cout << "[DUMP] End of dump" << std::endl << std::endl;
}


template <typename T>
typename MyStack<T>::st_count_t MyStack<T>::get_counter () { return st_counter; }


template <typename T>
typename MyStack<T>::st_count_t MyStack<T>::get_size () { return st_size; }


template <typename T>
typename MyStack<T>::err_t MyStack<T>::get_errno () { return error_n; }


template <typename st_elem_t>
void MyStack<st_elem_t>::drop(err_t errcode)
{
    error_n = errcode;

    dout if (errcode) {
        std::cerr << "[INFO] from " << this << "\n";

        switch (errcode) {

        case EPOINTER:
            std::cerr << "[WARN] NULL pointer got" << std::endl;
            break;

        case ECOUNTER:
            std::cerr << "[WARN] Counter can't be negative" << std::endl <<
                         "[DUMP] Counter: " << st_counter << std::endl;
            break;

        case EMEMOUT:
            std::cerr << "[WARN] Data array hasn't been created" << std::endl;
            break;

        case EEMPTY:
            std::cerr << "[WARN] Pop from empty stack" << std::endl;

        case EGTMAX:
            std::cerr << "[WARN] Max size overflowed" << std::endl;

        case EPARAM:
            std::cerr << "[WARN] Invalid parameter" << std::endl;

        case tea_cup:
            break;

        default:
            // std::cerr << "[WARN] I dont know why you become here" << std::endl;
            break;
        }
        // std::cerr << "[DUMP] End of dump" << std::endl << std::endl;
        std::cerr << std::endl;
        // exit(1);
    }
}


template <typename st_elem_t>
int MyStack<st_elem_t>::d_resize ()
{
    dout std::cerr << "[INFO] Stack auto resized: " << this << std::endl;

    int new_size = st_size << 1;
    if (new_size < 0) {
        // errno = ERANGE;
        drop(EMEMOUT);
        return -1;
    }

    st_elem_t *ns = new st_elem_t [new_size];

    if (ns == NULL) {
        drop(EMEMOUT);
        return -1;
    }

//    std::cout << "pong" << std::endl; // ping

    for (int i = 0; i < st_counter; i++) {
        ns[i] = st_data[i];
    }

    delete [] st_data;

    st_size = new_size;
    st_data = ns;

    dout std::cerr << "[INFO] Success, new size: " << new_size << std::endl;

//    system("pause");

    return 0;
}


#endif // MYSTACK_H
