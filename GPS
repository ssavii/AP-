UART
//#include<lpc214x.h>
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

unsigned char UART1_GetChar(void)
{
	while(!(U1LSR & 0x01));
	return(U1RBR);
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

void UART1_INIT()
{
	PINSEL0 = 0x00050005;
	U1FCR = 0x07;
	U1LCR = 0x83;
	U1DLL = 0X62;
	U1DLM = 0X00;
	U1LCR = 0x03;
}
unsigned char UART1_PutChar(unsigned char Ch)
{
	while(!(U1LSR & 0x20));
	if(Ch=='\n')
	Ch = 0x0D;
	U1THR = Ch;
	return Ch;
}
void UART1_PutS(unsigned char *Ch)
{
	while(*Ch)
	UART1_PutChar(*Ch++);
}
void UART0_PutS(unsigned char *ch)
{
 	while (*ch)
 	UART0_PutChar(*ch++);
}




GPS
#include <lpc214x.h>
#include <stdio.h>
#include <string.h>
#include "uart_program.c"

unsigned char message_1[40] = "GPS program started uart initialised";
unsigned char message_2[40] = "\nInvalid GPS string";
unsigned char Lat_string[20] = "\nLatitude =";
unsigned char Long_string[20] = "\nLongitude =";
unsigned char rcv_byte,count;
unsigned char rcv_array[30];

void delay(unsigned int time)
{
	unsigned int i,j;										 
	for(i=0;i<time;i++)for(j=0;j<5000;j++);
}


int main()
{ 
	UART0_INIT(); 
	UART1_INIT(); 
	UART0_PutS(message_1);
	while(1)
	{
		while(rcv_byte !='$')
	 	{	rcv_byte = UART1_GetChar();
			UART1_PutChar(rcv_byte);
	 	};

		rcv_byte = UART1_GetChar();   // 'G"
	 	UART1_PutChar(rcv_byte);

	 	rcv_byte = UART1_GetChar();   // 'P"
	 	UART1_PutChar(rcv_byte);

	 	rcv_byte = UART1_GetChar();   // 'R"
	 	UART1_PutChar(rcv_byte);

	 	if(rcv_byte == 'R')
	 	{	 
			for (count = 0; count < 14 ; count++)
			{	rcv_byte = UART1_GetChar();   // UTC time and ,
				UART1_PutChar(rcv_byte);
			};

			rcv_byte = UART1_GetChar();   // 'A / V" 19th character
			UART1_PutChar(rcv_byte); 

			if(rcv_byte =='V')
			{	UART0_PutS(message_2); }
			else
			{		
				rcv_byte = UART1_GetChar();			//','
				UART1_PutChar(rcv_byte);

				for (count = 0; count < 24 ; count++)
				{	rcv_byte = UART1_GetChar();   // UTC time and ,
					rcv_array[count] = rcv_byte;
					UART1_PutChar(rcv_byte);
				};
			
				UART0_PutS(Lat_string);	 
				for (count = 0; count < 11 ; count++)
				{	UART0_PutChar(rcv_array[count]);  };
			 
				UART0_PutS(Long_string);
				for (count = 12; count < 25 ; count++)
				{	UART0_PutChar(rcv_array[count]);  };
			}
		}
	}
}
