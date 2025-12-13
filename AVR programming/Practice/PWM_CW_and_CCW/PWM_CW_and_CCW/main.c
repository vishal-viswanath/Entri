/*
 * PWM_CW_and_CCW.c
 *
 * Created: 08-12-2025 09:42:05
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // configure DDRD=1(output)
	DDRD|=((1<<DDD5)|(1<<DDD6));
	// set TCNT0=0
	TCNT0=0;
	
	// configure PWM mode (phase correct PWM selected)
	TCCR0A|=(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	
	// Select non-inverting mode (OCR is OCR0A)
	TCCR0A|=(1<<COM0A1);
	TCCR0A&=~(1<<COM0A0);
	
	// Configure non-inverting mode in OCR0B
	TCCR0A|=(1<<COM0B1);
	TCCR0A&=~(1<<COM0B0);
	
	//Configure prescalar(frequency)
	TCCR0B|=(1<<CS00);
	TCCR0B&=~(1<<CS01);
	TCCR0B&=~(1<<CS02);

    while (1) 
    {
		//CW rotation
		OCR0A=128;
		OCR0B=0;
		_delay_ms(2000);
		//CCW rotation
		OCR0B=250;
		OCR0A=0;
		_delay_ms(2000);
    }
}

