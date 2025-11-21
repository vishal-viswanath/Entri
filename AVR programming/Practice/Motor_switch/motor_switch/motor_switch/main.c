/*
 * motor_switch.c
 *
 * Created: 20-11-2025 21:11:25
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
   DDRD&=~(1<<DDD2);                         // set DDD2 as input
   DDRD&=~(1<<DDD5);                         // set DDD5 as input
   DDRB|=(1<<DDB5);                          // set DDB5 as output
   DDRB|=(1<<DDB4);                          // set DDb4 as output
    while (1) 
    {
		if(PIND&(1<<PD2) && !(PIND&(1<<PD5)))          // check PD2 high and PD5 low
		{
			PORTB|=(1<<PB4);                           // set PB4=1
			PORTB&=~(1<<PB5);                          // set PB5=0
		}
		else if(PIND&(1<<PD5) && !(PIND&(1<<PD2)))     // check PD5 high and PD2 low
		{   
			PORTB&=~(1<<PB4);                          // set PB4=0 
			PORTB|=(1<<PB5);                           // set PB5=1
		}
		else
		{
			PORTB&=~(1<<PB4);                          // set PB4=0
			PORTB&=~(1<<PB5);                          // set PB5=0
		}
    }
}

