#ifndef PREY_H
#define PREY_H
#include "creature.h"
class Prey:public Creature
{
public:
    Prey();
    Prey(char f,Coord p);
    void Move(Grid& g); //it choose a random direction to move in if that direct is available.
                        //Otherwise, it stays at its original position.
    void Breed(Grid& g); //after a certain time, if there's space available around the prey,
                         //it will reprodice at a random direction.
    void Increment(Grid& g, int i, int j);  //update the information of the prey, including the steps
                                            //and resetting move flag.
};

#endif // PREY_H
