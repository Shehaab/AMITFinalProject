
/*
 * timer.h
 *
 * Created: 09-Mar-20 2:38:23 PM
 *  Author: shehab
 */ 



// Initiate Timer with desired time.
void TIMER0_void_Init(uint16 prescaler, f32 t_sec_desired);

// Helper Function for initializing TCNT0 if time desired < maximum time TIMER0 can reach.
uint8 TIMER0_uint8_InitCounterReg(f32 t_microsec_desired, f32 t_microsec_counter);

// Disable timer.
void TIMER0_void_DisableTimer();

// Enable timer.
void TIMER0_void_EnableTimer();