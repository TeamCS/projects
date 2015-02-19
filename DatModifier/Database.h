#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

class Database
{
public:
    Database();
    ~Database();

    void ModifyDAT();
    void BreakUpVisa();
    void SplitVisa();
    void BreakUpMc();
    void SplitMc();

    bool Checker(string toCheck);
    bool Input(string temp);
    void Display();
    string Visa();
    string Amex();
    string MasterCard();
    string Discover();
    void WriteToFile();

private:
    string line1, line2, str;
    char data;
    vector<string> VisaBanks, VisaFirst6Num, VisaBankInfo, McBanks, McFirst6Num, McBankInfo;
    int CardNumber[16];
};

Database::Database()
{
    for(int i=0;i<16;i++)
        CardNumber[i] = 0;
}

Database::~Database()
{
    //empty
}

void Database::ModifyDAT()
{
    ifstream in1("visa.dat", ios::binary);
    ifstream in2("mc.dat", ios::binary);

    while(in1.get(data))
    {
        if((data>=48 && data<=57) || (data>=65 && data<=90))
            line1 += data;
        else if(data == 6)
            line1 += "&";
        else
            line1 += " ";

    }

    while(in2.get(data))
    {
        if((data>=48 && data<=57) || (data>=65 && data<=90))
            line2 += data;
        else if(data == 6)
            line2 += "&";
        else
            line2 += " ";

    }
    BreakUpVisa();
    SplitVisa();
    BreakUpMc();
    SplitMc();

}

void Database::BreakUpVisa()
{
    int cursor=0, start=0;
    string bank;

    while(cursor< (int)line1.size() && cursor != -1 && start != -1)
    {
          cursor = line1.find("&", start);
          bank = line1.substr(start,cursor-start);
          start = line1.find("4", cursor);
          VisaBanks.push_back(bank);
    }
}

void Database::SplitVisa()
{
    int firstLetter=0;
    string line1, temp;
    for(int i = 0; i < (int)VisaBanks.size(); i++)
    {
        line1 = VisaBanks[i];
        firstLetter = line1.find_first_not_of("0987654321");
        if(firstLetter != -1)
        {
            temp = line1.substr(0,firstLetter);
            if(temp.size() == 6)
            {
                line1 = line1.substr(firstLetter);

                firstLetter = line1.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                if(firstLetter != -1)
                {
                    VisaFirst6Num.push_back(temp);
                    VisaBankInfo.push_back(line1.substr(firstLetter));
                }
            }
        }

    }
}

void Database::BreakUpMc()
{
    int cursor=0, start=0;
    string bank;

    while(cursor< (int)line2.size() && cursor != -1 && start != -1)
    {
          cursor = line2.find("&", start);
          bank = line2.substr(start,cursor-start);
          start = line2.find("5", cursor);
          McBanks.push_back(bank);
    }
}

void Database::SplitMc()
{
    int firstLetter=0;
    string line2, temp;
    for(int i = 0; i < (int)McBanks.size(); i++)
    {
        line2 = McBanks[i];
        firstLetter = line2.find_first_not_of("0987654321");
        if(firstLetter != -1)
        {
            temp = line2.substr(0,firstLetter);
            if(temp.size() == 6)
            {
                line2 = line2.substr(firstLetter);

                firstLetter = line2.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                if(firstLetter != -1)
                {
                    McFirst6Num.push_back(temp);
                    McBankInfo.push_back(line2.substr(firstLetter));
                }
            }
        }
    }
}

bool Database::Checker(string toCheck)
{
    if(toCheck.length() != 16)
        return false;

    if(!Input(toCheck))
        return false;

    int sum = 0;

    for(int i=14; i>=0; i=i-2)
    {
        CardNumber[i] *= 2;

        if(CardNumber[i] > 9)
        {
            CardNumber[i] = CardNumber[i]-9;
        }
    }

    for(int i=0; i<16; i++)
    {
        sum += CardNumber[i];
    }

    cout << endl << "sum: " << sum <<endl;

    if(sum%10 == 0)
        return true;

    return false;
}

bool Database::Input(string temp)
{
    for(int i=0; i<16; i++)
    {
        CardNumber[i] = temp[i] - 48;

        if(CardNumber[i]>9 || CardNumber[i]<0)
            return false;
    }
    return true;
}


void Database::Display()
{
    for(int i=0; i<16; i++)
    {
        if(i==4||i==8||i==12)
            cout << " ";
        cout << CardNumber[i];
    }
}

void Database::WriteToFile()
{
    ofstream ThatFile("Saved Card Number.txt");

    ThatFile << endl << "The generated card number is: " << endl <<endl << str <<endl;
}

string Database::Visa()
{
    int index;
    int temp[16];
    int sum = 0;
    srand(time(NULL));
    str="";

    for(int i = 0; i < (int)VisaFirst6Num.size(); i++)
        cout<< "[" << i <<"] " <<VisaFirst6Num[i]<<"    "<< VisaBankInfo[i]<<endl;

    cout << endl << "Which bank do you want to use? Key in the index number: ";
    cin >> index;

    for(int i=0; i<=5; i++)
    {
        CardNumber[i] = VisaFirst6Num[index][i]-48;
        temp[i] = CardNumber[i];
    }


    for(int i=6; i<=15; i++)
    {
        CardNumber[i] = rand()%10;
        temp[i] = CardNumber[i];
    }


    for(int i=14; i>=0; i=i-2)
    {
        temp[i] *= 2;

        if(temp[i] > 9)
        {
            temp[i] = temp[i]-9;
        }
    }

    for(int i=0; i<=14; i++)
    {
        sum += temp[i];
    }

    cout << endl << "sum: " << sum <<endl;

    if(sum<10)
        CardNumber[15] = 10-sum;
    else
        CardNumber[15] = (sum/10+1)*10-sum;

    for(int i=0; i<16; i++)
    {
        if(i==4||i==8||i==12)
            str += " ";
        str += CardNumber[i]+48;
    }

    return str;
}

string Database::Amex()
{
    int temp[16];
    int sum = 0;
    str="";

    srand(time(NULL));

    CardNumber[0] = 3;
    temp[0] = 3;

    CardNumber[1] = 7;
    temp[1] = 7;

    for(int i=2; i<=15; i++)
    {
        CardNumber[i] = rand()%10;
        temp[i] = CardNumber[i];
    }


    for(int i=14; i>=0; i=i-2)
    {
        temp[i] *= 2;

        if(temp[i] > 9)
        {
            temp[i] = temp[i]-9;
        }
    }

    for(int i=0; i<=14; i++)
    {
        sum += temp[i];
    }

    cout << endl << "sum: " << sum <<endl;

    if(sum<10)
        CardNumber[15] = 10-sum;
    else
        CardNumber[15] = (sum/10+1)*10-sum;

    for(int i=0; i<16; i++)
    {
        if(i==4||i==8||i==12)
            str += " ";
        str += CardNumber[i]+48;
    }

    return str;
}

string Database::MasterCard()
{
    int index;
    int temp[16];
    int sum = 0;
    srand(time(NULL));
    str="";

    for(int i = 0; i < (int)McFirst6Num.size(); i++)
        cout<< "[" << i <<"] " <<McFirst6Num[i]<<"    "<< McBankInfo[i]<<endl;


    cout << endl << "Which bank do you want to use? Key in the index number: ";
    cin >> index;

    for(int i=0; i<=5; i++)
    {
        CardNumber[i] = McFirst6Num[index][i]-48;
        temp[i] = CardNumber[i];

    }

    for(int i=6; i<=15; i++)
    {
        CardNumber[i] = rand()%10;
        temp[i] = CardNumber[i];
    }


    for(int i=14; i>=0; i=i-2)
    {
        temp[i] *= 2;

        if(temp[i] > 9)
        {
            temp[i] = temp[i]-9;
        }
    }

    for(int i=0; i<=14; i++)
    {
        sum += temp[i];
    }

    cout << endl << "sum: " << sum <<endl;

    if(sum<10)
        CardNumber[15] = 10-sum;
    else
        CardNumber[15] = (sum/10+1)*10-sum;

    for(int i=0; i<16; i++)
    {
        if(i==4||i==8||i==12)
            str += " ";
        str += CardNumber[i]+48;
    }

    return str;
}

string Database::Discover()
{
    int temp[16];
    int sum = 0;
    str="";

    srand(time(NULL));

    CardNumber[0] = 6;
    temp[0] = 6;

    CardNumber[1] = 5;
    temp[1] = 5;

    for(int i=2; i<=15; i++)
    {
        CardNumber[i] = rand()%10;
        temp[i] = CardNumber[i];
    }


    for(int i=14; i>=0; i=i-2)
    {
        temp[i] *= 2;

        if(temp[i] > 9)
        {
            temp[i] = temp[i]-9;
        }
    }

    for(int i=0; i<=14; i++)
    {
        sum += temp[i];
    }

    cout << endl << "sum: " << sum <<endl;

    if(sum<10)
        CardNumber[15] = 10-sum;
    else
        CardNumber[15] = (sum/10+1)*10-sum;

    for(int i=0; i<16; i++)
    {
        if(i==4||i==8||i==12)
            str += " ";
        str += CardNumber[i]+48;
    }

    return str;
}

#endif // DATABASE_H
