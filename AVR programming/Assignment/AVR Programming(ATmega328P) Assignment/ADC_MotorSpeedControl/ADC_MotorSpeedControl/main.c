/*
 * ADC_MotorSpeedControl.c
 *
 * Created: 29-06-2026 13:08:51
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"
#include "adc.h"


int main(void)
{
	
	Init_PWM();   // Initialize PWM on pin PD6
	
	Init_ADC();   // initialize ADC for reading potentiometer
	
	while (1)
	{
		
		Map_ADC_To_CompareValue();    // Read ADC value to control motor speed
		
		_delay_ms(10);
	}
}