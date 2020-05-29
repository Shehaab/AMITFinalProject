/*
 * LCD.c
 *
 * Created: 2/15/2020 1:33:19 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8000000
#include <util/delay.h>

#include "typedef.h"
#include "DIO.h"

void LCD_voidSendCommand(uint8 command)
{
	uint8 upper=command>>4;
	uint8 lower=command&0x0F;
	
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN1,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN2,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_output);
	
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN1,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	if ((upper & 0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
	}
	if (((upper>>1)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_LOW);
	}
	if (((upper>>2)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_LOW);
	}
	if (((upper>>3)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_LOW);
	}
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	
	if (((lower>>0)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
	}
	if (((lower>>1)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_LOW);
	}
	if (((lower>>2)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_LOW);
	}
	if (((lower>>3)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_LOW);
	}
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	
}


void LCD_voidSendData(uint8 data)
{
	uint8 upper=data>>4;
	uint8 lower=data&0x0F;
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN1,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	if ((upper & 0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
	}
	if (((upper>>1)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_LOW);
	}
	if (((upper>>2)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_LOW);
	}
	if (((upper>>3)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_LOW);
	}
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	
	if (((lower>>0)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
	}
	if (((lower>>1)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN5,DIO_LOW);
	}
	if (((lower>>2)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN6,DIO_LOW);
	}
	if (((lower>>3)&0x01)==1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);
	}
	else
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_LOW);
	}
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	
}


void LCD_voidInit()
{
	_delay_ms(50);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN4,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN5,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN6,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN7,DIO_output);
	
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN1,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN2,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_output);
	
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN1,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN2,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
	
	/*LCD_voidSendCommand(0x28);
	_delay_ms(2);
	LCD_voidSendCommand(0x0C);
	_delay_ms(2);
	LCD_voidSendCommand(0x01);
	_delay_ms(2);*/
	
	/*LCD_voidSendCommand(0x03);
	_delay_ms(5);
	LCD_voidSendCommand(0x03);
	_delay_ms(11);
	LCD_voidSendCommand(0x03);*/
	
	//LCD_voidSendCommand(0x38);
	
	// return home.
	//LCD_voidSendCommand(0x02);
	//LCD_voidSendCommand(0x02);
	//LCD_voidSendCommand(0x80);
	//LCD_voidSendCommand (0x01);
	// display off cursor off, don't clear ddram.
	//LCD_voidSendCommand(0x08);
	
	//LCD_voidSendCommand(0x00);
	
	// Display on, cursor off.
	//LCD_voidSendCommand(0x0C);
	
	//LCD_voidSendCommand(0x00);
	
	
	//LCD_voidSendCommand (0x38);								/* Initialize 16X2 LCD in 8bit mode */
	//LCD_voidSendCommand (0x0C);								/* Display ON, Cursor OFF command */
	//LCD_voidSendCommand (0x06);								/* Auto Increment cursor */
	//LCD_voidSendCommand (0x01);								/* Clear LCD command */
	//LCD_voidSendCommand (0x80);								/* 8 is for first line and 0 is for 0th position */
	
	
	LCD_voidSendCommand(0x02);
	_delay_ms(2);
	
	// 4-bit mode & 2-line display mode & 5x7 display mode.
	LCD_voidSendCommand(0x28);
	_delay_ms(2);
	
	// Display turn on & cursor off & cursor blink off.
	LCD_voidSendCommand(0x0C);
	_delay_ms(2);
	
	// Clear LCD.
	LCD_voidSendCommand(0x01);
	_delay_ms(2);
	
	LCD_voidSendCommand(0x0F);
	_delay_ms(2);
}


void LCD_voidSendString(uint8 arr[])
{
	uint8 i=0;
	for (i=0;arr[i]!='\0';i++)
	{
		LCD_voidSendData(arr[i]);
	}
}