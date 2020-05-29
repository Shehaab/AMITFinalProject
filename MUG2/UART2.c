/*
 * UART2.c
 *
 * Created: 5/13/2020 3:05:50 PM
 *  Author: Lenovo
 */ 


#include "std_types.h"
#include "bitwise.h"
#include <avr/io.h>
#include "UART2.h"

void UART_voidInit()
{
	CLR_BIT(UCSRA,1);
	CLR_BIT(UCSRA,0);
	
	SET_BIT(SREG,7);
	//ucsrb
	SET_BIT(UCSRB,7);
	CLR_BIT(UCSRB,6);
	CLR_BIT(UCSRB,5);
	SET_BIT(UCSRB,4);
	SET_BIT(UCSRB,3);
	CLR_BIT(UCSRB,2);
	
	//ucsrc
	/*SET_BIT(UCSRC,2);
	SET_BIT(UCSRC,1);
	CLR_BIT(UCSRC,6);
	CLR_BIT(UCSRC,5);
	CLR_BIT(UCSRC,4);
	CLR_BIT(UCSRC,3);*/
	UCSRC=0b10000110;
	
	UBRRH = 0x00;
	UBRRL = 51;
	
	
	
}


void UART_voidSendchar(uint8 x)
{
	while (GET_BIT(UCSRA,5)==0);
	UDR = x;
}


uint8 UART_uint8RecChar(void)
{
	uint8 Value;
	while (GET_BIT(UCSRA,7)==0);
	Value=UDR;
	return Value;
}