#include "grid.h"
#include <iostream>
#include "creature.h"
#include "coord.h"
#include "Constant.h"
#include "hunter.h"
#include "prey.h"
#include "nukes.h"
#include "tanks.h"
#include "random.h"
#include <cmath>
using namespace std;

Grid::Grid()
{
    snap=new char*[MAXY];
    grid=new Creature**[MAXY];

    int y=0;
    int x=0;
    for(y=0;y<MAXY;y++)
    {
        snap[y]=new char [MAXX];
        grid[y]=new Creature*[MAXX];
        for(x=0;x<MAXY;x++)
        {
            grid[y][x]=NULL;
            snap[y][x]='.';
        }
    }
    Random R;

    for (int i=0;i<HUNTERN;i++)
    {
        AddHunter('X',R.RandomInt(MAXX),R.RandomInt(MAXY));
    }
    for (int i=0;i<PREYN;i++)
    {
        AddPrey('o',R.RandomInt(MAXX),R.RandomInt(MAXY));
    }
    for (int i=0;i<TANKN;i++)
    {
        AddTanks('T',R.RandomInt(MAXX),R.RandomInt(MAXY));
    }
    AddNukes(MAXX/2,MAXY/2);
}
void Grid::AddCreature(char ch, int c1, int c2)
{
    Coord c(c1,c2);
    grid[c2][c1]=new Creature(ch, c);
}
void Grid::AddHunter(char ch, int c1, int c2)
{
    Coord c(c1,c2);
    grid[c2][c1]=new Hunter(ch, c);
}
void Grid::AddPrey(char ch, int c1, int c2)
{
    grid[c2][c1]=NULL;
    Coord c(c1,c2);
    grid[c2][c1]=new Prey(ch, c);
}
void Grid::AddNukes(int c1, int c2)
{
    grid[c2][c1]=NULL;
    Coord c(c1,c2);
    grid[c2][c1]=new Nukes('B', c);
}
void Grid::AddTanks(char ch, int c1, int c2)
{
    grid[c2][c1]=NULL;
    Coord c(c1,c2);
    grid[c2][c1]=new Tanks(ch, c);
}

Grid::~Grid()
{
    int y=0;
    for(y=0;y<MAXY;y++)
    {
        delete grid[y];
        delete snap[y];
    }
    delete grid;
    delete snap;
}

void Grid::snapShot()
{
    int y=0;
    int x=0;


    for(y=0;y<MAXY;y++)
    {
        for(x=0;x<MAXX;x++)
        {
            snap[y][x]='.';
            if(grid[y][x]!=NULL)
                snap[y][x]=grid[y][x]->face;
        }
    }
}
char** Grid::GetSnap()
{
    return snap;
}
void Grid::Move()
{
    int y=0;
    int x=0;

    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==1)
            {
                grid[y][x]->Move(*this);

                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==2)
            {
                grid[y][x]->Move(*this);

                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
}
void Grid::Breed()
{
    int y=0;
    int x=0;

    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==1)
            {
                grid[y][x]->Breed(*this);
                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==2)
            {
               grid[y][x]->Breed(*this);
               x=MAXX+1;
               y=MAXY+1;
            }
        }
    }
}
void Grid::Die()
{
    int y=0;
    int x=0;

    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==1)
            {
                grid[y][x]->Die(*this);
                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
}
void Grid::Boom()
{
    int y=0;
    int x=0;

    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==3)
            {
                grid[y][x]->Boom(*this);
                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
}
void Grid::Armor()
{
    int y=0;
    int x=0;

    for (y=0;y<MAXY;y++)
    {
        for (x=0;x<MAXX;x++)
        {
            if(grid[y][x]!=NULL && grid[y][x]->ID==4)
            {
                grid[y][x]->Armor(*this);
                x=MAXX+1;
                y=MAXY+1;
            }
        }
    }
}
