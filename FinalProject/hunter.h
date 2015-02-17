#ifndef HUNTER_H
#define HUNTER_H
#include "creature.h"
class Hunter:public Creature
{
public:
    Hunter();
    Hunter(char f,Coord p);
    void Move(Grid& g); //it moves the hunter towards the direction of prey, then eat the prey
                        //if there's no prey around the hunter, it will just choose a random direction to move in.
                        //if no direction is available, it stays at its original position.
    void Breed(Grid& g);//after a certain time, if there's space available around the hunter,
                        //it will reprodice at a random direction.
    void Die(Grid& g); //after a certain time, if the hunter can't find a prey to eat, it dies.
    void Increment(Grid& g, int i, int j); //this update the step records of a hunter, and it also reset the move flag.
    int CheckEat(Grid& g, int i, int j); //it checks if any direction around the hunter has preys.
};

#endif // HUNTER_H
