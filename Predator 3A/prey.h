#ifndef PREY_H
#define PREY_H
#include "creature.h"
#include <cstdlib>

class Prey: public Creature
{
public:
    Prey();
    char Face();
    void Move(int& x, int& y, Creature*** G);
    void Breed(int& x, int& y, Creature*** G);
    bool Dead();
    bool OutRange(int a, int b, int c);
    bool Finished();
};

#endif // PREY_H
