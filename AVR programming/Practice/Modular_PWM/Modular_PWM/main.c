/*
 * Modular_PWM.c
 *
 * Created: 08-12-2025 20:12:21
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "power.h"


int main(void)
{
	//Set DDD6 as output
	DDRD|=(1<<DDD6);
	//User defined function for configure POWER control
    power_init();
	// User defined function for set power/speed
	speed(64);
    while (1) 
    {
    }
}

