/*
 * Timer0_without_prescalar.c
 *
 * Created: 28-11-2025 22:59:20
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)
{
	TCNT0=0;  //set timer0 value 0.
	
	TCCR0A&=~(1<<WGM00);  // set timer0 normal mode
	TCCR0A&=~(1<<WGM01);

	TCCR0B&=~(1<<CS01);   // set clk selector (no prescaling)
	TCCR0B&=~(1<<CS02);
	TCCR0B|=(1<<CS00);
	
	for(long int i=0; i<62500;i++) // repeat 62500 for getting 1sec delay 
	{
		while(!(TIFR0&(1<<TOV0))); // checking TOV0 flag
		TIFR0|=(1<<TOV0);        // writing 1 to make TOV0=0; strange rule
		
	}
	
	
}


int main(void)
{
    DDRB|=(1<<DDB5);     //set DDB5 output
	
    while (1) 
    {
		PORTB^=(1<<PB5); // set PB5 as output
		delay_1s();      // call delay function
    }
}

