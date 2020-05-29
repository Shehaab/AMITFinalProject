/*
 * UART2.c
 *
 * Created: 5/13/2020 3:05:50 PM
 *  Author: Lenovo
 */ 

#define F_CPU 8000000


#include "typedef.h"
#include "BIT_LVL.h"
#include <avr/io.h>
#include "UART2.h"
#include "keypad.h"
#include "LCD.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

uint8 st[6];

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

void UART_SendPassword(void)
{
	uint8 digits[6];
	uint8 count=0;		//to make sure password is 6 digits
	uint8 key;
	uint8 n=1;		//for wrong password trials
	uint8 h=0;
	
	//while (h==0)
	//{
		LCD_voidSendCommand(0x80);
		LCD_voidSendString("enter password:  ");
		LCD_voidSendCommand(0xC0);
		// prompt user to enter password and confirm
		while (1)
		{
			
			//key=0;
			key = KEYPAD_uint8GetKey();
			_delay_ms(80);
			//while (KEYPAD_uint8CheckPressed()==0);
			
			if(key=='#' &&  count==6  && key!=0xff)
			{
				count=0;
			
				UART_voidSendchar(0x01);
				_delay_ms(100);
				
				for (uint8 i=0;i<6;i++)
				{
					/*LCD_voidSendCommand(0x01);
					sprintf(st,"sending: %d",digits[i]);
					LCD_voidSendString(st);*/
					
					UART_voidSendchar(digits[i]);
					_delay_ms(100);
				}
				
				UART_voidSendchar(0x55);
				_delay_ms(100);
				
				//LCD_voidSendCommand(0x01);
				//LCD_voidSendString("sent");
				break;
			
			}
			
			else if (key!=0xff && key!='#')
			{
				
				
				if (key == '*')
				{
					_delay_ms(30);
					LCD_voidSendCommand(0x10);
					//key = 0;
					count--;
					key=0;
					continue;
				}
				else
				{
					_delay_ms(30);
					LCD_voidSendData('*');
					digits[count]=key;
					key=0;
					count++;
				}
		
			} // else if (key!=0xff && key!='#')
		}//while (1)
		
	//}//while (h==0)
}


/*ISR(USART_RXC_vect)
{
	LCD_voidSendCommand(0x80);
	LCD_voidSendString("received");
}*/