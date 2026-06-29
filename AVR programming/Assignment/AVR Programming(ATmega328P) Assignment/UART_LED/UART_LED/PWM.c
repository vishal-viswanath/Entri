/*
 * PWM.c
 *
 * Created: 28-06-2026 22:52:14
 *  Author: User
 */ 


#include <avr/io.h>
#include <string.h>
#include "UART.h"


void Init_PWM()   // Set Fast PWM on OC0A/PD6
{
	
	TCCR0B &= ~(1<< WGM02);    // Set Fast PWM on TIMER0 : WGM0 2:0 = 011
	TCCR0A |= (1<< WGM01)|(1<< WGM00);
	
	TCCR0A |=(1<<COM0A1);    // set non-inverting output on PD5: COM01:0 = 10
	TCCR0A &=~(1<< COM0A0);
	
	
	DDRD |= (1<< DDD6);     // set PD6 as output pin
	
	
	TCCR0B &=~(1<< CS02);    // set prescaler 64 : CS02:0=011
	TCCR0B |= (1<< CS01)|(1<< CS00);
	
}
// Helper function for string-number conversion
static uint16_t Convert_String_ToNumber(char *str)
{
	uint16_t number=0, digit,i=0;
	
	while(str[i]!='\0')
	{
		unsigned char ch= str[i];
		// Convert character to digit:
		digit = ch -'0';
		
		// Do conversion if digit is valid
		if(ch>='0'&& ch<='9')
		{
			number = (number*10)+ digit;
		}
		else
		{
			break;
		}
		
		
		i++;
	}
	return number;
}

// Function to receive UART command
// Updates LED status
void Update_LED_status(char *cmd)
{
	
	// If command is : ON
	if(strcmp(cmd,"ON")==0)
	{
		// Turn ON LED 
		// - PD6 is a PWM pin
		// - Cannot be controlled using PORT register
		// - Set 100% Duty cycle
		OCR0A = 255;
		
		UART_Send_string("\n\rLED is now ON");    // Send message : "LED is now ON"
		
		
	}
	// If command is : OFF
	if(strcmp(cmd,"OFF")==0)
	{
		// Turn OFF LED 
		// - PD6 is a PWM pin
		// - Cannot be controlled using PORT register
		// - Set 0% Duty cycle
		OCR0A = 0;
		
		UART_Send_string("\n\rLED is now OFF");   // Send message : "LED is now OFF"
		
	}

	// If command is a number : 0-100
	// - Convert command string to a number
	// - Check if number is valid : 0-100
	// - Convert number to compare value (OCR0A)
	// - OCR0A = (number /100)* TOP (255)
	// - set compare value to adjust LED brightness
	uint16_t number, compare_value=0;
	if(*cmd >= '0' && *cmd<='9')
	{
		number= Convert_String_ToNumber(cmd);
		
		if(number > 100)
		{
			
			UART_Send_string("\n\rEntered number is Invalid (>100)");    // Invalid number
			number=0;
			return;
		}
		
		compare_value = (number * 255)/100;
		
		OCR0A = compare_value;    // Update brightness
		
		UART_Send_string("\n\rBrightness set to ");    // Send message
		UART_Send_number(number);
		UART_Send_data('%');
	}
	
}