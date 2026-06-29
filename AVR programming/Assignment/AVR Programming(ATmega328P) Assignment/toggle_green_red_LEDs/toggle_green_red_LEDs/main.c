/*
 * toggle_green_red_LEDs.c
 *
 * Created: 28-06-2026 18:25:59
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD &= ~(1 << DDD2);   // PD2 input
	PORTD |= (1 << PD2);    // enable pull-up on PD2

	DDRB |= (1 << DDB5);    // PB5 output
	DDRB |= (1 << DDB4);    // PB4 output

	PORTB |= (1 << PB5);    // start with Red ON
	PORTB &= ~(1 << PB4);   // Green OFF

	while (1)
	{
		if (!(PIND & (1 << PD2)))                // button pressed, active low
		{
			_delay_ms(20);                       // debounce
			if (!(PIND & (1 << PD2)))
			{
				if (PORTB & (1 << PB5))
				{
					PORTB &= ~(1 << PB5);         // Red OFF
					PORTB |= (1 << PB4);          // Green ON
				}
				else
				{
					PORTB &= ~(1 << PB4);         // Green OFF
					PORTB |= (1 << PB5);          // Red ON
				}

				while (!(PIND & (1 << PD2)));     // wait for release
				_delay_ms(20);                    // debounce release
			}
		}
	}
}
