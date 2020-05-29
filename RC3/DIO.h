/*
 * DIO.h
 *
 * Created: 2/14/2020 11:22:15 AM
 *  Author: Lenovo
 */ 
#include "typedef.h"


#ifndef DIO_H_
#define DIO_H_

void DIO_voidSetPinDirection(uint8 port,uint8 pin,uint8 dir);
void DIO_voidSetPinValue(uint8 port, uint8 pin, uint8 value);
void DIO_voidTogglePin(uint8 port, uint8 pin);
uint8 DIO_uint8GetPinVlaue(uint8 port, uint8 pin);


#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_LOW 0
#define DIO_HIGH 1

#define DIO_output 1
#define DIO_input 0
#endif /* DIO_H_ */