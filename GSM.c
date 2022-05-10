UART
#include<lpc214x.h>
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


GSM
#include <lpc214x.h>
#include "uartx_init.c"

unsigned char message_1[40] = "GSM program started uart initialised";
unsigned char AT_cmd[10] = "AT\r";
//voice call commands
unsigned char ATD_string[25] = "ATD8830017665;\r";  // call a person(dial a number)
unsigned char ATH_string[10] = "ATH0\r";  // disconnect the call
// SMS commands
unsigned char CMGF_string[10] = "AT+CMGF=1\r"; //format message
unsigned char CMGS_string[30] = "AT+CMGS =\"8830017665\"\r";   //sending message
unsigned char cntl_z = 0x1a;
unsigned char TEXT_string[40] = "Take classes offline, plss";
unsigned char rcv_byte;
unsigned char rcv_array[20];

void delay(unsigned int time)
{
	unsigned int i,j;										 
	for(i=0;i<time;i++)for(j=0;j<20000;j++);
}

int main()
{
	UART0_INIT();		
	UART1_INIT();       
	
	UART0_PutS(message_1);	

	
	while(1)
	{
		//TRANSMIT AT command
		UART1_PutS(AT_cmd);
        delay(10000);   // > 1 sec
		//TRANSMIT ATD command
		UART1_PutS(ATD_string);
        delay(30000);   // > 5 sec
		//TANSMIT ATH command
 		UART1_PutS(ATH_string);
        delay(3000);   // > 5 sec
		//SMS
		UART1_PutS(CMGF_string); // text mode 
        delay(10000);   // > 1 sec
        UART1_PutS(CMGS_string);
        delay(1000);   // > 2 sec   (actually we should wait
		//Actual message transmit
		UART1_PutS(TEXT_string);
        delay(10);   // > 5 sec
		UART1_PutChar(cntl_z);     // message terminating char
		break;
	}
}	
