/*
 * PWM.c
 *
 * Created: 29-06-2026 13:12:15
 *  Author: User
 */ 

#include <avr/io.h>


void Init_PWM()   // Set Fast PWM on OC0A/PD6
{
	
	TCCR0B &= ~(1<< WGM02);     // Set Fast PWM on TIMER0 : WGM0 2:0 = 011
	TCCR0A |= (1<< WGM01)|(1<< WGM00);
	
	TCCR0A |=(1<<COM0A1);     // set non-inverting output on PD6: COM01:0 = 10
	TCCR0A &=~(1<< COM0A0);
	
	DDRD |= (1<< DDD6);    // set PD6 as output pin
	
	TCCR0B &=~(1<< CS02);    // set prescaler 64 : CS02:0=011
	TCCR0B |= (1<< CS01)|(1<< CS00);
	
}