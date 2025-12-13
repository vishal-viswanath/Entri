/*
 * PWM_DC_motor.c
 *
 * Created: 30-11-2025 14:44:58
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Configure
	
	DDRD|=(1<<DDD6);
	
	// configuring for phase correct PWM
	
	TCCR0A|=(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	
	//configuring for non inverting PWM
	
	TCCR0A|=(1<<COM0A1);
	TCCR0B&=~(1<<COM0A0);
	
	// configure for prescalar =8
	
	TCCR0B&=~(1<<CS02);
	TCCR0B&=~(1<<CS01);
	TCCR0B|=(1<<CS00);
	
	OCR0A=100;
	
	
	while (1)
	{
	}
}

