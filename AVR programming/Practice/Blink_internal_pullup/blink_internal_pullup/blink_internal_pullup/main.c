/*
 * blink_internal_pullup.c
 *
 * Created: 22-11-2025 20:57:14
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
	DDRD&=~(1<<DDD2);  // set DDD2 as input
	PORTD|=(1<<PD2);   // set PD2 as output
	DDRB|=(1<<PB2);    // set PD2 as output
	
	while (1)
	{
		if(!(PIND&(1<<PD2)))  //check condition 
		{
			PORTB|=(1<<PB2);
		}
		else
		{
			PORTB&=~(1<<PB2);
		}
	}
}

