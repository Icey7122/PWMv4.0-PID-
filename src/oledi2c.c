#include<STC12C5A60S2.H>
#include<INTRINS.H>


typedef unsigned char uc8;


sbit SDA = P0^1;
sbit SCL = P0^0;


void IICstart()
{
    SDA = 1;
    SCL = 1;
    SDA = 0;
    SCL = 0;
}

void IICstop()
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}


void IICwrite(unsigned char dat)
{
    uc8 i = 0;

    SCL = 0;
    for(i = 0;i < 8; i++)
    {
        SDA = dat >> 7;
        dat <<= 1;

        SCL = 1;
        SCL = 0;
    }
    SCL = 1;
    SCL = 0;
}





