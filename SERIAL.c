TRANSMISSION AND TRANSMISSION RECEPTION : 
#include<lpc214x.h>

void uart_init()
{
	PINSEL0=0x00000005;
	U0LCR=0x83;
	U0FCR=0x07;
	U0DLL=0x62;
	U0DLM=0x00;
	U0LCR=0x03;
}

int main()
{
	unsigned char data[10],i;
	uart_init();
	for(i=0;data[i]!=’\0’;i++)
 {
     while(!(UOLSR & 0x20));
     UOTHR =data[i];
 }while(1);
return 0;
}
—--------------------------------------------------------------
#include<lpc214x.h>

void uart_init()
{
	PINSEL0=0x00000005;
	U0LCR=0x83;
	U0FCR=0x07;
	U0DLL=0x62;
	U0DLM=0x00;
	U0LCR=0x03;
}

int main()
{
	unsigned char i=0,data[10];
	uart_init();
	while(i<5)
	{
		while(!(U0LSR & 0x01));
		data[i]=U0RBR;
		i++;
	}
	i=0;
	while(i<5)
	{
		while(!(U0LSR & 0x20));
		U0THR=data[i];
		i++;
	}while(1);
	return 0;
}
