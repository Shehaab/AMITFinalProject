/*
 * MUG.c
 *
 * Created: 23-May-20 12:25:53 PM
 * Author : Mohamed Tarek & ShehabEldeen Ehab.
 */ 



#include <stdio.h>
#include <stdlib.h>
#include "I2C_Master_H_file.h"
#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"
#include "LCD.h"
#include "UART2.h"
//#include "timer.h"
#include "SendHelp.h"


#define slave_write_address_sr 0x20
#define slave_read_address_sr 0x21
#define slave_write_address_ac 0x30
#define slave_read_address_ac 0x31


uint8 secs = 0;
uint8 mins = 0;
uint8 hrs = 0;
uint8 days = 0;
uint8 months = 0;
uint8 years1 = 0;
uint8 years2 = 0;


// Main Unit.
int main(void)
{	
	// Initiate UART and LCD Drivers.
	UART_voidInit();
	LCD_void_init();
	
	
	// Password status flag
	uint8 pass_status = 0;
	
	// buffer for received frame, byte number in frame, and LCD buffer.
	uint8 frame_rx[10];
	uint8 count_bytes = 0;
	char buffer[16];
	
	// Current password used.
	uint8 current_password[6] = {'1', '1', '1', '1', '1', '1'};
		
	// Values for calender settings sent.
	uint8 calender_frame[7];
	
	// Pointer to  Received temperature sensors from sensor ECU.
	uint8* ptr_frame;
	
	// Check Status of sending and receiving.
	uint8 status_check;
	
	// TIMER0_void_Init(64, 1);
   
   

  // On power up: Receive UART Self-Test frame from remote control.
 

  do 
   {
	   
	   // Receive frame byte via UART, print operation on LCD, clear index and receive frame buffers.
	   frame_rx[count_bytes] = UART_uint8RecChar();
	   sprintf(buffer, "Rx: %d", frame_rx[count_bytes]);
	   LCD_void_SendCommand(0xc0);
	   LCD_void_WriteString(buffer);
	   count_bytes++;
   } while (frame_rx[count_bytes - 1] != 0x55); 
   count_bytes = 0;
   reset_buffer(frame_rx);
      
	// For debugging purposes.
	//_delay_ms(500);
	
 /* Send and Receive self-test frame via I2C to and from sensor ECU */
	
	// Send self test to sensor ECU.
	status_check = send_self_test(slave_write_address_sr);
	
	// Receive self test confirmation from sensor ECU.
	status_check = receive_self_test(slave_read_address_sr);
	
	I2C_Stop();
	_delay_ms(2);
	
	/* Send and receive self-test frame to and from actuator ECU. */
	
	// Send self test to actuator ECU.
	status_check = send_self_test(slave_write_address_ac);
	
	// Receive self test confirmation from actuator ECU.
	status_check = receive_self_test(slave_read_address_ac);
	
	I2C_Stop();
	_delay_ms(2);
	
	// Send Self-Test Confirmation to Remote Control Unit.
	UART_voidSendchar(0x00);

	
	while(1)
	{
		_delay_ms(200);
		
		 do
		 {
			 // Receive frame byte via UART, print operation on LCD.
			 frame_rx[count_bytes] = UART_uint8RecChar();
			 sprintf(buffer, "%d : %d",count_bytes, frame_rx[count_bytes]);
			 LCD_void_SendCommand(0xc0);
			 LCD_void_WriteString(buffer);
			 //_delay_ms(2);
			 count_bytes++;
		 } while (frame_rx[count_bytes - 1] != 0x55);
		 
		 
		 // Frame ID.
		 switch(frame_rx[0])
		 {	 
			 // I want the three temperatures.
			 case 0x08:
				status_check = send_want_temp(slave_write_address_sr);
				count_bytes = 0;
				reset_buffer(frame_rx);
				ptr_frame = receive_want_temp(slave_read_address_sr);
				
				 /* for(int i = 0; i<6; i++)
				{
					sprintf(buffer, "%d ->>> %d",i, ptr_frame[i]);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer);
					_delay_ms(1000);
					
				} */
				
				// Debugging.
				_delay_ms(500);
				
				// Send Temperatures to remote control.
				for(int i=2; i<5; i++)
				{
					UART_voidSendchar(ptr_frame[i]);
					sprintf(buffer, "%d TEMP Sent.", ptr_frame[i]);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer);
					_delay_ms(100);  // Debugging.
				}
				
				reset_buffer(frame_rx);
				count_bytes = 0;
				free(ptr_frame);
				break;
			
			// Change A/C temperature.	
			case 0x07:
			
				LCD_void_SendCommand(0x80);
				LCD_void_WriteString("0x07 now");
				status_check = send_change_temp(slave_write_address_sr, frame_rx[1], frame_rx[2], frame_rx[3]);
				
				reset_buffer(frame_rx);
				count_bytes = 0;
				break;
				
			// Close Door.
			case 0x0a:
				status_check = send_door_status(slave_write_address_ac, frame_rx[1], 0);
				
				reset_buffer(frame_rx);
				count_bytes = 0;
				break;
			
			// Open Door.
			case 0x09:
			status_check = send_door_status(slave_write_address_ac, frame_rx[1], 1);
			
			reset_buffer(frame_rx);
			count_bytes = 0;
			break;
				
			// Check Password
			case 0x01:
				pass_status = 0;
			   _delay_ms(200);
				for(int i=0; i<6; i++)
				{
					
					// Incorrect Password
					if(current_password[i] != frame_rx[i+1])
					{
						// Wrong Password.
						UART_voidSendchar(0x01);
						_delay_ms(100);
						pass_status++;
						break;
					} // if(current_password[i] != frame_rx[i+1])
				} // for(int i=0; i<6; i++)
				
				if(pass_status == 0)
				{
					// Correct Password.
					UART_voidSendchar(0x00);
					_delay_ms(100);
				} // if(pass_status == 0)
				
				reset_buffer(frame_rx);
				count_bytes = 0;
				break;
				
			// Change Password.
			case 0x03:
				for(int i=0; i<6; i++)
				{	
					current_password[i] = frame_rx[i+1];
					sprintf(buffer, "%d ->>> %d", i, frame_rx[i+1]);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer);
					//_delay_ms(1000);
				}
				
				UART_voidSendchar(0x04);
				_delay_ms(100);
				reset_buffer(frame_rx);
				count_bytes = 0;
				break;
				
			// Read Calender readings for sensor ECU.
			case 0x06:
			
				status_check = send_want_calender(slave_write_address_sr);
				
				ptr_frame = receive_want_calender(slave_read_address_sr);
				
				for(int i=0; i<7; i++)
				{
					
					UART_voidSendchar(ptr_frame[i]);
					sprintf(buffer, "%d changed %d   ",i, ptr_frame[i]);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer);
					_delay_ms(100);
				} // for(int i=0; i<7; i++)
				
				free(ptr_frame);
				count_bytes = 0;
				reset_buffer(frame_rx);
				
			/*	// Update frame with current calender values.
				calender_frame[0] = years1;
				calender_frame[1] = years2;
				calender_frame[2] = months;
				calender_frame[3] = days;
				calender_frame[4] = hrs;
				calender_frame[5] = mins;
				calender_frame[6] = secs;
				
				_delay_ms(200);
				for(int i=0; i<7; i++)
				{	
					
					UART_voidSendchar(calender_frame[i]);
					sprintf(buffer, "%d changed %d   ",i, calender_frame[i]);
					LCD_void_SendCommand(0xc0);
					LCD_void_WriteString(buffer);
					_delay_ms(100);
				} // for(int i=0; i<7; i++)
				
				count_bytes = 0;
				reset_buffer(frame_rx);
				*/
				break;
				
			// Change Calender readings.
			case 0x05:
			
			/*	// Disable timer.
				years1 = frame_rx[1];
				years2 = frame_rx[2];
				months = frame_rx[3];
				days = frame_rx[4];
				hrs = frame_rx[5];
				mins = frame_rx[6];
				secs = frame_rx[7];
				
				count_bytes = 0;
				reset_buffer(frame_rx);
			*/
				status_check = send_change_calender(slave_write_address_sr,frame_rx[1], frame_rx[2], frame_rx[3], frame_rx[4], frame_rx[5], frame_rx[6],  frame_rx[7]);
				count_bytes = 0;
				break;
		 } // switch(frame_rx[0])
		 
		
	} // While(1)

} // MAIN

