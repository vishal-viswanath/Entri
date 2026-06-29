/*
 * LM35_DCmotor.c
 *
 * Created: 29-06-2026 12:54:03
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int system_on = 0;   // system flag

void adc_init()
{
	ADMUX = (1 << REFS0);   // AVcc as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // enable ADC, prescaler 128
}

int read_lm35()
{
	ADMUX &= 0xF0;                 // select ADC0
	ADCSRA |= (1 << ADSC);         // start conversion
	while (ADCSRA & (1 << ADSC));  // wait until finish
	return ADC;                    // return ADC value
}

void pwm_init()
{
	DDRD |= (1 << DDD6);                                    // PD6 as output for PWM

	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);   // Fast PWM, non-inverting mode
	TCCR0B = (1 << CS01);                                   // prescaler 8
}

void motor_speed(int temp)
{
	if(temp < 25)
	{
		OCR0A = 80;    // low speed
	}
	else if(temp < 35)
	{
		OCR0A = 160;   // medium speed
	}
	else
	{
		OCR0A = 240;   // high speed
	}
}

int main(void)
{
	int adc_value;
	int temp;

	DDRD &= ~(1 << DDD2);   // PD2 as input button
	PORTD |= (1 << PD2);    // pull-up enable
	DDRB |= (1 << DDB5);    // PB5 as output LED

	adc_init();
	pwm_init();

	while(1)
	{
		if(!(PIND & (1 << PD2)))   // button pressed
		{
			_delay_ms(20);    // debounce delay

			if(!(PIND & (1 << PD2)))
			{
				system_on = !system_on;        // toggle system
				while(!(PIND & (1 << PD2)));   // wait for button release
				_delay_ms(20);                 // debounce release
			}
		}

		if(system_on)
		{
			PORTB |= (1 << PB5);       // LED ON

			adc_value = read_lm35();   // read sensor
			temp = adc_value / 10;     // convert to temperature approx

			motor_speed(temp);         // set motor speed
		}
		else
		{
			PORTB &= ~(1 << PB5);   // LED OFF
			OCR0A = 0;              // motor OFF
		}

		_delay_ms(100);   // small delay
	}
}
