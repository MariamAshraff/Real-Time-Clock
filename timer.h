/*
 * timer.h
 *
 * Created: 9/1/2014 7:22:18 PM
 *  Author: M
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer0_CTC_init_interrupt(void);
void timer_wave_nonPWM(void);
void timer_wave_fastPWM(void);
void timer_wave_phasecorrectPWM(void);
void timer2_overflow_init_interrupt(void);

#endif /* TIMER_H_ */