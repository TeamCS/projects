#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include "node.h"
#include <string>
#include <iomanip>
#include "include.h"
#include "mixed.h"

using namespace std;

class myQueue //parent class of voidQueue
{
public:
        myQueue();
        myQueue(void *&data, string &type, const int &s=50);
        virtual ~myQueue();
        myQueue(myQueue &other);
        myQueue& operator=(myQueue &other);

        void* frontData();
        string frontDataType();
        void* backData();
        string backDataType();

        bool full() const;
        bool empty() const;
        int size() const;
        int TheMaxSize() const;
        void resize(int s);
        void clear();

protected:
        int maxSize, head, tail;
        node anchor;

        void copy(myQueue &other);
        void nukem();
        node& front();
        node& back();

        void enqueue(void *data, string &type);
        void dequeue();
        void dequeue(void* &data, string &type);
private:

};

myQueue::myQueue()
{
    anchor.nextNode()=NULL;
    head=-1;
    tail=-1;
    maxSize=50;
}

myQueue::myQueue(void *&data, string &type, const int& s)
{
    if(s < 1)
        throw BAD_maxSize;

    head=0;
    tail=0;
    maxSize=s;
    node* newNode=new node(data,type);
    anchor.nextNode() = newNode;
}

myQueue::~myQueue()
{
    nukem();
}

myQueue::myQueue(myQueue &other)
{
    copy(other);
}

myQueue& myQueue::operator=(myQueue &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

//-----------------------------------------------------------------

void* myQueue::frontData()
{
    if(empty())
        throw EMPTY;
    return anchor.nextNode()->theData();
}

string myQueue::frontDataType()
{
    if(empty())
        throw EMPTY;

    return anchor.nextNode()->theType();
}

void* myQueue::backData()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return start->theData();
}

string myQueue::backDataType()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return start->theType();
}

bool myQueue::full() const
{
    return (tail + 1)%maxSize == head;
}

bool myQueue::empty() const
{
    if(head==-1 && tail==-1)
        return true;
    else
        return false;
}

int myQueue::size() const
{
    if((tail==-1) && (head==-1))
       return 0;
    else
       return tail - head + 1;
}

int myQueue::TheMaxSize() const
{
    return maxSize;
}

void myQueue::resize(int s)
{
    if(s <= size())
        throw BAD_maxSize;

    maxSize=s;
}

void myQueue::clear()
{
    nukem();
}

//-------------------------------------------------------------

void myQueue::copy(myQueue &other)
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
                enqueue(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the queue is full" << endl;
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
                enqueue(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the queue is full" << endl;
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
                enqueue(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the queue is full" << endl;
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
                enqueue(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the queue is full" << endl;
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
                enqueue(newVoidData, newString2);
            }
            catch(...)
            {
                cout << "the queue is full" << endl;
            }

        }
    }
}

void myQueue::nukem()
{
    node *bye = anchor.nextNode();
    while(bye)
    {
        anchor.nextNode() = anchor.nextNode()->nextNode();
        delete bye;
        bye = anchor.nextNode();
    }
    maxSize=0;
    head=-1;
    tail=-1;
}

node& myQueue::front()
{
    if(empty())
        throw EMPTY;

    return *anchor.nextNode();
}

node& myQueue::back()
{
    if(empty())
        throw EMPTY;

    node *start = &anchor;
    for(; start->nextNode(); start = start->nextNode());

    return *start;
}

//-------------------------------------------------------------

void myQueue::enqueue(void *data, string &type)
{
    if(full())
        throw FULL;
    else if(empty())
    {
        head=0;
        tail=0;
    }
    else
    {
        head=0;
        tail++;
    }

    node *start = &anchor,
            *newNode = new node(data, type);

    for(; start->nextNode(); start = start->nextNode());

    if(!start->nextNode())
    {
        start->nextNode() = newNode;
    }
}

void myQueue::dequeue()
{
    if(empty())
        throw EMPTY;
    else
    {
        if(head==tail)
        {
            head=-1;
            tail=-1;
        }
        else
        {
            head=0;
            tail--;
        }

        node *dequeueNode = new node();

        dequeueNode=anchor.nextNode();

        anchor.nextNode()=anchor.nextNode()->nextNode();

        delete dequeueNode;
    }
}

void myQueue::dequeue(void* &data, string &type)
{
    if(empty())
        throw EMPTY;
    else
    {
        if(head==tail)
        {
            head=-1;
            tail=-1;
        }
        else
        {
            head=0;
            tail--;
        }

        node *dequeueNode = new node();

        dequeueNode=anchor.nextNode();

        data = anchor.nextNode()->theData();
        type = anchor.nextNode()->theType();

        anchor.nextNode()=anchor.nextNode()->nextNode();

        delete dequeueNode;
    }
}

#endif // MYQUEUE_H
