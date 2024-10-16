#include"header.h"
#define RIND ((IOPIN0>>15)&1)
#define LIND ((IOPIN0>>14)&1)
#define HL ((IOPIN0>>16)&1)
#define LEDL ((1<<17));

int gltflag=0;	//globaltimerflag
msg m;
int main()
{

	unsigned int tempr,btry;
	int linflag,rinflag,hlflag;
	IODIR0|=LEDL;
	IOSET0=LEDL;
	linflag=1;
	rinflag=1;
	hlflag=1;
can2_init();
adc_init();
config_timer1_for_VIC();
timer1_config();
uart0_init(115200);
uart0_tx_string("In Node A\r\n");
while(1)
{
	if(LIND==0)				//if left ind switch is pressed
	{
		while(LIND==0);
		IOCLR0=LEDL;
		m.id=0x311;
		m.dlc=2;
		m.rtr=0;
		if(linflag==1)
		{
			m.byteA=0x12;					//ON left indicator
			m.byteB=0;
			linflag=linflag^1;   //toggle the value to send alternate on and off data
		}
		else
		{
			m.byteA=0x13;				//OFF left indicator
			m.byteB=0;
			linflag=linflag^1;	//toggle the value to send alternate on and off data
		}
		can2_tx(m);
	}
	if(RIND==0)			//if right indicator switch is pressed
	{
		while(RIND==0); 
		m.id=0x312;
		m.dlc=2;
		m.rtr=0;
		if(rinflag==1)		//ON Right indicator
		{
			m.byteA=0x14;
			m.byteB=0;
			rinflag=rinflag^1;   //toggle the value to send alternate on and off data
		}
		else
		{
			m.byteA=0x15;		//OFF right indicator
			m.byteB=0;
			rinflag=rinflag^1;   //toggle the value to send alternate on and off data
		}
		can2_tx(m);
	}
	if(HL==0)
	{
		while(HL==0);
		m.id=0x310;
		m.dlc=2;
		m.rtr=0;
		if(hlflag==1)		//ON headlight 
		{
			m.byteA=0x10;
			m.byteB=0;
			hlflag=hlflag^1;   //toggle the value to send alternate on and off data
		}
		else
		{
			m.byteA=0x09;		//OFF headlight
			m.byteB=0;
			hlflag=hlflag^1;   //toggle the value to send alternate on and off data
		}
		can2_tx(m);
	}
	if(gltflag==1)
	{
		gltflag=0;
		btry=adc_read(2);  //read battery status
		tempr=adc_read(1); // tempo
		m.id=0x309;    //Battery status data frame
		m.dlc=2;
		m.rtr=0;
		m.byteA=btry;
		m.byteB=0;
		can2_tx(m);
		m.id=0x308;    //Engine temperature status data frame
		m.dlc=2;
		m.rtr=0;
		m.byteA=tempr;
		m.byteB=0;
		can2_tx(m);	
	}
}
}