#ifndef GRID_H
#define GRID_H

/*this class creates a board*/

class Creature;

class Grid
{
public:
    Grid(); //It initializes the board with some hunters, preys, tanks, and a nuke.
    ~Grid();
    void AddCreature(char ch, int c1, int c2); //add a creature to position (c1, c2)
    void AddHunter(char ch, int c1, int c2);  //add a hunter to position (c1, c2)
    void AddPrey(char ch, int c1, int c2);  //add a prey to position (c1, c2)
    void AddNukes(int c1, int c2);  //add a nuke to position (c1, c2)
    void AddTanks(char ch, int c1, int c2);  //add a tank to position (c1, c2)

    void snapShot(); //create a double pointer to take a snapshot of the content on grid.
    char** GetSnap();  //return snap.
    void Move();  //if there is creature (either hunter, prey, tank, or nuke) on the board,
                  //it will call the move function of the actual creature.
    void Breed(); //it controls the reproduction of hunter and prey.
    void Die();  //it controls the death of the hunters.
    void Boom(); //it trigers the nuke to explode.
    void Armor(); //it call the tank armor function,which behaves like a move function.

    friend class Creature;

    Creature*** grid;
    char** snap;

};

#endif
