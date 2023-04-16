#include<STC12C5A60S2.H>


#define VL53L0X_IIC_SDA P14
#define VL53L0X_IIC_SCL P16


void delay2us(void);


void VL53L0X_IIC_start()
{
    VL53L0X_IIC_SDA = 1;
    delay2us();

    VL53L0X_IIC_SCL = 1;
    delay2us();

    VL53L0X_IIC_SDA = 0;
    delay2us();

    VL53L0X_IIC_SCL = 0;
    delay2us();
}

void VL53L0X_IIC_stop()
{
    VL53L0X_IIC_SDA = 0;
    delay2us();

    VL53L0X_IIC_SCL = 1;
    delay2us();

    VL53L0X_IIC_SDA = 1;
    delay2us();
}


void VL53L0X_IIC_wait_ark()   
{
    unsigned char ark = 1;

    ark = VL53L0X_IIC_SDA;
    VL53L0X_IIC_SCL = 1;        
    delay2us();

    if(ark)
    {
        VL53L0X_IIC_SCL = 0;
        delay2us();
        
        VL53L0X_IIC_stop();     
    }

    VL53L0X_IIC_SCL = 0;
    delay2us();
}


void VL53L0X_IIC_write(unsigned char dat)
{
    unsigned char i = 0;

    for(i = 0;i < 8; i++)
    {
        VL53L0X_IIC_SDA = dat >> 7;
        dat <<= 1;

        VL53L0X_IIC_SCL = 1;
        delay2us();  
        VL53L0X_IIC_SCL = 0;
        delay2us();
    }

}

unsigned char VL53L0X_IIC_read()
{
    unsigned char i = 0;
    unsigned char dat = 0;

    for(i = 0;i < 8; i++)
    {
        dat <<= 1;
        dat |= VL53L0X_IIC_SDA;

        VL53L0X_IIC_SCL = 1;
        delay2us();  
        VL53L0X_IIC_SCL = 0;
        delay2us();
    }

    return dat;
}


void VL53L0X_write(unsigned char address,unsigned char dat)
{
    VL53L0X_IIC_start();

    VL53L0X_IIC_write(0x52);
    VL53L0X_IIC_wait_ark();

    VL53L0X_IIC_write(address);
    VL53L0X_IIC_wait_ark();

    VL53L0X_IIC_write(dat);
    VL53L0X_IIC_wait_ark();

    VL53L0X_IIC_stop();
}

unsigned char VL53L0X_read(unsigned char address)
{
    unsigned char dat = 0;

    VL53L0X_IIC_start();

    VL53L0X_IIC_write(0x52);
    VL53L0X_IIC_wait_ark();
    VL53L0X_IIC_write(address);
    VL53L0X_IIC_wait_ark();

    VL53L0X_IIC_stop();
    VL53L0X_IIC_start();

    VL53L0X_IIC_write(0x53);
    VL53L0X_IIC_wait_ark();
    dat = VL53L0X_IIC_read();
    VL53L0X_IIC_wait_ark();

    VL53L0X_IIC_stop();

    return dat;
}

int Makeint16(int lsb, int msb) 
{
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}



void delay2us(void)
{

}





