#include "display.h"
#include <iostream>
#include "Constant.h"
using namespace std;

Display::Display()
{
    board=NULL;
}
void Display::Show()
{
    int y=0;
    int x=0;

    for(y=0;y<MAXY;y++)
    {
        cout << "                ";
        for(x=0;x<MAXX;x++)
        {
            cout << board[y][x] << " ";
        }
        cout << endl;
    }
    cout << endl << endl << "            ===================================================" << endl << endl;
}
void Display::Print(char** b)
{
    board=b;
    Show();
}
