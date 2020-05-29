/*
 * main_project.c
 *
 * Created: 5/17/2020 2:07:41 PM
 *  Author: Mohamed Tarek & ShehabEldeen Ehab.
 */ 

#include "main project.h"
#include "LCD.h"
#include "typedef.h"
#define F_CPU 8000000
#include <util/delay.h>
#include "keypad.h"
#include "UART2.h"
#include <stdio.h>
#include <stdlib.h>



extern uint8 list;      // List of Controls.
uint8 key;
sint8 option = 0;

uint8 x,y,z;			                  // Flags for while loops.
uint8 new_passkey[6];	                 // Array to save and send the new password.
uint8 position=4;
uint8 cur_position=0;					// To move right or left.
uint8 hours, mins ,secs	;		       // For digital calender.
uint8 day , month ;				      // For digital calender.
uint8 year1, year2;					 // For digital calender.
char str[5];						// To turn numbers into characters and display them on LCD.
uint8 RT1, RT2, RT3;			   // For temperature control.
char opt;
uint8 i=0,fl=0;

// Display Options.
uint8 change_pass[]="change passkey      ";
uint8 dig_calender[]="digital calender   ";
uint8 temperature[]="AC temp ctrl    ";
uint8 selfTest[]="Self Test Req.     ";
uint8 light_control[]="RGB light ctrl   ";


// Main Control.
void RC_voidDisplayList(void)
{
	uint8 password_status;
	while (1)
	{
		// Wait to get key.
		key = KEYPAD_uint8GetKey();
		_delay_ms(70);
	
		// Move up or down on list.
		if (key=='8' && key!=0xff && key!='#')
		{
			list++;
		}
	
		/*---------------------------------------------------------------------------------------------------*/
		else if (key=='2' && list!=0  && key!=0xff && key!='#')
		{
			list--;
		}
	
		/*---------------------------------------------------------------------------------------------------*/
		else if (key=='#' && key!=0xff)							//confirm on the selected element of the list
		{
	
			x=0;
			LCD_voidSendCommand(0x0F);
		
			switch(list)											//start of list code
			{
				case change_passkey:
				
					fl=0;								// start of change passkey option code
					UART_voidSendchar(0x03);
					_delay_ms(100);
					LCD_voidSendCommand(0x01);
					LCD_voidSendString("new passkey: ");
					LCD_voidSendCommand(0xC0);
			
					while (1)
					{
						key=0;
						key=KEYPAD_uint8GetKey();
						//while (KEYPAD_uint8CheckPressed()==0);
						_delay_ms(70);
						if (key!=0xff && key!='#')
						{
							new_passkey[i]=key;
							LCD_voidSendData('*');
							i++;
							//continue;
						} // if (key!=0xff && key!='#')
				
				
						/*---------------------------------------------------------------------------------------------------*/
						/*key=0;
						key=KEYPAD_uint8GetKey();
						_delay_ms(50);
						while (KEYPAD_uint8CheckPressed()==0);*/
				
						if (key=='#' && key!=0xff && i==6)				//confirm on the new passkey
						{
							for (uint8 i=0;i<6;i++)
							{
								UART_voidSendchar(new_passkey[i]);
								_delay_ms(100);
							} // for (uint8 i=0;i<6;i++)
							UART_voidSendchar(0x55);
							_delay_ms(100);
							LCD_voidSendCommand(0x01);
							//fl=1;
					
							break;
						}// if (key=='#' && key!=0xff && i==6)
				
					}//while(1)
			
					uint8 rec= UART_uint8RecChar();
					if (rec==0x04)
					{
						LCD_voidSendCommand(0x01);
						LCD_voidSendCommand(0x80);
						LCD_voidSendString("change successful");
						/*LCD_voidSendCommand(0xC0);
						LCD_voidSendString("3 trials");*/
						_delay_ms(300);
						UART_SendPassword();				//enter password and send it to MU to check if "ok" or "not ok"
						//LCD_voidSendCommand(0x0E);
					
						 password_status = UART_uint8RecChar();
					
						if (password_status == 0x00)
						{
						
							LCD_voidSendCommand(0x01);
							LCD_voidSendCommand(0x80);
							LCD_voidSendString("true password");
							_delay_ms(1000);
							LCD_voidSendCommand(0x01);
							//h=1;
						
							// Break and go to main list.
							//break;
						} //  if (password_status == 0x00)
					
						else if (password_status == 0x01)
						{
						
							LCD_voidSendCommand(0x01);
							LCD_voidSendCommand(0x80);
							LCD_voidSendString("wrong password");
							_delay_ms(1000);
							//LCD_voidSendCommand(0xC0);
						
						
							//LCD_voidSendString("try again");
							//_delay_ms(1000);
							//h=1;
							LCD_voidSendCommand(0x01);
						} // else if (password_status == 0x01)
					  } // if (rec==0x04)
					else
					{
						LCD_voidSendCommand(0x01);
						LCD_voidSendCommand(0x80);
						LCD_voidSendString("change not ok");
						_delay_ms(100);
				
					}
					LCD_voidSendCommand(0x01);
					break;												// end of change passkey option code
			
				/*---------------------------------------------------------------------------------------------------*/
				/*---------------------------------------------------------------------------------------------------*/
				case digital_calender:						//start of digital calender option code
					UART_voidSendchar(0x06);
					_delay_ms(100);
					UART_voidSendchar(0x55);
					_delay_ms(100);
			
					year1=UART_uint8RecChar();
					year2=UART_uint8RecChar();
					month=UART_uint8RecChar();
					day=UART_uint8RecChar();
					hours=UART_uint8RecChar();
					mins=UART_uint8RecChar();
					secs=UART_uint8RecChar();
			
					LCD_voidSendCommand(0x01);
			
			
				if (day<=9)
				{
					LCD_voidSendCommand(0x80+position);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0x80+position+1);
					sprintf(str,"%d",day);
					LCD_voidSendString(str);
					LCD_voidSendData('/');
				} 
				else
				{
					LCD_voidSendCommand(0x80+position);
					sprintf(str,"%d",day);
					LCD_voidSendString(str);
					LCD_voidSendData('/');
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if (month<=9)
				{
					LCD_voidSendCommand(0x80+position+3);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0x80+position+4);
					sprintf(str,"%d",month);
					LCD_voidSendString(str);
					LCD_voidSendData('/');
				}
				else
				{
					LCD_voidSendCommand(0x80+position+3);
					sprintf(str,"%d",month);
					LCD_voidSendString(str);
					LCD_voidSendData('/');
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if (year1<=9)
				{
				
					LCD_voidSendCommand(0x80+position+6);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0x80+position+7);
					LCD_voidSendData(year1);
				
				}
				else
				{
				
					LCD_voidSendCommand(0x80+position+6);
					sprintf(str,"%d",year1);
					LCD_voidSendString(str);
				
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if (year2<=9)
				{
				
					LCD_voidSendCommand(0x80+position+8);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0x80+position+9);
					LCD_voidSendData(year2);
				
				}
				else
				{
				
					LCD_voidSendCommand(0x80+position+8);
					sprintf(str,"%d",year2);
					LCD_voidSendString(str);
				
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if (hours<=9)
				{
					LCD_voidSendCommand(0xC0+position);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0xC0+position+1);
					sprintf(str,"%d",hours);
					LCD_voidSendString(str);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSendCommand(0xC0+position);
					sprintf(str,"%d",hours);
					LCD_voidSendString(str);
					LCD_voidSendData(':');
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if (mins<=9)
				{
					LCD_voidSendCommand(0xC0+position+3);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0xC0+position+4);
					sprintf(str,"%d",mins);
					LCD_voidSendString(str);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSendCommand(0xC0+position+3);
					sprintf(str,"%d",mins);
					LCD_voidSendString(str);
					LCD_voidSendData(':');
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				if ((secs)<=9)
				{
					LCD_voidSendCommand(0xC0+position+6);
					LCD_voidSendData('0');
					LCD_voidSendCommand(0xC0+position+7);
					sprintf(str,"%d",secs);
					LCD_voidSendString(str);
				
				}
				else
				{
					LCD_voidSendCommand(0xC0+position+6);
					sprintf(str,"%d",secs);
					LCD_voidSendString(str);
				
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				while (1)
				{
				
					key=KEYPAD_uint8GetKey();
					_delay_ms(70);
					if (key=='#' && key!=0xff)					// press confirm to edit date 
					{
						z=0;
						LCD_voidSendCommand(0x80+4);
						_delay_ms(10);
						key=0;
						break;
					}
				
					else if (key=='*' && key!=0xff)
					{
						LCD_voidSendCommand(0x01);
						z=1;
						x=1;
						break;
					}
					else
					continue;
				}
			
			
				/*---------------------------------------------------------------------------------------------------*/
			
				while (z==0)
				{
						key=0;
						key=KEYPAD_uint8GetKey();
						_delay_ms(70);
						//while (KEYPAD_uint8CheckPressed()==0);
					
						if (key=='#')							//confirm to finish editing date and start editing time
						{
							//LCD_voidSendCommand(0xC0+position);
							_delay_ms(10);
							z=1;
							x=0;
						}
					
						/*---------------------------------------------------------------------------------------------------*/
						else if (key=='6' && key!=0xff && key!='#')			//to move right
						{
							cur_position++;
							if (abs(cur_position%3)==0)
							{
								LCD_voidSendCommand(0x80+4);
							}
							else if (abs(cur_position%3)==1)
							{
								LCD_voidSendCommand(0x80+7);
							}
							else if (abs(cur_position%3)==2)
							{
								LCD_voidSendCommand(0x80+10);
							}
						
						
						}
					
						/*---------------------------------------------------------------------------------------------------*/
						else if (key=='4' && key!=0xff && key!='#')				//to move left
						{
							cur_position--;
							if (abs(cur_position%3)==0)
							{
								LCD_voidSendCommand(0x80+4);
							}
							else if (abs(cur_position%3)==1)
							{
								LCD_voidSendCommand(0x80+7);
							}
							else if (abs(cur_position%3)==2)
							{
								LCD_voidSendCommand(0x80+10);
							}
						
						}
					
						/*---------------------------------------------------------------------------------------------------*/
						else if (key=='2' && key!=0xff && key!='#')			//to increase value
						{
							uint8 p=abs(cur_position%3);
						
							switch (p)
							{
								case 0: day+=1;
								if (day<=9)
								{
									LCD_voidSendCommand(0x80+position);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+1);
									sprintf(str,"%d",day);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								else
								{
									LCD_voidSendCommand(0x80+position);
									sprintf(str,"%d",day);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								LCD_voidSendCommand(0x80+4);
								break;
							
								case 1: month+=1;
								if (month<=9)
								{
									LCD_voidSendCommand(0x80+position+3);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+4);
									sprintf(str,"%d",month);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								else
								{
									LCD_voidSendCommand(0x80+position+3);
									sprintf(str,"%d",month);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								LCD_voidSendCommand(0x80+7);
								break;
							
								case 2: year2+=1;
								if (year2<=9)
								{
								
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData(year2);
								
								}
								else
								{
								
									LCD_voidSendCommand(0x80+position+8);
									sprintf(str,"%d",year2);
									LCD_voidSendString(str);
								
								}
							
								if (year2>100)
								{
									year1+=1;
									year2=0;
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData('0');
								} 
								else if (year2<0)
								{
									year1-=1;
									year2=99;
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('9');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData('9');
								}
								break;
							
							
							}
						}
					
						/*---------------------------------------------------------------------------------------------------*/
						else if (key=='8' && key!=0xff && key!='#')			//to decrease value
						{
							uint8 p=abs(cur_position%3);
						
							switch (p)
							{
								case 0: day-=1;
								if (day<=9)
								{
									LCD_voidSendCommand(0x80+position);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+1);
									sprintf(str,"%d",day);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								else
								{
									LCD_voidSendCommand(0x80+position);
									sprintf(str,"%d",day);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								LCD_voidSendCommand(0x80+4);
								break;
							
								case 1: month-=1;
								if (month<=9)
								{
									LCD_voidSendCommand(0x80+position+3);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+4);
									sprintf(str,"%d",month);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								else
								{
									LCD_voidSendCommand(0x80+position+3);
									sprintf(str,"%d",month);
									LCD_voidSendString(str);
									//LCD_voidSendData('/');
								}
								LCD_voidSendCommand(0x80+7);
								break;
							
								case 2: year2-=1;
								if (year2<=9)
								{
								
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData(year2);
								
								}
								else
								{
								
									LCD_voidSendCommand(0x80+position+8);
									sprintf(str,"%d",year2);
									LCD_voidSendString(str);
								
								}
							
								if (year2>100)
								{
									year1+=1;
									year2=0;
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('0');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData('0');
								}
								else if (year2<0)
								{
									year1-=1;
									year2=99;
									LCD_voidSendCommand(0x80+position+8);
									LCD_voidSendData('9');
									LCD_voidSendCommand(0x80+position+9);
									LCD_voidSendData('9');
								}
								break;
							
							}
						}
						/*---------------------------------------------------------------------------------------------------*/
					
					
					
					
			
				}
				/*---------------------------------------------------------------------------------------------------*/
				/*---------------------------------------------------------------------------------------------------*/
				while (x==0)				//second line (edit time)
				{
					if (abs(cur_position%3)==0)
					{
						LCD_voidSendCommand(0xC0+4);
					}
					else if (abs(cur_position%3)==1)
					{
						LCD_voidSendCommand(0xC0+7);
					}
					else if (abs(cur_position%3)==2)
					{
						LCD_voidSendCommand(0xC0+10);
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					key=0;
					key=KEYPAD_uint8GetKey();
					_delay_ms(70);
					//while (KEYPAD_uint8CheckPressed()==0);
				
					if (key=='#')										//confirm to send data and return to the list select
					{
						_delay_ms(10);
						LCD_voidSendCommand(0x01);
						UART_voidSendchar(0x05);
						_delay_ms(100);
					
						UART_voidSendchar(year1);
						_delay_ms(100);
						UART_voidSendchar(year2);
						_delay_ms(100);
						UART_voidSendchar(month);
						_delay_ms(100);
						UART_voidSendchar(day);
						_delay_ms(100);
				
					
						UART_voidSendchar(hours);
						_delay_ms(100);
						UART_voidSendchar(mins);
						_delay_ms(100);
						UART_voidSendchar(secs);
						_delay_ms(100);
					
						UART_voidSendchar(0x55);
						_delay_ms(100);
						x=1;
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='6' && key!=0xff && key!='#')			//to move right
					{
						cur_position++;
						if (abs(cur_position%3)==0)
						{
							LCD_voidSendCommand(0xC0+4);
						}
						else if (abs(cur_position%3)==1)
						{
							LCD_voidSendCommand(0xC0+7);
						}
						else if (abs(cur_position%3)==2)
						{
							LCD_voidSendCommand(0xC0+10);
						}
					
					
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='4' && key!=0xff && key!='#')			//to move left
					{
						cur_position--;
						if (abs(cur_position%3)==0)
						{
							LCD_voidSendCommand(0xC0+4);
						}
						else if (abs(cur_position%3)==1)
						{
							LCD_voidSendCommand(0xC0+7);
						}
						else if (abs(cur_position%3)==2)
						{
							LCD_voidSendCommand(0xC0+10);
						}
					
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='2' && key!=0xff && key!='#')			//to increase value
					{
						uint8 p=abs(cur_position%3);
					
						switch (p)
						{
							case 0: hours+=1;
							if (hours<=9)
							{
								LCD_voidSendCommand(0xC0+position);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+1);
								sprintf(str,"%d",hours);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							else
							{
								LCD_voidSendCommand(0xC0+position);
								sprintf(str,"%d",hours);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							LCD_voidSendCommand(0xC0+4);
							break;
						
							case 1: mins+=1;
							if (mins<=9)
							{
								LCD_voidSendCommand(0xC0+position+3);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+4);
								sprintf(str,"%d",mins);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							else
							{
								LCD_voidSendCommand(0xC0+position+3);
								sprintf(str,"%d",mins);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							LCD_voidSendCommand(0xC0+7);
							break;
						
							case 2: secs+=1;
							if ((secs)<=9)
							{
								LCD_voidSendCommand(0xC0+position+6);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+7);
								sprintf(str,"%d",secs);
								LCD_voidSendString(str);
							
							}
							else
							{
								LCD_voidSendCommand(0xC0+position+6);
								sprintf(str,"%d",secs);
								LCD_voidSendString(str);
							
							}
							LCD_voidSendCommand(0xC0+10);
							break;
						
						}
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='8' && key!=0xff && key!='#')		//to decrease value
					{
						uint8 p=abs(cur_position%3);
					
						switch (p)
						{
							case 0: hours-=1;
							if (hours<=9)
							{
								LCD_voidSendCommand(0xC0+position);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+1);
								sprintf(str,"%d",hours);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							else
							{
								LCD_voidSendCommand(0xC0+position);
								sprintf(str,"%d",hours);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							LCD_voidSendCommand(0xC0+4);
							break;
						
							case 1: mins-=1;
							if (mins<=9)
							{
								LCD_voidSendCommand(0xC0+position+3);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+4);
								sprintf(str,"%d",mins);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							else
							{
								LCD_voidSendCommand(0xC0+position+3);
								sprintf(str,"%d",mins);
								LCD_voidSendString(str);
								//LCD_voidSendData(':');
							}
							LCD_voidSendCommand(0xC0+7);
							break;
						
							case 2: secs-=1;
							if ((secs)<=9)
							{
								LCD_voidSendCommand(0xC0+position+6);
								LCD_voidSendData('0');
								LCD_voidSendCommand(0xC0+position+7);
								sprintf(str,"%d",secs);
								LCD_voidSendString(str);
							
							}
							else
							{
								LCD_voidSendCommand(0xC0+position+6);
								sprintf(str,"%d",secs);
								LCD_voidSendString(str);
							
							}
							LCD_voidSendCommand(0xC0+10);
							break;
						
						}
					}
				
				
				
				
				
				}
				break;										//end of digital calender option code
			
				/*---------------------------------------------------------------------------------------------------*/
				/*---------------------------------------------------------------------------------------------------*/
				case AC_temperature:						//start of AC temperature option code
				y=0;
				UART_voidSendchar(0x08);
				_delay_ms(100);
				UART_voidSendchar(0x55);
				_delay_ms(100);
			
				RT1= UART_uint8RecChar();
				RT2= UART_uint8RecChar();
				RT3= UART_uint8RecChar();
			
				LCD_voidSendCommand(0x01);
				LCD_voidSendCommand(0x80);
				LCD_voidSendString("R1");
			
				LCD_voidSendCommand(0x80+4);
				LCD_voidSendString("R2");
			
				LCD_voidSendCommand(0x80+8);
				LCD_voidSendString("R3");
			
				LCD_voidSendCommand(0xC0);
				sprintf(str,"%d",RT1);
				LCD_voidSendString(str);
			
				LCD_voidSendCommand(0xC0+4);
				sprintf(str,"%d",RT2);
				LCD_voidSendString(str);
			
				LCD_voidSendCommand(0xC0+8);
				sprintf(str,"%d",RT3);
				LCD_voidSendString(str);
			
				/*---------------------------------------------------------------------------------------------------*/
				while (y==0)
				{
					key=0;
					key=KEYPAD_uint8GetKey();
					while (KEYPAD_uint8CheckPressed()==0);
					_delay_ms(60);
					if (key=='#'&&key!=0xff)					//confirm to change temp. threshold
					{
						if (abs(cur_position%3)==0)
						{
							LCD_voidSendCommand(0xC0);
						}
						else if (abs(cur_position%3)==1)
						{
							LCD_voidSendCommand(0xC0+4);
						}
						else if (abs(cur_position%3)==2)
						{
							LCD_voidSendCommand(0xC0+8);
						}
						x=0;
						break;
					}
					else if (key=='*'&&key!=0xff)
					{
						LCD_voidSendCommand(0x01);
						y=1;
						x=1;
					}
				
					else
					continue;
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				while (x==0)
				{
					key=0;
					key=KEYPAD_uint8GetKey();
					//while (KEYPAD_uint8CheckPressed()==0);
					_delay_ms(70);
				
					/*---------------------------------------------------------------------------------------------------*/
					if (key=='6'&&key!=0xff && key!='#')					//to move right
					{
						cur_position++;
						if (abs(cur_position%3)==0)
						{
							LCD_voidSendCommand(0xC0);
						}
						else if (abs(cur_position%3)==1)
						{
							LCD_voidSendCommand(0xC0+4);
						}
						else if (abs(cur_position%3)==2)
						{
							LCD_voidSendCommand(0xC0+8);
						}
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='4'&&key!=0xff && key!='#')				//to move left
					{
						cur_position--;
						if (abs(cur_position%3)==0)
						{
							LCD_voidSendCommand(0xC0);
						}
						else if (abs(cur_position%3)==1)
						{
							LCD_voidSendCommand(0xC0+4);
						}
						else if (abs(cur_position%3)==2)
						{
							LCD_voidSendCommand(0xC0+8);
						}
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='2'&&key!=0xff &&key!='#')				//to increase value
					{
						uint8 p=abs(cur_position%3);
						switch (p)
						{
							case 0: RT1++;
							sprintf(str,"%d",RT1);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0);
							break;
						
							case 1: RT2++;
							sprintf(str,"%d",RT2);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0+4);
							break;
						
							case 2: RT3++;
							sprintf(str,"%d",RT3);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0+8);
							break;
						}
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='8'&&key!=0xff &&key!='#')				//to decrease value
					{
						uint8 p=abs(cur_position%3);
						switch (p)
						{
							case 0: RT1--;
							sprintf(str,"%d",RT1);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0);
							break;
						
							case 1: RT2--;
							sprintf(str,"%d",RT2);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0+4);
							break;
						
							case 2: RT3--;
							sprintf(str,"%d",RT3);
							LCD_voidSendString(str);
							LCD_voidSendCommand(0xC0+8);
							break;
						}
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='#'&&key!=0xff)				//to confirm values and return to the main list
					{
					
						//_delay_ms(300);
						UART_voidSendchar(0x07);
						_delay_ms(100);
						//LCD_voidSendCommand	(0x01);
						//LCD_voidSendCommand(0x80);
						//LCD_voidSendString("sending");
						UART_voidSendchar(RT1);
						_delay_ms(100);
						UART_voidSendchar(RT2);
						_delay_ms(100);
						UART_voidSendchar(RT3);
						_delay_ms(100);
					
						UART_voidSendchar(0x55);
						_delay_ms(100);
						LCD_voidSendCommand(0x01);
						x=1;
					}
				}
			
				break;										//end of AC temperature option code
			
				/*---------------------------------------------------------------------------------------------------*/
				/*---------------------------------------------------------------------------------------------------*/
				case self_test:								//start of self test option code
				x=0;
				key=0;
				LCD_voidSendCommand(0x01);
				LCD_voidSendString("room number: ");
				//LCD_voidSendData('1');
			
			
				while (x==0)
				{
				key=0;
				key = KEYPAD_uint8GetKey();
				_delay_ms(50);
				//while (KEYPAD_uint8CheckPressed()==0);
			
			
				if (key=='8' && key!=0xff)
				{
					option++;
					key=0;
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				else if (key=='2' && key!=0xff )
				{
					option--;
					key=0;
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				else if (key=='#' && key!=0xff)				//confirm
				{
					y=0;
					LCD_voidSendCommand(0xC0);
					LCD_voidSendString("req. type:");
					LCD_voidSendString("open");				//default is door open
				
				
				
					while (y==0)
					{
					key=0;
					key=KEYPAD_uint8GetKey();
					_delay_ms(50);
					//while (KEYPAD_uint8CheckPressed()==0);
				
				
					if (key=='8' && key!=0xff)					//press '8' to change from open to close
					{
						LCD_voidSendCommand(0xCA);
						LCD_voidSendString("close");
						while (1)
						{
							key=0;
							key=KEYPAD_uint8GetKey();
							_delay_ms(50);
							//while (KEYPAD_uint8CheckPressed()==0);
							if (key=='#' && key!=0xff)				//confirm on door close
							{
								UART_voidSendchar(0x0A);
								LCD_voidSendCommand(0xc0);
								LCD_voidSendString("Sent 0x0A");
								_delay_ms(100);
								UART_voidSendchar(opt);
								_delay_ms(100);
								UART_voidSendchar(0x55);
								_delay_ms(100);
								LCD_voidSendCommand(0x01);
								y=1;
								x=1;
								break;
							}
						}
					
					
					}
				
					/*---------------------------------------------------------------------------------------------------*/
					else if (key=='#' && key!=0xff)				//confirm on door open
					{
						UART_voidSendchar(0x09);
						_delay_ms(100);
						UART_voidSendchar(opt);
						_delay_ms(100);
						UART_voidSendchar(0x55);
						_delay_ms(100);
						LCD_voidSendCommand(0x01);
						y=1;
						x=1;
					}
					//break;
					}
				
				}
			
				/*---------------------------------------------------------------------------------------------------*/
				 opt=abs((option)%5);
				switch (opt)					//ROOM NUMBER LIST
				{
					case 0: 
					LCD_voidSendData('1');
					LCD_voidSendCommand(0x10);
					break;
					case 1: 
					LCD_voidSendData('2');
					LCD_voidSendCommand(0x10);
					break;
					case 2: 
					LCD_voidSendData('3');
					LCD_voidSendCommand(0x10);
					break;
					case 3: 
					LCD_voidSendData('4');
					LCD_voidSendCommand(0x10);
					break;
					case 4: 
					LCD_voidSendData('5');
					LCD_voidSendCommand(0x10);
					break;
					//default: break;
				}
			
				}								
				break;									//end of self test option code
			
				/*---------------------------------------------------------------------------------------------------*/
				/*---------------------------------------------------------------------------------------------------*/
				case RGB_Light:
				UART_voidSendchar(0x03);
				break;
			}
		}
	
		char c=abs((list)%5);
		switch(c)
		{
			case change_passkey: LCD_voidSendCommand(0x80);
			LCD_voidSendString(change_pass);
			//_delay_ms(200);
			//LCD_voidSendCommand(0xC0);
		
			key=0;
			break;
		
			case digital_calender: LCD_voidSendCommand(0x80);
			LCD_voidSendString(dig_calender);
			//_delay_ms(200);
			//LCD_voidSendCommand(0x02);
			key=0;
			break;
		
			case AC_temperature: LCD_voidSendCommand(0x80);
			LCD_voidSendString(temperature);
			//_delay_ms(200);
			//LCD_voidSendCommand(0x80);
			key=0;
			break;
		
			case self_test: LCD_voidSendCommand(0x80);
			LCD_voidSendString(selfTest);
			//_delay_ms(200);
			//LCD_voidSendCommand(0x80);
			key=0;
			break;
		
			case RGB_Light:LCD_voidSendCommand(0x80);
			LCD_voidSendString(light_control);
			//_delay_ms(200);
			//LCD_voidSendCommand(0x02);
			key=0;
			break;
			default: break;
		}
	} // While(1)
	
} 