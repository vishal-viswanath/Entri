/*
 * Blink.c
 *
 * Created: 13-11-2025 20:46:02
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRD=0b00000100;       // DDRD(PD2) as output               
    
    while (1) 
    {
		PORTD=0b00000100;  // set PD2=1
		_delay_ms(1000);
		PORTD=0b00000000;  // set PD2=0
		_delay_ms(1000);
    }
}

