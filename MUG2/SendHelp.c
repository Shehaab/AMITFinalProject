/*
 * SendHelp.c
 *
 * Created: 24-May-20 11:45:50 AM
 *  Author: shehab
 */ 

#include "SendHelp.h"
#include <stdlib.h>
#include <stdio.h>
#include "LCD.h"
#define OPEN_DOOR 1
#define CLOSE_DOOR 0

void reset_buffer(uint8* buffer)
{
	for(int i=0; i<10; i++)
	{
		buffer[i] = 0;
	}
}

uint8 send_self_test(uint8 sla)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 frame_self_test[4] = {0xAA, 0x00, 0xAA^0x00, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		for (int i=0; i<4; i++)
		{
			status = I2C_Write(frame_self_test[i]);
			_delay_ms(200);
		} // for (int i=0 i<4; i++)
		
		return 1;
	} // if (status == 1)
	
	else
	{
		return 0;
	} // else
} // send_self_test(uint8 sla)

uint8 receive_self_test(uint8 sla)
{
	uint8 status;                 // Status of operation.
	uint8 count_bytes = 0;        // Count bytes in frame.
	uint8 data_Rx;                // data buffer.
	
	status = I2C_Repeated_Start(sla);
	_delay_ms(200);
	
	if(status == 1)
	{
		do 
		{	
			
			data_Rx = I2C_Read_Ack();         //  Receive byte with ACK.
			_delay_ms(200);
			count_bytes++;                    //  Next byte in frame.
		} while (count_bytes != 3);
		data_Rx = I2C_Read_Nack();           // Receive last byte.
		_delay_ms(200);
		
		// Success
		return 1;
		
	} // if(status == 1)
	else
	{
		// Fail
		return 0;
	}
	
} // receive_self_test(sla)

uint8 send_want_temp(uint8 sla)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 want_temp[4] = {0xAA, 0x08, 0xAA^0x08, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		for (int i=0; i<4; i++)
		{
			status = I2C_Write(want_temp[i]);
			_delay_ms(200);
		} // for (int i=0 i<4; i++)
		
		return 1;
	} // if (status == 1)
	
	else
	{
		return 0;
	} // else
	
	// I2C_Stop();
} // send_temp_want(uint8 sla)


uint8* receive_want_temp(uint8 sla)
{
	uint8 status;                 // Status of operation.
	uint8 count_bytes = 0;        // Count bytes in frame.
	uint8* data_Rx = malloc(sizeof(uint8) * 6);                // data buffer.
	static uint8 no_data_Rx[1] = {0};
	
	status = I2C_Repeated_Start(sla);
	_delay_ms(200);
	
	if(status == 1)
	{
		do
		{
			
			data_Rx[count_bytes] = I2C_Read_Ack();         //  Receive byte with ACK.
			_delay_ms(200);
			count_bytes++;                    //  Next byte in frame.
		} while (count_bytes != 5);
		data_Rx[count_bytes] = I2C_Read_Nack();           // Receive last byte.
		_delay_ms(200);
		
		I2C_Stop();
		_delay_ms(200);
		// Success
		return (uint8 *)data_Rx;
		
	} // if(status == 1)
	else
	{
		// Fail
		I2C_Stop();
		_delay_ms(200);
		return (uint8 *)no_data_Rx;
	}
	
} // receive_want_temp(uint8 sla)

uint8 send_change_temp(uint8 sla, uint8 temp1, uint8 temp2, uint8 temp3)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 change_temp[6] = {0xAA, 0x07,temp1, temp2, temp3, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		for (int i=0; i<6; i++)
		{
			status = I2C_Write(change_temp[i]);
			_delay_ms(200);
		} // for (int i=0 i<6; i++)
		
		
		I2C_Stop();
		return 1;
	} // if (status == 1)
	
	else
	{
		I2C_Stop();
		return 0;
	} // else
	
	
} // uint8 send_change_temp(uint8 sla)


uint8 send_door_status(uint8 sla, uint8 door_id, uint8 door_status)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 open_door[4] = {0xaa, 0x09, door_id, 0x55};
	uint8 close_door[4] = {0xaa, 0x0a, door_id, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		if(door_status == OPEN_DOOR)
		{
			for (int i=0; i<4; i++)
			{
				status = I2C_Write(open_door[i]);
				_delay_ms(200);
			} // for (int i=0 i<4; i++)
		} // if(door_status == OPEN_DOOR)
		
		else if (door_status == CLOSE_DOOR)
		{
			for (int i=0; i<4; i++)
			{
				status = I2C_Write(close_door[i]);
				_delay_ms(200);
			} // for (int i=0 i<4; i++)
		} // else if (door_status == CLOSE_DOOR)
		
		I2C_Stop();
		return 1;
	} // if (status == 1)
	
	else
	{
		return 0;
	} // else
} // uint8 send_door_status(uint8 sla, uint8 door_id, uint8 door_status)

uint8 send_want_calender(uint8 sla)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 want_calender[2] = {0x06, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		for (int i=0; i<2; i++)
		{
			status = I2C_Write(want_calender[i]);
			_delay_ms(200);
		} // for (int i=0 i<4; i++)
		
		return 1;
	} // if (status == 1)
	
	else
	{
		return 0;
	} // else
	
	// I2C_Stop();
} // uint8 send_want_calender(uint8 sla)

uint8* receive_want_calender(uint8 sla)
{
	uint8 status;                 // Status of operation.
	uint8 count_bytes = 0;        // Count bytes in frame.
	uint8* data_Rx = malloc(sizeof(uint8) * 7);                // data buffer.
	static uint8 no_data_Rx[1] = {0};
	
	status = I2C_Repeated_Start(sla);
	_delay_ms(200);
	
	if(status == 1)
	{
		do
		{
			
			data_Rx[count_bytes] = I2C_Read_Ack();         //  Receive byte with ACK.
			_delay_ms(200);
			count_bytes++;                    //  Next byte in frame.
		} while (count_bytes != 6);
		data_Rx[count_bytes] = I2C_Read_Nack();           // Receive last byte.
		_delay_ms(200);
		
		I2C_Stop();
		_delay_ms(200);
		// Success
		return (uint8 *)data_Rx;
		
	} // if(status == 1)
	else
	{
		// Fail
		I2C_Stop();
		_delay_ms(200);
		return (uint8 *)no_data_Rx;
		
	} 
} // uint8* receive_want_calender

// Send changed calender settings
uint8 send_change_calender(uint8 sla, uint8 years1, uint8 years2, uint8 months, uint8 days, uint8 hrs, uint8 mins, uint8 secs)
{
	uint8 status;
	
	// Self-Test frame.
	uint8 change_calender[9] = {0x05, years1, years2, months, days, hrs, mins, secs, 0x55};
	
	// Send start condition.
	status = I2C_Start(sla);
	_delay_ms(200);
	
	// Continue if slave sent Acknowledge.
	if (status == 1)
	{
		for (int i=0; i<9; i++)
		{
			status = I2C_Write(change_calender[i]);
			_delay_ms(200);
		} // for (int i=0 i<6; i++)
		
		
		I2C_Stop();
		_delay_ms(200);
		return 1;
	} // if (status == 1)
	
	else
	{
		I2C_Stop();
		_delay_ms(200);
		return 0;
	} // else
} // uint8 send_change_calender(uint8 sla, uint8 year1, uint8 years2, uint8 months, uint8 days, uint8 hrs, uint8 mins, uint8 secs)



