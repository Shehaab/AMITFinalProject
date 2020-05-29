/*
 * keypad.c
 *
 * Created: 2/21/2020 1:37:55 PM
 *  Author: Lenovo
 */ 
#include "DIO.h"
#include "typedef.h"
#include "keypad.h"

#define F_CPU 8000000
#include <util/delay.h>


void KEYPAD_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN0,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_output);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_input);	
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN5,DIO_input);	
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN6,DIO_input);
	//DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_input);	
	
	/*DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);*/
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN6,DIO_HIGH);
	//DIO_voidSetPinValue(DIO_PORTC,DIO_PIN7,DIO_HIGH);
	
	
	
}


uint8 KEYPAD_uint8GetKey(void)
{
	uint8 buffer;
	//_delay_ms(2);
	//first row
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_LOW);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	
	
	buffer=0;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,DIO_PIN4);
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN5))<<1;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN6))<<2;
	//buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN7))<<3;
	switch (buffer)
	{
		case 6: return '1';
		break;
		case 5: return '2';
		break;
		case 3: return '3';
		break;
		/*case 7: return '+';
		break;*/
	}
	//_delay_ms(2);
	//second row
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_LOW);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	
	
	buffer=0;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,DIO_PIN4);
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN5))<<1;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN6))<<2;
	//buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN7))<<3;
	switch (buffer)
	{
		case 6: return '4';
		break;
		case 5: return '5';
		break;
		case 3: return '6';
		break;
		//case 7: return '-';
		//break;
	}
	//_delay_ms(2);
	//3rd row
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	
	
	buffer=0;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,DIO_PIN4);
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN5))<<1;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN6))<<2;
	//buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN7))<<3;
	switch (buffer)
	{
		case 6: return '7';
		break;
		case 5: return '8';
		break;
		case 3: return '9';
		break;
		//case 7: return '*';
		//break;
	}
	//_delay_ms(2);
	//4th row
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
	
	
	buffer=0;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,DIO_PIN4);
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN5))<<1;
	buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN6))<<2;
	//buffer|=DIO_uint8GetPinVlaue(DIO_PORTC,(DIO_PIN7))<<3;
	switch (buffer)
	{
		case 6: return '*';
		break;
		case 5: return '0';
		break;
		case 3: return '#';
		break;
		//case 7: return '/';
		//break;
	}
 return 0xff;	
}

uint8 KEYPAD_uint8CheckPressed(void)
{
	uint8 key=KEYPAD_uint8GetKey();
	if (key!=0xff)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}