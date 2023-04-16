#include<MATH.H>
#include"oled.h"
#include"distance.h"
#include"pwmcontrol.h"



void delay_ms(unsigned int time);


unsigned int dis = 0;
int u = 0,e = 0;
double k = 0.2,kd = 0,ki = 0;


void Pcontroller(unsigned int aim)
{
    dis = Distance();
    
    OLED_showfir(0,0,dis,1,0);

    e = aim - dis;
    OLED_showfir(0,2,abs(e),1,0);

    u = e*k;
    OLED_showfir(0,4,abs(u),1,0);

    if(u > 100)
    {
        u = 100;
    }
    else if(u < -100)
    {
        u = -100;
    }

    if(u >= 0)
    {
        PWMfreanddut(u,1,'D');
        delay_ms(50);
        PWMfreanddut(0,2,'D');
        delay_ms(50);
    }
    else if(u < 0)
    {
        PWMfreanddut(abs(u),2,'D');
        delay_ms(50);
        PWMfreanddut(0,1,'D');
        delay_ms(50);        
    }

}