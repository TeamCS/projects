/*this class display the board onto screen*/

#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{
public:
    Display();
    void Show();//print the snapshot
    void Print(char** b); //call the Show() to print the board on screen

    char** board;
};

#endif // DISPLAY_H
