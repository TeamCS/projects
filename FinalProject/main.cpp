//CS3A
//Title: Final Project - Hunter Prey Tank Nuke
//Author: Xizhao Deng
/*Introduction:
 Hunters(US marines) and preys(Japanese troops) behave exactly like what the book says. The nuke trigers if half
 of the board is filled with preys. The nukes(naval bombs) is targeting at the middle of the board, once it explodes,
 a huge amount of preys around the nuke will be killed. Then, a new nuke will be placed on the board.
 The tanks move 3 steps every round and are always looking for the direction that has hunters.
 If there are hunters standing on the direction tanks are moving to,
 these hunter get killed. Also, tanks can only be destroyed by nukes.
*/

#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
#include "graph.h"
using namespace std;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    Graph Board;
    Board.show();

//--------------------------------------------------------------------------------------------
    cout << endl << "                        Bloody Ridge, Guadalcanal" << endl
         << "                           September 20th, 1942" << endl
         << "        US Marines has been defending this high land for 2 weeks," << endl
         << "           but it seems that the Japanese 35th Infantry Brigade " << endl
         << "                 never give up the effort to take it back." << endl
         << "           Now the Japanese are preparing a huge attack..." << endl << endl
         << "             [ Mission briefing ]: This is a strategic area." << endl
         << "    Intel shows that about 2000 to 3000 Japanese troops landed last night."
         << "         Our scout also reported the existence of at least 20 enemy light tanks."
         << "           Colonel, command your infantry troops to hold their position!" << endl
         << "           If half of the surface defending positions are lost." << endl
         << "                    The naval will cannonade your area." << endl << endl
         << "    ------------------------------------------------------------------------" << endl
         << " Battle Rule:  US marines kill Japanese troops." << endl
         << "               Japanese tanks kill US marines" << endl
         << "               Naval bombing kills Japaneses infantrys as well as their tanks" << endl
         << "               But keep this in mind: the bombs don't have eyes" << endl << endl;
//--------------------------------------------------------------------------------------------
    cout << endl << "            ==========================END=========================" << endl;

    return app.exec();
}
