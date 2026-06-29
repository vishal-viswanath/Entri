/*
 * UART_LED.c
 *
 * Created: 28-06-2026 22:50:53
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "PWM.h"

int main(void)
{
	
	Init_UART();   // Initialize UART
	
	Init_PWM();
	
	char command[50]="";   // Buffer for receiving user-command
	

	while (1)
	{
		
		UART_Receive_string(command, 50);    // Receive command from user
		
		Update_LED_status(command);      // Update LED status based on the command
		
		_delay_ms(100);
	}
}

