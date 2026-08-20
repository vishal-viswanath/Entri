





#include <stdint.h>
#include "stm32f401xx_gpio_driver.h"
#include "TIMERs_Baremetal.h"

int LED_main(void)
{
	// Initialize PA0 as output pin for LED
	GPIO_Handle_t led;
	led.pGPIOx                             = GPIOA;
	led.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_0;
	led.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;

	GPIO_Init(&led);

	// Initialize PA1 as input pin for button and enable pull up resistor
	GPIO_Handle_t button;
	button.pGPIOx                             = GPIOA;
	button.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_1;
	button.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IN;
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;

	GPIO_Init(&button);


	// Initialize timer 2 for delay creation
	Timer_Delay_Creation();

	// Declare variables for detecting falling edge
	uint8_t current_state, previous_state =1;

	while(1)
	{
		// Use debounce logic to prevent multiple toggles per press

		// Read current state of the input pin
		current_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1 );

		// Detect falling edge
		if(current_state == 0 && previous_state == 1)
		{
			// Applay small delay for bounce to settle
			delay_ms(50);

			// Confirm button still presssed
			if(!GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1 ))
			{
				// Perform LED toggle
				GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_0);
			}

		}

		// reset previous state
		previous_state = current_state;

	}

}
