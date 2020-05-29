/*
 * SendHelp.c
 *
 * Created: 24-May-20 11:45:50 AM
 *  Author: shehab
 */ 

#include "SendHelp.h"

void reset_buffer(uint8* buffer)
{
	for(int i=0; i<10; i++)
	{
		buffer[i] = 0;
	}
}