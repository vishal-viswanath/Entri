/*
 * power.c
 *
 * Created: 08-12-2025 20:13:37
 *  Author: User
 */ 

#include <avr/io.h>
#include "power.h"

void power_init(void)
{
	//Set TCNT0=0
	TCNT0=0;
	//Configure PWM mode(phase correct PWM)
	TCCR0A|=(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	//Configure non-inverting mode
	TCCR0A|=(1<<COM0A1);
	TCCR0A&=~(1<<COM0A0);
	//Set prescalar for appropriate frequency(here clk frequency selected without prescalar)
	TCCR0B|=(1<<CS00);
	TCCR0B&=~(1<<CS01);
	TCCR0B&=~(1<<CS02);
		
}
void speed(uint16_t power)
{
	OCR0A=power;
}
