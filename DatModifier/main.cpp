#include "Database.h"
using namespace std;

void menu(char &ans);
void perform(char ans, Database& that);

int main()
{
    Database DAT;
    DAT.ModifyDAT();

    char ans;
    do
    {
       menu(ans);
       perform(toupper(ans), DAT);
    }while(toupper(ans) != 'Q');
    return 0;
}
void menu(char &ans)
{
    cout<<endl<<endl
        <<"Here are your options:"<<endl
        <<"  A. Check a credit card number"<<endl
        <<"  B. Generate a Visa card number"<<endl
        <<"  C. Generate a Master card number"<<endl
        <<"  D. Generate a Discover card number"<<endl
        <<"  E. Generate a American Express card number"<<endl
        <<"  W. Write map to a text file"<<endl
        <<"  Q. Quit this program"<<endl
        <<"Please make a selection: ";

    cin>>ans;
}

void perform(char ans, Database &that)
{
    string card, result;

    switch(ans)
        {

            case 'A' :  cout << endl << "Please input a 16 digit credit card number: ";
                        cin >> card;
                        if(that.Checker(card))
                            cout << endl << "Valid Card";
                        else
                            cout << endl << "Invalid Card";
                         break;

            case 'B' :  result = that.Visa();
                        cout << endl <<result << endl;
                         break;

            case 'C' :  result = that.MasterCard();
                        cout << endl <<result << endl;
                         break;

            case 'D' :  result = that.Discover();
                        cout << endl <<result << endl;
                         break;

            case 'E' :  result = that.Amex();
                        cout << endl <<result << endl;
                         break;

            case 'W' :   that.WriteToFile();
                         break;

            case 'Q' :   cout<<"Thank you for using this program"<<endl;
                         break;

            default  : cout<<"Not a valid selection. Please try again."<<endl;
        }
}
