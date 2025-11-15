/*
 * Blink_XOR.c
 *
 * Created: 15-11-2025 21:49:35
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD|=(1<<DDD5);          // Set DDD5(PD5) as output
    
    while (1) 
    {
		PORTD^=(1<<PD5);     // Set PD5=1 (XOR is used)
		_delay_ms(3000);
		PORTD^=(1<<PD5);     // Set PD5=0 (XOR is used)
		_delay_ms(1000);
    }
}

