/*
 * ADC.h
 *
 * Created: 26-Feb-20 4:14:32 PM
 *  Author: shehab
 */ 


#ifndef ADC_H_
#define ADC_H_





#endif /* ADC_H_ */

// Initiates ADC.
void ADC_void_Init();

// Chooses channel (which pin of PORTA), starts conversion, and return the digital value.
uint32 ADC_uint8_ReadInput(uint8 channel);
