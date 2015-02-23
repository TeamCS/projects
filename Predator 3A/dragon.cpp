#include "dragon.h"
#include <iostream>
#include <vector>

using namespace std;

Dragon::Dragon()
{
    Finish = false;
}

char Dragon::Face()
{
    return 'D';
}

void Dragon::Move(int& x, int& y, Creature*** G)
{
    vector<int> d;
    if(y > 0 && x > 0)
     d.push_back(1);
    if(y > 0)
     d.push_back(2);
    if(y > 0 && x < size-1)
     d.push_back(3);
    if(x < size-1)
     d.push_back(4);
    if(x< size-1 && y< size-1)
     d.push_back(5);
    if(y< size-1)
     d.push_back(6);
    if(x > 0 && y < size-1)
     d.push_back(7);
    if(x > 0)
     d.push_back(8);
    int l = d.size();
    int dr = d[rand()%l];
    if(l != 0)
    {
        switch (dr)
        {
        case 1:
        G[x-1][y-1] = G[x][y];
        G[x][y] = NULL;
        break;
        case 2:
        G[x][y-1] = G[x][y];
        G[x][y] = NULL;
        break;
        case 3:
         G[x+1][y-1] = G[x][y];
         G[x][y] = NULL;
         break;
        case 4:
         G[x+1][y] = G[x][y];
         G[x][y] = NULL;
         break;
        case 5:
         G[x+1][y+1] = G[x][y];
         G[x][y] = NULL;
         break;
        case 6:
         G[x][y+1] = G[x][y];
         G[x][y] = NULL;
         break;
        case 7:
         G[x-1][y+1] = G[x][y];
         G[x][y] = NULL;
         break;
        case 8:
         G[x-1][y] = G[x][y];
         G[x][y] = NULL;
         break;
        }
    }
    Finish = true;
}

void Dragon::Fire(int& x, int& y, Creature*** G)
{
    int minX = x-3;
    int maxX = x+3;
    if(minX < 0)
        minX = 0;
    if(maxX > size-1)
        maxX = size-1;
    int minY = y-3;
    int maxY = y+3;
    if(minY < 0)
        minY = 0;
    if(maxY > size-1)
        maxY = size-1;
//    cout << x << "   " << y << endl;
//    cout << minX << "  " << maxX << endl;
//    cout << minY << "  " << maxY << endl;
    for(int i = minX; i < maxX+1; i++)
    {
        for(int j = minY; j < maxY+1; j++)
        {
            if(i != x && j != y)
            {
                delete G[i][j];
                G[i][j] = NULL;
            }
        }
    }
}

void Dragon::Breed(int &x, int &y, Creature *** G)
{
    Fire(x,y,G);
}

bool Dragon::Dead()
{
    return false;
}

bool Dragon::Finished()
{
    if(Finish == true)
        return true;
    return false;
}
