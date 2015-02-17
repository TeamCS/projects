#ifndef NODE_H
#define NODE_H
#include<iostream>
#include <cstdlib>
#include <string>
#include "include.h"

using namespace std;


class node
{
    public:
        node();
        node(void *&d, string &t);
        ~node();
        node(const node &other);
        node& operator=(const node &other);

        void* &theData();
        string theType();
        node* &nextNode();

        friend
        ostream& operator<<(ostream &out, node &other);

        friend
        istream& operator>>(istream &in, node &other);


        void* data;
        string type;
        node* next;
        void copy(const node &other);


    private:

};

node::node()
{
    next = NULL;
}

node::node(void *&d, string &t)
{
    data = d;
    type = t;
    next = NULL;
}

node::~node()
{
    next = NULL;
}

node::node(const node &other)
{
    copy(other);
}

node& node::operator=(const node &other)
{
    if(this != &other)
        copy(other);
    return *this;
}


void*& node::theData()
{
    return data;
}

string node::theType()
{
    return type;
}

node*& node::nextNode()
{
    return next;
}

//------------------------------------------------------------------
void node::copy(const node &other)
{
    data = other.data;
    next = NULL;
}
//------------------------------------------------------------------
ostream& operator<<(ostream &out, node &other)
{
    out<<other.theData()<<endl;
    return out;
}

istream& operator>>(istream &in, node &other)
{
    void* d;
    string x;
    string& t=x;
    if(in>>d>>t)
    {
       other.data = d;
       other.type = t;
       other.next = NULL;
    }
    return in;
}


#endif // NODE_H
