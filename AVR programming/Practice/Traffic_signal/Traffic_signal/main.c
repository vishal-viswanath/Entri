/*
 * Traffic_signal.c
 *
 * Created: 20-11-2025 19:39:55
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void RED()                        //set PD3=1,PD4 and PD5 0
{
	PORTD|=(1<<PD3);
	PORTD&=~(1<<PD4);
	PORTD&=~(1<<PD5);
	_delay_ms(5000);
}

void ORANGE()                  // set PD4=1, PD3 and PD5 0
{
	PORTD&=~(1<<PD3);
	PORTD|=(1<<PD4);
	PORTD&=~(1<<PD5);
	_delay_ms(3000);
}

void GREEN()                  // set PD5=1, PD3 and PD4 0
{
	PORTD&=~(1<<PD3);
	PORTD&=~(1<<PD4);
	PORTD|=(1<<PD5);
	_delay_ms(5000);
}
int main(void)
{
   DDRD|=((1<<DDD3) | (1<<DDD4) | (1<<DDD5));         // set DDD3,DDD4 and DDD5 as output
    while (1) 
    {                                               
		RED();
		ORANGE();
		GREEN();
    }
	return 0;
}


