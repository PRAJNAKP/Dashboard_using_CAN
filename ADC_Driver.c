#include"header.h"
#define DONE ((ADDR>>31)&1)


void adc_init(void)
{
PINSEL1|=0x15400000;  //configure P0.27 to P0.30 as analog pins
ADCR=0x00200400;
}


unsigned int adc_read(unsigned char ch_num)
{
unsigned int result=0;
ADCR|=(1<<ch_num);
ADCR|=(1<<24);
while(DONE==0);
ADCR^=(1<<24);
ADCR^=(1<<ch_num);
result=(ADDR>>6)&0x3FF;
return result;
}

