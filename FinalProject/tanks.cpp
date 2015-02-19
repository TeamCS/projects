#include "tanks.h"
#include "creature.h"
#include "grid.h"
#include "coord.h"
#include "Constant.h"
#include "random.h"
#include <iostream>
#include <cmath>
using namespace std;

Tanks::Tanks()
{
}
Tanks::Tanks(char f,Coord p)
{
    steps=0;
    stepsHunger=0;
    stepsBreed=0;
    face=f;
    ID=4;
    position=p;
    moveFlag=false;
}
void Tanks::Increment(Grid& g, int i, int j)
{
    g.grid[j][i]->steps++;
    g.grid[j][i]->stepsBreed++;
    g.grid[j][i]->stepsHunger++;
    g.grid[j][i]->moveFlag=true;
}
void Tanks::Armor(Grid& g)
{
    int y;
    int x;

    Random r; //0-left 1-up 2-right 3-down

    for(y=0;y<MAXY;y++)
    {
        for(x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->ID==4 && g.grid[y][x]->moveFlag==false)
            {
                if(CheckEat(g,x,y)==0)
                {
                    Increment(g, x, y);

                    g.grid[y][x-3]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==1)
                {
                    Increment(g, x, y);

                    g.grid[y-3][x]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==2)
                {
                    Increment(g, x, y);

                    g.grid[y][x+3]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==3)
                {
                    Increment(g, x, y);

                    g.grid[y+3][x]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==-1)
                {
                    int temp=r.RandomInt(MAXR);
                    if(temp==0 && x-3>=0 && g.grid[y][x-3]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y][x-3]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==1 && y-3>=0 && g.grid[y-3][x]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y-3][x]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==2 && x+3<=MAXX-3 && g.grid[y][x+3]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y][x+3]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==3 && y+3<=MAXY-3 && g.grid[y+3][x]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y+3][x]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                }
            }
        }
    }
    for(y=0;y<MAXY;y++)
    {
        for(x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->ID==4 && g.grid[y][x]->moveFlag==true)
            {
                g.grid[y][x]->moveFlag=false;
            }
        }
    }
}
int Tanks::CheckEat(Grid& g, int i, int j)
{
    if(i-3>=0 && g.grid[j][i-3]!=NULL && g.grid[j][i-3]->ID==1)
        return 0;
    else if(j-3>=0 && g.grid[j-3][i]!=NULL && g.grid[j-3][i]->ID==1)
        return 1;
    else if(i+3<=MAXX-3 && g.grid[j][i+3]!=NULL && g.grid[j][i+3]->ID==1)
        return 2;
    else if(j+3<=MAXY-3 && g.grid[j+3][i]!=NULL && g.grid[j+3][i]->ID==1)
        return 3;
    else
        return -1;
}
