/*
 * LED_brightnes_control.c
 *
 * Created: 28-06-2026 19:14:09
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void Init_FastPWM()
{

	TCCR0A |= (1<< WGM01) | (1<< WGM00);   // Set Fast PWM mode (WGM01 = 1, WGM00 = 1)
	
	TCCR0A |= (1<< COM0A1);   // Set non-inverting output on OC0A(PD6): COM0A 1:0= 10
	TCCR0A &= ~(1<< COM0A0);
	
	// Set duty cycle 25%
	// compare value = duty cycle*(top)/ 100

	OCR0A = 63;
	
	TCCR0B &= ~(1<< CS02);   // Set prescaler 64: CS0 2:0= 011
	TCCR0B |= (1<< CS01)|(1<< CS00);
}

// Use an array to store compare values
// Duty cycles : 25%, 50%, 75%, 100%, OFF
uint8_t pwm_level[]= {63, 127, 191, 255, 0}, i=0;

// Update duty cycle when button press occurs
// Continue same pattern after full cycle
void Update_brightness()
{
	i++;
	
	if(i>=5)
	{
		i =0;
	}
	OCR0A = pwm_level[i];
}
void Init_pins()
{
	
	DDRD |= (1<< DDD6);     // Set PD6 as output pin for PWM
	
	DDRD &= ~(1<< DDD2);    // Set PD2 as input for push button and enable pull-up resistor
	PORTD |= (1<< PORTD2);
}


int main(void)
{
	Init_FastPWM();
	
	Init_pins();
	
	uint8_t prev_state=1, current_state;    // Variables for edge detection
	
	while (1)
	{
		
		current_state = (PIND >>2)&1;           // Read button state on PD2 (0 = pressed due to pull-up)
		
		if(prev_state==1 && current_state==0)   // If Edge detected
		{
			
			_delay_ms(20);           // wait for bounce to settle
			
			if(!(PIND&(1<<PIND2)))   // re-check button state
			{
				Update_brightness();
			}
			
		}
		
		prev_state= current_state;  // Reset state
	}
}


