/*
 * Traffic_signal_and_DCmotor.c
 *
 * Created: 25-11-2025 10:22:55
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void delay(uint16_t ms);
void red(void);
void orange(void);
void green(void);
void stp_LED(void);
void stp_motor(void);
void clk(void);
void cclk(void);
volatile uint8_t int0_flag = 0;


void delay(uint16_t ms)                // user defined function for 1sec delay
{
	while (ms--)
	{
		while(!(TIFR0&(1<<OCF0A)));
		TIFR0|=(1<<OCF0A);
	}
}

ISR(INT0_vect)                     // ISR for change from normal state to interrupt state
{
	int0_flag = 1;
}

int main(void)
{
	
	TCNT0=0;                       // set TCNT0 initial value
	
	TCCR0A&=~(1<<WGM00);           // configure CTC mode
	TCCR0A|=(1<<WGM01);
	
	TCCR0B|=(1<<CS00|1<<CS01);     // configure prescalar 64
	TCCR0B&=~(1<<CS02);
	
	OCR0A=249;                     // set OCR value range
	
	EIMSK|=(1<<INT0);              // set external interrupt type
	
	EICRA|=(1<<ISC00)|(1<<ISC01);  // configure interrupt sense control
	
	EIFR|=(1<<INTF0);              // set flag=0
	
	
	DDRB|=(1<<DDB5)|(1<<DDB4)|(1<<DDB3);    // configure data direction registers(DDB5,DDB4 And DDB3)
	DDRD|=(1<<DDD5)|(1<<DDD6);
	
	sei();                                  // enable global interrupt
	
	while (1)
	{
		
		
		if (int0_flag == 1)              // Traffic light rule after interrupt occur 
		{
			clk();
			red();
			delay(6000);
			//_delay_ms(5000);
			red();
			stp_motor();
			delay(5000);
			//_delay_ms(5000);
			cclk();
			red();
			delay(6000);
			//_delay_ms(5000);
			stp_motor();
			orange();
			delay(5000);
			//_delay_ms(3000);
			green();
			delay(3000);
			//_delay_ms(3000);
			orange();
			delay(3000);
			//_delay_ms(3000);
								
			int0_flag =0;           // flag changes to normal state

		}
		else
		{
			red();                 // Traffic light rule under normal conditions
			delay(3000);
			//_delay_ms(3000);
			orange();
			delay(3000);
			//_delay_ms(3000);
			green();                           
			delay(3000);
			//_delay_ms(3000);
			orange();
			delay(3000);
			//_delay_ms(3000);
				
		}
		
	}
}
void red()                     // function for RED LED
{
	PORTB|=(1<<PB5);
	PORTB&=~(1<<PB4);
	PORTB&=~(1<<PB3);
}
void orange()                // function for orange LED
{
	PORTB&=~(1<<PB5);
	PORTB|=(1<<PB4);
	PORTB&=~(1<<PB3);
}
void green()                 // function for green LED
{
	PORTB&=~(1<<PB5);
	PORTB&=~(1<<PB4);
	PORTB|=(1<<PB3);
}
void clk()                  // function for clock-wise motor rotation
{
	PORTD|=(1<<PD5);
	PORTD&=~(1<<PD6);
}
void cclk()                // function for anti clock-wise motor rotation
{
	PORTD&=~(1<<PD5);
	PORTD|=(1<<PD6);
}
void stp_motor()           // function for stop motor rotation
{
	PORTD&=~(1<<PD5);
	PORTD&=~(1<<PD6);
}
void stp_LED()             // function for stop LED blinking
{
	PORTB&=~(1<<PB5);
	PORTB&=~(1<<PB4);
	PORTB&=~(1<<PB3);
}


