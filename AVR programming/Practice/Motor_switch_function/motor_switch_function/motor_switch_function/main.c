/*
 * motor_switch_function.c
 *
 * Created: 21-11-2025 14:33:44
 * Author : User
 */ 

#include <avr/io.h>

void CW(void);
void CCW(void);
void STP(void);

int main(void)
{
    DDRD&= ~((1<<DDD2) | (1<<DDD5));
	DDRB|=(1<<DDB4) | (1<<DDB5);
	
    while (1) 
    {
		if((PIND&(1<<PD2)) && !(PIND&(1<<PD5)))
		{
			CW();
		}
		else if((PIND&(1<<PD5)) && !(PIND&(1<<PD2)))
		{
			CCW();
		}
		else
		{
			STP();
		}
    }
}
void CW()
{
	PORTB|=(1<<PB4);
	PORTB&=~(1<<PB5);
}
void CCW()
{
	PORTB|=(1<<PB5);
	PORTB&=~(1<<PB4);
}
void STP()
{
	PORTB&=~(1<<PB4);
	PORTB&=~(1<<PB5);
}


