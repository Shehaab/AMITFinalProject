/*
 * SendHelp.h
 *
 * Created: 24-May-20 11:45:33 AM
 *  Author: shehab
 */ 


#include "std_types.h"
#include "I2C_Master_H_file.h"


void reset_buffer(uint8* buffer);


uint8 send_self_test(uint8 sla);
uint8 receive_self_test(uint8 sla);

uint8 send_want_temp(uint8 sla);
uint8* receive_want_temp(uint8 sla);

uint8 send_change_temp(uint8 sla, uint8 temp1, uint8 temp2, uint8 temp3);

uint8 send_door_status(uint8 sla, uint8 door_id, uint8 door_status);

uint8 send_want_calender(uint8 sla);

uint8* receive_want_calender(uint8 sla);

uint8 send_change_calender(uint8 sla, uint8 year1, uint8 years2, uint8 months, uint8 days, uint8 hrs, uint8 mins, uint8 secs);


