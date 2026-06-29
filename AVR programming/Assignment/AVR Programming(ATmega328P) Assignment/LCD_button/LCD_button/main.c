/*
 * LCD_button.c
 *
 * Created: 28-06-2026 22:16:02
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "LCD.h"

int main(void)
{
	
	Init_pins();   // Initialize pins
	
	Init_lcd();    // Initialize LCD for display
	
	lcd_send_number(0);   // Start count from zero
	
	// Detect button press inside the loop
	// Use edge detection + delay for De-bouncing
	
	uint8_t previous_state=1, current_state;    // Variables to detect edge
	
	uint16_t press_count;     // Variable to detect button press time

	uint32_t count=0;   // Variable to display LCD count
	
	while (1)
	{
		
		current_state= (PIND >> 2) & 1;    // Read current state of button inside the loop
		
		// If Button press happens: State changes-
		if(previous_state==1 && current_state==0)
		{
			// Find button press duration:
			// Increment press count every 1 millisecond
			// If count >= 2000,
			// - Button pressed for more than 2 seconds
			// - Reset LCD count to zero
			// - Exit from the loop even if button still pressed
			press_count=0;
			
			while(!((PIND>>2)&1))
			{
				press_count++;
				_delay_ms(1);
				
				if(press_count >= 2000)
				{
					lcd_set_cursor(0,0);
					lcd_reset();
					count=0;
					break;
				}
			}
			
			// After exiting from loop, check press duration
			// If short press
			if(press_count< 2000)
			{
				// Update count
				lcd_set_cursor(0,0);
				lcd_send_number(++count);
				
			}
			
		}
		
		previous_state= current_state;     // Update previous state
		
	}
}