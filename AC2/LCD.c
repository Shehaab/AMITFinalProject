/*
 * LCD.c
 *
 * Created: 15-Feb-20 1:20:36 PM
 *  Author: shehab
 */ 

// After upper make an enable pulse, and after lower make a pulse.
#include "LCD.h"
// Does it defer if I defined F_CPU before or after the delay.h preprocessor?
#define F_CPU 8000000UL
#include <util/delay.h>

// Take a 8-bit command on 4 pins -> 4-bit mode.
void LCD_void_SendCommand(uint8 command)
{
	// Left 4-bit of the command.
	uint8 upper = command >> 4;
	
	// Right 4-bit of the command.
	uint8 lower = command & 0x0f;
	
	// Tell LCD_RS what is coming is a command, data direction is done in init() function.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_1, DIO_LOW);
	
	// Set LCD-E (enable) to zero until I put data.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
	
	// First PIN: D4 -> Take upper first bit(0/1) "this is the least significant bit".
	if (((upper >> 0) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_LOW);
	}
	
	// Second PIN: D5 -> Take upper second bit(0/1).
	if (((upper >> 1) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_LOW);
	}
	
	// Third PIN: D6 -> Take upper third bit(0/1).
	if (((upper >> 2) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_LOW);
	}
	
	// Fourth PIN: D7 -> Take upper fourth bit(0/1).
	if (((upper >> 3) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_LOW);
	}
	
	// Make an enable pulse-> Documentation.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);
	_delay_ms(2);
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);

	
	
	
	// First PIN: D4 -> Take upper first bit(0/1) "this is the least significant bit". -> for lower
	if (((lower >> 0) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_LOW);
	}
	
	// Second PIN: D5 -> Take upper second bit(0/1).
	if (((lower >> 1) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_LOW);
	}
	
	// Third PIN: D6 -> Take upper third bit(0/1).
	if (((lower >> 2) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_LOW);
	}
	
	// Fourth PIN: D7 -> Take upper fourth bit(0/1).
	if (((lower >> 3) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_LOW);
	}
	
	// Make an enable pulse-> Documentation.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);
	_delay_ms(2);
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
}

void LCD_void_SendData(uint8 data)
{
	// Left 4-bit of the command.
	uint8 upper = data >> 4;
	
	// Right 4-bit of the command.
	uint8 lower = data & 0x0f;
	
	// Tell LCD_RS what is coming is data, data direction is done in init() function.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_1, DIO_HIGH);
	
	// Set LCD-E (enable) to zero until I put data.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
	
	// First PIN: D4 -> Take upper first bit(0/1) "this is the least significant bit".
	if (((upper >> 0) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_LOW);
	}
	
	// Second PIN: D5 -> Take upper second bit(0/1).
	if (((upper >> 1) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_LOW);
	}
	
	// Third PIN: D6 -> Take upper third bit(0/1).
	if (((upper >> 2) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_LOW);
	}
	
	// Fourth PIN: D7 -> Take upper fourth bit(0/1).
	if (((upper >> 3) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_LOW);
	}

	// Read data when E is high, write data at the falling edge of E.
	
	// Make an enable pulse-> Documentation.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);
	_delay_ms(2);
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
	
	// First PIN: D4 -> Take upper first bit(0/1) "this is the least significant bit". -> for lower
	if (((lower >> 0) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_4, DIO_LOW);
	}
	
	// Second PIN: D5 -> Take upper second bit(0/1).
	if (((lower >> 1) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_5, DIO_LOW);
	}
	
	// Third PIN: D6 -> Take upper third bit(0/1).
	if (((lower >> 2) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_6, DIO_LOW);
	}
	
	// Fourth PIN: D7 -> Take upper fourth bit(0/1).
	if (((lower >> 3) & 0x01) == 1)
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_7, DIO_LOW);
	}
	
	// Make an enable pulse-> Documentation.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);
	_delay_ms(2);
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
}

void LCD_void_init()
{
	// Documentation: wait some time.
	_delay_ms(50);
	
	// Initialize D-pins
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_4, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_5, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_6, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_7, DIO_OUTPUT);
	//_delay_ms(100);
	
	// LCD-RS:PB1, LCD-W/R:PB2, LCD-E:PB3
	DIO_void_SetPinDirection(DIO_PORTB, DIO_PIN_1, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTB, DIO_PIN_2, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTB, DIO_PIN_3, DIO_OUTPUT);
	//_delay_ms(100);
	
	// Set the above control pins to zero to make sure everytHing is okay.
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_1, DIO_LOW);
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_2, DIO_LOW);  // <- High: Read Operation, Low: Write Operation
	DIO_void_SetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);
	//_delay_ms(100);
	
	// Return cursor home.
	LCD_void_SendCommand(0x02);
	_delay_ms(2);
	
	// 4-bit mode & 2-line display mode & 5x7 display mode.
	LCD_void_SendCommand(0x28);
	_delay_ms(2);
	
	// Display turn on & cursor off & cursor blink off.
	LCD_void_SendCommand(0x0C);
	_delay_ms(2);
	
	// Clear LCD.
	LCD_void_SendCommand(0x01);
	_delay_ms(2);
	/*
	
	// Then Why we made LCD_void_init() the last function we made?
	// to make the LCD work in a 4-bit mode.
	LCD_void_SendCommand(0x28);
	
	// Wait for the command to finish, it is 39us in doc, but make it bigger.
	_delay_ms(2);
	
	// Work display and work the cursor.
	LCD_void_SendCommand(0x0C);
	_delay_ms(2);
	
	// Clear display
	LCD_void_SendCommand(0x01);
	_delay_ms(2); 
	
	*/
}

void LCD_void_WriteString(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	LCD_void_SendData(a[i]);
}

void LCD_void_CustomCharacter(uint8 loc, uint8 *msg)
{
	uint8 i;
	
	if(loc<8)
	{
		// its 5 * 7 or 8, but we give 8 locations for 5 bit locations anyways.
		LCD_void_SendCommand(0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	                   /* Write 8 byte for generation of 1 character */
		LCD_void_SendData(msg[i]);
	}
}
