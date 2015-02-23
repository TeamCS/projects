#include <iostream>
#include "grid.h"
#include "creature.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(NULL));
    Grid w;
    w.InitializeH();
    w.InitializeP();
    w.InitializeD();
    w.InitializeV();
    char ans;
    do
    {
        w.Display();
        w.Run();
        cin.get(ans);
    }while(ans == '\n');

}
