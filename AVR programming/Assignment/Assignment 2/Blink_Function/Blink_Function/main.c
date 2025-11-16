/*
 * Blink_Function.c
 *
 * Created: 16-11-2025 20:35:44
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void cw()                  // function to pin 1 on and pin 2 off
{
    PORTB|=(1<<PB5);
	PORTB&=~(1<<PB4);
	_delay_ms(5000);
}
void stp()
{
    PORTB&=~(1<<PB5);    // Both PB5 and PB4 off
	PORTB&=~(1<<PB4);
	_delay_ms(3000);
}
void ccw()
{
	PORTB&=~(1<<PB5);   // Function to pin 1 off and pin 2 off
	PORTB|=(1<<PB4);
	_delay_ms(5000);
}
	
int main(void)
{
    DDRB|=(1<<DDB5)|(1<<DDB4);    // set DDD5(PD5) and DDD4(PD4) as output
    while (1) 
    {
		cw();                    // function calling
		stp();
		ccw();
    }
    return 0;
}

