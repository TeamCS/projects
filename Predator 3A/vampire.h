#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "creature.h"
#include <cstdlib>

class Vampire: public Creature
{
public:
    Vampire();
    char Face();
    void Move(int& x, int& y, Creature*** G);
    void Breed(int &x, int &y, Creature *** G);
    void Turn(int &x, int &y, Creature *** G);
    bool Dead();
    bool Finished();
private:
    bool impossible;
};

#endif // VAMPIRE_H
