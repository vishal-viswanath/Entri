/*
 * timer0_interrupt.c
 *
 * Created: 04-12-2025 20:44:58
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t count=0;      // define count
ISR(TIMER0_OVF_vect)            // Interrupt service routine Pgm(inside the parenthesis is the vector table address)
{
	if(count>977)
	{
		PORTB^=(1<<PB5);
		count=0;
	}
	else
	{
		count++;
	}
}
int main(void)
{
 DDRB|=(1<<DDB5);                // set DDB5 as output
 sei();                          // enable global interrupt( if use interrupt in the code, [sei();] it must use in the starting)
 TCNT0=0;                        // set TCNT0=0
 TCCR0A&=~(1<<WGM00|1<<WGM01);   // configure WGM normal mode
 
 TCCR0B|=(1<<CS00|1<<CS01);      // configure prescalar 64
 TCCR0B&=~(1<<CS02);
 
 TIMSK0|=(1<<TOIE0);             // set Timer interrupt mask register(here TIMSK0 bcz timer 0 is used for interruption)
 
    while (1) 
    {
		
    }
}

