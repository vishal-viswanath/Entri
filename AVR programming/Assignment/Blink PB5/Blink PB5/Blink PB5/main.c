/*
 * Blink PB5.c
 *
 * Created: 14-11-2025 23:18:28
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
   DDRB=0b00100000;           // set DDB5(PB5) as output
    while (1) 
    {
		PORTB=0b00100000;    // set PB5=1
		_delay_ms(3000);
		PORTB=0b00000000;    // set PB5=0
		_delay_ms(3000);
		
    }
}

