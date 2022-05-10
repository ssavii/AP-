#include "LPC214X.h"
void delay(unsigned int sec) //DELAY routine using TIMER 0
{
T0PR = 15000; //For delay of 1ms when Fosc is 15 MHz( PR = Fosc*delay)
T0TC = 0; //Timer Counter register increments when PC reaches its maximun
value as specified by PR
T0TCR = 0X01;
while(T0TC < sec);
T0TCR = 0X00;
}
int main()
{
int i,j;
PINSEL2 = 0X00000000; //To set all pins as GPIO (P1.16 to P1.31)
IODIR1 = 0XFFFFFFFF; //To set all pins as OUTPUT
while(1)
{
IOSET1 = 0XAA000000; //To glow alternate LED'S from P1.24 to P1.31
delay(1000);
IOCLR1 = 0XAA000000; //To make alternate LED'S off from P1.24 to P1.31
delay(1000);
for(i=24;i<=31;i++)
{
IOSET1 = 1<<i;
delay(500);
IOCLR1 = 1<<i;
delay(500);
}
for(i=31;i>=24;i--)
{
IOSET1 = 1<<i;
delay(500);
IOCLR1 = 1<<i;
delay(500);
}

}

}
//PC = Prescalar counter register.
//increments on evrey PCLK
//When PC reaches value in PR ,PC is reset back to 0 and timer counter is incremented by
