#ifndef DRAGON_H
#define DRAGON_H
#include "creature.h"
#include <cstdlib>

class Dragon: public Creature
{
public:
    Dragon();
    char Face();
    void Move(int& x, int& y, Creature*** G);
    void Fire(int& x, int& y, Creature*** G);
    void Breed(int &x, int &y, Creature *** G);
    bool Dead();
    bool Finished();
};

#endif // DRAGON_H
