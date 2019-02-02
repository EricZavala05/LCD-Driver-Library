







/*
* LCD.c
*	Driver Functions for LCD
*
*	Creatrd on: 1/6/2019
*			Author: Eric Zavala
*/
#include "LCD.h"
#include <stdio.h>

/************************************************************************************************************/
/*																																																					*/
/*															1. Static Helper Functions																											*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Configures the mode of a pin as output 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@retval	None 
**/
static void InitOuputPin(GPIO_TypeDef *GPIOx,uint16_t pin_no)
{
	GPIOx->MODER |= (0x01 << 2*pin_no);
	GPIOx->OTYPER &= ~(1 << pin_no);
	GPIOx->OSPEEDR |= (0x02 << 2*pin_no);
	GPIOx->PUPDR &= ~(0x03 << 2*pin_no);
}

/**
	* @brief	Sets the corresponding bit for the byte to be sent
	*						on the data bus line of the LCD
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	state		:	0 if pin is to be low, otherwise pin will be high
	*	@retval	None 
**/
static void SendBitToLCD(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t state)
{
	if (state)
	{
		GPIOx->ODR |= (1 << pin_no);
	}
	else 
	{
		GPIOx->ODR &= ~(1 << pin_no);
	}
}

/**
	* @brief	Sends a single character to the LCD 
	* @param	character	:	character to be displayed on the LCD
	*	@retval	None 
**/
static void SendByteToLCD(char character)
{
	SendBitToLCD(LCDDB0PORT,LCDDB0PIN, character & 0x01);
	SendBitToLCD(LCDDB1PORT,LCDDB1PIN, character & 0x02);
	SendBitToLCD(LCDDB2PORT,LCDDB2PIN, character & 0x04);
	SendBitToLCD(LCDDB3PORT,LCDDB3PIN, character & 0x08);
	SendBitToLCD(LCDDB4PORT,LCDDB4PIN, character & 0x10);
	SendBitToLCD(LCDDB5PORT,LCDDB5PIN, character & 0x20);
	SendBitToLCD(LCDDB6PORT,LCDDB6PIN, character & 0x40);
	SendBitToLCD(LCDDB7PORT,LCDDB7PIN, character & 0x80);
}

/**
	* @brief	Writes 1 to the specified pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@retval	None 
**/
static void WriteHigh(GPIO_TypeDef *GPIOx,uint16_t pin_no)
{
	GPIOx->ODR |= (1 << pin_no);
}

/**
	* @brief	Writes 0 to the specified pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@retval	None 
**/
static void WriteLow(GPIO_TypeDef *GPIOx,uint16_t pin_no)
{
	GPIOx->ODR &= ~(1 << pin_no);
}

void delay(uint32_t delay)
{
	volatile int i;
	for(i = 0; i < delay; i++)
	{
	}	
}
/************************************************************************************************************/
/*																																																					*/
/*															2. Driver Exposed API																													*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Initializes the pins to be used for sending data to the LCD
	*	@retval	None 
**/
void LCDInitPins(void)
{
	InitOuputPin(LCDDB0PORT,LCDDB0PIN);
	InitOuputPin(LCDDB1PORT,LCDDB1PIN);
	InitOuputPin(LCDDB2PORT,LCDDB2PIN);
	InitOuputPin(LCDDB3PORT,LCDDB3PIN);
	InitOuputPin(LCDDB4PORT,LCDDB4PIN);
	InitOuputPin(LCDDB5PORT,LCDDB5PIN);
	InitOuputPin(LCDDB6PORT,LCDDB6PIN);
	InitOuputPin(LCDDB7PORT,LCDDB7PIN);
	
	InitOuputPin(LCD_ENABLE_PORT,LCD_ENABLE_PIN);
	InitOuputPin(LCD_READ_WRITE_PORT,LCD_READ_WRITE_PIN);
	InitOuputPin(LCD_REG_SELECT_PORT,LCD_REG_SELECT_PIN);
}

/**
	* @brief	Clears the LCD display, turns on the display and the blinky cursor. Turns on bottom line on display
	*	@retval	None 
**/
void LCDInitDisplay(void)
{
	// clear the display
	LCDSendCommand(LCD_CLEAR_DISPLAY);
	// turn on display, cursor, and make cursor blink
	LCDSendCommand(LCD_TURN_ON_DISPLAY_ONLY);
	// Turn on both lines
	LCDSendCommand(LCD_USE_BOTH_LINES);
}


/**
	* @brief	Writes and displays a character on the LCD display
	*	@param	character	:	character to be displayed on the LCD
	*	@retval	None 
**/
void LCDSendCharacter(char character)
{
	// lcd set to write 
	WriteLow(LCD_READ_WRITE_PORT,LCD_READ_WRITE_PIN);
	
	// lcd character mode
	WriteHigh(LCD_REG_SELECT_PORT,LCD_REG_SELECT_PIN);
	
	// enable 
	delay(40000);
	WriteHigh(LCD_ENABLE_PORT,LCD_ENABLE_PIN);
	
	// send a character
	SendByteToLCD(character);
	
	
	delay(80000);
	WriteLow(LCD_ENABLE_PORT,LCD_ENABLE_PIN);
	
}

/**
	* @brief	Sends a command to the LCD to manipulate the display
	*	@param	character	:	command to be executed to by the display
	*	@retval	None 
**/
void LCDSendCommand(char command)
{
	// lcd set to write 
	WriteLow(LCD_READ_WRITE_PORT,LCD_READ_WRITE_PIN);
	
	// lcd command mode
	WriteLow(LCD_REG_SELECT_PORT,LCD_REG_SELECT_PIN);
	
	// enable 
	delay(40000);
	WriteHigh(LCD_ENABLE_PORT,LCD_ENABLE_PIN);
	
	// send a character
	SendByteToLCD(command);
	
	delay(80000);
	WriteLow(LCD_ENABLE_PORT,LCD_ENABLE_PIN);
	
}

/**
	* @brief	Writes and displays a string on the LCD display
	*	@param	*CharString	:	String to be displayed on the display
	*	@retval	None 
**/
void LCDSendCharacterString(char *CharString)
{
	while(*CharString != '\0')
	{
		LCDSendCharacter(*CharString++);
	}
}

/**
	* @brief	Writes and displays an integer number on the LCD display
	*	@param	number	:	number to be displayed on the display
	*	@retval	None 
**/
void LCDSendNumber(uint32_t number)
{
	
	int digits = 0;
	int num = number;
	// count the number of digits in the number to be printed
	while(num != 0)
	{
		num = num / 10;
		digits++;
	}
	char printNum[digits];
	sprintf(printNum,"%d",number);
	LCDSendCharacterString(printNum);
	
}

/**
	* @brief	Sets the cursor to a specific location on the LCD 
	*	@param	x	:	position x units along the length of the display (0 - 15)
	*	@param	y	:	position y uints along the height of the display (0 or 1)
	*	@retval	None 
**/
void LCDSetPosition(uint8_t x, uint8_t y)
{
	char location;
	if(y == 1)
	{
		location = 0x80;
		for(int i = 0; i <= x; i++)
		{
			location++;
		}
		LCDSendCommand(location);
	}
	if(y == 0)
	{
		location = 0xC0;
		for(int i = 0; i <= x; i++)
		{
			location++;
		}
		LCDSendCommand(location);
	}
}


