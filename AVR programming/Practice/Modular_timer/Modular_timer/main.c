/*
 * Modular_timer.c
 *
 * Created: 02-12-2025 20:24:49
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay.h"   


int main(void)
{
    DDRB|=(1<<DDB5); // set PB5 as output 
	timer0_init();
    while (1) 
    {
		PORTB^=(1<<PB5);
		delay_ms(3000);    // user defined function for delay
    }
}

