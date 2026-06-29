/*
 * traffic_interrupt.c
 *
 * Created: 28-06-2026 18:53:18
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t emergency_flag = 0;

void clearlight(void)
{
	PORTB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3));
}

void greenlight(void)
{
	clearlight();
	PORTB |= (1 << PB1);
}

void orangelight(void)
{
	clearlight();
	PORTB |= (1 << PB2);
}

void redlight(void)
{
	clearlight();
	PORTB |= (1 << PB3);
}

ISR(INT0_vect)
{
	emergency_flag = 1;
}

int main(void)
{
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
	DDRD &= ~(1 << DDD2);
	PORTD |= (1 << PD2);

	EICRA &= ~(1 << ISC00);
	EICRA |= (1 << ISC01);     // falling edge
	EIMSK |= (1 << INT0);
	sei();

	while (1)
	{
		greenlight();
		_delay_ms(10000);
		if (emergency_flag)
		{
			emergency_flag = 0;
			greenlight();
			_delay_ms(10000);
		}

		orangelight();
		_delay_ms(3000);
		if (emergency_flag)
		{
			emergency_flag = 0;
			greenlight();
			_delay_ms(10000);
		}

		redlight();
		_delay_ms(10000);
		if (emergency_flag)
		{
			emergency_flag = 0;
			greenlight();
			_delay_ms(10000);
		}
	}
}


