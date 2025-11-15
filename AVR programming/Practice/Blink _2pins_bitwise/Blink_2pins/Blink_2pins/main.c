/*
 * Blink_2pins.c
 *
 * Created: 15-11-2025 20:56:08
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD|=(1<<DDD5)|(1<<DDD2);     // Set DDD5(PD5) and DDD2 (PD2) as output                 
	                   
    
    while (1) 
    {
		// Pin 1 on 2 off
		PORTD|=(1<<PD2); 
		PORTD&=~(1<<PD5);              
		_delay_ms(5000);
		
		// Pin 1 and 2 off
		PORTD&=~(1<<PD2); 
		PORTD&=~(1<<PD5);           
		_delay_ms(3000);
		
		// Pin 1 off 2 on
		PORTD&=~(1<<PD2);
		PORTD|=(1<<PD5);               
		_delay_ms(5000);
		
		             
		
    }
}

