/*
 * LCD.c
 *
 * Created: 28-06-2026 22:18:05
 *  Author: User
 */ 


// Define ENABLE and RS pins
#define EN_PIN PORTB3
#define RS_PIN PORTB4

#include "LCD.h"

void enable_pulse()
{
	
	PORTB|=(1<<EN_PIN);    // Send enable pulse
	_delay_us(1);
	
	PORTB&=~(1<<EN_PIN);
	_delay_us(50);
}
void send_nibble(uint8_t nib)
{
	
	PORTB&=~(1<<RS_PIN);   // RS=0  -> sending command
	
	PORTD=PORTD& 0x0F;     // clear pins PD7-PD4
	PORTD|=(nib<<4);       // send nibble
	
	enable_pulse();
	
	_delay_ms(2);         // provide delay after sending commands & data
	
}
void lcd_cmnd(uint8_t cmd)
{
	
	PORTB&=~(1<<RS_PIN);    // RS=0 : command
	
	
	PORTD=(PORTD&0x0F)|(cmd&0xF0);   // send upper nibble of command
	
	enable_pulse();
	
	PORTD=(PORTD&0x0F)|(cmd<<4);   // send lower nibble of command
	
	enable_pulse();
	
	_delay_ms(2);
}
void lcd_data(uint8_t data)
{
	PORTB|=(1<<RS_PIN);  // RS=1 : data
	
	PORTD=(PORTD&0x0F)|(data&0xF0);  // send upper nibble of data
	
	enable_pulse();
	
	PORTD=(PORTD&0x0F)|(data<<4);  // send lower nibble of data
	
	enable_pulse();
	
	_delay_ms(2);
}
void Init_lcd()
{
	
	_delay_ms(20);     // time to stabilize
	
	
	PORTB&=~(1<<EN_PIN);   // set ENABLE Pin as low
	
	send_nibble(0x03);    // set 8 bit mode
	_delay_ms(5);
	send_nibble(0x03);
	_delay_us(150);
	send_nibble(0x03);
	_delay_us(150);
	
	send_nibble(0x02);   // set 4 bit mode
	
	lcd_cmnd(0x28);      // function set : a-bit mode, 2 line, 5*8 font
	
	lcd_cmnd(0x0c);      // display ON
	
	lcd_cmnd(0x06);      // entry mode : Increment cursor
	
	lcd_cmnd(0x01);      // clear display
	
	_delay_ms(2);
	
}
void lcd_send_string(char *str)
{
	while(*str)
	{
		lcd_data(*str);
		str++;
	}
}
void lcd_set_cursor(uint8_t row, uint8_t col)
{
	// set cursor to given position (row,col)
	
	uint8_t pos;
	
	if(row==0)
	{
		pos= 0x80+ (col&0x0F);
	}
	else
	{
		pos= 0xC0+ (col&0x0F);
	}
	
	// go to that position
	lcd_cmnd(pos);
}
void lcd_send_number(unsigned int num)
{
	char string[10];
	
	// convert number to a string
	// use format specifier %09u to pad with 9 zeros
	sprintf(string, "%09u", num);
	
	lcd_send_string(string);
}
void lcd_clear_display()
{
	
	lcd_cmnd(0x01);    // clear display
	
	_delay_ms(2);
}
void lcd_reset()
{
	
	lcd_send_number(0);     // Display zero
}
void Init_pins()
{
	
	DDRB |= (1<<EN_PIN) | (1<<RS_PIN);    // PB3, PB4 as output
	
	DDRD |= 0xF0;    // PD7-PD4 as output
	
	DDRD &=~(1<< DDD2);    // PD2 as input for push button
	
	PORTD |= (1<< PORTD2);    // enable pull up resistor
}