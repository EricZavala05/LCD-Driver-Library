/*
* LCD.h
*	Driver Functions for LCD
*
*	Creatrd on: 1/6/2019
*			Author: Eric Zavala
*/
#ifndef LCD_H
#define LCD_H


#include <stdint.h>
#include "stm32f446xx.h"


/************************************************************************************************************/
/*																																																					*/
/*															1. Macros for GPIO Pin Initialization 																			*/
/*																																																					*/
/************************************************************************************************************/

// pin numbers and ports to be used to transfer data from
// the mcu to the the data bus lines of the LCD
// change the pin and ports to use different pins
#define LCDDB0PIN 						0
#define LCDDB0PORT 						GPIOB

#define LCDDB1PIN 						1
#define LCDDB1PORT					  GPIOB

#define LCDDB2PIN 						5
#define LCDDB2PORT 						GPIOB

#define LCDDB3PIN 						6
#define LCDDB3PORT 						GPIOB

#define LCDDB4PIN 						8
#define LCDDB4PORT 						GPIOB

#define LCDDB5PIN 						9
#define LCDDB5PORT 						GPIOB

#define LCDDB6PIN 						10
#define LCDDB6PORT 						GPIOB

#define LCDDB7PIN 						12
#define LCDDB7PORT 						GPIOB

// pin number and port to be used to control the enable signal
#define LCD_ENABLE_PIN 				13
#define LCD_ENABLE_PORT 			GPIOB

// pin number and port to be used to control the read/write signal
#define LCD_READ_WRITE_PIN 		14
#define LCD_READ_WRITE_PORT 	GPIOB

// pin number and port to be used to control the register select signal
#define LCD_REG_SELECT_PIN 		15
#define LCD_REG_SELECT_PORT 	GPIOB

// commands for controlling the LCD display
#define LCD_CLEAR_DISPLAY	0x01
#define LCD_USE_ONE_LINE 0x37
#define LCD_USE_BOTH_LINES 0x3B
#define LCD_TURN_ON_DISPLAY_AND_BLINKY_CURSOR 0x0F
#define LCD_TURN_ON_DISPLAY_AND_CURSOR 0x0E
#define LCD_TURN_ON_DISPLAY_ONLY 0x0C
#define LCD_MOVE_ON_TO_NEXT_LINE 0xC0

/************************************************************************************************************/
/*																																																					*/
/*															2. Driver Exposed API																													*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Initializes the pins to be used for sending data to the LCD
	*	@retval	None 
**/
void LCDInitPins(void);

/**
	* @brief	Clears the LCD display, turns on the display and the blinky cursor. Turns on bottom line on display
	*	@retval	None 
**/
void LCDInitDisplay(void);

/**
	* @brief	Writes and displays a character on the LCD display
	*	@param	character	:	character to be displayed on the LCD
	*	@retval	None 
**/
void LCDSendCharacter(char character);

/**
	* @brief	Sends a command to the LCD to manipulate the display
	*	@param	character	:	command to be executed by the display
	*	@retval	None 
**/
void LCDSendCommand(char command);

/**
	* @brief	Writes and displays a string on the LCD display
	*	@param	*CharString	:	String to be displayed on the display
	*	@retval	None 
**/
void LCDSendCharacterString(char *CharString);

/**
	* @brief	Writes and displays an integer number on the LCD display
	*	@param	number	:	number to be displayed on the display
	*	@retval	None 
**/
void LCDSendNumber(uint32_t number);

/**
	* @brief	Sets the cursor to a specific location on the LCD 
	*	@param	x	:	position x units along the length of the display (0 - 15)
	*	@param	y	:	position y units along the height of the display (0 or 1)
	*	@retval	None 
**/
void LCDSetPosition(uint8_t x, uint8_t y);

#endif
