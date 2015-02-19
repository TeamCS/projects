#ifndef MIXED_H
#define MIXED_H
#include "fraction.h"
#include <sstream>

class Mixed : public Fraction
{
public:
    Mixed();
    Mixed(int numerator, int denominator = 1, int wholeNum = 0, bool imag = false);
    ~Mixed();
    Mixed(const Mixed &other);
    Mixed& operator =(const Mixed &other);
    Mixed toPow(const Mixed &powerOf);
    int getWhole();
    int getNum();
    int getDenom();
    bool getImag();

    friend Mixed operator +(const Mixed& left, const Mixed& right);
    friend Mixed operator -(const Mixed& left, const Mixed& right);
    friend Mixed operator *(const Mixed& left, const Mixed& right);
    friend Mixed operator /(const Mixed& left, const Mixed& right);
    friend ostream& operator <<(ostream& out, const Mixed& mix);
private:
    bool isImag;
};

Mixed::Mixed()
{
    num = 0;
    denom = 1;
    isImag = false;
}

Mixed::Mixed(int numerator, int denominator, int wholeNum, bool imag)
{
    num = numerator;
    if(denominator == 0)
        throw DIVIDE_BY_ZERO;

    if(wholeNum<0)
    {
        denom = denominator;
        wholeNum=-wholeNum;
        num += wholeNum*denom;
        num=-num;
    }
    else
    {
        denom = denominator;
        num += wholeNum*denom;
    }
    isImag = imag;
}

Mixed::~Mixed()
{
    //intentionally left blank
}

Mixed::Mixed(const Mixed &other)
{
    num = other.num;
    denom = other.denom;
    isImag = other.isImag;
}

Mixed& Mixed::operator =(const Mixed &other)
{
    if(this != &other)
    {
        num = other.num;
        denom = other.denom;
        isImag = other.isImag;
    }
    return *this;
}

int Mixed::getWhole()
{
    int returnWhole = 0;
    int tempNum = num;
    bool isNeg = false;

    if(tempNum < 0)
    {
        isNeg = true;
        tempNum = abs(tempNum);
    }

    returnWhole=tempNum/denom;


    if(returnWhole > 0 && isNeg)
        return 0-returnWhole;
    else
        return returnWhole;
}

int Mixed::getNum()
{
    int tempNum = num;

    if(tempNum < 0)
        tempNum = abs(tempNum);


    tempNum=tempNum%denom;


    if(abs(num) < denom && num < 0)
        return 0 - tempNum;
    else
        return tempNum;
}

int Mixed::getDenom()
{
    return denom;
}

bool Mixed::getImag()
{
    return isImag;
}

Mixed Mixed::toPow(const Mixed &powerOf)
{
    double power = static_cast<double>(powerOf.num) / static_cast<double>(powerOf.denom);
    //if(num < 0 && ((power > 0 && !(powerOf.denom % 2)) || (power < 0 && !(powerOf.num % 2))))//check for imaginary solution
    if(num < 0 && powerOf.denom != 1)//if there is possible imaginary
    {
        throw INVALID_EQU_FORMAT;
        //isImag = true;
        //num = -num;
    }
    double baseNum = static_cast<double>(num);
    double baseDenom = static_cast<double>(denom);
    double tempNum = pow(baseNum,power);
    double tempDenom = pow(baseDenom,power);
    double tempResult = tempNum / tempDenom;
    stringstream ss;
    string temp,result;
    ss<<tempResult;
    ss>>result;
    ss.clear();
    int resultWhole = 0, resultNum = 0, resultDenom = 1, decLength;
    bool isNeg = false;
    int pos = result.find('.');
    if(pos != -1)
    {
        if(result[0]=='-')
        {
            isNeg = true;
            temp = result.substr(1,pos);
            ss<<temp;
            ss>>resultWhole;
            ss.clear();
        }
        else
        {
            temp = result.substr(0,pos);
            ss<<temp;
            ss>>resultWhole;
            ss.clear();
        }
        temp = result.substr(pos+1,result.size());
        decLength = temp.size();
        stringstream ss1;//ss does not work but creating a new ss1 works
        ss1<<temp;
        ss1>>resultNum;
        ss1.clear();
        resultDenom = pow(10., static_cast<double>(decLength));
    }
    else
    {
        pos = 0;
        if(result[0]=='-')
        {
            isNeg = true;
            temp = result.substr(1);
            ss<<temp;
            ss>>resultWhole;
            ss.clear();
        }
        else
        {
            ss<<result;
            ss>>resultWhole;
            ss.clear();
        }
    }
    if(isNeg)
        resultWhole = -resultWhole;
    Mixed tempFrac(resultNum, resultDenom, resultWhole, isImag);
    return tempFrac;
}

ostream& operator <<(ostream& out,const Mixed& frac)
{
    int negflag=1;
    int tempNum = frac.num;
    int wholeNum = 0;

    if(frac.num<0)
    {
        tempNum=-tempNum;
        negflag=-1;
    }


    if(tempNum > frac.denom)
    {
        while(tempNum >= frac.denom)
        {
            tempNum -= frac.denom;
            wholeNum++;
        }
        if(tempNum==0)
        {
            if(negflag==-1)
                wholeNum=-wholeNum;

            cout<<wholeNum;
            if(frac.isImag)
                cout<<"i";
            return out;
        }
        else
        {
            if(negflag==-1)
                wholeNum=-wholeNum;
            cout<<wholeNum<<" "<<tempNum;
            if(frac.isImag)
                cout<<"i";
            cout<<"/"<<frac.denom;
            return out;
        }
    }
    else
    {
        if(abs(frac.num)==1 && frac.denom == 1)
        {
            cout << frac.num;
            if(frac.isImag)
                cout<<"i";
        }
        else
        {
            cout<<frac.num;
            if(frac.isImag)
                cout<<"i";
            cout<<"/"<<frac.denom;
        }
        return out;
    }
}

Mixed operator +(const Mixed& left, const Mixed& right)
{
    Mixed temp(right.num * left.denom + right.denom * left.num,
               left.denom * right.denom, left.isImag+right.isImag);
    return temp;
}

Mixed operator -(const Mixed& left, const Mixed& right)
{
    Mixed temp(right.denom* left.num - right.num * left.denom,
               left. denom * right.denom, left.isImag+right.isImag);
    return temp;
}

Mixed operator *(const Mixed& left, const Mixed& right)
{
    Mixed temp(left.num * right.num, left.denom * right.denom, left.isImag+right.isImag);
    return temp;
}

Mixed operator /(const Mixed& left, const Mixed& right)
{
    int makeNeg = 1;
    if(right.num < 0)
        makeNeg = -1;
    Mixed temp(left.num * right.denom, left.denom * right.num, left.isImag+right.isImag);
    return temp;
}

#endif // MIXED_H
