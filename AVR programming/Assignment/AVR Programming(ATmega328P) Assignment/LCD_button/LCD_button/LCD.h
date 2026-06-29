/*
 * LCD.h
 *
 * Created: 28-06-2026 22:16:46
 *  Author: User
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void enable_pulse();
void send_nibble(uint8_t nib);
void lcd_cmnd(uint8_t cmd);
void lcd_data(uint8_t data);
void Init_lcd();
void Init_pins();
void lcd_send_string(char *str);
void lcd_send_number(unsigned int  num);
void lcd_reset();
void lcd_clear_display();
void lcd_set_cursor(uint8_t row, uint8_t col);



#endif /* LCD_H_ */