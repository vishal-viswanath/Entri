/*
 * BMP_280.c
 *
 * Created: 07-01-2026 10:56:55
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"


int main(void)
{
	UART_Init();
	uint8_t chip_id;
    DDRB|=(1<<DDB2)|(1<<DDB3)|(1<<DDB5); // MOSI, SCK, CSB are configured as output
	DDRB&=~(1<<DDB4); // MISO is configured as input
	
	SPCR|=((1<<SPE)|(1<<SPR0)|(1<<MSTR));
	SPCR&=~((1<<SPR1)|(1<<CPOL)|(1<<CPHA));
    while (1) 
    {
		PORTB&=~(1<<PB2); // Slave select(ss or CSB)
		SPDR=(0xD0|0x80);  // Ensuring 1 on MSB (reading)
		while(!(SPSR&(1<<SPIF))); // Waiting for data transmission complete(SPIF flag set)
		(void)SPDR; // Reading SPDR(for dummy garbage value)
		//PORTB|=(1<<PB2); //De selecting slave
		
		//PORTB&=~(1<<PB2); // Slave select
		SPDR=0X00; // Dummy value for getting actual value
		while(!(SPSR&(1<<SPIF))); //Waiting until flag set
		chip_id=SPDR; // reading chip id (actual value)
		PORTB|=(1<<PB2); // De selecting slave
		
		UART_TxHex(chip_id);
		_delay_ms(1000);
		
		
		
    }
}

