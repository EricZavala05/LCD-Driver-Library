/*
* main.c
*	Testing Driver Functions for LCD
*
*	Creatrd on: 1/6/2019
*			Author: Eric Zavala
*/

#include <stdint.h>
#include "stm32f446xx.h"
#include "LCD.h"


typedef enum 
{
	Open, 
	Closed
}State; 

int main(void)
{
	RCC->AHB1ENR |= (1 << 1);
	
	LCDInitPins();

	LCDInitDisplay();
	
	
	
	LCDSendCommand(0x40);
	LCDSendCharacter(0x07);
	LCDSendCharacter(0x08);
	LCDSendCharacter(0x13);
	LCDSendCharacter(0x14);
	LCDSendCharacter(0x13);
	LCDSendCharacter(0x08);
	LCDSendCharacter(0x07);
	LCDSendCharacter(0x00);
	
	LCDSendCharacter(0x00);
	LCDSendCharacter(0x10);
	LCDSendCharacter(0x00);
	LCDSendCharacter(0x00);
	LCDSendCharacter(0x00);
	LCDSendCharacter(0x10);
	LCDSendCharacter(0x00);
	LCDSendCharacter(0x00);
	
	LCDSendCharacter(0x0E);
	LCDSendCharacter(0x1F);
	LCDSendCharacter(0x15);
	LCDSendCharacter(0x1F);
	LCDSendCharacter(0x1F);
	LCDSendCharacter(0x1F);
	LCDSendCharacter(0x0A);
	LCDSendCharacter(0x00);
	
	for(int i = 0; i < 16; i++)
	{	
		LCDSendCommand(LCD_CLEAR_DISPLAY);
		LCDSetPosition(i,1);
		LCDSendCharacter(0x00);
		LCDSendCharacter(0x01);
		
		LCDSetPosition(i+3,1);
		LCDSendCharacter(0x02);
	}
	
	
	// use sprintf to print numbers
	while(1)
	{}
		

}
