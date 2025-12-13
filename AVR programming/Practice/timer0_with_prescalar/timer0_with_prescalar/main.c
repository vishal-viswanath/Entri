/*
 * timer0_with_prescalar.c
 *
 * Created: 29-11-2025 12:33:15
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s()    //Defining a function
{
	for(int i=0;i<61;i++)   // Repeating the loop for 61 times for get 1sec delay
	{
		while(!(TIFR0&(1<<TOV0)));   // waiting for timer flag (TOV0) to set 1.
		TIFR0|=(1<<TOV0);            // Reset timer flag to 0.
	}
}

int main(void)
{
    TCNT0=0;   // Set timer0 value
	
	TCCR0A&=~(1<<WGM00|WGM01);  // Select timer mode (normal mode)
	
	TCCR0B|=(1<<CS00|1<<CS02);  // Select clk mode (prescalar 1024)
	TCCR0B&=~(1<<CS01);
	
	DDRB|=(1<<DDB5);    // Set DDB5 1
		
    while (1) 
    {
		PORTB^=(1<<PB5);   //Toggling PB5
		delay_1s();    // Calling user defined dalay function
    }
}

