#ifndef VECTORHeap_H
#define VECTORHeap_H
#include <cmath>
#include "node.h"

using namespace std;


template<typename T>
class vectorHeap
{
public:
    vectorHeap(unsigned int s = 3, TYPE m = LESS);
    vectorHeap(T d, string lp, unsigned int s = 3, TYPE m = LESS);
    ~vectorHeap();
    vectorHeap(const vectorHeap<T> &other);
    vectorHeap<T>& operator=(const vectorHeap<T> &other);

    vectorHeap<T>& operator<<(T d);
    vectorHeap<T>& operator>>(node<T> &d);

    void insert(T d, string lp);
    void pop(node<T>& d);
    int levels();       //return the level that the heap has
    void clear();
    bool full();
    bool empty() const;
    unsigned int size();    //return the actual number of nodes in this heap

    template<typename U>
    friend
    ostream& operator<<(ostream& out, vectorHeap<U> &h);

    template<typename U>
    friend
    istream& operator>>(istream& in, vectorHeap<U> &h);

private:

    typedef bool (vectorHeap<T>::*fptr)(node<T> &x, node<T> &y);

    vector<node<T>*> theHeap;
    unsigned int lastNode, capacity, root;
    TYPE minMax;
    fptr compare[2];


    int Left(int index);
    int Right(int index);
    void copy(const vectorHeap<T> &other);
    void nukem();
    int findParent(int num);

    void reHeapifyUp();
    void reHeapifyDown();
    bool greater(node<T> &x, node<T> &y);
    bool less(node<T> &x, node<T> &y);
    node<T>* getNode(unsigned int nodeNum);
    void swap(node<T> &x, node<T> &y);
};

template<typename T>
vectorHeap<T>::vectorHeap(unsigned int s, TYPE m)
{

    theHeap.push_back(NULL);
    lastNode = 0;
    capacity = s;
    minMax = m;
    root=0;
    compare[0] = &vectorHeap<T>::less;
    compare[1] = &vectorHeap<T>::greater;
}

template<typename T>
vectorHeap<T>::vectorHeap(T d, string lp, unsigned int s, TYPE m)
{

    theHeap.push_back(NULL);

    node<T>* newNode = new node<T>(d, lp);

    theHeap[0] = newNode;

    lastNode = 1;
    capacity = s;
    minMax = m;
    root=1;
    compare[0] = &vectorHeap<T>::less;
    compare[1] = &vectorHeap<T>::greater;
}

template<typename T>
vectorHeap<T>::~vectorHeap()
{
    nukem();
}

template<typename T>
vectorHeap<T>::vectorHeap(const vectorHeap<T> &other)
{
    copy(other);
}

template<typename T>
vectorHeap<T>& vectorHeap<T>::operator=(const vectorHeap<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
vectorHeap<T>& vectorHeap<T>::operator<<(T d)
{
    insert(d);
    return *this;
}

template<typename T>
vectorHeap<T>& vectorHeap<T>::operator>>(node<T> &d)
{
    pop(d);
    return *this;
}

//---------------------------------------------------------------

template<typename T>
void vectorHeap<T>::insert(T d, string lp)
{
    lastNode++;
    node<T>* newNode = new node<T>(d, lp);

    if(empty())
    {
        theHeap[0] = newNode;
    }

    else
    {

        if(lastNode > theHeap.size())        //resize the heap
        {
            theHeap.resize(theHeap.size()+pow(2., levels()-1));

            int tempsize = theHeap.size();

            for(int i = lastNode-1 ; i < tempsize ; i++)
                theHeap[i] = NULL;

            capacity = theHeap.size();
        }


        theHeap[lastNode-1] = newNode;

        reHeapifyUp();
    }
    root = 1;
}

template<typename T>
void vectorHeap<T>::pop(node<T>& d)
{
    if(empty())
        throw EMPTY;


    if(lastNode == 1)
    {
        d = *theHeap[lastNode-1];
        delete theHeap[root];
        theHeap[0] = NULL;

        root = 0;
        lastNode = 0;
    }
    else
    {
        int deleteIndex = lastNode-1;

        node<T>* temp;
        node<T>* temp2;

        temp = theHeap[0];

        temp2 = theHeap[deleteIndex];

        swap(*temp, *temp2);
        d = *theHeap[deleteIndex];

        theHeap.pop_back();

        lastNode--;
        reHeapifyDown();
    }
}


template<typename T>
int vectorHeap<T>::levels()
{
    if(lastNode == 0 || root == 0)
        return 0;

    return 1+(int)(log10(lastNode*1.)/log10(2.));
}

template<typename T>
void vectorHeap<T>::clear()
{
    nukem();
}

template<typename T>
bool vectorHeap<T>::full()
{
    return (capacity == 0) ? false
                           : capacity == lastNode;
}

template<typename T>
bool vectorHeap<T>::empty() const
{
    return root==0 || lastNode == 0;
}

template<typename T>
unsigned int vectorHeap<T>::size()
{
    return lastNode;
}

//----------------------------------------------------
template<typename T>
int vectorHeap<T>::Left(int index)
{
    return index*2;
}

template<typename T>
int vectorHeap<T>::Right(int index)
{
    return index*2+1;
}

template<typename T>
void vectorHeap<T>::copy(const vectorHeap<T> &other)
{
    node<T>* temp;

    if(other.empty())
        return;


    nukem();

    capacity = other.capacity;
    minMax = other.minMax;
    theHeap=vector< node<T>* >(capacity);


    for(int i = 0; i < other.lastNode; i++)
    {
        temp = other.theHeap[i];
        insert(temp->data, temp->LinePara);

    }

}

template<typename T>
void vectorHeap<T>::nukem()
{
    if(empty())
        return;

    while(lastNode != 1)
    {
        delete theHeap[lastNode-1];
        theHeap[lastNode-1] = NULL;
        theHeap.pop_back();
        lastNode--;
    }
    delete theHeap[root];
    theHeap[root] = NULL;

    root = 0;
    lastNode = 0;

}

template<typename T>
int vectorHeap<T>::findParent(int num)
{
    int parent = num/2;
    return parent;
}

//----------------------------------------------------------

template<typename T>
void vectorHeap<T>::  reHeapifyUp()
{
    unsigned int parent = lastNode >> 1,
                 child = lastNode;

    node<T> *p, *c;

    while(child != 1)
    {
        p=getNode(parent);
        c=getNode(child);

        if((this->*compare[minMax])(*c,*p))
        {
            swap(*p, *c);
        }
        else
            return;
        child = parent;
        parent >>= 1;
    }
}

template<typename T>
void vectorHeap<T>::reHeapifyDown()
{
    int ptr = root, candidate;
    bool onGoing = true;

    while(onGoing && Left(ptr) <= lastNode)
    {
        if(!(Right(ptr) <=lastNode))
            candidate = Left(ptr);
        else
        {
            node<T>* temp1;
            node<T>* temp2;

            temp1 = theHeap[Left(ptr)-1];
            temp2 = theHeap[Right(ptr)-1];


            candidate = ((*this).*compare[minMax])(*temp1, *temp2) ?
                        Left(ptr) : Right(ptr);

        }

        node<T>* temp3;
        node<T>* temp4;

        temp3 = theHeap[candidate-1];
        temp4 = theHeap[ptr-1];

        if( ((*this).*compare[minMax])(*temp3, *temp4))
        {
            node<T>* temp5;
            node<T>* temp6;

            temp5 = theHeap[ptr-1];
            temp6 = theHeap[candidate-1];

            swap(*temp5, *temp6);

        }
        else
            onGoing = false;
        ptr = candidate;
    }
}

template<typename T>
bool vectorHeap<T>::greater(node<T> &x, node<T> &y)
{
    return x > y;
}

template<typename T>
bool vectorHeap<T>::less(node<T> &x, node<T> &y)
{
    return x < y;
}

template<typename T>
node<T>* vectorHeap<T>::getNode(unsigned int nodeNum)
{
    node<T> *ptr;
    ptr = theHeap[nodeNum-1];

    return ptr;
}

template<typename T>
void vectorHeap<T>::swap(node<T> &x, node<T> &y)
{

    T temp = x.data;
    x.data = y.data;
    y.data = temp;

    string temp2 = x.LinePara;
    x.LinePara = y.LinePara;
    y.LinePara = temp2;
}

template<typename U>
ostream& operator<<(ostream& out, vectorHeap<U> &h)
{
    U data;
    while(!h.empty())
    {
        h>>data;
        out<<data<<" ";
    }
    return out;
}

template<typename U>
istream& operator>>(istream& in, vectorHeap<U> &h)
{
    U data;
    while(in>>data)
        h<<data;
    return in;
}

#endif // VECTORHeap_H
