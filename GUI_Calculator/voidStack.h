#ifndef VOIDSTACK_H
#define VOIDSTACK_H
#include "myStack.h"
#include "include.h"
#include "typeinfo"
#include <iomanip>
using namespace std;

class voidStack : public myStack
{
public:
    voidStack();
    ~voidStack();

    template<typename T>
    void push(T data);

    template<typename T>
    void pop(T &data);

    template<typename T>
    voidStack& operator>>(T &d);
    template<typename T>
    voidStack& operator<<(T &d);

    template<typename T>
    void topData(T& data);

    void show();//display the voidstack
private:


};

voidStack::voidStack()
{
    anchor.nextNode()=NULL;
    tos=-1;
    maxSize=50;
}

voidStack::~voidStack()
{
    nukem();
}



template<typename T>
void voidStack::push(T data)
{
    T *dataAdded = new T;
    *dataAdded = data;

    string type(typeid(data).name());

    myStack::push((void*)dataAdded, type);
}


template<typename T>
void voidStack::pop(T &data)
{
    if(empty())
        throw EMPTY;

    string type(typeid(data).name());
    if(type!=top().type)
        throw WRONG_TYPE;

    data = *(T*)top().data;
    delete(T*)top().data;
    top().data=NULL;
    myStack::pop();
}


template<typename T>
voidStack& voidStack::operator>>(T &d)
{
    pop(d);
    return *this;
}

template<typename T>
voidStack& voidStack::operator<<(T &d)
{
    push(d);
    return *this;
}

template<typename T>
void voidStack::topData(T& data)
{
    if(empty())
        throw EMPTY;

    string type(typeid(data).name());
    if(type!=top().type)
        throw WRONG_TYPE;

    data = *(T*)top().data;
}

void voidStack::show()
{
    node* temp;
    temp=anchor.nextNode();
    cout << "stack is: ";

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
}


#endif // VOIDSTACK_H
