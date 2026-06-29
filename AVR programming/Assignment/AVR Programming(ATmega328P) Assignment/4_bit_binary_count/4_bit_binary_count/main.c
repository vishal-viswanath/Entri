/*
 * 4_bit_binary_count.c
 *
 * Created: 28-06-2026 18:39:28
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void Init_pins()
{
	DDRD &= ~(1<< DDD2);                                             // Set PD2 as input for button : Enable pull up resistor
	PORTD |=(1<< PORTD2);
	
	DDRB |= (1<< DDB0)|(1<< DDB1)|(1<< DDB2)|(1<< DDB3);             // Set PB0,PB1,PB2,PB3 as output for LEDs
	PORTB&= ~((1<< PORTB0)|(1<< PORTB1)|(1<< PORTB2)|(1<< PORTB3));  // Set LEDs as LOW
}

uint8_t count=0;

void Update_count()
{
	
	count++;
	if(count > 15)
	{
		count = 0;
	}
	PORTB = count & 0x0F;
}

int main(void)
{
	
	Init_pins();  // Initialize pins
	
	
	uint8_t prev_state=1, current_state;  // Variables for edge detection
	
	while (1)
	{
		current_state = (PIND >>2)&1;
		
		if(prev_state==1 && current_state==0)  // If Edge detected
		{

			_delay_ms(20);            // wait for bounce to settle
			
			
			if(!(PIND&(1<<PIND2)))    // re-check button state
			{
				Update_count();
			}
			
		}
		
		prev_state= current_state;   // Reset state
		
		
	}
}


