/*
 * traffic traffic.c
 *
 * Created: 12-12-2025 16:38:11
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void redlight();
void yellowlight();
void greenlight();
void motor();
void clearlight();

ISR(INT0_vect)
{
	//redlight();
	motor();
}



int main(void)
{
	sei(); //enable interrupt

	EIFR|=(1<<INTF0); //manually make it zero

	EIMSK|=(1<<INT0); //enable external interrupt

	EICRA|=(1<<ISC00)|(1<<ISC01); //configuring interrupt for rising edge

	//DDRD&=~(1<<DDD1);  //port D input port

	//PORTD|=(1<<PD1); // internal pull up

	DDRB|=(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5);// port B output port
	/* Replace with your application code */
	while (1)
	{
		greenlight();
		_delay_ms(5000);
		yellowlight();
		_delay_ms(2000);
		redlight();
		_delay_ms(5000);
		yellowlight();
		_delay_ms(2000);
	}
}
void redlight()
{
	clearlight();
	PORTB|=(1<<PB3);
	//_delay_ms(5000);
}
void greenlight()
{
	clearlight();
	PORTB|=(1<<PB1);
	//_delay_ms(5000);
}
void yellowlight()
{
	clearlight();
	PORTB|=(1<<PB2);
	//_delay_ms(2000);
}
void motor()
{
	redlight();
	PORTB|=(1<<PB4);
	PORTB&=~(1<<PB5);
	_delay_ms(3000);
	PORTB&=~(1<<PB4);
	PORTB|=(1<<PB5);
	_delay_ms(3000);
	PORTB&=~(1<<PB4);
	PORTB&=~(1<<PB5);
}
void clearlight()
{
	PORTB&=~((1<<PB3)|(1<<PB2)|(1<<PB1));
}
