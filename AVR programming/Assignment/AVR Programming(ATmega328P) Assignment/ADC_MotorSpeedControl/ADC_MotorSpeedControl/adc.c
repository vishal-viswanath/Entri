/*
 * adc.c
 *
 * Created: 29-06-2026 13:13:52
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
	
	ADMUX &=~(1<< REFS1);    // Reference voltage : REFS1:0 = 01
	ADMUX |=(1<< REFS0);
	
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) |(1<<MUX2) | (1<<MUX3));     // Select channel0: MUX2:0 = 000
	
	// Set prescale factor 128: ADPS 2:0= 111
	// F_ADC = F_CPU / 128 = 125KHz
	ADCSRA |= (1<< ADPS2)	|(1<< ADPS1)|(1<< ADPS0);
	
	ADCSRA |= (1<< ADEN);  	// Enable ADC
	
}

uint16_t Get_ADC_value()
{
	
	ADCSRA |= (1<< ADSC);    // Start conversion
	
	while(ADCSRA & (1<< ADSC));     // Wait till conversion finishes
	
	return ADC;    //Read value
}

// Map ADC value to set compare value for motor control
// Compare value        -> 0-255  (8-bit)
// ADC value range      -> 0-1023 (10-bit)
// Compare value = ADC value >> 2
void  Map_ADC_To_CompareValue()
{
	
	uint16_t ADC_Value= Get_ADC_value();   // Read ADC value
	
	uint8_t comp_value= ADC_Value >> 2;    // Map it to 8-bit value
	
	OCR0A = comp_value;     // Set compare value in OCR0A
	
}