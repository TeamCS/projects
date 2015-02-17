#ifndef VOIDQUEUE_H
#define VOIDQUEUE_H
#include "myQueue.h"
#include "include.h"
#include "typeinfo"
#include <iomanip>
using namespace std;

class voidQueue : public myQueue
{
public:
    voidQueue();
    ~voidQueue();

    template<typename T>
    void enqueue(T data);

    template<typename T>
    void dequeue(T &data);

    template<typename T>
    voidQueue& operator>>(T &d);
    template<typename T>
    voidQueue& operator<<(T &d);

    template<typename T>
    void frontData(T& data);
    template<typename T>
    void backData(T& data);

    void show();//display the voidqueue

private:


};


voidQueue::voidQueue()
{
    anchor.nextNode()=NULL;
    head=-1;
    tail=-1;
    maxSize=50;
}

voidQueue::~voidQueue()
{
    nukem();
}

template<typename T>
void voidQueue::enqueue(T data)
{
    T *dataAdded = new T;
    *dataAdded = data;

    string type(typeid(data).name());

    myQueue::enqueue((void*)dataAdded,type);
}

template<typename T>
void voidQueue::dequeue(T &data)
{
    if(empty())
        throw EMPTY;
    string type(typeid(data).name());
    if(type!=front().type)
        throw WRONG_TYPE;

    data = *(T*)front().data;
    delete(T*)front().data;
    front().data=NULL;
    myQueue::dequeue();
}

template<typename T>
voidQueue& voidQueue::operator>>(T &d)
{
    dequeue(d);
    return *this;
}

template<typename T>
voidQueue& voidQueue::operator<<(T &d)
{
    enqueue(d);
    return *this;
}

template<typename T>
void voidQueue::frontData(T& data)
{
    if(empty())
        throw EMPTY;
    string type(typeid(data).name());
    if(type!=front().type)
        throw WRONG_TYPE;

    data = *(T*)front().data;

}

template<typename T>
void voidQueue::backData(T& data)
{
    if(empty())
        throw EMPTY;

    string type(typeid(data).name());
    if(type!=back().type)
        throw WRONG_TYPE;

    data = *(T*)back().data;
}

void voidQueue::show()
{
    node* temp;
    temp=anchor.nextNode();
    cout << "queue is: ";

    for(;temp != NULL;temp = temp->nextNode())
    {
        if(temp->theType()=="Ss")
        {
            string newString;
            newString=*(string*)temp->theData();
            cout << " " << newString << " ";

        }
        else if(temp->theType()=="i")
        {
            int newInt;
            newInt=*(int*)temp->theData();
            cout << " " << newInt << " ";

        }
        else if(temp->theType()=="c")
        {
            char newChar;
            newChar=*(char*)temp->theData();
            cout << " " << newChar << " ";

        }
        else if(temp->theType()=="d")
        {
            double newDouble;
            newDouble=*(double*)temp->theData();
            cout << " " << newDouble << " ";
        }
        else if(temp->theType()=="5Mixed")
        {
            Mixed newMixed;
            newMixed=*(Mixed*)temp->theData();
            cout << " " << newMixed << " ";
        }
    }
    cout <<endl;
}


#endif // VOIDQUEUE_H
