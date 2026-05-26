/*
 * switch_interface.c
 *
 * Created: 20-11-2025 20:44:52
 * Author : User
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	DDRD&=~(1<<DDD2);           // configure DDD2 as input
	DDRB|=(1<<DDB5);           // configure DDB5 as output
	
	while (1)
	{
		if(PIND&(1<<PD2))      // check whether PD2=1
		{
			PORTB|=(1<<PB5);  // set PB5=1
		}
		else
		{
			PORTB&=~(1<<PB5);  // set PB5=0
		}
	}
}

