#include<LPC21xx.h>
#include"header.h"


void lcd_cmd(unsigned char cmd)
{
IOCLR1=0xFE<<16;
IOSET1=((cmd&0xf0)<<16);
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0xFE<<16;
IOSET1=((cmd&0x0f)<<20);
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}


void lcd_init()
{
IODIR1=0xFE<<16;
PINSEL2=0x0;
IOSET1=1<<19;	//clear previous data
lcd_cmd(0x02);  //Enable 4 bit mode
lcd_cmd(0x28);	//Double line enable
lcd_cmd(0x0e);	//Enable cursor
lcd_cmd(0x01);  //clear screen
}

void cgram_rightIndc(void)
{
unsigned char cg_ram[8]={0x10,0x18,0x1C,0x1E,0x1C,0x18,0x10,0x00};
int i;
lcd_cmd(0x48);
for(i=0;i<8;i++)
{
lcd_data(cg_ram[i]);
}
}

void cgram_leftIndc(void)
{
unsigned char cg_ram[8]={0x01,0x03,0x07,0x0F,0x07,0x03,0x01,0x00};
int i;
lcd_cmd(0x40);
for(i=0;i<8;i++)
{
lcd_data(cg_ram[i]);
}
}

void cgram_hl(void)
{
unsigned char cg_ram[8]={0x00,0x00,0x04,0x15,0x0E,0x1F,0x1F,0x00};
int i;
lcd_cmd(0x50);
for(i=0;i<8;i++)
{
lcd_data(cg_ram[i]);
}
}

void cgram_bA(void)
{
unsigned char cg_ram[8]={0x04,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x00};
int i;
lcd_cmd(0x58);
for(i=0;i<8;i++)
{
lcd_data(cg_ram[i]);
}
}

void cgram_bB(void)
{
unsigned char cg_ram[8]={0x04,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x00};
int i;
lcd_cmd(0x60);
for(i=0;i<8;i++)
{
lcd_data(cg_ram[i]);
}
}

void cgram_bC(void)
{
	unsigned char cg_ram[8]={0x04,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x00};
	int i;
	lcd_cmd(0x68);
	for(i=0;i<8;i++)
	{
		lcd_data(cg_ram[i]);
	}
}

void cgram_bD(void)
{
	unsigned char cg_ram[8]={0x04,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};
	int i;
	lcd_cmd(0x70);
	for(i=0;i<8;i++)
	{
		lcd_data(cg_ram[i]);
	}
}





void lcd_data(unsigned char data)
{
	IOCLR1=0xFE<<16;
	IOSET1=((data&0xf0)<<16);
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
	
	IOCLR1=0xFE<<16;
	IOSET1=((data&0x0f)<<20);
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
}

void lcd_string(unsigned char *ptr)
{
	while(*ptr)
	{
		lcd_data(*ptr++);
	
	}
}


void lcd_integer(int num)
{
	int a[10],i;
	if(num==0)
	{
		lcd_data('0');
	}
	if(num<0)
	{
		lcd_data('-');
		num=-num;
	}
	i=0;
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		lcd_data(a[i]);
	}
}





