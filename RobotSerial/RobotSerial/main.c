/*
* LCDScreens.c
*
* Created: 2/6/2023 3:38:41 PM
* Author : ssami
*/
#include "C:/Users/ssami/Desktop/MRE_lib/F_cpu_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "C:/Users/ssami/Desktop/MRE_lib/LCD_lib.h"
#include "C:/Users/ssami/Desktop/MRE_lib/Serial_lib2.h"
#include "C:/Users/ssami/Desktop/MRE_lib/A2D_lib.h"
#include "C:/Users/ssami/Desktop/MRE_lib/Motor_PWM_lib.h"
#define FORWARD 001
#define LEFT 002
#define RIGHT 003
#define STOP 004
#define SLEFT 005
#define SRIGHT 006

int main(void)
{
	uint16_t valAD = 0;
	uint8_t PC_char;
	

	LCD_init(); // col, row initialize the LCD display
	LCDGoToPosition(1, 1); // set col, row starting point for string on LCD
	
	_delay_ms(1000); //wait for one second.
	AD_init(); // setup the analog inputs.
	USART_vInit();
	sei(); // enable interrupts
	LCDClearScreen();
	HBridgeInit();
	uint8_t state = STOP;
	
	/* Replace with your application code */
	while (1)
	{
		uint16_t val;
		
		if(ADComplete)
		{
			val= getADval(0);
			ADComplete =0;
		}
		if(serialCheckRxComplete()!= 0)
		{
			PC_char = USART_vReceiveByte();
		}
		

		//States of the robot		
		switch(state){
			
			//0 is right motor, 1 is left motor
			//1 is forward, 0 is backwards
			
			case FORWARD:
			HBridgeCommand(1,95,0);
			HBridgeCommand(0,100,0);
			if(PC_char == 'f')
			{
				state = FORWARD;
				
				
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			case LEFT:
			HBridgeCommand(0,100,0);
			HBridgeCommand(1,0,0);
			if(PC_char =='l'){
				
				
				}else if (PC_char ='f'){
				state = FORWARD;
				
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			case RIGHT:
			HBridgeCommand(1,100,0);
			HBridgeCommand(0,0,0);
			if(PC_char == 'r'){
			
				}else if (PC_char ='f'){
				state = FORWARD;
				
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			case STOP:
			_delay_ms(2000);
			HBridgeCommand(0,0,1);
			HBridgeCommand(1,0,1);
			if(PC_char == 's'){
				
				
				}else if (PC_char ='f'){
				state = FORWARD;
				
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			case SLEFT:
			HBridgeCommand(0,100,0);
			HBridgeCommand(1,60,0);
			if(PC_char == 'a'){
			
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			case SRIGHT:
			HBridgeCommand(1,100,0);
			HBridgeCommand(0,60,0);
			if(PC_char =='d'){
			
				
				}else if(PC_char == 'l'){
				state = LEFT;
				}else if (PC_char =='r'){
				state = RIGHT;
				}else if(PC_char =='s'){
				state = STOP;
				}else if(PC_char =='a'){
				state = SLEFT;
				}else if(PC_char =='d'){
				state=SRIGHT;
				
			}
			break;
			default:
			// code to execute if PC_char doesn't match any of the cases
			HBridgeCommand(1,0,1);
			HBridgeCommand(0,0,1);
			break;
		}
	
	}

}