/*
 * toggle_LED.c
 *
 * Created: 28-06-2026 18:10:19
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD|=(1<<DDD5);        // Set DDD5(PD5) as output
	while (1)
	{
		PORTD|=(1<<PD5);    // Set PD5=1
		_delay_ms(3000);
		PORTD&=~(1<<PD5);   // Set PD5=0
		_delay_ms(5000);
		
	}
}
