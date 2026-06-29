/*
 * adc.c
 *
 * Created: 28-06-2026 21:57:38
 *  Author: User
 */ 

#include <avr/io.h>

// Initialize ADC to read potentiometer
// - Set reference voltage as Avcc
// - Select channel 0
// - Set ADC frequency as 125KHz
// - Use single-shot conversion

void Init_ADC()
{
	
	ADMUX &=~(1<< REFS1);   // Reference voltage : REFS1:0 = 01
	ADMUX |=(1<< REFS0);
	
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) |(1<<MUX2) | (1<<MUX3));  // Select channel0: MUX2:0 = 000
	
	ADCSRA |= (1<< ADPS2)	|(1<< ADPS1)|(1<< ADPS0);   
	
	ADCSRA |= (1<< ADEN);  // Enable ADC
	
}

uint16_t Get_ADC_value()
{
	
	ADCSRA |= (1<< ADSC);    // Start conversion
	
	while(ADCSRA & (1<< ADSC));   // Wait till conversion finishes
	
	return ADC;   //Read value
}

uint16_t Map_ADC_To_PulseWidth(uint16_t ADC_value)
{
	
	uint16_t pulse_width = 1000 + ((uint32_t)ADC_value*1000)/1023;   // Prevent overflow : type cast to uint32_t
	
	return pulse_width;
}