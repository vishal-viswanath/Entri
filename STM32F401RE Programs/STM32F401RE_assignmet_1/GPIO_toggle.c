/*
 * GPIO_toggle.c
 *
 *  Created on: Feb 7, 2026
 *      Author: User
 */

#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

int main (void)
{


	// initialization for LED
		GPIO_Handle_t GPIOLED;

		GPIOLED.pGPIOx = GPIOA;
		GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
		GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERY_HIGH;
		GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PUSH_PULL;
		GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_Init(&GPIOLED);

		// initialization for PUSH BUTTON
		GPIO_Handle_t GPIO_PUSH_BUTTON;

		GPIO_PUSH_BUTTON.pGPIOx = GPIOC;
		GPIO_PUSH_BUTTON.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
		GPIO_PUSH_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
		GPIO_PUSH_BUTTON.GPIO_PinConfig.GPIO_PinSpeed = 0;
		GPIO_PUSH_BUTTON.GPIO_PinConfig.GPIO_PinOPType = 0;
		GPIO_PUSH_BUTTON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOC, Enable);

		GPIO_Init(&GPIO_PUSH_BUTTON);


		//toggle 2 external LEDs


		GPIO_Handle_t GPIO_toggle_LED_1;

		GPIO_toggle_LED_1.pGPIOx = GPIOA;
		GPIO_toggle_LED_1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GPIO_toggle_LED_1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
		GPIO_toggle_LED_1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERY_HIGH;
		GPIO_toggle_LED_1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PUSH_PULL;
		GPIO_toggle_LED_1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_Init(&GPIO_toggle_LED_1);

		GPIO_Handle_t GPIO_toggle_LED_2;

		GPIO_toggle_LED_2.pGPIOx = GPIOA;
		GPIO_toggle_LED_2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GPIO_toggle_LED_2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
		GPIO_toggle_LED_2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERY_HIGH;
		GPIO_toggle_LED_2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PUSH_PULL;
		GPIO_toggle_LED_2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_Init(&GPIO_toggle_LED_2);


		static uint8_t reference = 1;    // reference value for avoiding debounce
		uint8_t value;   // variable to store read value from push button

		uint32_t RST_Counter=0;   // variable used to non-blocking delay function
		uint8_t flag = 0;   // flag to check loop status


		while(1)
		{
			if(RST_Counter <= 250000) // non-blocking delay function
		    {
		    	flag = 1;
		    }
		    else
		    {
		    	flag =0;
		    	if(RST_Counter >= 500000)
		    	{
		    	RST_Counter = 0;
		    	}
		    }
		    RST_Counter ++;


		    if(flag)   // check flag status and follow the instructions(for external LED)
		    {
		    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_SET);    // GPIOA PIN6 ON
		    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_CLEAR);  // GPIOA PIN7 OFF
		    }
		    else
		    {
		    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_CLEAR); // GPIOA PIN6 OFF
		    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_SET);   // GPIOA PIN7 ON
		    }


		    value = GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13);  //read the button value

		    if(value == GPIO_PIN_CLEAR && reference == GPIO_PIN_SET)  //working condition on-board LED
		    {

		    	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);    // toggle GPIOA PIN5

		    }
		    reference = value;


		}
}











