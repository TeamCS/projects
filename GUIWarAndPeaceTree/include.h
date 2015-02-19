#ifndef INCLUDE_H
#define INCLUDE_H
#include <string>

using namespace std;

enum DIRECTION {LEFT, RIGHT};
enum TYPE {LESS, GREATER};
enum ERRORS {EMPTY, FULL};

int AbbrevArraySize = 839;    //size of the abbreviation database array
int ContracArraySize = 70;    //size of the contraction database array

char filename2[] = "Saved Data.txt";       //file name for the text file that will save all the information from analyzing text
char filename3[] = "abbrev.txt";           //abbreviation database1
char filename4[] = "abbreviations.txt";    //abbreviation database2 that pairs up with database1

#endif // INCLUDE_H


//===========================================================
/*
#ifndef INCLUDE_H
#define INCLUDE_H
#include <string>
#include <fstream>

using namespace std;


enum DIRECTION {LEFT, RIGHT};
enum TYPE {LESS, GREATER};
enum ERRORS {EMPTY, FULL};

int AbbrevArraySize = 839;
int ContracArraySize = 70;

char filename[] = "WarAndPeaceText.txt";
// war and peace.txt   The Three Musketeers.txt  TwoCities.txt
//WarAndPeaceText.txt   Les Miserables.txt
//    18.614                6.691                 4.103
//    18.78                19.9


char filename2[] = "Saved Data.txt";
char filename3[] = "abbrev.txt";
char filename4[] = "abbreviations.txt";

#endif // INCLUDE_H
*/
