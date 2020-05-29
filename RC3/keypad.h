/*
 * keypad.h
 *
 * Created: 2/21/2020 1:37:41 PM
 *  Author: Lenovo
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define change_passkey 1
#define digital_calender 2
#define AC_temperature 3
#define self_test 4
#define RGB_Light 0


void KEYPAD_voidInit(void);
uint8 KEYPAD_uint8GetKey(void);
uint8 KEYPAD_uint8CheckPressed(void);



#endif /* KEYPAD_H_ */