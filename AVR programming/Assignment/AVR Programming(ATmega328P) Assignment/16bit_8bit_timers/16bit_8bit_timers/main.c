/*
 * 16bit_8bit_timers.c
 *
 * Created: 28-06-2026 18:57:43
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>

void Timer1_init()
{
	
	TCCR1B &= ~(1<< WGM13);  // Set CTC mode: WGM1 3:0 = 0100
	TCCR1B |= (1<< WGM12);
	TCCR1A &= ~((1<< WGM11)|(1<< WGM10));
	
	TCNT1= 0;   // Reset count
	
	OCR1A = 49999;   // Set compare value
	
	TCCR1B &= ~(1<< CS12);   // Set pre-scalar 64 : CS1 2:0 = 011
	TCCR1B |= (1<< CS11) | (1<< CS10);
	
	TIMSK1 |= (1<< OCIE1A);  // Enable compare match interrupt
	
}

void Timer2_init()
{
	// Set CTC mode : WGM2 2:0= 010
	TCCR2A |= (1<< WGM21);
	TCCR2A &= ~(1<< WGM20);
	TCCR2B &= ~(1<< WGM22);
	
	
	TCNT2 =0;      // Reset count
	
	
	OCR2A = 249;   // Set compare value
	
	
	TCCR2B |= (1<< CS22)|(1<< CS21);  // Set pre scalar 256 : CS2 2:0 = 110
	TCCR2B &= ~(1<< CS20);
	
	TIMSK2 |= (1<< OCIE2A);    // Enable compare match interrupt
	
}
// Define ISR for timer1 and timer2

volatile uint16_t count_1=0, count_2=0;
ISR(TIMER1_COMPA_vect)
{
	count_1++;
	
	if(count_1==10)
	{
		
		PORTB ^= (1<< PORTB1);  // Toggle LED and reset count
		
		count_1=0;
	}
}
ISR(TIMER2_COMPA_vect)
{
	count_2++;
	
	if(count_2== 125)
	{
		
		PORTB ^= (1<< PORTB2);  // Toggle LED and reset count
		
		count_2=0;
	}
}
void Init_pins()
{
	DDRB |= (1<< DDB1);
	DDRB |= (1<< DDB2);
}

int main(void)
{
	
	Init_pins();    // Initialize pins for LEDs
	
	Timer1_init();  // Initialize timers
	Timer2_init();
	
	sei();          // Enable global interrupt
	
	while (1)
	{
	}
}


