#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <cmath>
#include "node.h"

using namespace std;

enum ORDER {IN_ORDER, POST_ORDER, PRE_ORDER};

template<typename T>
class binaryTree
{
public:
    binaryTree();
    binaryTree(T d, int l, int p, int c = 1);
    ~binaryTree();
    binaryTree(const binaryTree<T> &other);
    binaryTree<T>& operator =(const binaryTree<T> &other);

    void insert(T d, string lp, int c = 1);
    bool remove(T d);
    int find(T d, int c = 0);
    ORDER getTraversal();
    void setTraversal(ORDER traversal);
    int depth(int c = 0);
    int totalNodes();
    int totalDataItems();
    int largestNode();
    void clear();
    bool empty();
    binaryTree<T>& operator<<(T d);
    int treeToArray(vector< node<T> > &list, int c = 0);//copies all nodes in order to list vector

    template<typename U>
    friend ostream& operator<<(ostream& out, binaryTree<U> &n);

    template<typename U>
    friend istream& operator>>(istream& in, binaryTree<U> &n);

private:
    vector< node<T>* > r;
    ORDER printOrder;
    void nukem();
    void copy(const binaryTree< node<T>* > &other);
    void display(ostream& out = cout, int c = 0);//c is node number. Can print subtree if c is specified
    int resizeTo();//find out what array size is required to hold 1 extra layer
    node<T>* copyNode(node<T>* other);//makes a pointer copy of a node
    int findParent(T d);
    int findLeftMost(int c = 0);//make sure parameter c exists
    int findRightMost(int c = 0);//make sure paramter c exists
    void moveSub(int oldRoot, int newRoot);//moveSubtree
    void promote(int c);//promotes whole subtree up
    void demote(int oldRoot, int newRoot);//same as moveSub but starts moving from bottom
    void rebalance();
    void rotateLeft(int c);
    void rotateRight(int c);
    int balanceFactor(int c);
    int left(int c);//find left child
    int right(int c);//find right child

};

template<typename T>
binaryTree<T>::binaryTree()
{
    printOrder = IN_ORDER;
    r.resize(3);
}

template<typename T>
binaryTree<T>::binaryTree(T d, int l, int p, int c)
{
    printOrder = IN_ORDER;
    r[0] = new node<T>(d,l,p,c);
    r.resize(3);
}

template<typename T>
binaryTree<T>::~binaryTree()
{
    nukem();
}

template<typename T>
binaryTree<T>::binaryTree(const binaryTree<T> &other)
{
    copy(other);
}

template<typename T>
binaryTree<T>& binaryTree<T>::operator=(const binaryTree<T> &other)
{
    if(this != other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void binaryTree<T>::insert(T d, string lp, int c)
{
    int currentSize = resizeTo();//current array size
    int i = 0;
    while(r[i])//check if node exists
    {
        if(r[i]->data == d)//node already exist
        {
            r[i]->count++;//increment
            r[i]->LinePara.append(lp);//append the new data for line and paragraph
            //r[i]->LinePara.append(":");
            return;//exit the insert function
        }
        else if(d < r[i]->data)//if d < node
            i = left(i);//move to next left
        else
            i = right(i);
    }//loop exits when next left or right doesn't exist or found a node
    r[i] = new node<T>(d,lp,c);//make a new node at empty location
    int newSize = resizeTo();//find new  required array size
    if(abs(newSize - currentSize))//check if depth changes
    {                           //so there won't be needless resizing
        //cout<<"resizing to:"<<resizeTo()<<endl;
        r.resize(resizeTo());
        rebalance();//rebalances tree
    }
}

template<typename T>
bool binaryTree<T>::remove(T d)
{
    int pos = find(d);//finds the node to be removed
    if(pos != -1)//if node is found
    {
        int currentSize = resizeTo();//find current array size
        r[pos]->count--;//decrements node
        if(r[pos]->count == 0 )//check if the node has a count still
        {
            delete r[pos];
            if(r[left(pos)])//check if left subtree is there
            {
                int toPromote = findRightMost(left(pos));//find greatest node in left subtree
                r[pos] = r[toPromote];//move the node to be promoted
                r[toPromote] = NULL;//set it to NULL just incase it stays vacant
                if(left(toPromote))//check if left subtree exists
                    promote(left(toPromote));//promote left subtree
            }
            else
            {
                int toPromote = findLeftMost(right(pos));//find greatest node in right subtree
                r[pos] = r[toPromote];//move the node to be promoted
                r[toPromote] = NULL;//set to null just incase it stays vacant
                if(right(toPromote))//check if right subtree exists
                    promote(right(toPromote));//promot right subtree
            }
        }
        int newSize = resizeTo();//new required array size
        if(abs(newSize - currentSize))//check if there is a difference
        {
            //cout<<"resizing to:"<<resizeTo()<<endl;
            r.resize(resizeTo());
            rebalance();
        }
        return 1;
    }
    else
        return 0;//return 0 so it knows to throw an error message
}

template<typename T>
int binaryTree<T>:: find(T d, int c)
{
    int i = c;
    while(r[i])//check it exists
    {
        if(r[i]->data == d)//found node
            return i;
        else if(d < r[i]->data)
            i = left(i);//if less than current node find left child
        else
            i = right(i);//if greater than current find right child
    }
    return -1;//if loop ends without returning i return -1 to show node was not found
}

template<typename T>
ORDER binaryTree<T>::getTraversal()
{
    return printOrder;
}

template<typename T>
void binaryTree<T>::setTraversal(ORDER traversal)
{
    printOrder = traversal;
}

template<typename T>
int binaryTree<T>::depth(int c)
{
    if(c != 0)
        return r[c] ? 1 + max(depth(left(c)),depth(right(c))) : 0;//find depth of subtree
    else
        return ((int)(log2((double)(largestNode())))+1);//find depth of whole tree
}

template<typename T>
int binaryTree<T>::totalNodes()
{
    int c = 0;
    for(int i = 0, size = r.size(); i < size; i++)
    {
        if(r[i])
            c++;
    }
    return c;
}

template<typename T>
int binaryTree<T>::totalDataItems()
{
    int dataItems = 0;
    for(int i = 0, size = r.size(); i < size; i++)
        if(r[i])
            dataItems += r[i]->count;
    return dataItems;
}

template<typename T>
int binaryTree<T>::largestNode()
{
    for(int i = r.size() - 1; i >= 0; i--)//size - 1 since largest size isnt a location in array
        if(r[i])
            return i+1;//so when 0 is largest it won't mess it up
}

template<typename T>
void binaryTree<T>::clear()
{
    nukem();
}

template<typename T>
bool binaryTree<T>::empty()
{
    return r[0];
}

template<typename T>
binaryTree<T>& binaryTree<T>::operator<<(T d)
{
    insert(d);
    return *this;
}

template<typename T>
int binaryTree<T>::treeToArray(vector<node<T> > &list, int c)
{
    int buffer= totalNodes();

    if(!r[c])
        return 0;
    if(r[left(c)])
        treeToArray(list, left(c));
    if(printOrder == IN_ORDER && r[c])
    {
        list.push_back(*r[c]);//push each node into array from least to greatest
    }
    if(r[right(c)])
        treeToArray(list, right(c));

    return buffer;
}

template<typename T>
void binaryTree<T>::nukem()
{
    for(int i = 0, size = r.size(); i < size; i++)
        if(r[i])
        {
            delete r[i];
            r[i] = NULL;
        }
    r.resize(1);
}

template<typename T>
void binaryTree<T>::copy(const binaryTree< node<T>* > &other)
{
    r.resize(other.size());
    for(int i = 0, size = r.size(); i < size; i++)
        if(other[i])
            r[i] = copyNode(other[i]);
}

template<typename T>
void binaryTree<T>::display(ostream& out, int c)
{
    if(!r[c])
        return;
    if(printOrder == PRE_ORDER && r[c])
        out<<*r[c];
    if(r[left(c)])
        display(out, left(c));
    if(printOrder == IN_ORDER && r[c])
        out<<*r[c];
    if(r[right(c)])
        display(out, right(c));
    if(printOrder == POST_ORDER && r[c])
        out<<*r[c];
}

template<typename T>
node<T>* binaryTree<T>::copyNode(node<T> *other)
{
    node<T>* temp = new node<T>(other->data, other->count);
    return temp;
}

template<typename T>
int binaryTree<T>::resizeTo()
{
    return (1<<(depth()+1))-1;
}

template<typename T>
int binaryTree<T>::findParent(T d)
{
    int child = find(d);
    if(child != -1)
        return (child-1)/2;
    else
        return child;//returns -1 if parent not found
}

template<typename T>
int binaryTree<T>::findLeftMost(int c)
{
    for(int i = c, size = r.size(); i < size; i = left(i))
        if(!r[left(i)])
            return i;
    return c;
}

template<typename T>
int binaryTree<T>::findRightMost(int c)
{
    for(int i = c, size = r.size(); i < size; i = right(i))
        if(!r[right(i)])
            return i;
    return c;
}

//for the for loop the statement is checks is that the node being moved is always less than the largest node()
template<typename T>
void binaryTree<T>::moveSub(int oldRoot, int newRoot)
{
    for(int i = 0, largest = largestNode(); (1<<((int)(log2((double)(i+1))))) * oldRoot + i < largest; i++)
    {
        //cout<<"movingSUB:"<<(1<<((int)(log2((double)(i+1))))) * oldRoot + i<<" to:"<<(1<<((int)(log2((double)(i+1))))) * newRoot + i<<endl;
        r[(1<<((int)(log2((double)(i+1))))) * newRoot + i] =
                r[(1<<((int)(log2((double)(i+1))))) * oldRoot + i];
        r[(1<<((int)(log2((double)(i+1))))) * oldRoot + i] = NULL;
    }
}

template<typename T>
void binaryTree<T>::promote(int c)
{
    moveSub(c,(c-1)/2);
}

template<typename T>
void binaryTree<T>::demote(int oldRoot, int newRoot)
{//starts from bottom of subtree instead of root so it does not overwrite
    for(int i = (1<<depth(oldRoot))-1; i >= 0; i--)
    {
        r[(1<<((int)(log2((double)(i+1))))) * newRoot + i] =
                r[(1<<((int)(log2((double)(i+1))))) * oldRoot + i];
        r[(1<<((int)(log2((double)(i+1))))) * oldRoot + i] = NULL;
    }
}

template<typename T>
void binaryTree<T>::rebalance()
{
    for(int i = 0, largest = largestNode(); i < largest; i++)
    {
        if(r[i])
        {
            if(balanceFactor(i) > 1)//needs to be rotated right
            {
                if(balanceFactor(left(i)) < 1)//check left right case
                    rotateLeft(left(i));
                rotateRight(i);//left left case
            }
            else if(balanceFactor(i) < -1)//needs to be rotated left
            {
                if(balanceFactor(right(i)) > 1)//check if right left case
                    rotateRight(right(i));
                rotateLeft(i);//right right case
            }
        }
    }
    r.resize(resizeTo());//resize after rebalancing just incase we can get rid of a layer
    //cout<<"CURRENT SIZE:"<<r.size()<<endl;
}

template<typename T>
void binaryTree<T>::rotateLeft(int c)
{
    if(r[left(c)])
        demote(left(c), left(left(c)));//demote left side
    r[left(c)] = r[c];//demote root to left
    r[c] = NULL;

    if(r[left(right(c))])
        moveSub(left(right(c)),right(left(c)));//move subtree
    r[c] = r[right(c)];//promote right child to new root
    r[right(c)] = NULL;
    promote(right(right(c)));//prmote whole right side up
}

template<typename T>
void binaryTree<T>::rotateRight(int c)
{//same as rotateLeft but all opposite
    if(r[right(c)])
        demote(right(c), right(right(c)));
    r[right(c)] = r[c];
    r[c] = NULL;
    if(r[right(left(c))])
        moveSub(right(left(c)),left(right(c)));
    r[c] = r[left(c)];
    r[left(c)] = NULL;
    promote(left(left(c)));
}

template<typename T>
int binaryTree<T>::balanceFactor(int c)
{
    //cout<<depth(left(c)) - depth(right(c))<<endl;
    return depth(left(c)) - depth(right(c));
}

template<typename T>
int binaryTree<T>::left(int c)
{
    return (2*c+1);
}

template<typename T>
int binaryTree<T>::right(int c)
{
    return (2*c+2);
}

template<typename U>
ostream& operator<<(ostream& out, binaryTree<U> &n)
{
    if(out != cout)
        out<<"Print order was: "<<n.printOrder<<endl;
    n.display(out);
    //cout<<"Current Depth: "<<n.depth()<<endl;
    return out;
}

template<typename U>
istream& operator>>(istream& in, binaryTree<U> &n)
{
    U data;
    int counts, printOrder;
    char junk;
    string line;
    stringstream ss;
    ORDER order[3] = {IN_ORDER, PRE_ORDER, POST_ORDER};
    if(in != cin)
    {
        getline(in, line);
        ss<<line.substr(line.find(':')+1);
        ss>>printOrder;
        n.printOrder = order[printOrder];
    }
    while(in>>data>>junk>>counts>>junk)
        n.insert(data,counts);  //might be a problem
    return in;
}

#endif // BINARYTREE_H
