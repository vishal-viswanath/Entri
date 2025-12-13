/*
 * PWM_LEDandMOTOR.c
 *
 * Created: 05-12-2025 21:32:55
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // Configuring DDRD, set as output
	DDRD|=(1<<DDD5);
	DDRD|=(1<<DDD6);
	
	// Store initial value of  TCNT0
	TCNT0=0;
	
	// Configure PWM mode(here phase correct PWM chosen)
	TCCR0A|=(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	
	// Configuring non-inverting mode,OCR0A chosen here
	TCCR0A|=(1<<COM0A1);
	TCCR0A&=~(1<<COM0A0);
	
	// Configuring non-inverting mode,OCR0B chosen here
	TCCR0A|=(1<<COM0B1);
	TCCR0A&=~(1<<COM0B0);
	
	// Configure prescalar 64 
	TCCR0B|=((1<<CS00)|(1<<CS01));
	TCCR0B&=~(1<<CS02);
	
	//Configure OCR0B value for output power
	OCR0B=255;
	
    while (1) 
    {
		for(int i=0;i<255;i++)
		{
			OCR0A=i;
			_delay_ms(5);
		}
		for(int i=255; i>0; i--)
		{
			OCR0A=i;
			_delay_ms(10);
		}
	}
}

