#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include "include.h"
#include <cmath>

using namespace std;


class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominator = 1);
    ~Fraction();
    Fraction(const Fraction &other);
    Fraction& operator=(const Fraction &other);
    int getNum(); //return numerator
    int getDenom(); //returns denominator
    void reduce(); //reduces fractions
    int GCD(int p, int q); //returns GCD of fraction p/q
    Fraction toPow(Fraction powerOf);//Fraction to power of fraction

    friend Fraction operator +(const Fraction& left, const Fraction& right);
    friend Fraction operator -(const Fraction& left, const Fraction& right);
    friend Fraction operator *(const Fraction& left, const Fraction& right);
    friend Fraction operator /(const Fraction& left, const Fraction& right);
    friend ostream& operator <<(ostream& out, const Fraction& frac);
protected:
    int num, denom;
    bool isNeg;
};

Fraction::Fraction()
{
    num = 0;
    denom = 1;
}

Fraction::Fraction(int numerator, int denominator)
{
    num = numerator;
    if(num < 0)
    {
        isNeg = !isNeg;
        num = abs(num);
    }
    if(denominator == 0)
        throw DIVIDE_BY_ZERO;
    denom = denominator;
    reduce();
}

Fraction::~Fraction()
{
    //intentionally left blank
}

Fraction::Fraction(const Fraction &other)
{
    num = other.num;
    denom = other.denom;
}

Fraction& Fraction::operator =(const Fraction &other)
{
    if(this != &other)
    {
        num = other.num;
        denom = other.denom;
    }
    return *this;
}

int Fraction::getNum()
{
    return num;
}

int Fraction::getDenom()
{
    return denom;
}

void Fraction::reduce()
{
    int greatCommonDenom = GCD(num, denom);
    num = num / greatCommonDenom;
    denom = denom/ greatCommonDenom;
}

int Fraction::GCD(int p, int q)
{
    if(p<0)
        p=-p;
    return q == 0 ? p : GCD(q, p % q);
}

Fraction operator +(const Fraction& left, const Fraction& right)
{
    Fraction temp(right.num * left.denom + right.denom * left.num, left.denom * right.denom);
    return temp;
}

Fraction operator -(const Fraction& left, const Fraction& right)
{
    Fraction temp(right.denom* left.num - right.num * left.denom, left. denom * right.denom);
    return temp;
}

Fraction operator *(const Fraction& left, const Fraction& right)
{
    Fraction temp(left.num * right.num, left.denom * right.denom);
    return temp;
}

Fraction operator /(const Fraction& left, const Fraction& right)
{
    int makeNeg = 1;
    if(right.num < 0)
        makeNeg = -1;
    Fraction temp(makeNeg * left.num * right.denom, abs(left.denom * right.num));
    return temp;
}

ostream& operator <<(ostream& out, const Fraction& frac)
{
    out<<frac.num<<"/"<<frac.denom;
    return out;
}

#endif // FRACTION_H
