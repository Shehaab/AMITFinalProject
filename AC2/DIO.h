/*
 * DIO.h
 *
 * Created: 14-Feb-20 11:22:01 AM
 *  Author: shehab
 */ 

/*

 */

#ifndef DIO_H_
#define DIO_H_
//-------------------------------------------
// Port Names.
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3
//-------------------------------------------
// Pin Names.
#define DIO_PIN_0 0
#define DIO_PIN_1 1
#define DIO_PIN_2 2
#define DIO_PIN_3 3
#define DIO_PIN_4 4
#define DIO_PIN_5 5
#define DIO_PIN_6 6
#define DIO_PIN_7 7
//--------------------------------------------
// Pin State(INPUT/OUTPUT) Name.
#define DIO_INPUT 0
#define DIO_OUTPUT 1
//---------------------------------------------
// pin Voltage State(o volts/5 volts) Name.
#define DIO_LOW 0
#define DIO_HIGH 1
//---------------------------------------------

#endif /* DIO_H_ */


void DIO_void_SetPinDirection(uint8 port, uint8 pin, uint8 dir);
void DIO_void_SetPinValue(uint8 port, uint8 pin, uint8 value);
void DIO_void_TogglePin(uint8 port, uint8 pin);
uint8 DIO_uint8_GetPinValue(uint8 port, uint8 pin);

