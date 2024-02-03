/*
 * Real_Time_Clock.c
 *
 * Created: 2/3/2024 6:20:55 AM
 *  Author: Mariam
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "sev_seg.h"
#include "LCD.h"
#include "keypad.h"
#include "std_macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>
volatile unsigned char sec_counter=0;
unsigned char minutes=0,hours=0;
unsigned char val,first_digit,second_digit;
int main(void)
{
	LCD_vInit();
	keypad_vInit();
	seven_seg_vinit('B');
	LCD_vSend_string(" Press 1 to set");
	LCD_movecursor(2,6);
	LCD_vSend_string("clock");
	timer2_overflow_init_interrupt();
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRA,3);
	SET_BIT(DDRD,3);
	while(1)
	{
		val=keypad_u8check_press();
		if (val!=NOTPRESSED)
		{
			SET_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			SET_BIT(PORTA,3);
			SET_BIT(PORTD,3);
			if (val=='1')
			{
				label1:
				LCD_clearscreen();
				LCD_vSend_string("Hours=--");
				LCD_movecursor(1,7);
				_delay_ms(500);
				do 
				{
					first_digit=keypad_u8check_press();
					
				} while (first_digit==NOTPRESSED);
				LCD_vSend_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_u8check_press();
					
				} while (second_digit==NOTPRESSED);
				LCD_vSend_char(second_digit);
				_delay_ms(300);
				hours=(first_digit-48)*10+(second_digit-48);
				if (hours>24)
				{
					LCD_clearscreen();
					LCD_vSend_string("Error Hours are");
					LCD_movecursor(2,1);
					LCD_vSend_string("between 0 and 24");
					_delay_ms(2000);
					LCD_clearscreen();
					LCD_vSend_string("   Try again");
					_delay_ms(1000);
					goto label1;
				}
				label2:
				LCD_clearscreen();
				LCD_vSend_string("minutes=--");
				LCD_movecursor(1,9);
				_delay_ms(500);
				do
				{
					first_digit=keypad_u8check_press();
					
				} while (first_digit==NOTPRESSED);
				LCD_vSend_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_u8check_press();
					
				} while (second_digit==NOTPRESSED);
				LCD_vSend_char(second_digit);
				_delay_ms(300);
				minutes=(first_digit-48)*10+(second_digit-48);
				if (minutes>60)
				{
					LCD_clearscreen();
					LCD_vSend_string("Error min are");
					LCD_movecursor(2,1);
					LCD_vSend_string("between 0 and 60");
					_delay_ms(2000);
					LCD_clearscreen();
					LCD_vSend_string("   Try again");
					_delay_ms(1000);
					goto label2;
				}
				label3:
				LCD_clearscreen();
				LCD_vSend_string("seconds=--");
				LCD_movecursor(1,9);
				_delay_ms(500);
				do
				{
					first_digit=keypad_u8check_press();
					
				} while (first_digit==NOTPRESSED);
				LCD_vSend_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_u8check_press();
					
				} while (second_digit==NOTPRESSED);
				LCD_vSend_char(second_digit);
				_delay_ms(300);
				sec_counter=(first_digit-48)*10+(second_digit-48);
				if (sec_counter>60)
				{
					LCD_clearscreen();
					LCD_vSend_string("Error sec are");
					LCD_movecursor(2,1);
					LCD_vSend_string("between 0 and 60");
					_delay_ms(2000);
					LCD_clearscreen();
					LCD_vSend_string("   Try again");
					_delay_ms(1000);
					goto label3;
				}
				
			}
			else
			{
				LCD_clearscreen();
				LCD_vSend_string("  Wrong answer");
				LCD_movecursor(2,4);
				LCD_vSend_string("try again");
				_delay_ms(1000);
				
			}
			LCD_clearscreen();
			LCD_vSend_string(" Press 1 to set");
			LCD_movecursor(2,6);
			LCD_vSend_string("clock");
			
			
		}
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTA,3);
		SET_BIT(PORTD,3);
		CLR_BIT(PORTC,0);
		seven_seg_write('B',sec_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTA,3);
		SET_BIT(PORTD,3);
		CLR_BIT(PORTC,1);
		seven_seg_write('B',sec_counter/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,3);
		SET_BIT(PORTA,3);
		SET_BIT(PORTD,3);
		CLR_BIT(PORTC,2);
		seven_seg_write('B',minutes%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTA,3);
		SET_BIT(PORTD,3);
		CLR_BIT(PORTC,3);
		seven_seg_write('B',minutes/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTD,3);
		CLR_BIT(PORTA,3);
		seven_seg_write('B',hours%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTA,3);
		CLR_BIT(PORTD,3);
		seven_seg_write('B',hours/10);
		_delay_ms(5);
		if (sec_counter==60)
		{
			sec_counter=0;
			minutes++;
		}
		if (minutes==60)
		{
			minutes=0;
			hours++;
		}
		if (hours==24)
		{
			hours=0;
		}
		
	}

}
ISR(TIMER2_OVF_vect)
{
	sec_counter++;
}