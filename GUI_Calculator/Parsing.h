#ifndef PARSING_H
#define PARSING_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include "include.h"
#include "voidQueue.h"
#include "voidStack.h"
#include <cmath>

using namespace std;


class Parsing
{
public:
    Parsing();
    ~Parsing();

    /*Void ParseString(String s) first calls tokenize() to tokenize the equation string from user input
      and stores it on the Equ_Queue. Then it calls toRPN() to transform the Equ_Queue in RPN format
      and stores the RPN equation on the output queue.*/



    void ParseString(string s);
    bool checkFormat(string s);  //check the tail formatting of the input equation
    int precedence(char c);  //return int specifying the precedence of operators
    void tokenize(); //tokenize StrInput and stores it on Equ_Queue
    void toRPN();  //transform the equation on Equ_Queue to RPN and stores it on output queue
    string calc(); //do the actual calculation with the RPN formatting equation, and return the result as a string
    string RPNstring(); //return the RPN equation as a string

    /*Ope_Stack stores operator during the RPN transformation process
      Cal_Stack is used to hold results of the calculation temperarily
      Equ_Queue stores the tokenized original equation
      output stores the RPN formatted equation*/

    voidStack Ope_Stack, Cal_Stack;
    voidQueue Equ_Queue, output;

private:
    string StrInput; //stores the original equation string

};

Parsing::Parsing()
{

}

Parsing::~Parsing()
{
    //leave empty
}


bool Parsing::checkFormat(string s)
{
    if(s.find_last_of("+-*/(")==s.size()-1)
    {
        //cout << "The equation must ends with a number or bracket, not anything else." <<endl;
        return false;
    }
    else
        return true;
}

void Parsing::ParseString(string s)
{
    StrInput=s;
    //cout <<"StrInput: " << StrInput <<endl;

    try
    {
        if(!checkFormat(StrInput))
            throw INVALID_EQU_FORMAT;

        tokenize();
        toRPN();
    }
    catch(ERRORS e)
    {
        //cout << endl << "In ParsingString(), error received from tokenize or toRPN." <<endl;
        throw e;

    }


}


void Parsing::tokenize()
{
    stringstream ss;
    int int1, int2, int3;
    string Str1, Str2, Str3;
    char char1;

    int pos1=0;
    int pos2=0;
    int pos3=0;
    int pos4=0;


    //cout << "StrInput Size: " << StrInput.size() <<endl;

    try
    {
        while(pos1<StrInput.size())
        {
            if(StrInput[pos1]<=57 && StrInput[pos1]>=48)     //a digit found
            {
                pos2=StrInput.find_first_of("+-*/()^", pos1);

                if(StrInput[pos2]=='/' && StrInput[pos2-1]!=' ')    //fraction or mixed found
                {
                    if(StrInput[pos2+1]<48 || StrInput[pos2+1]>57)
                        throw INVALID_EQU_FORMAT;      //following the fraction sign must be number, anything else, throw error

                    pos2=StrInput.find_first_of("+-*/()^", pos2+1);

                    if(StrInput[pos2]=='/' && StrInput[pos2-1]!=' ')         //for example 3/4/7 instead of 3/4 / 7
                    {
                        //cout << "The equation has invalid format. 2 Mixed number must can't be put together." <<endl;
                        throw INVALID_EQU_FORMAT;
                    }

                    Str1=StrInput.substr(pos1, pos2-pos1-1);  //cotain that fraction or mixed, minus 1 for that extra space "3 1/2 "

                    pos3=Str1.find_first_of(" ");

                    if(pos3!=-1) //space found, it is a mixed
                    {

                        Str2=Str1.substr(0, pos3); //whole number part of mixed
                        ss.clear();
                        ss<<Str2;
                        ss>>int1;

                        if (StrInput[pos1-1]== '-')
                        {
                            int1=-int1;
                        }

                        Str2=Str1.substr(pos3);    //fraction part of mixed
                        pos4=Str2.find_first_of("/");
                        Str3=Str2.substr(0, pos4);    //numerator
                        ss.clear();
                        ss<<Str3;
                        ss>>int2;

                        Str3=Str2.substr(pos4+1);   //denominator
                        ss.clear();
                        ss<<Str3;
                        ss>>int3;

                        Mixed Mixed1(int2, int3, int1);   //num dem whole
                        Equ_Queue.enqueue(Mixed1);

                        //Equ_Queue.show();

                    }
                    else  //space not found, it is a fraction
                    {
                        pos3=Str1.find_first_of("/");

                        Str2=Str1.substr(0, pos3);    //numerator
                        ss.clear();
                        ss<<Str2;
                        ss>>int2;

                        if (StrInput[pos1-1]== '-')
                        {
                            int2=-int2;
                        }

                        Str2=Str1.substr(pos3+1);    //denominator
                        ss.clear();
                        ss<<Str2;
                        ss>>int3;

                        Mixed Mixed1(int2, int3);
                        Equ_Queue.enqueue(Mixed1);

                        //Equ_Queue.show();

                    }
                    pos1=StrInput.find(Str1, pos1)+Str1.size();   //cursor for next loop is updated


                }
                else //an integer or decimal
                {
                    Str1=StrInput.substr(pos1, pos2-pos1-1);
                    pos3=Str1.find_first_of(".");

                    if(pos3!=-1)  //a decimal
                    {
                        Str2=Str1.substr(0, pos3);  //integer part
                        Str3=Str1.substr(pos3+1);   //decimal part

                        ss.clear();
                        ss<<Str2;
                        ss>>int2;

                        if (StrInput[pos1-1]== '-')
                        {
                            int2=-int2;
                        }

                        ss.clear();
                        ss<<Str3;
                        ss>>int3;

                        double decimalbase = pow(10.0, static_cast<double>(Str3.size()));
                        int decimalbaseInt = (int)decimalbase;

                        Mixed Mixed1(int3, decimalbaseInt, int2);
                        Equ_Queue.enqueue(Mixed1);

                        //Equ_Queue.show();

                    }
                    else  //an integer
                    {
                        ss.clear();
                        ss<<Str1;
                        ss>>int1;

                        if (StrInput[pos1-1]== '-')
                        {
                            int1=-int1;
                        }

                        Mixed Mixed1(0,1,int1);
                        Equ_Queue.enqueue(Mixed1);

                        //Equ_Queue.show();

                    }

                    pos1=StrInput.find(Str1, pos1)+Str1.size();   //cursor for next loop is updated

                }
            }


            else if(StrInput[pos1]=='+'||StrInput[pos1]=='-'
                    ||StrInput[pos1]=='*'||StrInput[pos1]=='/'
                    ||StrInput[pos1]=='('||StrInput[pos1]==')'||StrInput[pos1]=='^') //an operator found
            {
                if(pos1==0)   //check the start of the equation for invalid formatting
                {

                    if(StrInput[pos1]=='-' && StrInput[pos1+1]!=' ')  //negative notatio at the start of the equation
                    {
                        //do nothing
                    }
                    else if(StrInput[pos1]=='(' && StrInput[pos1+1]==' ')
                    {
                        //do nothing
                    }
                    else
                    {
                        //cout << "Invalid Equation format, the start of the equation can't be operator besides '(' or negative notation." <<endl;
                        throw INVALID_EQU_FORMAT;

                    }
                }

                if(StrInput[pos1]=='-' && StrInput[pos1+1]!=' ')                   //when reaches a '-' that works as a negative sign, do nothing
                {
                   //do nothing
                }
                else
                {
                    if(StrInput[pos1+1]!=' ')                                  //check if the operators are followed by a space, if not, throw error
                        throw INVALID_EQU_FORMAT;

                    if(StrInput[pos1]=='+'||StrInput[pos1]=='-'||StrInput[pos1]=='*'||StrInput[pos1]=='/'||StrInput[pos1]=='^')
                    {
                        if(StrInput[pos1+2]=='+'||StrInput[pos1+2]=='.'||StrInput[pos1+2]=='*'||StrInput[pos1+2]=='/'||StrInput[pos1+2]==')'||StrInput[pos1+2]=='^')
                            throw INVALID_EQU_FORMAT;
                    }


                    if(StrInput[pos1]=='('||StrInput[pos1]==')')
                    {
                        if(StrInput[pos1+2]=='+'||StrInput[pos1+2]=='.'||StrInput[pos1+2]=='*'||StrInput[pos1+2]=='/'||StrInput[pos1+2]=='('||StrInput[pos1+2]==')'||StrInput[pos1+2]=='^')
                            throw INVALID_EQU_FORMAT;
                    }

                    ss.clear();
                    ss<<StrInput[pos1];
                    ss>>char1;

                    Equ_Queue.enqueue(char1);

                    //Equ_Queue.show();

                }

                pos1++; //cursor for next loop is updated

            }
            else if(StrInput[pos1]==' ')   //beside digit and operator, if only a space is read, move the cursor forward by 1
                pos1++;


        }//end of the while loop
    }
    catch(ERRORS e)
    {
        //cout << "In tokenize(), error received." <<endl;
        throw e;
    }

    //Equ_Queue.show();

}


void Parsing::toRPN()
{
    char theOperator, tempOperator, tempOperator2;
    Mixed pushToOutput;


    try
    {
        while(!Equ_Queue.empty())                              //go through the equation queue
        {
//            Ope_Stack.show();
//            cout<<endl;
//            output.show();
//            cout<<endl;

            if(Equ_Queue.frontDataType()=="5Mixed")            //meet a number
            {
                Equ_Queue.dequeue(pushToOutput);
                output.enqueue(pushToOutput);
            }
            else if(Equ_Queue.frontDataType()=="c")            //meet an operator
            {
                Equ_Queue.dequeue(theOperator);

                if(theOperator == '(')                         //if it's '(', push it onto operator stack
                {
                   Ope_Stack.push(theOperator);

                }
                else if(theOperator == ')')                     //if it's ')', pop operators off the operator stack
                {                                              //and enqueue them to output queue until '(' is met
                    Ope_Stack.topData(tempOperator);          //pop the '(' off operator stack. If no '(' found, report error

                    while(tempOperator!='(' && !Ope_Stack.empty())
                    {
                        Ope_Stack.pop(tempOperator);
                        output.enqueue(tempOperator);

                        if(!Ope_Stack.empty())
                            Ope_Stack.topData(tempOperator);
                    }

                    if(Ope_Stack.empty())
                    {
                        //cout << "no left parenthesis was found, the format of the equation is invalid."<<endl;
                        throw NO_LEFT_PAREN;
                    }
                    else                 //the top node of the operator stack should be '(' now
                    {
                        Ope_Stack.pop(tempOperator);
                    }
                }
                else if(theOperator == '+' || theOperator == '-'|| theOperator == '*' || theOperator == '/' || theOperator == '^')//meet an operator +-*/^
                {

                    if(!Ope_Stack.empty())
                    {
                        Ope_Stack.topData(tempOperator2);

                        char holdOpe=theOperator;

                        while((!Ope_Stack.empty())&&(precedence(holdOpe)!=4))//&&(precedence(theOperator)<=precedence(tempOperator2)))
                        {
                            if(precedence(theOperator)<=precedence(tempOperator2))
                            {
                                Ope_Stack.pop(tempOperator2);

                                output.enqueue(tempOperator2);


                                if(!Ope_Stack.empty())
                                {
                                    Ope_Stack.topData(tempOperator2);
                                }
                            }
                            else
                            {
                                holdOpe='^';  //precedence will return 0, force the while loop to end
                            }
                        }
                        Ope_Stack.push(theOperator);

                    }

                    else
                    {
                        Ope_Stack.push(theOperator);
                    }

                }

            }
        }

        while(!Ope_Stack.empty())             //if there are still operators on the stack, pop them onto output queue
        {
            Ope_Stack.topData(tempOperator);
            if(tempOperator=='(' || tempOperator ==')')
            {
                //cout << "there are mismatched parenthesis"<<endl;
                throw MIS_MATCH_PATHEN;
            }
            else
            {
                Ope_Stack.pop(tempOperator);
                output.enqueue(tempOperator);
            }
        }

        //cout << "Converted to RPN, output ";
        //output.show();
    }
    catch(ERRORS e)
    {
        //cout << "In toRPN(), error received" <<endl;
        throw e;
    }


}



int Parsing::precedence(char c)
{
    if(c=='^')
        return 4;
    else if(c=='*' || c=='/')
        return 3;
    else if(c=='+' || c=='-')
        return 2;
    else
        return 0;
}

string Parsing::calc()
{
    try
    {
        while(!output.empty())
        {
            if(output.frontDataType() == "5Mixed")
            {
                Mixed temp;
                output.dequeue(temp);
                Cal_Stack.push(temp);
            }
            else
            {
                Mixed left, right, ans;
                char tempChar;
                Cal_Stack.pop(right);
                Cal_Stack.pop(left);
                output.dequeue(tempChar);

                switch(tempChar)
                {
                case '+':
                    ans = left + right;
                    Cal_Stack.push(ans);
                    break;
                case '-':
                    ans = left - right;
                    Cal_Stack.push(ans);
                    break;
                case '*':
                    ans = left * right;
                    Cal_Stack.push(ans);
                    break;
                case '/':
                    ans = left / right;
                    Cal_Stack.push(ans);
                    break;
                case '^':
                    ans = left.toPow(right);
                    Cal_Stack.push(ans);
                    break;
                }
            }
        }

        stringstream ss;
        Mixed tempResult;
        string resultString;

        Cal_Stack.pop(tempResult);
        //cout<<  "the result of the equation: "  <<tempResult <<endl;

        if(tempResult.getWhole())
        {
            if(tempResult.getNum())
            {
                if(tempResult.getImag())
                    ss<<tempResult.getWhole()<<" "<<tempResult.getNum()<<"i/"<<tempResult.getDenom();
                else
                    ss<<tempResult.getWhole()<<" "<<tempResult.getNum()<<"/"<<tempResult.getDenom();
            }
            else
            {
                if(tempResult.getImag())
                    ss<<tempResult.getWhole()<<tempResult.getImag();
                else
                    ss<<tempResult.getWhole();
            }
        }
        else
        {
            if(tempResult.getNum())
            {
                if(tempResult.getImag())
                    ss<<tempResult.getNum()<<"i/"<<tempResult.getDenom();
                else
                    ss<<tempResult.getNum()<<"/"<<tempResult.getDenom();
            }
        }
        resultString = ss.str();
        return resultString;

    }
    catch(ERRORS e)
    {
        //cout <<endl << "In calc(), error received." <<endl;
        throw e;
    }

}




string Parsing::RPNstring()
{
    stringstream ss1;
    Mixed tempMx;
    char tempOp;
    string theRPNstr="";

    voidQueue output_copy;
    output_copy=output;


    try
    {
        while(!output_copy.empty())
        {
            if(output_copy.frontDataType()=="5Mixed")
            {
                output_copy.dequeue(tempMx);

                if(tempMx.getWhole())
                {
                    if(tempMx.getNum())
                    {
                        ss1<<" "<<tempMx.getWhole()<<" "<<tempMx.getNum()<<"/"<<tempMx.getDenom()<<" ";
                    }
                    else
                    {
                        ss1<<" "<<tempMx.getWhole()<<" ";
                    }
                }
                else
                {
                    if(tempMx.getNum())
                    {
                        ss1<<" "<<tempMx.getNum()<<"/"<<tempMx.getDenom()<<" ";
                    }
                }

                theRPNstr = ss1.str();
            }
            else if(output_copy.frontDataType()=="c")
            {
                output_copy.dequeue(tempOp);
                ss1<<tempOp;
            }
        }

        theRPNstr = ss1.str();

        return theRPNstr;
    }
    catch(ERRORS e)
    {
        //cout << endl << "In RPNString, error received." <<endl;
        throw e;
    }
}



#endif // PARSING_H
