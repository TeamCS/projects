#include "random.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Random::Random()
{
}

int Random::RandomInt(int maximum)
{
    int r;
    r=0+(rand()%maximum);
    return r;
}
