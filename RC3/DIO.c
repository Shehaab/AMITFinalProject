/*
 * DIO.c
 *
 * Created: 2/14/2020 11:21:42 AM
 *  Author: Lenovo
 */ 
#include "typedef.h"
#include "BIT_LVL.h"
#include <avr/io.h>
#include "DIO.h"

void DIO_voidSetPinDirection(uint8 port,uint8 pin,uint8 dir)
{
	switch (port)
	{
		case 0:
		if (dir==0)
		{
			CLR_BIT(DDRA,pin);
		}
		else
		{
			SET_BIT(DDRA,pin);
		}
		break;
		case 1:
		if (dir==0)
		{
			CLR_BIT(DDRB,pin);
		}
		else
		{
			SET_BIT(DDRB,pin);
		}
		case 2:
		if (dir==0)
		{
			CLR_BIT(DDRC,pin);
		}
		else
		{
			SET_BIT(DDRC,pin);
		}
		break;
		case 3:
		if (dir==0)
		{
			CLR_BIT(DDRD,pin);
		}
		else
		{
			SET_BIT(DDRD,pin);
		}
		break;
	}
}

void DIO_voidSetPinValue(uint8 port, uint8 pin, uint8 value)
{
	switch (port)
	{
		case 0:
		if (value==0)
		{
			CLR_BIT(PORTA,pin);
		}
		else
		{
			SET_BIT(PORTA,pin);
		}
		break;
		case 1:
		if (value==0)
		{
			CLR_BIT(PORTB,pin);
		}
		else
		{
			SET_BIT(PORTB,pin);
		}
		case 2:
		if (value==0)
		{
			CLR_BIT(PORTC,pin);
		}
		else
		{
			SET_BIT(PORTC,pin);
		}
		break;
		case 3:
		if (value==0)
		{
			CLR_BIT(PORTD,pin);
		}
		else
		{
			SET_BIT(PORTD,pin);
		}
		break;
	}	
}


uint8 DIO_uint8GetPinVlaue(uint8 port, uint8 pin)
{
	uint8 ReturnValue;
	switch (port)
	{
		case 0: ReturnValue=GET_BIT(PINA,pin);
		break;
		case 1:ReturnValue=GET_BIT(PINB,pin);
		break;
		case 2: ReturnValue=GET_BIT(PINC,pin);
		break;
		case 3: ReturnValue=GET_BIT(PIND,pin);
		break;
	}
	return ReturnValue;
}


void DIO_voidTogglePin(uint8 port, uint8 pin)
{
	switch (port)
	{
		case 0: TOGGLE_BIT(PORTA,pin); 
		break;
		case 1:TOGGLE_BIT(PORTB,pin); 
		break;
		case 2:TOGGLE_BIT(PORTC,pin);
		break;
		case 3:TOGGLE_BIT(PORTD,pin); 
		break; 
		
	}
}