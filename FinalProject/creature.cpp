#include "creature.h"
#include "grid.h"
#include "coord.h"
#include "Constant.h"
#include <iostream>
using namespace std;



Creature::Creature():steps(0),stepsHunger(0),stepsBreed(0),face('.'),position(0,0),ID(0),moveFlag(false)
{
}
Creature::Creature(char f,Coord p):steps(0),stepsHunger(0),stepsBreed(0),face(f),position(p),ID(0),moveFlag(false)
{
}
