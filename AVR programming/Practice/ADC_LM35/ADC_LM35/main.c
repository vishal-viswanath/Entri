/*
 * ADC_LM35.c
 *
 * Created: 13-02-2026 11:01:39
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void ADC_init(void)
{
	ADMUX|=(1<<REFS0); // ADC reference voltage 5V
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Prescalar 128
}

uint16_t ADC_Read(uint8_t channel)
{
	channel &= 0x07; // limiting the channel
	ADMUX = (ADMUX & 0xF0)|channel; // Channel selection
	ADCSRA |= (1<<ADSC); // Start conversion
	while(ADCSRA & (1 << ADSC));
	return (ADCL|(ADCH<<8));
}


int main(void)
{
    uint16_t adc_value;
	lcd_init();
	ADC_init();
	
    while (1) 
    {
		adc_value = ADC_Read(0);
		float temp = adc_value*0.488; // Converting adc value to temperature
		
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_print("Temperature:");
		lcd_set_cursor(1,0);
		lcd_print_float(temp);
		lcd_data(0xDF);
		lcd_print("C");
		_delay_ms(500);
    }
}

