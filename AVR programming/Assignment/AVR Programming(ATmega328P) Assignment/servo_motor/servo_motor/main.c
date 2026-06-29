/*
 * servo_motor.c
 *
 * Created: 28-06-2026 21:55:46
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"
#include "adc.h"

int main(void)
{
	
	Init_PWM();   // Initialize timer1 PWM for servo control
	
	Init_ADC();   // Initialize ADC for reading potentiometer
	
	uint16_t ADC_value, pulse_width;
	
	while (1)
	{
		
		ADC_value= Get_ADC_value();     // Read potentiometer value
		
		pulse_width = Map_ADC_To_PulseWidth(ADC_value);   // Convert ADC value to servo pulse width
		
		Set_pulse_width(pulse_width);     // Update pulse width to control servo angle
		
		_delay_ms(5);
	}
}

