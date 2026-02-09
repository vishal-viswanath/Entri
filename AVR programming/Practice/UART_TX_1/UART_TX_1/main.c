/*
 * UART_TX_1.c
 *
 * Created: 04-01-2026 20:24:45
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	char a='A';
	
    UBRR0H=0;  // Set baud rate to 9600
	UBRR0L=103;
	
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); // Set 8 bit mode
	
	UCSR0C&=~(1<<USBS0)|(1<<UPM00)|(1<<UPM01); // No parity, 1 stop bit
	
	UCSR0B|=(1<<TXEN0); // Transmitter enable
	
    while (1) 
    {
		UDR0=a;
		while(!(UCSR0A & (1<<UDRE0))); // Wait until the transmission complete
		_delay_ms(1000);
		
    }
}

