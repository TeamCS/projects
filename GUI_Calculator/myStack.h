#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include "node.h"
#include <string>
#include <iomanip>
#include "include.h"
#include "mixed.h"

using namespace std;

class myStack //parent class for VoidStack
{
public:
        myStack();
        myStack(void *&data, string &type, const int &s=50);
        virtual ~myStack();
        myStack(myStack &other);
        myStack& operator=(myStack &other);

        void* topData();
        string topDataType();
        bool full() const;
        bool empty() const;
        int size() const;
        int TheMaxSize() const;
        void resize(int s);
        void clear();

protected:
        int maxSize, tos;
        node anchor;

        void copy(myStack &other);
        void nukem();
        node& top();

        void push(void *data, string &type);
        void pop();
        void pop(void* &data, string &type);
private:

};

//----------------------------------------------------------------
myStack::myStack()
{
    anchor.nextNode()=NULL;
    tos=-1;
    maxSize=50;
}

myStack::myStack(void *&data, string &type, const int& s)
{
    if(s < 1)
        throw BAD_SIZE;

    tos=0;
    maxSize=s;
    node* newNode=new node(data,type);
    anchor.nextNode() = newNode;
}

myStack::~myStack()
{
    nukem();
}

myStack::myStack(myStack &other)
{
    copy(other);
}

myStack& myStack::operator=(myStack &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}
//-------------------------------------------------------------------------------

void myStack::push(void *data, string &type)
{
    if(full())
        throw FULL;

    node *start = &anchor,
            *newNode = new node(data, type);

    for(; start->nextNode(); start = start->nextNode());

    if(!start->nextNode())//nextnode=NULL
    {
        start->nextNode() = newNode;
        tos++;
    }

}


void myStack::pop()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor,
         *popNode = new node();
    for(; start->nextNode()->nextNode(); start = start->nextNode());

    popNode=start->nextNode();

    tos--;

    start->nextNode()=NULL;
    delete popNode;
}

void myStack::pop(void* &data, string &type)
{
    if(empty())
        throw EMPTY;

    node *start = &anchor,
         *popNode = new node();
    for(; start->nextNode()->nextNode(); start = start->nextNode());

    popNode=start->nextNode();

    data = start->nextNode()->theData();
    type = start->nextNode()->theType();
    tos--;

    start->nextNode()=NULL;
    delete popNode;
}




//-----------------------------------------------------------------------
void *myStack::topData()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return start->theData();
}

string myStack::topDataType()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return start->theType();
}

bool myStack::full() const
{
    return tos+1 == maxSize;
}

bool myStack::empty() const
{
    return tos<0;
}

int myStack::size() const
{
    return tos+1;
}

int myStack::TheMaxSize() const
{
    return maxSize;
}

void myStack::resize(int s)
{
    if(s < 1 || s < tos+1)
        throw BAD_SIZE;
    maxSize=s;
}
void myStack::clear()
{
    nukem();
}

node& myStack::top()
{
    if(empty())
        throw EMPTY;
    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return *start;
}

//------------------------------------------------------------

void myStack::copy(myStack &other)
{

    nukem();

    maxSize=other.maxSize;

    node* temp;
    temp=other.anchor.nextNode();


    for(;temp != NULL;temp = temp->nextNode())
    {
        if(temp->theType()=="Ss")
        {
            void* newVoidData;
            string* newString;
            newString=new string(*(string*)temp->theData());

            newVoidData = newString;
            string newString2 ="Ss";

            try
            {
                push(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the stack is full" << endl;
            }

        }
        else if(temp->theType()=="i")
        {
            void* newVoidData;
            int* newInt;
            newInt=new int(*(int*)temp->theData());

            newVoidData = newInt;
            string newString2 ="i";

            try
            {
                push(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the stack is full" << endl;
            }
        }
        else if(temp->theType()=="c")
        {
            void* newVoidData;
            char* newChar;
            newChar=new char(*(char*)temp->theData());

            newVoidData = newChar;
            string newString2 ="c";

            try
            {
                push(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the stack is full" << endl;
            }
        }
        else if(temp->theType()=="d")
        {
            void* newVoidData;
            double* newDouble;
            newDouble=new double(*(double*)temp->theData());

            newVoidData = newDouble;
            string newString2 ="d";

            try
            {
                push(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the stack is full" << endl;
            }

        }
        else if(temp->theType()=="5Mixed")
        {
            void* newVoidData;
            Mixed* newMixed;
            newMixed=new Mixed(*(Mixed*)temp->theData());

            newVoidData = newMixed;
            string newString2 ="5Mixed";

            try
            {
                push(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the stack is full" << endl;
            }

        }
    }
}

void myStack::nukem()
{
    node *bye = anchor.nextNode();
    while(bye)
    {

        anchor.nextNode() = anchor.nextNode()->nextNode();
        delete bye;
        bye = anchor.nextNode();
    }
    maxSize=0;
    tos=-1;
}


#endif // MYSTACK_H
