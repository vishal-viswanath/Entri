/*
 * timer0_CTCmode.c
 *
 * Created: 29-11-2025 13:25:13
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_3s()  // defining delay function
{
	for(int i=0;i<300;i++)  // Set loop for 3 second delay.prescalar is 1024.compare value is 156.
	{
		while(!(TIFR0&(1<<OCF0A)));  // Wait until OCF0A flag set
		TIFR0|=(1<<OCF0A);           // Reset OCF0A flag to 0
	}
}


int main(void)
{
	TCNT0=0;                    // Load minimum value of counter
	OCR0A=156;                  // Set maximum compare value
	
	TCCR0A&=~(1<<WGM00);        // configure timer mode as CTC
	TCCR0A|=(1<<WGM01);
	
	TCCR0B|=(1<<CS00|1<<CS02);  // configure frequency mode (prescalar(1024))
	TCCR0B&=~(1<<CS01);
		
	DDRB|=(1<<DDB5);           // Set DDB as output
	
	while (1)
	{
		PORTB^=(1<<PB5);       // Toggle PB5
		delay_3s();            // Calling user defined delay function
	}
}