/*
 * oneway_traffic_light.c
 *
 * Created: 28-06-2026 18:45:48
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void delay_s(int sec)                //Defining a function
{
	for(int i=0;i<61*sec;i++)        // Repeating the loop for 61 times for get 1sec delay
	{
		while(!(TIFR0&(1<<TOV0)));   // waiting for timer flag (TOV0) to set 1.
		TIFR0|=(1<<TOV0);            // Reset timer flag to 0.
	}
}

void RED()                      //set PB2=1,PB3 and PB4 0
{
	PORTB|=(1<<PB2);
	PORTB&=~(1<<PB3);
	PORTB&=~(1<<PB4);
	delay_s(10);
}

void ORANGE()                  // set PB3=1, PB2 and PB4 0
{
	PORTB&=~(1<<PB2);
	PORTB|=(1<<PB3);
	PORTB&=~(1<<PB4);
	delay_s(3);
}

void GREEN()                  // set PB4=1, PB2 and PB3 0
{
	PORTB&=~(1<<PB2);
	PORTB&=~(1<<PB3);
	PORTB|=(1<<PB4);
	delay_s(10);
}
int main(void)
{
	TCNT0=0;   // Set timer0 value
	
	TCCR0A&=~(1<<WGM00|WGM01);  // Select timer mode (normal mode)
	
	TCCR0B|=(1<<CS00|1<<CS02);  // Select clk mode (prescalar 1024)
	TCCR0B&=~(1<<CS01);

	DDRB|=((1<<DDB2) | (1<<DDB3) | (1<<DDB4));  // set DDB2,DDB3 and DDB4 as output
	while (1)
	{
		GREEN();
		ORANGE();
		RED();
	}
	return 0;
}


