/*
 * timer.c
 *
 * Created: 9/1/2014 7:22:07 PM
 *  Author: m
 */ 
 
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
void timer0_CTC_init_interrupt(void)
{
	/* select CTC mode*/
	SET_BIT(TCCR1B,WGM12);
	/* load a value in OCR0 */
	 OCR1A = 39062.5;
	/* select timer clock */	
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS12);
	/* enable interrupt*/
	sei();
	SET_BIT(TIMSK,OCIE1A);
	
}
void timer2_overflow_init_interrupt(void){
	SET_BIT(ASSR,AS2);
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	sei();
	SET_BIT(TIMSK,TOIE2);
}
