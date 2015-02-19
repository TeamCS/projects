#include "human.h"
#include <iostream>
#include <vector>

using namespace std;

Human::Human()
{
    Finish = false;
    round = 0;
    hunger = 0;
}

char Human::Face()
{
    return 'H';
}

void Human::Move(int& x, int& y, Creature*** G)
{
    if(Dead())
    {
        delete G[x][y];
        G[x][y] = NULL;
    }
    else
    {
        vector<int> pd;
        vector<int> d;
        if(y > 0)
        {
            if(G[x][y-1] == NULL)
                d.push_back(1);
            else if(G[x][y-1] != NULL && G[x][y-1]->Face()=='P')
                pd.push_back(1);
        }
        if(x < size-1)
        {
            if(G[x+1][y] == NULL)
                d.push_back(2);
            else if(G[x+1][y] != NULL && G[x+1][y]->Face()=='P')
                pd.push_back(2);
        }
        if(y < size-1)
        {
            if(G[x][y+1] == NULL)
                d.push_back(3);
            else if(G[x][y+1] != NULL && G[x][y+1]->Face()=='P')
                pd.push_back(3);
        }
        if(x > 0)
        {
            if(G[x-1][y] == NULL)
                d.push_back(4);
            else if(G[x-1][y] != NULL && G[x-1][y]->Face()=='P')
                pd.push_back(4);
        }
        int pdl = pd.size();
        int dl = d.size();
        if(pdl!= 0)
        {
            int pdr = rand()%pdl;
            if(pd[pdr] == 1)
            {
                Finish = true;
                G[x][y-1] = G[x][y];
                G[x][y] = NULL;

            }
            else if(pd[pdr] == 2)
            {
                Finish = true;
                G[x+1][y] = G[x][y];
                G[x][y] = NULL;
            }
            else if(pd[pdr] == 3)
            {
                Finish = true;
                G[x][y+1] = G[x][y];
                G[x][y] = NULL;
            }
            else if(pd[pdr] == 4)
            {
                Finish = true;
                G[x-1][y] = G[x][y];
                G[x][y] = NULL;
            }
            round++;
            hunger = 0;
        }
        else if(pdl==0 && dl!= 0)
        {
            int dr = rand()%dl;
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
            hunger++;
        }
        else
            hunger++;
    }
}

void Human::Breed(int& x, int& y, Creature*** G)
{
    if(round == 8)
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
                G[x][y-1] = new Human;

            }
            else if(d[dr] == 2)
            {
                G[x+1][y] = new Human;
            }
            else if(d[dr] == 3)
            {
                G[x][y+1] = new Human;
            }
            else if(d[dr] == 4)
            {
                G[x-1][y] = new Human;
            }
            round = 0;
        }
    }
    else if(round > 8)
    {
        round = 0;
    }
}

bool Human::Dead()
{
    if(hunger == 3)
        return true;
    return false;
}


bool Human::Finished()
{
    if(Finish == true)
        return true;
    return false;
}
