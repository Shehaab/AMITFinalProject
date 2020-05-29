
/*
 * timer.c
 *
 * Created: 09-Mar-20 2:38:09 PM
 *  Author: Shehab
 */ 

#include <avr/interrupt.h>
#include <stdio.h> // for sprintf function.

// User-Defined Modules.
#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"
#include "LCD.h"

// Calender variables for ISR routine. (Declaration: No Memory Allocation).
extern uint8 days, months, hrs, mins, secs, years1, years2;

// Debugging
uint8 count_debug = 0;
char buffer[10];

// 16 Mhz, Not any more working with atmega32 which have 8 MHZ frequency.
#define F_MC 8

// Counter starts from zero = 256 counts.
#define COUNTER_RESOLUTION_MAX 256

// TIMER0 ISR eye on number of given overflows TIMER0 does till Desired Time if Desired Time > Maximum Time of TIMER0 can reach.
uint32 isr_see_overflows = 0;

// TIMER0 ISR counter to reach time needed.
uint32 isr_counter = 0;

// TIMER0 ISR eye on Desired Time and Overflow Time of TIMER0.
f32 g_t_desired_micro=0;
f32 g_t_overflow_micro=0;

// Start Value of TCNT0 reg value for ISR. -> There is an error, you initiate it in ISR even if it doesn't have to be filled sometimes.
uint32 start_pos_TCNT0;




uint8 TIMER0_uint8_InitCounterReg(f32 t_microsec_desired, f32 t_microsec_counter)
	/* 
	    Arguments:
		    t_microsec_desired: Time Entered in Microseconds.
		    t_microsec_counter: Time taken by TIMER0 to make a full cycle.
		
	    Return Value:
		    Returns a number for the starting position of TIMER0 TCNT0 register in case of desired time < Maximum time TIMER0 can reach. 
	*/
{
	// The value @ which TCNTO starts in case Time desired < Maximum time the micro-controller can do.
	f32 counter_start = COUNTER_RESOLUTION_MAX - (t_microsec_desired / t_microsec_counter);
	
	// In case there is decimal point in the number. 8-bit counter doesn't accept floats.
	return (uint8) counter_start;
}



void TIMER0_void_Init(uint16 prescaler, f32 t_sec_desired)
	/*
		Arguments:
			prescaler: Choose to divide your source frequency by(0<No Prescaler> or 8 or 64 or 256 or 1024)
			t_sec_desired: Time entered in Seconds.
	*/
{	
	// Avoid Zero-Division Error, and divide by float not integer.
	//prescaler += 0.0; //<- May be the problem is here because Prescaler is an integer?,
	// yes the problem was here, prescaler is an integer, even if you add 0.0, you still have 0, and the ATMEGA gcc compiler doesn't catch
	// Division by zero error, You will get undefined behavior.
	
	// Clock Cycle of the timer's counter.
	f32 t_microsec_counter;
	
	// If no prescaler is used.
	if (prescaler == 0)
		t_microsec_counter = 1 / ( F_MC / 1.0);
	else
		t_microsec_counter = 1 / ( F_MC / (prescaler + 0.0)); // Avoid zero-division error.
	
	// Maximum time of TIMER0 counter.
	f32 t_microsec_overflow = t_microsec_counter * COUNTER_RESOLUTION_MAX;
	
	// Time in Micro seconds.
	f32 t_microsec_desired = t_sec_desired * 1000000;
	
	// For ISR control
	g_t_desired_micro = t_microsec_desired;
	g_t_overflow_micro = t_microsec_overflow;

	// Force-Output-Compare (Not Used).
	CLR_BIT(TCCR0, 7);
	
	// WaveForm Generation Mode (Normal Mode).
	CLR_BIT(TCCR0, 6);
	CLR_BIT(TCCR0, 3);
	
	// Compare Match Output Mode (Not Used).
	CLR_BIT(TCCR0, 4);
	CLR_BIT(TCCR0, 5);
	
	// Time of counter for timer.
	switch(prescaler)
	{
		// No Pre-scaling (Micro-controller's installed Frequency).
		case 0:
			SET_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
		
		// Atmega32a: 2 MHZ.
		case 8:
			CLR_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
		
		// 250 kHZ.
		case 64:
			SET_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
			
		// 62.5 KHZ.
		case 256:
			CLR_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);
			break;
		
		// 15.625 KHZ.
		case 1024:
			SET_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);
			break;
	}
	
	
	// Check Value of Time to calibrate the counter accordingly.
	if ( t_microsec_desired < t_microsec_overflow)
	{
		TCNT0 = TIMER0_uint8_InitCounterReg(t_microsec_desired, t_microsec_counter);
		start_pos_TCNT0 = TCNT0;
	}
	
	
	else if (t_microsec_desired > t_microsec_overflow)
	{
		f32 digital_count = t_microsec_desired / t_microsec_overflow;
		
		f32 excess = digital_count - (uint32) digital_count;
		
		
		if (excess == 0)
		{	
			// Number of clock cycles till you reach time.
			isr_see_overflows = digital_count;
		}
		
		// Compute the mantissa part of digital count to convert it into time, and to add it to the register starting position.
		else
		{
			f32 t_desired2_micro = excess * t_microsec_overflow;
			
			start_pos_TCNT0 = TIMER0_uint8_InitCounterReg(t_desired2_micro, t_microsec_counter);
			
			TCNT0 = start_pos_TCNT0;
			
			// Total number of clock cycles + the excess part clock cycle.
			isr_see_overflows = digital_count + 1;
		}
	}
	
	// Start the timer.
	SET_BIT(TIMSK, 0);  // PIE
	SET_BIT(TIFR, 0);   // PIF -> This what makes the timer starts, Make these registers @ end of driver.
	SET_BIT(SREG, 7);   // GIF
}

void TIMER0_void_DisableTimer()
{
	CLR_BIT(TIMSK, 0);  // PIE
	//CLR_BIT(TIFR, 0);   // PIF 
	CLR_BIT(SREG, 7);   // GIF
}

void TIMER0_void_EnableTimer()
{
	// Start the timer.
	SET_BIT(TIMSK, 0);  // PIE
	SET_BIT(TIFR, 0);   // PIF -> This what makes the timer starts, Make these registers @ end of driver.
	SET_BIT(SREG, 7);   // GIF
}
ISR(TIMER0_OVF_vect)
{
	
	if(g_t_desired_micro > g_t_overflow_micro)
	{	
		// Increment time_count until you reach desired time.
		isr_counter++;
		
		// Desired time reached.
		if (isr_counter == isr_see_overflows)
		{
			isr_counter = 0;
			TCNT0 = start_pos_TCNT0;
			
			/* Do what you want to happen after the desired time you entered. */
			 
			 secs++;
			 
		 // LCD format calibrating
			 if(secs <= 9)
			 {
				 sprintf(buffer, "%d", secs);
				 LCD_void_SendCommand(0x80 + 11);
				 LCD_void_WriteString(buffer);
				 
			 }
			 else
			 {
				 sprintf(buffer, "%d", secs);
				 LCD_void_SendCommand(0x80 + 10);
				 LCD_void_WriteString(buffer);
			 }
			 
		
			  // Reached a whole minute.
			  if(secs==60)
			  {
				  secs = 0;
				  mins++;
				  
				  /*
				  // Calibrate LCD format.
				  LCD_void_SendCommand(0xC0+10);
				  LCD_void_WriteString("00"); */
				  
				/*  if(mins <= 9)
				  {
					  sprintf(buffer, "%d", mins);
					  LCD_void_SendCommand(0xC0 + 8);
					  LCD_void_WriteString(buffer);
					  
				  }
				  else
				  {
					  sprintf(buffer, "%d", mins);
					  LCD_void_SendCommand(0xC0 + 7);
					  LCD_void_WriteString(buffer);
				  } */
				  
			  } // If (secs) 
			  
			   // Reached a whole hour.
			   if(mins==60)
			   {
				   mins = 0;
				   hrs++;
				   
				   /*
				   // Calibrate LCD format.
				   LCD_void_SendCommand(0xC0+7);
				   LCD_void_WriteString("00");
				   
				   if(hrs <= 9)
				   {
					   sprintf(buffer, "%d", hrs);
					   LCD_void_SendCommand(0xC0 + 5);
					   LCD_void_WriteString(buffer);
					   
				   }
				   else
				   {
					   sprintf(buffer, "%d", hrs);
					   LCD_void_SendCommand(0xC0 + 4);
					   LCD_void_WriteString(buffer);
				   } */
			   } // If (mins)
			   
			   // Reached a whole day.
			   if(hrs==24)
			   {
				   hrs = 0;
				   days++;
				   
				   /*
				   // Calibrate LCD format (Zero the hrs position on LCD).
				   LCD_void_SendCommand(0xC0+4);
				   LCD_void_WriteString("00");
				   
				   if(days <= 9)
				   {
					   sprintf(buffer, "%d", days);
					   LCD_void_SendCommand(0x80 + 4);
					   LCD_void_WriteString(buffer);
					   
				   }
				   else
				   {
					   sprintf(buffer, "%d", days);
					   LCD_void_SendCommand(0xC0 + 3);
					   LCD_void_WriteString(buffer);
				   } */
			   } // If (hrs)
			   
			   // Reached a whole Month.
			   if(days==30)
			   {
				   days = 0;
				   months++;
				   
				   /*
				   // Calibrate LCD format (Zero the days position on LCD).
				   LCD_void_SendCommand(0x80+3);
				   LCD_void_WriteString("00");
				   
				   if(months <= 9)
				   {
					   sprintf(buffer, "%d", months);
					   LCD_void_SendCommand(0x80 + 7);
					   LCD_void_WriteString(buffer);
					   
				   }
				   else
				   {
					   sprintf(buffer, "%d", months);
					   LCD_void_SendCommand(0xC0 + 6);
					   LCD_void_WriteString(buffer);
				   } */
			   } // If (days)
			   
			    // Reached a whole year.
				/*
			    if(months==12)
			    {
				    months = 0;
				    years++;
				    // Calibrate LCD format (Zero the months position on LCD).
				    LCD_void_SendCommand(0x80+6);
				    LCD_void_WriteString("00");
				    
				    if(years <= 2020)
				    {
					    sprintf(buffer, "%d", years);
					    LCD_void_SendCommand(0x80 + 12);
					    LCD_void_WriteString(buffer);
					    
				    }
				    else
				    {
					    sprintf(buffer, "%d", years);
					    LCD_void_SendCommand(0xC0 + 11);
					    LCD_void_WriteString(buffer);
				    }
			    } // If (years) */
			
		} // If (isr_counter...)
			
	} // If (g_t_desired_micro...)
		

	
	else if(g_t_desired_micro < g_t_overflow_micro)
	{
		TCNT0 = start_pos_TCNT0;
		// Do action.
		// LED 2 is toggled after every 512 micro second.
		//DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_3, DIO_OUTPUT);
		//DIO_void_TogglePin(DIO_PORTD, 3);
	}
	
	else
	{
		// Do action.
	}
	
	/* For Debugging Purposes.
	// Increment till you reach desired time.
	isr_counter++;
	
	if (isr_counter == isr_see_overflows)
	{
		// Reset counter to start all over again.
		isr_counter = 0;
		
		// Toggle Pin.
		DIO_void_TogglePin(DIO_PORTD, DIO_PIN_3);
	} */
} // ISR

