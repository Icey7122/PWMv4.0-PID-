#include<STC12C5A60S2.H>


void UartInit(void)		//9600bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器时钟1T模式
	BRT = 0xB2;			//设置定时重载值
	AUXR |= 0x01;		//串口1使用独立波特率发射器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发射器
}



void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}


void SendStr(unsigned char *str)
{
    while(*str != '\0')
    {
        SendOneByte(*str);
        str++;
    }
}
