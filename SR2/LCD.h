/*
 * LCD.h
 *
 * Created: 15-Feb-20 1:20:58 PM
 *  Author: shehab
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"

/*
#define clr_display 0x01
#define 4-bit 0x28
*/



#endif /* LCD_H_ */

// These functions work perfectly.
void LCD_void_SendCommand(uint8 command);
void LCD_void_SendData(uint8 data);
// the problem was here, initiation process is everything.
void LCD_void_init();
void LCD_void_WriteString(char *a);

// Saves a custom character to CGRAM
void LCD_void_CustomCharacter(uint8 loc, uint8 *msg);




// LCD_void_SendCommand(0x01); -> Clear display & return cursor to home
// LCD_void_SendCommand(0x02); -> Return cursor to home without clearing the display, if you wrote after, it will overwrite.
// LCD_void_SendCommand(0x04); -> Shifts cursor left, and it will write from right to left.
// LCD_void_SendCommand(0x05); -> Doc says shift display right, but it deletes all display and you can't print anything else afterwards.
// LCD_void_SendCommand(0x06); -> Doc says it shift cursor right, but that doesn't happen.
// LCD_void_SendCommand(0x07); -> it shifts display left depending on the number of characters you print afterward 1-> shift 1, else it does nothing.
// LCD_void_SendCommand(0x08); -> Cursor off Display off.
// LCD_void_SendCommand(0x0A); -> Display off, cursor on.
// LCD_void_SendCommand(0x0C); -> Display on, cursor off.
// LCD_void_SendCommand(0x0E); -> Display on, cursor blinking off.
// LCD_void_SendCommand(0x0F); -> Display on, cursor blinking on.
// LCD_void_SendCommand(0x10); -> Shift cursor position to left, and continue writing from left to right opposite to 0x04.
// LCD_void_SendCommand(0x14); -> Shift cursor position to right, and continue writing from left to right.
// LCD_void_SendCommand(0x18); -> Shift entire display to left by one character.
// LCD_void_SendCommand(0x1C);  -> Shift entire display to right by one character.
// LCD_void_SendCommand(0x80); -> Force cursor to the beginning of first line.
// LCD_void_SendCommand(0xC0); -> Force Cursor to the beginning of second line.
