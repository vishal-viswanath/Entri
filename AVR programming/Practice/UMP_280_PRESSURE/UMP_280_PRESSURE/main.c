/*
 * UMP_280_PRESSURE.c
 *
 * Created: 14-01-2026 19:34:08
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"


int main(void)
{
	UART_Init();
	uint8_t chip_id,msb,lsb,xlsb,t1_lsb,t1_msb,t2_lsb,t2_msb;
	int8_t t3_lsb,t3_msb;
	uint16_t dig_T1,dig_T2;
	int16_t dig_T3;
	uint32_t temp;
	int T_int,T_frac,T_new;
	float var1,var2,T,t_fine;
	
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
		
		SPDR=0X00; // Dummy value for getting actual value
		while(!(SPSR&(1<<SPIF))); //Waiting until flag set
		chip_id=SPDR; // reading chip id (actual value)
		PORTB|=(1<<PB2); // de select slave
		
		// Enabling measurement by writing 0x27 t0 0xF4 register of BMP280
		
		PORTB&=~(1<<PB2);  // selecting slave
		SPDR=(0xF4 & 0x7F); // ensuring 0 on MSB(writing)
		while(!(SPSR & (1<<SPIF)))// Waiting until flag set
		(void)SPDR; // Reading SPDR(for clear the register)
		
		SPDR=0X27; // writing 27 to 0xF4
		while(!(SPSR & (1<<SPIF)))// Waiting until flag set
		(void)SPDR; //dummy reading
		PORTB|=(1<<PB2); //de select slave
		
		//Reading data from 0xF7
		
		PORTB&=~(1<<PB2); // Slave selecting
		SPDR=(0xF7|0x80);  // writing 1 to 0xFA for reading data from there
		while(!(SPSR&(1<<SPIF))); //waiting until flag is set
		(void)SPDR; // reading dummy data
		
		SPDR=0X00; // sending dummy data for 0xFA
		while(!(SPSR&(1<<SPIF))); //waiting until flag is set
		msb=SPDR; 	//load value from SPDR(0xFA) to msb
		//UART_TxNumber(msb);
		
		
		//Reading data from 0xF8
		
		SPDR=0X00; // loading dummy value for 0xFB
		while(!(SPSR&(1<<SPIF))); // wait until flag set
		lsb=SPDR; // load value from SPDR(0xFB) to lsb
		//UART_TxNumber(lsb);
		
		
		//Reading data from 0xF9
		
		SPDR=0X00; // load dummy value for 0xFC
		while(!(SPSR&(1<<SPIF))); // Wait until flag set
		xlsb=SPDR; // load value from SPDR(0xFC) to xlsb
		//UART_TxNumber(xlsb);
		
		temp=((uint32_t )msb << 12)|((uint32_t)lsb << 4)|((uint32_t)xlsb >> 4); // loading combined data
		PORTB|=(1<<PB2); // de select slave
		
		//reading temperature compensation values
		
		PORTB&=~(1<<PB2); // Slave select(ss or CSB)
		SPDR=(0x88|0x80); //load 0 to msb for read data
		while(!(SPSR & (1<<SPIF))); // wait until flag set
		(void)SPDR; // dummy reading
		
		//dig_T1
		
		SPDR=0x00; //load dummy value for 0x88
		while(!(SPSR&(1<<SPIF))); //wait until flag set
		t1_lsb=SPDR; //load 0x88 value to dig_T1_lsb
		
		SPDR=0x00; //load dummy value for 0x89
		while(!(SPSR & (1<<SPIF))); // Wait until flag set
		t1_msb=SPDR; // load 0x89 value to dig_T1_msb
		
		//dig_T2
		
		SPDR=0x00;//load dummy value for 0x8A
		while(!(SPSR&(1<<SPIF))); //wait until flag set
		t2_lsb=SPDR; //load 0x8A value to dig_T2_lsb
		
		SPDR=0x00; // dummy value for 0x8B
		while(!(SPSR&(1<<SPIF))); //wait until flag set
		t2_msb=SPDR; // load 0x8B value to dig_T2_msb
		
		//dig_T3
		
		SPDR=0x00;//load dummy value for 0x8A
		while(!(SPSR&(1<<SPIF))); //wait until flag set
		t3_lsb=SPDR; //load 0x8C value to dig_T3_lsb
		
		SPDR=0x00; // dummy value for 0x8B
		while(!(SPSR&(1<<SPIF))); //wait until flag set
		t3_msb=SPDR; // load 0x8D value to dig_T3_msb
		PORTB|=(1<<PB2); // de select slave
		
		dig_T1 = ((uint16_t)t1_msb << 8 | t1_lsb); // combine 0x88 and 0x89
		dig_T2 = ((uint16_t)t2_msb << 8 | t2_lsb); // combine 0x8A and 0x8B
		dig_T3 = ((int16_t)t3_msb << 8 | t3_lsb); // combine 0x8C and 0x8D
		
		var1 = ((temp/16384.0f)-(dig_T1/1024.0f))* dig_T2;
		var2 = ((temp/131072.0f)-(dig_T1/8192.0f))* dig_T3;
		
		t_fine= var1+var2;
		
		T= t_fine/5120.0f;
		
		T_new = T*100;
		T_int = T_new / 100;
		T_frac = T_new % 100;
		
		UART_TxNumber(T_int);
		UART_TxChar('.');
		
		if(T_frac<10)
		{
			UART_TxChar('0');
		}
		
		UART_TxNumber(T_frac);
		UART_TxChar('\n');
		_delay_ms(1000);
		//UART_TxNumber(dig_T1);
		//UART_TxChar('\n');
		//UART_TxNumber(dig_T2);
		//UART_TxChar('\n');
		//UART_TxNumber(dig_T3);
		//UART_TxChar('\n');
		//_delay_ms(1000);
		
	}
}