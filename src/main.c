#include<STC12C5A60S2.H>
#include<INTRINS.H>
#include"used.h"
#include"oled.h"
#include"distance.h"
#include"pwmcontrol.h"
#include"controller.h"





void delay_ms(unsigned int time);


void main()
{
    unsigned int i = 0;
    unsigned int dis = 0;

    UartInit();
    OLEDinit1();
    PAGE_fillorclear(0);

    PWMfreanddut(320,1,'F');
    PWMfreanddut(320,2,'F');

    while(1)
    {
        // dis = Distance();
        // OLED_showfir(0,0,dis,1,0);
        // dis = Distance();
        // if(dis > 500)
        // {
        //     PWMfreanddut(0,2,'D');
        //     delay_ms(40);
        //     PWMfreanddut(50,1,'D');
        //     delay_ms(40);
        // }
        // else
        // {
        //     PWMfreanddut(0,1,'D');
        //     delay_ms(40);
        //     PWMfreanddut(50,2,'D');
        //     delay_ms(40);
        // }
        Pcontroller(300);

    };
}
