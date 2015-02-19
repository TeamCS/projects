#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "include.h"

using namespace std;

template<typename T>
struct node
{
    T data;
    string LinePara;  //saves all the positions of the word as a single string
                      //with format:    paragraph-line paragraph-line .....

    node()
    {
    }

    node(const node<T> &other)
    {
        data = other.data;
        LinePara = other.LinePara;
    }

    node(T d, string lp)
    {
        data = d;
        LinePara = lp;
    }

    ~node()
    {
    }

    template<typename U>
    friend
    bool operator<(node x, node y);


    template<typename U>
    friend
    bool operator>(node x, node y);

    template<typename U>
    friend
    bool operator==(node x, node y);

    template<typename U>
    friend
    bool operator>=(node x, node y);

    template<typename U>
    friend
    bool operator<=(node x, node y);

};

template<typename U>
bool operator<(node<U> x, node<U> y)
{
    return x.data < y.data;
}

template<typename U>
bool operator>(node<U> x, node<U> y)
{
    return x.data > y.data;
}

template<typename U>
bool operator==(node<U> x, node<U> y)
{
    return x.data == y.data;
}

template<typename U>
bool operator>=(node<U> x, node<U> y)
{
    return x.data >= y.data;
}

template<typename U>
bool operator<=(node<U> x, node<U> y)
{
    return x.data <= y.data;
}
#endif // NODE_H
