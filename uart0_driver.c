/*uart driver*/
#include<LPC21xx.h>
#define RDR (U0LSR&1)
#define THRE ((U0LSR>>5)&1)

/*uart0_init() function*/
void uart0_init(unsigned short int baud)
{
unsigned short int pclk,a[]={15,60,30,15,15},result;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
U0LCR=0x83;
U0DLL=(result&0xFF);
U0DLM=((result>>8)&0xFF);
U0LCR=0x03;
PINSEL0|=5;
}
/*Transmit string using uart0*/
void uart0_tx_string(char *s)
{
	while(*s)
	{
		U0THR=*s;
		while(THRE==0);
		s++;
	}
}

/*Transmit data*/
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}


/*implimenting loop back*/
unsigned char uart0_rx(void)
{
	unsigned char r_data;
	while(RDR==0);
	r_data=U0RBR;
	U0THR=r_data;
	while(THRE==0);
	uart0_tx_string("\n\r");
	return r_data;
}


/*Transmit ascii*/
void uart0_tx_ascii(unsigned char data)
{
	int i=0;
	unsigned char asci[3];
	uart0_tx_string("ASCII: ");
	for(i=0;data;data=data/10)
	{
		asci[i]=(data%10)+48;
		i++;
	}
	if(i==1)
	{
		asci[i]=48;
		asci[i+1]=48;
		i=2;
	}
	else if(i==2)
	{
		asci[i]=48;
	}
	else
	{
		i=i-1;
	}
	for(i;i>=0;i--)
	{
		U0THR=asci[i];
		while(THRE==0);
	}
	uart0_tx_string("\n\r");
}

/*Transmit hex*/
void uart0_tx_hex(unsigned char data)
{
	unsigned char hex[2];
	int i;
	uart0_tx_string("HEX: 0x");
	hex[0]=(data>>4)+48;
	hex[1]=(data&0x0F)+48;
	for(i=0;i<=1;i++)
	{
		U0THR=hex[i];
		while(THRE==0);
	}
	uart0_tx_string("\n\r");
}


void uart0_int_tx(unsigned int num)
{
	unsigned char res[10];
	int i=0,rem;
	for(;num;num=num/10)
	{
		res[i]=(num%10)+48;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		U0THR=res[i];
		while(THRE==0);
	}
}

void uart0_float_tx(float num)
{
	int temp;
	temp=num;
	uart0_int_tx(temp);
	uart0_tx('.');
	temp=(num-temp)*1000000;
	uart0_int_tx(temp);
}





		

		
		
	
		