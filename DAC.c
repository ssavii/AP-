#include<lpc214x.h> 
void delay(unsigned int time) 
{ 
unsigned int i,j; 
for(i=0;i<time;i++) for(j=0;j<2000;j++); 
} 
int main() 
{ 
int i=0,value=0; 
PINSEL1=0x00080000; //OR 1<<19 ;P0.25 as DAC output 
while(1) 
{ 
for(i=0;i<1023;i=1+426) 
{
DACR=i<<6; 
} 
return 0; 
}
