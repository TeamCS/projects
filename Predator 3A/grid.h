#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <fstream>
#include "creature.h"
#include "dragon.h"
#include "vampire.h"
#include "human.h"
#include "prey.h"
#include <cstdlib>



using namespace std;

class Grid
{
//    friend class creature;
//    friend class Dragon;
//    friend class Vampire;
//    friend class human;
//    friend class prey;
public:
    Grid();
    ~Grid();
    void InitializeH();
    void InitializeP();
    void InitializeD();
    void InitializeV();
    void Display();
    void Set(int x, int y, Creature* SetThis);
    void Run();
    void Save();
    void Load();
    Creature* Getthis(int x, int y);
    void SunRise();

private:
    Creature*** grid;
};

#endif // GRID_H
