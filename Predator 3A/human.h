#ifndef HUMAN_H
#define HUMAN_H
#include "creature.h"
#include <cstdlib>

class Human: public Creature
{
public:
    Human();
    char Face();
    void Move(int& x, int& y, Creature *** G);
    void Breed(int &x, int &y, Creature *** G);
    bool Dead();
    bool OutRange(int a, int b, int c);
    bool Finished();
private:
    int hunger;
    char face;
};

#endif // HUMAN_H
