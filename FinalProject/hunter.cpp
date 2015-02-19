#include "hunter.h"
#include "creature.h"
#include "grid.h"
#include "coord.h"
#include "Constant.h"
#include "random.h"
#include <iostream>
#include <cmath>
using namespace std;

Hunter::Hunter()
{
}
Hunter::Hunter(char f,Coord p)
{
    steps=0;
    stepsHunger=0;
    stepsBreed=0;
    face=f;
    position=p;
    ID=1;
    moveFlag=false;
}
void Hunter::Move(Grid& g)
{
    int y;
    int x;

    Random r; //0-left 1-up 2-right 3-down

    for(y=0;y<MAXY;y++)
    {
        for(x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->ID==1 && g.grid[y][x]->moveFlag==false)
            {
                if(CheckEat(g,x,y)==0)
                {
                    Increment(g, x, y);

                    g.grid[y][x]->stepsHunger=0;
                    g.grid[y][x-1]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==1)
                {
                    Increment(g, x, y);

                    g.grid[y][x]->stepsHunger=0;
                    g.grid[y-1][x]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==2)
                {
                    Increment(g, x, y);

                    g.grid[y][x]->stepsHunger=0;
                    g.grid[y][x+1]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==3)
                {
                    Increment(g, x, y);

                    g.grid[y][x]->stepsHunger=0;
                    g.grid[y+1][x]=g.grid[y][x];
                    g.grid[y][x]=NULL;
                }
                else if(CheckEat(g,x,y)==-1)
                {
                    int temp=r.RandomInt(MAXR);
                    if(temp==0 && x-1>=0 && g.grid[y][x-1]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y][x-1]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==1 && y-1>=0 && g.grid[y-1][x]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y-1][x]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==2 && x+1<=MAXX-1 && g.grid[y][x+1]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y][x+1]=g.grid[y][x];
                        g.grid[y][x]=NULL;
                    }
                    else if(temp==3 && y+1<=MAXY-1 && g.grid[y+1][x]==NULL)
                    {
                        Increment(g, x, y);

                        g.grid[y+1][x]=g.grid[y][x];
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
            if(g.grid[y][x]!=NULL && g.grid[y][x]->ID==1 && g.grid[y][x]->moveFlag==true)
            {
                g.grid[y][x]->moveFlag=false;
            }
        }
    }
}
//=====================================================================
void Hunter::Breed(Grid& g)
{
    int y;
    int x;


    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->stepsBreed!=0
               && g.grid[y][x]->stepsBreed%HUNTERB==0 && g.grid[y][x]->ID==1)
            {
                if(x-1>=0 && g.grid[y][x-1]==NULL)
                {
                    Coord c(y,x-1);
                    delete g.grid[y][x-1];
                    g.grid[y][x-1]=new Hunter(g.grid[y][x]->face, c);
                }
                else if(y-1>=0 && g.grid[y-1][x]==NULL)
                {
                    Coord c(y-1,x);
                    delete g.grid[y-1][x];
                    g.grid[y-1][x]=new Hunter(g.grid[y][x]->face, c);
                }
                else if(x+1<=MAXX-1 && g.grid[y][x+1]==NULL)
                {
                    Coord c(y,x+1);
                    delete g.grid[y][x+1];
                    g.grid[y][x+1]=new Hunter(g.grid[y][x]->face, c);
                }
                else if(y+1<=MAXY-1 && g.grid[y+1][x]==NULL)
                {
                    Coord c(y+1,x);
                    delete g.grid[y+1][x];
                    g.grid[y+1][x]=new Hunter(g.grid[y][x]->face, c);
                }
            }
        }
    }
}
void Hunter::Die(Grid& g)
{
    int y;
    int x;


    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->stepsHunger!=0
               && g.grid[y][x]->stepsBreed%HUNTERD==0 && g.grid[y][x]->ID==1)
            {
                g.grid[y][x]=NULL;
                delete g.grid[y][x];
            }
        }
    }
}
void Hunter::Increment(Grid& g, int i, int j)
{
    g.grid[j][i]->steps++;
    g.grid[j][i]->stepsBreed++;
    g.grid[j][i]->stepsHunger++;
    g.grid[j][i]->moveFlag=true;
}

int Hunter::CheckEat(Grid& g, int i, int j)
{
    if(i-1>=0 && g.grid[j][i-1]!=NULL && g.grid[j][i-1]->ID==2)
        return 0;
    else if(j-1>=0 && g.grid[j-1][i]!=NULL && g.grid[j-1][i]->ID==2)
        return 1;
    else if(i+1<=MAXX-1 && g.grid[j][i+1]!=NULL && g.grid[j][i+1]->ID==2)
        return 2;
    else if(j+1<=MAXY-1 && g.grid[j+1][i]!=NULL && g.grid[j+1][i]->ID==2)
        return 3;
    else
        return -1;
}
