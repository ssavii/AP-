#include <lpc214x.h>
#include "uart_add.c"

unsigned char msg1[25]="\nADC Value in HEX: ";
unsigned char msg2[20]="Uart Initialized\n";
unsigned char end[20]=" \r";
void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<5000;j++);
}

void adcinit()
{
	PINSEL1|=0x01000000;
	AD0CR=0x01200302;
}

int main()
{
	unsigned int data;
	unsigned char ascii[3],i,number;
	UART0_INIT();
	UART0_PutS(msg2);
	adcinit();
	while(1)
	{
		AD0CR=0x01200302;
		while((AD0DR1 & 0x80000000)!=0x80000000);

		UART0_PutS(msg1);
		data=(AD0DR1&0x0000FFC0)>>6;
		delay(100);
		ascii[2]=(data&0x0000000F);
		ascii[1]=(data&0x000000F0)>>4;
		ascii[0]=(data&0x00000F00)>>8;
		for(i=0;i<3;i++)
		{
			if(ascii[i]>=0 && ascii[i]<=9)
			{
				number=ascii[i]+0x30;
			}
			else if(ascii[i]>=0x0A && ascii[i]<=0x0F)
			{
				number=ascii[i]+0x37;
			}
			UART0_PutChar(number);
		}
		UART0_PutS(end);
	}
}

UART
unsigned char UART0_PutChar(unsigned char Ch)
{
	if(Ch=='\n')
	{
		while(!(U0LSR & 0x20));
		U0THR = 0x0D;
	}
	while(!(U0LSR & 0x20));
	return(U0THR = Ch);
}
void UART0_INIT()
{
	PINSEL0 |= 0x00000005;
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 0X62;
	U0DLM = 0X00;
	U0LCR = 0x03;
}
void UART0_PutS(unsigned char *ch)
{
	while (*ch)
 	UART0_PutChar(*ch++);
}
