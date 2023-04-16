void OLEDinit1(void);
// void OLEDinit(void);
void PAGE_fillorclear(unsigned char dat);
void OLED_showchar(unsigned char x,unsigned char y,unsigned char chr,unsigned char np,unsigned char clear);
void OLED_showstr(unsigned char x,unsigned char y,unsigned char *str,unsigned char np,unsigned char clear);
void OLED_showfir(unsigned char x,unsigned char y,unsigned int fir,unsigned char np,unsigned char clear);