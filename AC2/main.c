/*
 * AC.c
 *
 * Created: 23-May-20 12:27:27 PM
 * Author : Mohamed Tarek & ShehabEldeen Ehab.
 */ 

#include <avr/io.h>
#include <stdio.h>


#include "I2C_Slave_H_File.h"
#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"
#include "LCD.h"
#include "SendHelp.h"

#define slave_address_ac 0x30

// Actuator unit.
int main(void)
{
	// Self-Test frame.
	uint8 frame_self_test[4] = {0xAA, 0x00, 0xAA^0x00, 0x55};
	uint8 frame_Rx[10];
	
	// Port A - Pin 0,1,2,3 are outputs on LEDS.
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_0, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_1, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_2, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_3, DIO_OUTPUT);
	
	// LEDS are on by default (Doors are open).
	DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_0, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_1, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_2, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTA, DIO_PIN_3, DIO_HIGH);
	
	// Frame Byte Number.
	uint8 byte_count = 0;
	
	// Buffer to hold data.
	char buffer[10];
	
	// data buffer
	//uint8 data_Rx;
	
	// Slave-transmit status.
	int Ack_status;
	int packet_count = 0;
	
	// Initialize LCD and I2C interface.
	LCD_void_init();
	I2C_Slave_Init(slave_address_ac);
	
	LCD_void_SendCommand(0x80);
	LCD_void_WriteString("Slave:");
	
	while (1)
	{
		switch(I2C_Slave_Listen())
		{
			case 0:
				LCD_void_SendCommand(0xC0);
				LCD_void_WriteString("SLA+W, ACK sent");
			
				do
				{
					frame_Rx[byte_count] = I2C_Slave_Receive();
					sprintf(buffer, "Rx: %d            ", frame_Rx[byte_count]);
					LCD_void_SendCommand(0xC0);
					LCD_void_WriteString(buffer);
					byte_count++;
				} while (frame_Rx[byte_count - 1] != 0x55);
				
				// Open Door with id frame_Rx[3]
				if(frame_Rx[1] == 0x09)
				{
					// make sure that leds are on pin numbers  from 0 to 3.
					DIO_void_SetPinValue(DIO_PORTA, frame_Rx[2], DIO_HIGH);
				} // if frame_rx == 0x09
				
				// Close Door with id frame_Rx[3]
				else if (frame_Rx[1] == 0x0A)
				{
					DIO_void_SetPinValue(DIO_PORTA, frame_Rx[2], DIO_LOW);
				} // else if frame_rx == 0x0A
				
				byte_count = 0;
				reset_buffer(frame_Rx);
				break;
				
			case 1:
				LCD_void_SendCommand(0xC0);
				LCD_void_WriteString("SLA+R + ACK     ");
			
				do
				{
					// Something wrong happened @ the sender.
					if(packet_count == 4){
						LCD_void_SendCommand(0xC0);
						LCD_void_WriteString("Error while sending.");
					}
				
					Ack_status = I2C_Slave_Transmit(frame_self_test[packet_count]);
					sprintf(buffer, "Status: %d        ", Ack_status);
					LCD_void_SendCommand(0xC0);
					LCD_void_WriteString(buffer);
					packet_count++;
				
				} while (Ack_status == 0);
				packet_count = 0;
				break;
			
			default:
				LCD_void_SendCommand(0xC0);
				LCD_void_WriteString("Bad Interface.     ");
		} // switch(I2C_Slave_Listen())
		
		
	} // While(1)
} // Main

