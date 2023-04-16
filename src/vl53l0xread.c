#include<STC12C5A60S2.H>
#include<INTRINS.H>
#include"vl53l0x.h"
// #include"oled.h"

void delay_ms(unsigned int time);	


unsigned char gbuf[16];
unsigned int Acnt,Scnt,Dist;
unsigned char DeviceRangeStatusInternal;


unsigned int Distance()
{
	unsigned char val = 0;	
	int cnt = 0;
    VL53L0X_write(VL53L0X_REG_SYSRANGE_START, 0x01);
    while (cnt < 100) 
    { 
        delay_ms(10);
        val = VL53L0X_read(VL53L0X_REG_RESULT_RANGE_STATUS);
        if (val & 0x01) 
        {
            break;
        }
        cnt++;
    }
    // if (val & 0x01) 
    // {
    //     OLED_showstr(0,4,"READ",1,0);
    // }
    // else 
    // {
    //     OLED_showstr(0,4,"NOT READ",1,0);
    // }
    gbuf[0]=VL53L0X_read(0x14);
    gbuf[11]=VL53L0X_read(0x14+11);
    gbuf[10]=VL53L0X_read(0x14+10);
    Dist = Makeint16(gbuf[11], gbuf[10]);
    DeviceRangeStatusInternal = ((gbuf[0] & 0x78) >> 3);
    if(DeviceRangeStatusInternal==11&&Dist>0&&Dist<2000)
    {
        return Dist;
    } 
    
    return Dist;
}

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 12;
	j = 168;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(unsigned int time)
{
    unsigned int i;
    for(i=1; i<=time; i++)
    {
        Delay1ms();
    }

}