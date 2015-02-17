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
