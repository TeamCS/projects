#include "vampire.h"
#include <iostream>
#include <vector>

using namespace std;

Vampire::Vampire()
{
    Finish = false;
}

char Vampire::Face()
{
    return 'V';
}

void Vampire::Move(int& x, int& y, Creature*** G)
{
    vector<int> d;
    if(y > 0 && G[x][y-1] == NULL)
        d.push_back(1);
    if(x < size-1 && G[x+1][y] == NULL)
        d.push_back(2);
    if(y < size-1 && G[x][y+1] == NULL)
        d.push_back(3);
    if(x > 0 && G[x-1][y] == NULL)
        d.push_back(4);
    int l = d.size();
    if(l != 0)
    {
        int dr = rand()%l;
        if(d[dr] == 1)
        {
            Finish = true;
            G[x][y-1] = G[x][y];
            G[x][y] = NULL;
        }
        else if(d[dr] == 2)
        {
            Finish = true;
            G[x+1][y] = G[x][y];
            G[x][y] = NULL;
        }
        else if(d[dr] == 3)
        {
            Finish = true;
            G[x][y+1] = G[x][y];
            G[x][y] = NULL;
        }
        else if(d[dr] == 4)
        {
            Finish = true;
            G[x-1][y] = G[x][y];
            G[x][y] = NULL;
        }
    }
}

void Vampire::Breed(int &x, int &y, Creature *** G)
{
    Turn(x,y,G);
}

void Vampire::Turn(int &x, int &y, Creature *** G)
{
    vector<int> t;
    if(y > 0 && G[x][y-1] != NULL && G[x][y-1]->Face()=='H')
    {
        t.push_back(1);
    }
    if(x < size-1 && G[x+1][y] != NULL && G[x+1][y]->Face()=='H')
    {
        t.push_back(2);
    }
    if(y < size-1 && G[x][y+1] != NULL && G[x][y+1]->Face()=='H')
    {
        t.push_back(3);
    }
    if(x > 0 && G[x-1][y] != NULL && G[x-1][y]->Face()=='H')
    {
        t.push_back(4);
    }
    int l = t.size();
    if(l != 0)
    {
        int dr = rand()%l;
        if(t[dr] == 1)
        {
            delete G[x][y-1];
            G[x][y-1] = NULL;
            G[x][y-1] = new Vampire;
        }
        else if(t[dr] == 2)
        {
            delete G[x][y-1];
            G[x][y-1] = NULL;
            G[x+1][y] = new Vampire;
        }
        else if(t[dr] == 3)
        {
            delete G[x][y-1];
            G[x][y-1] = NULL;
            G[x][y+1] = new Vampire;
        }
        else if(t[dr] == 4)
        {
            delete G[x][y-1];
            G[x][y-1] = NULL;
            G[x-1][y] = new Vampire;
        }
    }
}

bool Vampire::Dead()
{
    return false;
}

bool Vampire::Finished()
{
    if(Finish == true)
        return true;
    return false;
}
