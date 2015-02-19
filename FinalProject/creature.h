#ifndef CREATURE_H
#define CREATURE_H
#include "coord.h"
#include "grid.h"
#include <iostream>
using namespace std;

class Grid;

/*this class creates a creature*/

class Creature
{
public:
    Creature();
    Creature(char f, Coord pos);

    virtual void Move(Grid& g)
    {
        cout << endl << "virtual move works" << endl;
        if(g.grid[0][0]==NULL)
            cout << "test";
    }
    virtual void Breed(Grid& g)
    {
        cout << endl << "virtual breed works" << endl;
        if(g.grid[0][0]==NULL)
            cout << "test";
    }
    virtual void Die(Grid& g)
    {
        cout << endl << "virtual die works" << endl;
        if(g.grid[0][0]==NULL)
            cout << "test";
    }
    virtual void Boom(Grid& g)
    {
        cout << endl << "virtual nukes works" << endl;
        if(g.grid[0][0]==NULL)
            cout << "test";
    }
    virtual void Armor(Grid& g)
    {
        cout << endl << "virtual armor works" << endl;
        if(g.grid[0][0]==NULL)
            cout << "test";
    }

    int steps;
    int stepsHunger;
    int stepsBreed;
    char face;
    Coord position;
    int ID;
    bool moveFlag;


    friend class Grid;
};

#endif // CREATURE_H
