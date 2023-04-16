#include"charset.h"


typedef unsigned char uc8;
typedef unsigned int ui16;


void IICstart();
void IICstop();
void IICwrite(unsigned char dat);



/*
    This write is continuous data write 

    If you do this, you will have no choice to insert command,
    because the ssd1306 will recognize the number as data, not
    command.
*/
void OLEDwrite_data(unsigned char dat,unsigned char np)
{
	if(!np)
	{
		dat = ~dat;
	}
    IICstart();
    IICwrite(0x78);     
    IICwrite(0x40);
	IICwrite(dat);	
    IICstop();
}

/*
    Oh! 
    //I will write the command continuously;
    I can't do that
*/
void OLEDwrite_command(unsigned char cmd)
{
    IICstart();
    IICwrite(0x78);
    IICwrite(0x00);
    IICwrite(cmd);
    IICstop();
}



void PAGE_fillorclear(unsigned char dat)
{
	unsigned char m,n;
	for(m = 0;m < 8; m++)
	{
		OLEDwrite_command(0xB0+m);
		OLEDwrite_command(0x00); //((start <<4)>>4));
		OLEDwrite_command(0x10); //(start >> 4));
		for(n = 0;n < 128; n++)
		{
			OLEDwrite_data(dat,1);
		}
	}
}


void LOC_set(unsigned char x,unsigned char y)
{
	OLEDwrite_command(0xb0+y);
	OLEDwrite_command(x & 0x0f);
	OLEDwrite_command(0x10 | (x >> 4));
}

void OLED_on()
{
	OLEDwrite_command(0x8D);
	OLEDwrite_command(0x14);
	OLEDwrite_command(0xAF);
}

void OLED_off()
{
	OLEDwrite_command(0x8D);
	OLEDwrite_command(0x10);
	OLEDwrite_command(0xAE);
}


void OLED_showchar(unsigned char x,unsigned char y,unsigned char chr,unsigned char np,unsigned char clear)
{
	uc8 i,c;
	c = chr - ' ';
	if(clear)
	{
		LOC_set(x,y);
		for(i = 0;i < 8; i++)
		{
			OLEDwrite_data(0,np);
		}
		LOC_set(x,y+1);
		for(i = 0;i < 8; i++)
		{
			OLEDwrite_data(0,np);
		}
	}
	else
	{
		LOC_set(x,y);
		for(i = 0;i < 8; i++)
		{
			OLEDwrite_data(F8X16[c*16+i],np);
		}
		LOC_set(x,y+1);
		for(i = 0;i < 8; i++)
		{
			OLEDwrite_data(F8X16[c*16+i+8],np);
		}
	}


}

void OLED_showstr(unsigned char x,unsigned char y,unsigned char *str,unsigned char np,unsigned char clear)
{
	while(*str != '\0')
	{
		OLED_showchar(x,y,(*str),np,clear);
		x += 8;
		str++;

		if(x > 127)
		{
			y += 2;
			x = 0;
			if(y > 7)
			{
				y = 0;
			}
		}
	}
}

void OLED_showfir(unsigned char x,unsigned char y,unsigned int fir,unsigned char np,unsigned char clear)
{
	char i = 4;
	unsigned char a[6] = { 0 };

	for(i = 0;i <= 4; i++)
	{
		a[4-i] = (fir % 10) + 48;
		fir /= 10;
	}
	OLED_showstr(x,y,a,np,clear);
}


// void OLED_Clear(void)  
// {  
	
// 		OLEDwrite_command(0xb0+i);   
// 		OLEDwrite_command(0x00);      
// 		OLEDwrite_command(0x10);         
// 		OLEDwrite_data(0); 
// }


// void OLEDinit()
// {
// 	OLEDwrite_command(0xAE);

// 	OLEDwrite_command(0x20);
// 	OLEDwrite_command(0x10);

// 	OLEDwrite_command(0x00);	
// 	OLEDwrite_command(0x10);

// 	OLEDwrite_command(0x40);

// 	OLEDwrite_command(0x81);
// 	OLEDwrite_command(0xff);

// 	OLEDwrite_command(0xA0);

// 	OLEDwrite_command(0xA4);

// 	OLEDwrite_command(0xA6);

// 	OLEDwrite_command(0xA8);
// 	OLEDwrite_command(0x3F);

// 	OLEDwrite_command(0xB0);

// 	OLEDwrite_command(0xC0);

// 	OLEDwrite_command(0xD3);
// 	OLEDwrite_command(0x00);

// 	OLEDwrite_command(0xD5);
// 	OLEDwrite_command(0x80);

// 	OLEDwrite_command(0xD9);//Set Pre-Charge Period
// 	OLEDwrite_command(0xF1);//

// 	OLEDwrite_command(0xDA);//set com pin configuartion
// 	OLEDwrite_command(0x12);//

// 	OLEDwrite_command(0xDB);//set Vcomh
// 	OLEDwrite_command(0x30);//

// 	OLEDwrite_command(0x8D);//set charge pump enable
// 	OLEDwrite_command(0x14);//

// 	OLEDwrite_command(0xAF);

// }


void OLEDinit1(void)
{ 	
	OLEDwrite_command(0xAE);//--display off
	OLEDwrite_command(0x00);//---set low column address
	OLEDwrite_command(0x10);//---set high column address
	OLEDwrite_command(0x40);//--set start line address  
	OLEDwrite_command(0xB0);//--set page address
	OLEDwrite_command(0x81); // contract control
	OLEDwrite_command(0xFF);//--128   
	OLEDwrite_command(0xA1);//set segment remap 
	OLEDwrite_command(0xA6);//--normal / reverse
	OLEDwrite_command(0xA8);//--set multiplex ratio(1 to 64)
	OLEDwrite_command(0x3F);//--1/32 duty
	OLEDwrite_command(0xC8);//Com scan direction
	OLEDwrite_command(0xD3);//-set display offset
	OLEDwrite_command(0x00);//
	
	OLEDwrite_command(0xD5);//set osc division
	OLEDwrite_command(0x80);//
	
	OLEDwrite_command(0xD8);//set area color mode off
	OLEDwrite_command(0x05);//
	
	OLEDwrite_command(0xD9);//Set Pre-Charge Period
	OLEDwrite_command(0xF1);//
	
	OLEDwrite_command(0xDA);//set com pin configuartion
	OLEDwrite_command(0x12);//
	
	OLEDwrite_command(0xDB);//set Vcomh
	OLEDwrite_command(0x30);//
	
	OLEDwrite_command(0x8D);//set charge pump enable
	OLEDwrite_command(0x14);//
	
	OLEDwrite_command(0xAF);//--turn on oled panel
}  