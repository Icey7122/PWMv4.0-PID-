#include<STC12C5A60S2.H>
#include"used.h"


void PWMfreanddut(unsigned int freanddut,unsigned char dec,unsigned char FD)
{
    unsigned char PUB[] = {"S00000T"};
    unsigned char i = 0;

    PUB[1] += dec;
    PUB[2] = FD;
    
    for(i = 5; i >= 3; i--)
    {
        PUB[i] += (freanddut % 10);
        freanddut /= 10;
    }

    SendStr(PUB);
}