#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// uzduotyje nurodyta, jog skaiciaus skaitmenys
// saugomi  kaip 10^n pagrindo skaitmenys
#define RADIX 100

typedef struct Digit
{
    int value;
    struct Digit *next;

} Digit;

typedef struct BigInteger
{
    Digit *head;
    bool isNegative;

} BigInteger;

BigInteger *createBigInteger();
BigInteger *createBigIntegerFromString(char *str);
BigInteger *addTwoBigIntegers(BigInteger *first, BigInteger *second);
BigInteger *subtractTwoBigIntegers(BigInteger *first, BigInteger *second);
BigInteger *multiplyTwoBigIntegers(BigInteger *first, BigInteger *second);
BigInteger *createBigIntegerFromInt(int value);

// funkcija, kuri prideda skaiciu prie BigInteger
void appendDigit(BigInteger *num, int value);
int isZero(BigInteger *num);
void freeBigInteger(BigInteger *num);
void printBigInteger(BigInteger *num);
int compareBigIntegers(BigInteger *a, BigInteger *b);
int getLength(BigInteger *num);
BigInteger *copyBigInteger(BigInteger *original);
double bigIntegerToDouble(BigInteger *bigInt);
double divideBigIntegers(BigInteger *dividend, BigInteger *divisor);
#endif