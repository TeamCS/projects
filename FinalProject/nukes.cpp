#include "nukes.h"
#include "creature.h"
#include "grid.h"
#include "coord.h"
#include "Constant.h"
#include "random.h"
#include <iostream>
#include <cmath>
using namespace std;

Nukes::Nukes()
{
}
Nukes::Nukes(char f,Coord p)
{
    steps=0;
    stepsHunger=0;
    stepsBreed=0;
    face=f;
    ID=3;
    position=p;
    moveFlag=false;
}
void Nukes::Boom(Grid& g)
{
    int y;
    int x;
    int preyCounter=0;
    Random r;

    for(y=0;y<MAXY;y++)
    {
        for(x=0;x<MAXX;x++)
        {
            if(g.grid[y][x]!=NULL && g.grid[y][x]->ID==2)
            {
                preyCounter++;
            }
        }
    }

    if(preyCounter>=(MAXX*MAXY/3))
    {
        for(y=MAXY/5;y<(MAXY/5*4);y++)
        {
            for(x=MAXX/5;x<(MAXX/5*4);x++)
            {
                if(g.grid[y][x]!=NULL && g.grid[y][x]->ID!=1 && g.grid[y][x]->ID!=3)
                {
                    g.grid[y][x]=NULL;
                    delete g.grid[y][x];
                }
            }
        }
    }
}
