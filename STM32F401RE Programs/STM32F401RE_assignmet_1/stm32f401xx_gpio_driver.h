/*
 * stm32f401xx_gpio_driver.h
 *
 *  Created on: Feb 2, 2026
 *      Author: User
 */

#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h"


/*
 * Configuration structure for a gpio pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;           // Pin number (0,15)
	uint8_t GPIO_PinMode;             // Mode: Input/Output/Altfn/Analog
	uint8_t GPIO_PinSpeed;            // Speed: Low/Medium/High/Very high
	uint8_t GPIO_PinPuPdControl;      // Pull up/Pull down configuration
	uint8_t GPIO_PinOPType;           // Output type: Push Pull/ OpenDrain
	uint8_t GPIO_PinAltMode;          // Alternate function (0-15)
}GPIO_PinConfig_t;

/*
 * Handle structure for a GPIO pin
 */
typedef struct
{
	GPIO_RegDef_t *pGPIOx;            // Pointer to GPIO port base address
	GPIO_PinConfig_t GPIO_PinConfig;  // Pin configuration settings
}GPIO_Handle_t;

/*
 * Macros for GPIO Pin numbers
 */

#define GPIO_PIN_NO_0            0
#define GPIO_PIN_NO_1            1
#define GPIO_PIN_NO_2            2
#define GPIO_PIN_NO_3            3
#define GPIO_PIN_NO_4            4
#define GPIO_PIN_NO_5            5
#define GPIO_PIN_NO_6            6
#define GPIO_PIN_NO_7            7
#define GPIO_PIN_NO_8            8
#define GPIO_PIN_NO_9            9
#define GPIO_PIN_NO_10           10
#define GPIO_PIN_NO_11           11
#define GPIO_PIN_NO_12           12
#define GPIO_PIN_NO_13           13
#define GPIO_PIN_NO_14           14
#define GPIO_PIN_NO_15           15

/*
 * Macros for GPIO Modes
 */

#define GPIO_MODE_IN             0    /* Input mode value    00 */
#define GPIO_MODE_OUT            1    /* output mode value   01 */
#define GPIO_MODE_ALTFN          2    /* Alt Func mode value 10 */
#define GPIO_MODE_ANALOG         3    /* Analog mode value   11 */
#define GPIO_MODE_IT_FT          4    /* Interrupt mode falling edge */
#define GPIO_MODE_IT_RT          5    /* Interrupt mode rising edge */
#define GPIO_MODE_IT_RFT         6    /* Interrupt mode falling and rising edge */

/*
 * Macros for GPIO Speed
 */

#define GPIO_SPEED_LOW           0    /* Low speed mode value       00 */
#define GPIO_SPEED_MEDIUM        1    /* Medium speed mode value    01 */
#define GPIO_SPEED_HIGH          2    /* High speed mode value      10 */
#define GPIO_SPEED_VERY_HIGH     3    /* Very high speed mode value 11 */

/*
 * Macros for GPIO PU-PD control
 */

#define GPIO_NO_PUPD             0    /* No pull up pull down mode value 00 */
#define GPIO_PULL_UP             1    /* Pull up mode value              01 */
#define GPIO_PULL_DOWN           2    /* Pull down mode value            10 */

/*
 * Macros for GPIO Output type push pull/ OpenDrain
 */

#define GPIO_OUTPUT_PUSH_PULL    0    /* Output push-pull mode value  00 */
#define GPIO_OUTPUT_OPEN_DRAIN   1    /* Output open-drain mode value 01 */

/*
 * Macros for GPIO pin set
 */

#define GPIO_PIN_SET             1
#define GPIO_PIN_CLEAR           0


void GPIO_PeriClockControl(GPIO_RegDef_t * pGPIOx, uint8_t EnorDi);

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value );

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);







#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */
