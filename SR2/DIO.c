/*
 * DIO.c
 *
 * Created: 14-Feb-20 11:21:03 AM
 *  Author: Shehab
 */ 
#include "std_types.h"
#include "bitwise.h"
#include <avr/io.h>
#include "DIO.h"

// Set pin direction (INPUT/OUTPUT).
void DIO_void_SetPinDirection(uint8 port, uint8 pin, uint8 dir)
{
	switch(port){
		
		// Port A 
		case 0:
			// pin is input.
			if(dir == 0)
			{
				CLR_BIT(DDRA, pin);
			}
			
			// pin is output.
			else
			{
				SET_BIT(DDRA, pin);
			}
			break;
		
		// Port B
		case 1:
			if(dir == 0)
			{
				CLR_BIT(DDRB, pin);
			}
			else
			{
				SET_BIT(DDRB, pin);
			}
			break;
		
		// Port C
		case 2:
			if(dir == 0)
			{
				CLR_BIT(DDRC, pin);
			}
			else
			{
				SET_BIT(DDRC, pin);
			}
			break;
		
		// Port D
		case 3:
			if(dir == 0)
			{
				CLR_BIT(DDRD, pin);
			}
			else
			{
				SET_BIT(DDRD, pin);
			}
			break;
	}
}

// Set pin voltage (O VOLTS / 5 VOLTS).
void DIO_void_SetPinValue(uint8 port, uint8 pin, uint8 value)
{
	switch(port){
		
		// Port A
		case 0:
		// pin is 0 volts.
		if(value == 0)
		{
			CLR_BIT(PORTA, pin);
		}
		
		// pin is 5 volts.
		else
		{
			SET_BIT(PORTA, pin);
		}
		break;
		
		// Port B
		case 1:
		if(value == 0)
		{
			CLR_BIT(PORTB, pin);
		}
		else
		{
			SET_BIT(PORTB, pin);
		}
		break;
		
		// Port C
		case 2:
		if(value == 0)
		{
			CLR_BIT(PORTC, pin);
		}
		else
		{
			SET_BIT(PORTC, pin);
		}
		break;
		
		// Port D
		case 3:
		if(value == 0)
		{
			CLR_BIT(PORTD, pin);
		}
		else
		{
			SET_BIT(PORTD, pin);
		}
		break;
	}
}

uint8 DIO_uint8_GetPinValue(uint8 port, uint8 pin)
{
	// Holds pin state
	uint8 ReturnValue;
	
	switch(port)
	{
		// Port A
		case 0:
		ReturnValue = GET_BIT(PINA, pin);
		break;
		// Port B
		case 1:
		ReturnValue = GET_BIT(PINB, pin);
		break;
		// Port C
		case 2:
		ReturnValue = GET_BIT(PINC, pin);
		break;
		// Port D
		case 3:
		ReturnValue = GET_BIT(PIND, pin);
		break;
	}
	
	return ReturnValue;
}

void DIO_void_TogglePin(uint8 port, uint8 pin)
{
	switch(port){
		case 0:
			TOGGLE_BIT(PORTA, pin);
			break;
		case 1:
			TOGGLE_BIT(PORTB, pin);
			break;
		case 2:
			TOGGLE_BIT(PORTC, pin);
			break;
		case 3:
			TOGGLE_BIT(PORTD, pin);
			break;
	}
}
