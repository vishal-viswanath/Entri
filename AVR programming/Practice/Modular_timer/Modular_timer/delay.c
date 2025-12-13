/*
 * delay.c
 *
 * Created: 02-12-2025 20:31:40
 *  Author: User
 */ 
#include<avr/io.h>
#include "delay.h"


void timer0_init(void)    
{
	TCNT0=0;  //Set timer counter
	
	TCCR0A&=~(1<<WGM00);   // configure WGM in CTC mode (clear timer on compare match
	TCCR0A|=(1<<WGM01);
	
	TCCR0B|=(1<<CS00|1<<CS01);   // set prescalar 64
	TCCR0B&=~(1<<CS02);
	
	OCR0A=249;                   // load compare value on Output compare register 0A(OCR0A)
}
void delay_ms(uint16_t ms)
{
	
	while(ms--)
	{
		
	while(!(TIFR0&(1<<OCF0A)));
	TIFR0|=(1<<OCF0A);
    }
}