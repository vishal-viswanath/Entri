/*
 * PWM.c
 *
 * Created: 28-06-2026 22:06:19
 *  Author: User
 */ 

#include <avr/io.h>

void Init_PWM()
{
	
	TCCR1B |= (1<< WGM13);     // Set mode10 (Phase correct PWM with top= ICR1)
	TCCR1B &=~(1<< WGM12);
	TCCR1A |= (1<< WGM11);
	TCCR1A &=~(1<< WGM10);
	
	TCCR1A |= (1<< COM1A1);    // Set non-inverting output on OC1A (PB1)
	TCCR1A &= ~(1<< COM1A0);
	
	DDRB|= (1<< DDB1);    // Set PB1 as output pin
	
	ICR1 = 19999;    // Set top value: 19999 (top+1= 20000)
	
	TCCR1B &=~((1<< CS12)| (1<< CS10));   // Set pre scaler 8: CS2:0 = 010
	TCCR1B |= (1<< CS11);
	
}

void Set_pulse_width(uint16_t pulse_width)
{

	uint16_t comp_value= (pulse_width*2);
	OCR1A = comp_value;
}