#include "prey.h"
#include <iostream>
#include <vector>

using namespace std;

Prey::Prey()
{
    Finish = false;
    round = 0;
}

char Prey::Face()
{
    return 'P';
}

void Prey::Move(int& x, int& y, Creature*** G)
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
        round++;
    }
}

void Prey::Breed(int& x, int& y, Creature*** G)
{
    if(round == 6)
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
                G[x][y-1] = new Prey;
            }
            else if(d[dr] == 2)
            {
                G[x+1][y] = new Prey;
            }
            else if(d[dr] == 3)
            {
                G[x][y+1] = new Prey;
            }
            else if(d[dr] == 4)
            {
                G[x-1][y] = new Prey;
            }
            round = 0;
        }
    }
    else if(round > 6)
    {
        round = 0;
    }
}

bool Prey::Dead()
{
    return false;
}

bool Prey::Finished()
{
    if(Finish == true)
        return true;
    return false;
}
