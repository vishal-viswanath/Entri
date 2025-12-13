/*
 * PWM_Phase_correct.c
 *
 * Created: 29-11-2025 21:11:57
 * Author : User
 */ 

#include <avr/io.h>


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
	
	OCR0A=128;
	
	
    while (1) 
    {
    }
}

