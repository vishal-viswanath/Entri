/*
 * Gpioint.c
 *
 *  Created on: Feb 19, 2026
 *      Author: User
 */

#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

int main(void)
{
	GPIO_Handle_t GpioLed, GpioIntr;

	/*Configuration for LED*/
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber       = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode         = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed        = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType       = GPIO_OUTPUT_PUSH_PULL;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, Enable);
	GPIO_Init(&GpioLed);

	/*Configuration for Interrupt button*/
	GpioIntr.pGPIOx = GPIOC;
	GpioIntr.GPIO_PinConfig.GPIO_PinNumber       = GPIO_PIN_NO_13;
	GpioIntr.GPIO_PinConfig.GPIO_PinMode         = GPIO_MODE_IT_FT;
	GpioIntr.GPIO_PinConfig.GPIO_PinSpeed        = GPIO_SPEED_VERY_HIGH;
	GpioIntr.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_PULL_UP;

	GPIO_PeriClockControl(GPIOC, Enable);
	GPIO_Init(&GpioIntr);

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI10_15, Enable);

	while(1);

}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}
