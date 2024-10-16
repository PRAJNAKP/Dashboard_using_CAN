#include"header.h"
#define TCS ((C2GSR>>3)&1)
void can2_init(void)
{
PINSEL1|=0x14000;
VPBDIV=1;
AFMR=2;
C2MOD=1;
C2BTR=0x001C001D;
C2MOD=0;
}

void can2_tx(msg m)
{
C2TFI1=(m.dlc)<<16;
C2TID1=m.id;
if(m.rtr==0)
{
C2TDA1=m.byteA;
C2TDB1=m.byteB;
}
else
C2TFI1|=1<<30;
C2CMR=1|(1<<5);
while(TCS==0);
}
