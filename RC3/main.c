/*
 * main.c
 *
 * Created: 2/21/2020 1:37:18 PM
 * Author : Mohamed Tarek & ShehabEldeen Ehab

	Remote Control Main Program.
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// User-Defined Drivers.
#include "typedef.h"
#include "BIT_LVL.h"
#include "keypad.h"
#include "LCD.h"
#include "DIO.h"
#include "UART2.h"
#include "main project.h"

// List of Options
sint8 list=1;


// RC2
int main(void)
{
	uint8 password_status;
	// Self-Test Frame to send.
	uint8 self_test_t[2] = {0x00, 0x55};
		
	// LCD buffer
	char buffer[16];
		
	// Initiate drivers.
    LCD_voidInit();
	KEYPAD_voidInit();
	UART_voidInit();
	
	// List Control.
	uint8 option=1;
	uint8 n=1;
	
	// Send self test frame.
	 for(int i=0; i<2; i++)
	 {
		 UART_voidSendchar(self_test_t[i]);
		 _delay_ms(100);
	 } // for(int i=0; i<2; i++)
	 
	 // Wait to Receive
	 while(UART_uint8RecChar() != 0x00);
	 
	 // Application Initiation GUI.
	 LCD_voidSendCommand(0x80);
	 LCD_voidSendString("Welcome");
	 _delay_ms(1000);
	  
	  // Check Password (Send it to main unit).
	 
	 while (1)
	 {
		UART_SendPassword();
		//LCD_voidSendCommand(0x0E);
		password_status = UART_uint8RecChar();
	  
	  if (password_status == 0x00)
		{
			
			LCD_voidSendCommand(0x01);
			LCD_voidSendCommand(0x80);
			LCD_voidSendString("true password");
			_delay_ms(1000);
			LCD_voidSendCommand(0x01);
			//h=1;
			
			// Break and go to main list.
			break;
		} //  if (password_status == 0x00)
		
		else if (password_status == 0x01)
		{
			
			LCD_voidSendCommand(0x01);
			LCD_voidSendCommand(0x80);
			LCD_voidSendString("wrong password");
			_delay_ms(1000);
			//LCD_voidSendCommand(0xC0);
			
			
			//LCD_voidSendString("try again");
			//_delay_ms(1000);
			//h=1;
			LCD_voidSendCommand(0x01);
		
		} // else if (password_status == 0x01)
	 } // While(1) -> UART_sendPassword.
	
    while (1) 
    {	
		// Display of List of options.
		RC_voidDisplayList();
		}	
   
	

}
// 
ISR(USART_RXC_vect)
{
	//DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH);
	_delay_ms(2);
		//DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW);
}

