#ifndef NUKES_H
#define NUKES_H
#include "creature.h"

class Nukes:public Creature
{
public:
    Nukes();
    Nukes(char f,Coord p);
    void Boom(Grid& g); //if half of the board is occupied by the preys, the nuke explodes and kill all
                        //the tanks and preys within a certain area around this nuke.
};

#endif // NUKES_H
