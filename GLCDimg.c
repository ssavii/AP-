#include<lpc214x.h>
#define LCD_PORT 0x00FF0000
#define EN 1<<31
#define RS 1<<27
#define CS1 1<<26
#define CS2 1<<25  
#define GRST 1<<30
#define RW 1<<24
#define LCD_SHIFT 16

unsigned char Cat[1024] ={
};

void delay(unsigned int time)//small delay
{
    unsigned int i,j;
    for(i=0;i<time;i++)for(j=0;j<10;j++);
}
 
void ldelay(unsigned int time)//long delay
{
    unsigned int i,j;
    for(i=0;i<time;i++)for(j=0;j<5000;j++);
}

void LCD_strobe()//generate ENABLE pulse
{   		 
    IO1SET = EN;
    delay(5);
    IO1CLR = EN;
    delay(5);
}

void GLCD_data(unsigned char ch)
{
    IO1CLR = LCD_PORT;
    IO1SET = ch<<LCD_SHIFT;
    IO1SET = RS;
    LCD_strobe();
}

void GLCD_cmd(unsigned char ch)
{
    IO1CLR = LCD_PORT;
    IO1SET = ch<<LCD_SHIFT;
    IO1CLR = RS;
    LCD_strobe();
}

void GLCD_init()
{
    int i;
    PINSEL0 = 0;//set pins as GPIO
    PINSEL1 = 0;
    PINSEL2 = 0;
	 IODIR1 = LCD_PORT | RS | EN | CS1 | CS2 | GRST | RW;//set pins as output
    IOSET1 = GRST | CS1 | CS2;
    IOCLR1 = RW | RS | EN;
	 for(i=0;i<10;i++)
    GLCD_cmd(0x3F);    //Display ON
    GLCD_cmd(0x40);    //Set Y address as 0 (range 0-63)
    GLCD_cmd(0xB8);    //Set X address as 0 (page address)    (range 0-7)
}

void GLCD_disp(unsigned char *temp1)//display routine
{
    int i,j;
    for(i=0;i<8;i++)
	 {
		 IO1SET = CS1;//select controller 1
		 IO1CLR = CS2;  
		 GLCD_cmd(0xB8 | i);
   	 GLCD_cmd(0x40);
   	 for(j=0;j<64;j++)//display controller 1 data
   		 GLCD_data(temp1[(i*128)+j]);
   	 IO1CLR = CS1;//select controller 2
		 IO1SET = CS2;
		 GLCD_cmd(0xB8 | i);
   	 GLCD_cmd(0x40);
   	 for(j=64;j<128;j++)//display controller 2 data
   		 GLCD_data(temp1[(i*128)+j]);
	 }
}

int main()
{
	 GLCD_init();
	 GLCD_disp(Cat);
	 ldelay(4000);
}
