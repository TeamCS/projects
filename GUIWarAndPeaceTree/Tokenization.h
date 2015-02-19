#ifndef TOKENIZATION_H
#define TOKENIZATION_H
#include <sstream>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "binaryTree.h"
#include "include.h"

using namespace std;

class Tokenization
{
public:
//------------------------------------------------
    binaryTree<string> WordTree[26]; //it will pop words out in a sorted manner

    vector< node<string> > WordList; //alphabetical list of all the words
    vector<int> WordCount;//vector whose index corresponds with WordList. Holds all the counts
    string* Most10WordList;//list with the 10 most frequent words

    int netparaNum;//total paragraphs
    int netlineNum;//total lines
    int netsentNum;//total setences
    int networdNum;//total words
    int networdLength;//total word length to be used in reading level calculation
    int netnonrepeatwordCount; //total unique words
    clock_t t;//used to time

    string* Abbrev;//array of abbrevations
    string* Abbreviations;
    string* Contrac;//array of contractions
    int* EachLetterCount;    //save the count for each word group that starts with the 26 letters

    string tempstr;          //string buffer for word tokens



//-------------------functions---------------------
    Tokenization();
    ~Tokenization();

    string Tokenize(const char* filename);//where the magic happens

    float ReadingEase();//calcualtes the reading level
    string MergeLines(const char* filename);//merges all lines of text read in into one string
    string Abbreviation(string &line);//checks for abbreviation
    string Contraction(string &line);//checks for contraction
    void Sentences(string &line);//counts sentences and takes out punctuation
    void InitialArrays();//read abbreviations and contractions from text file

    void InsertInto26Trees(string &line, int l, int p);//insert orchard of binary trees
    void InsertToWordList();//inserts the orchard into a word list in alphabetical order
    void Find10Words();//finds top 10 frequently used words

    void showWordListAndCount();
    void WriteToFile(const char *filename);

private:

};


Tokenization::Tokenization()
{
    netparaNum = 1;
    netlineNum = 1;
    netsentNum = 0;
    networdNum = 0;
    networdLength = 0;
    netnonrepeatwordCount = 0;

    InitialArrays();

}

Tokenization::~Tokenization()
{
    netparaNum = 1;
    netlineNum = 1;
    netsentNum = 0;
    networdNum = 0;
    networdLength = 0;
    netnonrepeatwordCount = 0;


    WordList.clear();
    WordCount.clear();


    delete[] Abbrev;
    delete[] Abbreviations;
    delete[] Contrac;
    delete[] Most10WordList;
    delete[] EachLetterCount;

}



string Tokenization::MergeLines(const char *filename)
{
    ifstream file;
    string textline("");
    string mergedText("");

    file.open(filename);


    while(getline(file, textline))
    {
        if(textline.empty())//for windows mingw
        //if(textline.size() == 1)//for osx and linux
        {
            mergedText.append("& "); //mark the end of a paragraph with "& "
            netparaNum++;
            netlineNum++;   //blank line is also counted for lineNum
        }
        else
        {

            int flag = 0;
            while(flag!=-1)
            {
                flag = textline.find_first_of("/0123456789,:;<>()[]{}*+~#$\%^_|");
                if(flag != -1)
                    textline.replace(flag, 1, " ");
            }

            flag = 0;
            while(flag!=-1)
            {
                flag = textline.find("....");
                if(flag != -1)
                    textline.replace(flag, 4, "... ");
            }

            flag = 0;
            while(flag!=-1)
            {
                flag = textline.find("’");
                if(flag != -1)
                    textline.replace(flag, 4, "'");
            }


            flag = 0;
            while(flag!=-1)
            {
                flag = textline.find("---");

                if(flag != -1)
                    textline.replace(flag, 3, "   ");
            }

            flag = 0;
            while(flag!=-1)
            {
                flag = textline.find("--");
                if(flag != -1)
                    textline.replace(flag, 2, "  ");
            }

//----------------------find abbreviations and replace them with their completed form---------------------------

            flag = 0;
            int pos = 0, cursor = 0;
            int linesiz = textline.length();
            while(flag!=-1 && cursor<linesiz)
            {

                cursor = textline.find_first_of(".", cursor);
                flag = cursor;
                if(cursor != -1 && textline[cursor+1] == '.' && textline[cursor+2] == '.')
                    cursor += 3; //skip punctuation ...

                else if(cursor != -1 && textline[cursor-1] == ' ' )
                {
                    if(textline[cursor+1] == '.' && textline[cursor+2] == '.')
                        cursor +=3;
                    else
                        cursor++;
                }

                else if(cursor>=0 && textline[cursor+1] != '.')
                {
                    pos = textline.find_last_of(" ", cursor);

                    if(pos == -1)
                        pos = 0;                //the first word of a line is abbreviation, no space before it

                    pos = textline.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", pos);

                    string abbrevword = textline.substr(pos, cursor-pos);  //abbrev

                    abbrevword[0] = toupper(abbrevword[0]);    //Abbrev

                    string fullword = Abbreviation(abbrevword);  //Abbreviation

                    if(abbrevword != fullword)
                    {
                        textline.erase(pos, cursor-pos+1);    //erase abbrev.

                        textline.insert(pos, fullword);    //insert Abbreviation
                    }

                    cursor++;
                }

            }

//-----------------------------------------------------------------merge lines by string append function----------------------------------------------------------------

            mergedText.append(textline);

            mergedText.append("@ ");  //mark the end of a line with "@ "
            netlineNum++;
        }
    }

    mergedText.append("&");  //mark the end of the book with "&+"

    file.close();
    return mergedText;


    /*replace any characters in this set "/0123456789,:;()*" with " " in the text for convenience to determine sentence later.
    replace all "--" with " " in the text for convenience to determine sentence later.
    replace all "...." with "..." in the text for convenience to determine sentence later.
    only punctuations left are .?!" ...
    ' for contraction words.
    - for something like wound-up*/

}


string Tokenization::Abbreviation(string &line)
{
    int mark=-1;
    for(int i=0; i<AbbrevArraySize; i++)
    {
        if(line == Abbrev[i])
            mark = i;
    }

    if(mark != -1)
        return Abbreviations[mark];
    return line;
}

string Tokenization::Contraction(string &line)
{
    for(int i=0; i<ContracArraySize; i++)
    {
        if(line == Contrac[i])
            return line;
    }

    int mark = line.length()-1;
    if(line[mark] == 39)
        line.erase(mark);


    mark = line.length()-2;
    if((line[mark] == 39) && (line[mark+1] == 's'))
        line.erase(mark, 2);

    return line;
}

void Tokenization::Sentences(string &line)
{
    //the string should only have . ! ? " ... text(which includes letters and - ') at this point

    int cursor = 0;
    int length = line.length();

    while(cursor<=length)
    {

        if(line[cursor] == '!' || line[cursor] == '?')     // !?
        {
            line.replace(cursor, 1, " ");
            cursor++;
            netsentNum++;
        }
        else if(line[cursor] == '.')  // . ...
        {
            if(line[cursor+1] == '.' && line[cursor+2] == '.')
            {
                line.replace(cursor, 3, "   ");
                cursor += 3;
            }
            else
            {
                line.replace(cursor, 1, " ");
                cursor++;
            }
            netsentNum++;
        }
        else if(line[cursor] == '"')  // "
        {
            line.replace(cursor, 1, " ");
            cursor++;
        }
        else // text
            cursor++;
    }
    //. ? ! ...within quotation marks are counted as sentences since the reading ease calculation does include those.
    //the string should only have text(which includes letters and - ') at this point.
}

void Tokenization::InsertInto26Trees(string &line, int l, int p)
{
    string pp;

    stringstream ss;

    ss.clear();
    ss << p << "-" << l << " ";
    pp = ss.str();

    char capital = line[0];

    switch(capital)
    {
    case 'A':   WordTree[0].insert(line, pp);
                break;
    case 'B':   WordTree[1].insert(line, pp);
                break;
    case 'C':   WordTree[2].insert(line, pp);
                break;
    case 'D':   WordTree[3].insert(line, pp);
                break;
    case 'E':   WordTree[4].insert(line, pp);
                break;
    case 'F':   WordTree[5].insert(line, pp);
                break;
    case 'G':   WordTree[6].insert(line, pp);
                break;
    case 'H':   WordTree[7].insert(line, pp);
                break;
    case 'I':   WordTree[8].insert(line, pp);
                break;
    case 'J':   WordTree[9].insert(line, pp);
                break;
    case 'K':   WordTree[10].insert(line, pp);
                break;
    case 'L':   WordTree[11].insert(line, pp);
                break;
    case 'M':   WordTree[12].insert(line, pp);
                break;
    case 'N':   WordTree[13].insert(line, pp);
                break;
    case 'O':   WordTree[14].insert(line, pp);
                break;
    case 'P':   WordTree[15].insert(line, pp);
                break;
    case 'Q':   WordTree[16].insert(line, pp);
                break;
    case 'R':   WordTree[17].insert(line, pp);
                break;
    case 'S':   WordTree[18].insert(line, pp);
                break;
    case 'T':   WordTree[19].insert(line, pp);
                break;
    case 'U':   WordTree[20].insert(line, pp);
                break;
    case 'V':   WordTree[21].insert(line, pp);
                break;
    case 'W':   WordTree[22].insert(line, pp);
                break;
    case 'X':   WordTree[23].insert(line, pp);
                break;
    case 'Y':   WordTree[24].insert(line, pp);
                break;
    case 'Z':   WordTree[25].insert(line, pp);
                break;

    default: cout << "check the first letter of the line: " << line <<endl;
    }
}


float Tokenization::ReadingEase()
{
    float result;

    result = 206.835 - 1.015 * (networdNum * 1.) / (netsentNum * 1.) -84.6 * (networdLength * 1.) / 3. / (networdNum * 1.);

    return result;
}

void Tokenization::InsertToWordList()
{

    for(int i = 0; i < 26; i++)
    {
        //cout <<"      =====processing==WordTree["
        //     << i << "]=====" <<endl;

        EachLetterCount[i] = WordTree[i].treeToArray(WordList);

        netnonrepeatwordCount = WordList.size();
    }
    for(int i = 0, size = WordList.size(); i < size; i++)
        WordCount.push_back(WordList[i].count);
}

void Tokenization::Find10Words()
{
    int i=0, j=0;
    string temp;

    int* WordIndexArray = new int[netnonrepeatwordCount];
    int* WordCountArray = new int[netnonrepeatwordCount];


    for(i=0; i<netnonrepeatwordCount; i++)
    {
        WordIndexArray[i] = i;
        WordCountArray[i] = WordCount[i];
    }

    for(i=0; i<netnonrepeatwordCount; i++)
        for(j=0; j<=netnonrepeatwordCount; j++)
            if(WordCountArray[i] > WordCountArray[j])
            {
                WordCountArray[i] ^= WordCountArray[j] ^= WordCountArray[i] ^= WordCountArray[j];
                WordIndexArray[i] ^= WordIndexArray[j] ^= WordIndexArray[i] ^= WordIndexArray[j];
            }

    for(i=0; i<10; i++)
    {
        temp = WordList[WordIndexArray[i]].data;
        temp += "   ";

        stringstream s1;
        s1.clear();
        s1 << WordCount[WordIndexArray[i]];

        temp += s1.str();

        Most10WordList[i] = temp;
    }

}


void Tokenization::showWordListAndCount()
{

        if(WordList.size() == WordCount.size())
        {
            int listsize = WordList.size();
            for(int i=0; i< listsize;i++)
            {
                //cout << WordList[i].data << " - " << WordCount[i] <<endl;
            }
        }
        else
        {
            //cout << endl << "WordList vector is not of the same length with the WordCount vector" <<endl;

        }
}

void Tokenization::WriteToFile(const char *filename)
{
    //SetCurrentDirectoryA("C:\\Users\\Xizhao\\Desktop");  //a way to set the default file path

    ofstream ThatFile(filename2);

    ThatFile << endl << "    Information below is by analyzing [" << filename << "] and is saved in [" << filename2 << "]"
             << endl << endl << endl << endl << endl;

    ThatFile << endl << "      ====10 most frequent words & Occurrance#====" << endl <<endl;

    for(int i=0; i<10; i++)
    {
        ThatFile <<"           " << Most10WordList[i] << endl;
    }

    ThatFile << endl << "-------------------------------------------------------------------" << endl << endl
             << "            ====Statistic Information====" << endl << endl
             << "              Total Paragraph#: " <<netparaNum << endl
             << "              Total Line#: " <<netlineNum << " including new line" << endl
             << "              Total Sentence#: " <<netsentNum << endl
             << "              Total Word#: " <<networdNum <<endl
             << "              Reading Ease: " <<ReadingEase() <<endl
             << "              Program Time Cost: " << ((float)t)/CLOCKS_PER_SEC  << " sec"<<endl;

    ThatFile << endl <<endl << "    =========== word list ===========" <<endl << endl
             << "    ==Occurrance==      ==word==               === All positions (paragraph#-line#)===" <<endl;


    for(int i=0; i<netnonrepeatwordCount; i++)
    {
        ThatFile << "          [" << WordCount[i] << "]            " << WordList[i].data << "                     "
                 <<  WordList[i].LinePara << endl;
    }


   ThatFile << endl << "===========================END OF FILE==========================" <<endl;

}




void Tokenization::InitialArrays()
{
    Abbrev = new string [AbbrevArraySize];
    Abbreviations = new string [AbbrevArraySize];
    Contrac = new string [ContracArraySize];
    Most10WordList = new string [10];
    EachLetterCount = new int[26];

    ifstream AbbrevFile(filename3);

    string buffer;
    int count = 0;

    while(getline(AbbrevFile, buffer))
    {
        if(buffer.empty())
        {
            //do nothing
        }
        else
        {
            Abbrev[count] = buffer;
        }
        count++;
    }


    ifstream AbbreviationFile(filename4);
    count = 0;

    while(getline(AbbreviationFile, buffer))
    {
        if(buffer.empty())
        {
            //do nothing
        }
        else
        {
            Abbreviations[count] = buffer;
        }
        count++;
    }

    Contrac[0] = "Aren't";Contrac[1] = "Can't";Contrac[2] = "Could've";Contrac[3] = "Couldn't";Contrac[4] = "Didn't";
    Contrac[5] = "Doesn't";Contrac[6] = "Don't";Contrac[7] = "Hadn't";Contrac[8] = "Hasn't";Contrac[9] = "Haven't";
    Contrac[10] = "He'd";Contrac[11] = "He'll";Contrac[12] = "He's";Contrac[13] = "How'd";Contrac[14] = "How'll";
    Contrac[15] = "How's";Contrac[16] = "I'd";Contrac[17] = "I'll";Contrac[18] = "I'm";Contrac[19] = "I've";
    Contrac[20] = "Isn't";Contrac[21] = "It'd";Contrac[22] = "It'll";Contrac[23] = "It's";Contrac[24] = "Let's";
    Contrac[25] = "Ma'am";Contrac[26] = "Might've";Contrac[27] = "Must've";Contrac[28] = "Needn't";Contrac[29] = "O'clock";
    Contrac[30] = "Shan't";Contrac[31] = "She'd";Contrac[32] = "She'll";Contrac[33] = "She's";Contrac[34] = "Should've";
    Contrac[35] = "Shouldn't";Contrac[36] = "That'd";Contrac[37] = "That's";Contrac[38] = "There'd";Contrac[39] = "There've";
    Contrac[40] = "There's";Contrac[41] = "They'd";Contrac[42] = "They'll";Contrac[43] = "They're";Contrac[44] = "They've";
    Contrac[45] = "Wasn't";Contrac[46] = "We'd";Contrac[47] = "We'll";Contrac[48] = "We're";Contrac[49] = "We've";
    Contrac[50] = "Weren't";Contrac[51] = "What'll";Contrac[52] = "What're";Contrac[53] = "What's";Contrac[54] = "When's";
    Contrac[55] = "Where'd";Contrac[56] = "Where's";Contrac[57] = "Where've";Contrac[58] = "Who'll";Contrac[59] = "Who's";
    Contrac[60] = "Why's";Contrac[61] = "Won't";Contrac[62] = "Would've";Contrac[63] = "Wouldn't";Contrac[64] = "You'd";
    Contrac[65] = "You'll";Contrac[66] = "You're";Contrac[67] = "You've";Contrac[68] = "O'er";Contrac[69] = "Ne'er";
}


//=========================================================================================================


string Tokenization::Tokenize(const char *filename)
{
    t = clock();

//----------------------------merge the whole book into a single modified string------------------------------------------

    string mergedText = MergeLines(filename);

//------------------------determine how many sentence are there, remove . ... ? ! "----------------------------------------

    Sentences(mergedText);

//-------------------tokenize the string----(the long string only has & @ - ' space and actual text.)-----------------------

    int start=0, end=0, cursor=0, textSize=mergedText.size(), linePos=1, paraPos=1, linemark=0, paramark=0;

    while(cursor < textSize && start != -1)
    {
        networdNum++; //update the total word count

        if(cursor > linemark)              //update linePos
            linePos++;
        if(cursor > paramark)
        {
            paraPos++;                     //update paraPos, linePos will be cleared to be 1
            linePos=1;
        }
        paramark = mergedText.find_first_of("&", cursor);    //find the end of the current paragraph
        linemark = mergedText.find_first_of("@", cursor);    //find the end of the current line

        start = mergedText.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", cursor);
        end = mergedText.find_first_of("&@ ", start+1);


        cursor = end;   //update cursor, cursor always points to the last letter of the tokenized word

//-----------------------------get a token and capitalize the first letter-----------------------------

        if(start != -1 && end != -1)
        {
            tempstr = mergedText.substr(start, end-start);
            tempstr[0] = toupper(tempstr[0]);          //capitalize the first letter of a tokenized word
            networdLength += tempstr.length();         //calculate the total length of all words


//-----------------------------------------find contraction and convert----------------------------------------

            if(tempstr.find("'") != -1)
                tempstr = Contraction(tempstr);

//-------------------------------------------------put tokens into 26 heaps-----------------------------------------------------
            InsertInto26Trees(tempstr, linePos, paraPos);
        }


//-------------------------------------------for debug--------------------------------------------

        //cout <<"["  <<paraPos << " - "<<linePos << "]  " << tempstr <<endl;

//-------------------------------------end of while loop----------------------------------------
    }

//-------------------------------------------insert into word list------------------------------------

    InsertToWordList();

//-------------------------------------------find 10 most frequent word------------------------------------

    Find10Words();
    t = clock() - t;
    WriteToFile(filename);

//-------------------------------------for debugging-----------------------------------------

    //showWordListAndCount();

//--------------------------display all the statistic information-----------------------------------------
/*

    cout << endl << "--------------------------------------" <<endl <<endl
         << endl << "10 most frequent words list"<<endl <<endl;

    for(int i=0; i<10; i++)
        cout << Most10WordList[i] <<endl;

    cout << endl << "--------------------------------------" <<endl <<endl
         << endl << "EachLetterCount: " <<endl <<endl;

    for(int i=0; i<26; i++)
    {
        char a = i+65;
        cout << a << " : " << EachLetterCount[i] <<endl;
    }

    cout << endl
         << "Text size: " <<textSize <<endl
         << "Total paragraph: " <<netparaNum <<endl
         << "Total line: " <<netlineNum << " including new line" << endl
         << "Total sentence: " <<netsentNum <<endl
         << "Total word: " <<networdNum <<endl
         << "Total word length: " <<networdLength <<endl
         << "Total unique word: " <<netnonrepeatwordCount <<endl
         << "Reading ease: " <<ReadingEase() <<endl
         << "It took: " << ((float)t)/CLOCKS_PER_SEC << " sec" <<endl <<endl;


*/

//--------------------------Create result for displaying on GUI-----------------------------------------

    string result;
    stringstream ssBuffer;

    ssBuffer.clear();

    ssBuffer << endl
         << "Text size: " <<textSize <<endl<<endl
         << "Total Paragraphs#: " <<netparaNum <<endl<<endl
         << "Total Lines#: " <<netlineNum << " including new line" << endl<<endl
         << "Total Sentences#: " <<netsentNum <<endl<<endl
         << "Total Words#: " <<networdNum <<endl<<endl
         << "Total Words Length: " <<networdLength <<endl<<endl
         << "Total Non-duplicate Words#: " <<netnonrepeatwordCount <<endl<<endl
         << "Reading Ease: " <<ReadingEase() <<endl<<endl
         << "Program Time Cost: " << ((float)t)/CLOCKS_PER_SEC << " sec" <<endl <<endl
         << "10 most frequent words: " <<endl <<endl;

    for(int i=0; i<10; i++)
         ssBuffer << Most10WordList[i] <<endl;


    result = ssBuffer.str();

    return result;

}



//===================================================================================================


#endif // TOKENIZATION_H
