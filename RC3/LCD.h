/*
 * IncFile1.h
 *
 * Created: 2/15/2020 1:33:00 PM
 *  Author: Lenovo
 */ 
#include "DIO.h"

#ifndef INCFILE1_H_
#define INCFILE1_H_

void LCD_voidSendCommand(uint8 command);
void LCD_voidSendData(uint8 data);
void LCD_voidInit();
void LCD_voidSendString(uint8 arr[]);





#endif /* INCFILE1_H_ */