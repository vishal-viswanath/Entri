/*
 * External_interrupt.c
 *
 * Created: 11-12-2025 19:25:33
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)                    //Interrupt select routine
{
	PORTB^=(1<<PB5);
	
}
int main(void)
{
    sei();                         //Enable global interrupt
	DDRB|=(1<<DDB5)|(1<<DDB4);     //Configure DDB5 and DDB4 as output
	EIMSK|=(1<<INT0);              //Select INT0 (PD2) as external interrupt 
	EICRA|=(1<<ISC00)|(1<<ISC01);  //Configure rising edge as interrupt 
	EIFR|=(1<<INTF0);              //Configure external interrupt flag
	
    while (1) 
    {
		PORTB&=~(1<<PB5);           //Set PB5=0
		PORTB^=(1<<PB4);            //Set PB4 toggling form
		_delay_ms(500);
		
    }
}

