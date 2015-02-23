#ifndef CREATURE_H
#define CREATURE_H

const int size = 20;

class Creature
{
public:
    Creature();
    virtual char Face() = 0;
    virtual void Move(int& x, int& y, Creature*** G) = 0;
    virtual void Breed(int& x, int& y, Creature*** G) = 0;
    virtual bool Dead() = 0;
    virtual bool Finished() = 0;
    bool Finish;
    int round;
};

#endif // CREATURE_H
