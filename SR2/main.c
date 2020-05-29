/*
 * SR.c
 *
 * Created: 23-May-20 12:26:57 PM
 * Author : Mohamed Tarek & ShehabEldeen Ehab.
 */ 

#include <avr/io.h>
#include <stdio.h>

//#define F_CPU 8000000


#include <avr/interrupt.h>
#include "I2C_Slave_H_File.h"
#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"
#include "LCD.h"
#include "ADC.h"
#include "SendHelp.h"
#include "timer.h"
#include <util/delay.h>


#define slave_address_sr 0x20

uint8 secs = 0;
uint8 mins = 0;
uint8 hrs = 10;
uint8 days = 27;
uint8 months = 5;
uint8 years1 = 20;
uint8 years2 = 20;


// Sensor unit.
int main(void)
{
	// Enable timer.
	TIMER0_void_Init(64, 1);
	
   // Self-Test frame.
   uint8 frame_self_test[4] = {0xAA, 0x00, 0xAA^0x00, 0x55};
   uint8 frame_Rx[10];
   
   // Temperature values registers
   uint8 temp_0;
   uint8 temp_1;
   uint8 temp_2;
   
   // Frame Byte Number.
   uint8 byte_count = 0;
   
   // Buffer to hold data.
   //char buffer[10];
   
   // data buffer
   //uint8 data_Rx;
   
   // Slave-transmit status.
   int Ack_status;
   int packet_count = 0;
   
   // Initialize LCD and I2C interface.
   LCD_void_init();
   ADC_void_Init();
   I2C_Slave_Init(slave_address_sr);
   
    // Read values of Temperature sensors.
    //temp_0 = ADC_uint8_ReadInput(0);
    //temp_1 = ADC_uint8_ReadInput(1);
    //temp_2 = ADC_uint8_ReadInput(2);
	
	// A/C Temperatures.
	temp_0 = 11;
	temp_1 = 22;
	temp_2 = 33;
	
	//uint8 frame_Tx_ss[6] = {0xaa, 0x07, temp_0, temp_1, temp_2, 0x55};
   
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
				   /*sprintf(buffer, "Rx: %d            ", frame_Rx[byte_count]);
				   LCD_void_SendCommand(0xC0);
				   LCD_void_WriteString(buffer); */
				   byte_count++;
			   } while (frame_Rx[byte_count - 1] != 0x55);
			   
			   // Change Temperatures.
			   if(frame_Rx[1] == 0x07)
			   {
				   temp_0 = frame_Rx[2];
				   temp_1 = frame_Rx[3];
				   temp_2 = frame_Rx[4];
				   //_delay_ms(2000);
				   /*
				   sprintf(buffer, "%d, %d,  %d            ", temp_0, temp_1, temp_2);
				   LCD_void_SendCommand(0xC0);
				   LCD_void_WriteString(buffer); */
			   } // if(frame_Rx[1] == 0x07)
			   
			   else if(frame_Rx[0] == 0x05)
			    {
				    years1 = frame_Rx[1];
				    years2 = frame_Rx[2];
				    months = frame_Rx[3];
				    days = frame_Rx[4];
				    hrs = frame_Rx[5];
				    mins = frame_Rx[6];
				    secs = frame_Rx[7];
			    } // else if(frame_Rx[0] == 0x05) 
			   byte_count = 0;
			   //reset_buffer(frame_Rx);	
			   break;
			  
			  case 1:
			   LCD_void_SendCommand(0xC0);
			   LCD_void_WriteString("SLA+R + ACK     ");
			   
			   if(frame_Rx[1] == 0x08)
			   {
				 /* for(int i=0; i<6; i++)
				   {
					   Ack_status = I2C_Slave_Transmit(frame_Tx_ss[i]);
					   sprintf(buffer, "Status: %d        ", frame_Tx_ss[i]);
					   LCD_void_SendCommand(0xC0);
					   LCD_void_WriteString(buffer);
					   
				   } // for(int i=0; i<8; i++)
				 */
				 Ack_status = I2C_Slave_Transmit(0xaa);
				 Ack_status = I2C_Slave_Transmit(0x07);
				 Ack_status = I2C_Slave_Transmit(temp_0);
				 Ack_status = I2C_Slave_Transmit(temp_1);
				 Ack_status = I2C_Slave_Transmit(temp_2);
				 Ack_status = I2C_Slave_Transmit(0x55);
			   } // if(frame_Rx[1] == 0x08)
			   
			   // Take Calender Readings.
			    else if(frame_Rx[0] == 0x06)
			    {
					/*sprintf(buffer, "the secs is %d     ", secs);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer); */
					//TIMER0_void_DisableTimer();
				    Ack_status = I2C_Slave_Transmit(years1);
				    Ack_status = I2C_Slave_Transmit(years2);
				    Ack_status = I2C_Slave_Transmit(months);
				    Ack_status = I2C_Slave_Transmit(days);
				    Ack_status = I2C_Slave_Transmit(hrs);
				    Ack_status = I2C_Slave_Transmit(mins);
					Ack_status = I2C_Slave_Transmit(secs);
					//TIMER0_void_EnableTimer();
			    } // if(frame_Rx[0] == 0x06)
			   
			   // Send Self-Test.
			   else if(frame_Rx[1] == 0x00)
			   {
		   
				   do
				   {
					   Ack_status = I2C_Slave_Transmit(frame_self_test[packet_count]);
					   /*sprintf(buffer, "Status: %d        ", Ack_status);
					   LCD_void_SendCommand(0xC0);
					   LCD_void_WriteString(buffer); */
					   packet_count++;
			   
				   } while (Ack_status == 0);
				   packet_count = 0;
			   
			   } // else if(frame_Rx[1] == 0x00)
			   reset_buffer(frame_Rx);
			   break;
		   
		   default:
		   LCD_void_SendCommand(0xC0);
		   LCD_void_WriteString("Bad Interface.     ");
	   } // switch(I2C_Slave_Listen())
	   
	   
   } // While(1)
} // MAIN

