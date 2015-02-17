#ifndef TANKS_H
#define TANKS_H
#include "creature.h"
class Tanks:public Creature
{
public:
    Tanks();
    Tanks(char f,Coord p);
    void Armor(Grid& g);  //if 3 steps away, there is a hunter, this tank will move to that postion and kill the hunter.
                          //Otherwise, it choose a random direction and move 3 steps. If that direction is not available,
                          //it stays at its original position.
    void Increment(Grid& g, int i, int j); //update the information of the tank, including the steps
                                           //and resetting move flag.
    int CheckEat(Grid& g, int i, int j);   //it checks if any direction around the tank has hunters.
};

#endif // TANKS_H
