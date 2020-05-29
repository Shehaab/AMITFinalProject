/*
 * ADC.c
 *
 * Created: 26-Feb-20 4:14:15 PM
 *  Author: shehab
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"

void ADC_void_Init()
{
	// Make ADC channel 0 as input -> PORT A PIN 0.
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_0, DIO_INPUT);
	
	// Make it the whole PORT A for now.
	//DDRA = 0x00;
	
	// activate Pull-up resistor behavior.
	// the Logical High is represented by 'red' and Logical Low is represented by 'blue' on Proteus.
	//PORTA= 0xFF;
	
	// Enable Channel 0, Work @ AVCC as reference voltage, and MSBs last two bits are in ADCH. update: work at vint.
	//ADMUX = 0xC0;
	
	// Enable ADC and work at speed: F/128 HZ
	//ADCSRA = 0x87;
	
	// My Driver, The above works fine.
	
	// Set PortA as input PORT
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_0, DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_1, DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_2, DIO_INPUT);
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_3, DIO_INPUT);
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_4, DIO_INPUT);
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_5, DIO_INPUT);
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_6, DIO_INPUT);
	//DIO_void_SetPinDirection(DIO_PORTA, DIO_PIN_7, DIO_INPUT);
	
	PORTA = 0xFF;
	
	// Will See about making it active low or not.
	
	// Decoupling capacitors are used to provide short bursts of energy during digital switching circuits.
	// Work with internal 2.56V voltage reference with external capacitor on AREF PIN.
	SET_BIT(ADMUX, 6);
	SET_BIT(ADMUX, 7);
	
	// Rest of channel bits, are not used (reserved).
	CLR_BIT(ADMUX, 3);
	CLR_BIT(ADMUX, 4);
	
	// Work with ADCH and ignore ADCL(LSBs d0,d1)
	SET_BIT(ADMUX, 5);
	
	// Turn ADC on (ADEN).
	SET_BIT(ADCSRA, 7);
	
	// Wait, don't start converting now (ADSC) -> write this bit to one to start each conversion.
	CLR_BIT(ADCSRA, 6);
	
	// Disable this property (ADATE)
	CLR_BIT(ADCSRA, 5);
	
	// This bit is set when an ADC conversion completes,  and the Data Registers are updated (ADIF).
	SET_BIT(ADCSRA,4);
	
	// Disable this property (ADIE)
	CLR_BIT(ADCSRA, 3);
	
	// Work @ Frequency/64 Hz.
	SET_BIT(ADCSRA, 2);
	SET_BIT(ADCSRA, 1);
	CLR_BIT(ADCSRA, 0);
}

uint32 ADC_uint8_ReadInput(uint8 channel)
{
	/*
	// Hold data of ADCL and ADCH register respectively.
	uint8 Ain, AinLow;
	
	// Set input channel to read.
	ADMUX=ADMUX|(channel & 0x0f);
	
	// Start Conversion.
	ADCSRA |= (1<<ADSC);
	
	// Monitor end of conversion Interrupt. As long as the conversion is going on do nothing.
	while((ADCSRA&(1<<ADIF))==0);
	
	_delay_us(10);
	
	AinLow = (int)ADCL;		// Read lower byte
	Ain = (int)ADCH*256;	// Read higher 2 bits and multiply be weight
	
	Ain = Ain + AinLow;
	return (Ain);			// Return digital value
	*/
	
	// Digital value register.
	uint32 digital_value = 0;
	
	// Choose Channel.
	switch(channel)
	{	
		// Channel 0: PORT A PIN 0.
		case 0:
			CLR_BIT(ADMUX,0);
			CLR_BIT(ADMUX,1);
			CLR_BIT(ADMUX,2);
			break;
		
		// Channel 1: PORT A PIN 1.	
		case 1:
			SET_BIT(ADMUX,0);
			CLR_BIT(ADMUX,1);
			CLR_BIT(ADMUX,2);
			break;
		
		// Channel 2: PORT A PIN 2.
		case 2:
			CLR_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			CLR_BIT(ADMUX,2);
			break;
		
		// Channel 3: PORT A PIN 3.
		case 3:
			SET_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			CLR_BIT(ADMUX,2);
			break;
		
		// Channel 4: PORT A PIN 4.
		case 4:
			CLR_BIT(ADMUX,0);
			CLR_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
		
		// Channel 5: PORT A PIN 5.
		case 5:
			SET_BIT(ADMUX,0);
			CLR_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
		
		// Channel 6: PORT A PIN 6.
		case 6:
			CLR_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
		
		// Channel 7: PORT A PIN 7.
		case 7:
			SET_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
	}
	
	// Take 100 samples to take average.
	for(uint8 i=0; i<100; i++)
	{
		SET_BIT(ADCSRA, 6);
		
		while(GET_BIT(ADCSRA, 4) == 0);
		
		SET_BIT(ADCSRA, 4);
		
		digital_value += ADCH;
	}
	
	digital_value /= 100;
	
	// convert it to uint8 to decrease size -> (uint8).
	return  digital_value;
}
