#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "include.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
struct node
{
    T data;
    int count;
    string LinePara;

    node();
    node(T d, string lp, int c = 1);
    node(const node<T> &other);
    node<T>& operator=(const node<T> &other);
    ~node();

    template<typename U>
    friend
    ostream& operator<<(ostream& out, node<U> &n);

    template<typename U>
    friend
    istream& operator>>(istream& in, node<U> &n);

    template<typename U>
    friend
    bool operator<(node<U> a, node<U> b);

    template<typename U>
    friend
    bool operator>(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator==(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator<=(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator>=(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator!=(node<U> a, node<U> b);
};

template<typename T>
node<T>::node()
{
    count = 0;
}

template<typename T>
node<T>::node(T d, string lp, int c)
{
    data = d;
    count = c;
    LinePara = lp;
}


template<typename T>
node<T>::node(const node<T> &other)
{
    data = other.data;
    count = other.count;
    LinePara = other.LinePara;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        data = other.data;
        count = other.count;
        LinePara = other.LinePara;
    }
    return *this;
}

template<typename T>
node<T>::~node()
{
    count = 0;
}

template<typename U>
ostream& operator<<(ostream& out, node<U> &n)
{
    out<<n.data<<"["<<n.count<<"] ";
    return out;
}

template<typename U>
istream& operator>>(istream& in, node<U> &n)
{
    char junk;
    U data;
    int count;
    if(in>>data>>junk>>count>>junk)
    {
        n.data = data;
        n.count = count;
    }
    return in;
}



template<typename U>
bool operator<(node<U> a, node<U> b)
{
    return a.data < b.data;
}


template<typename U>
bool operator>(node<U> a, node<U> b)
{
    return a.data > b.data;
}


template<typename U>
bool operator==(node<U> a, node<U> b)
{
    return a.data == b.data;
}


template<typename U>
bool operator<=(node<U> a, node<U> b)
{
    return a.data <= b.data;
}


template<typename U>
bool operator>=(node<U> a, node<U> b)
{
    return a.data >= b.data;
}


template<typename U>
bool operator!=(node<U> a, node<U> b)
{
    return a.data != b.data;
}

#endif // NODE_H
