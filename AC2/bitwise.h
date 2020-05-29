/*
 * bitwise.h
 *
 * Created: 21-Feb-20 10:26:24 AM -> This is the last update.
 *  Author: shehab
 */ 


// Macros are capital.
#ifndef BITWISE_H_
#define BITWISE_H_
#define SET_BIT(reg, pin) reg|=(1<<pin)
#define CLR_BIT(reg, pin) reg&=(~(1<<pin))
#define TOGGLE_BIT(reg, pin) reg^=(1<<pin)

// Here I'm Interested in only one bit, I don't  care about the whole register
// If I made the other approach I will get numbers like 8, 128,....etc.
#define GET_BIT(reg, pin) ((reg>>pin)&1)
#endif /* BITWISE_H_ */