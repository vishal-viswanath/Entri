/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: Feb 2, 2026
 *      Author: User
 */


#include "stm32f401xx_gpio_driver.h"

// GPIO PeriClockControl(GPIOx, Enable/Disable)
/************************************************************************
 * @fn             - GPIO_PericlockControl
 *
 * @brief          - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]      - pGPIOx: base address of the GPIO peripheral clock for the GPIO peripheral(GPIOA,GPIOB,...GPIOH)
 *
 * @param[in]      - FnorDi: Enable or Disable macros
 *
 * @return         - None
 *
 * @Note           - None
 */


void GPIO_PeriClockControl(GPIO_RegDef_t * pGPIOx, uint8_t EnorDi)
{

	if(EnorDi == Enable)
	{
		if(pGPIOx==GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx==GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx==GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx==GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx==GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx==GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx==GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx==GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx==GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx==GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx==GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx==GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}

}

/************************************************************************
 * @fn             - GPIO_Init
 *
 * @brief          - This function is used to initializes a given GPIO PORT PIN
 *
 * @param[in]      - pGPIOHandle: Pointer to GPIO_Handle_t structure
 *
 * @return         - none
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

	uint32_t temp = 0;
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx,Enable);

	// GPIO MODE Set

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Create a mask

		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the register

		pGPIOHandle->pGPIOx->MODER |= temp; //set the value to the register

		temp=0;

	}
	//Interrupt modes
	else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;

		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;

		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

		SYSCFG_PCLK_EN();

        SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2*4));
		SYSCFG->EXTICR[temp1] |= (portcode << (temp2 *4));

		// Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;


	}

	//GPIO Speed Set

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Create a mask

	pGPIOHandle->pGPIOx ->OSPEEDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the register

	pGPIOHandle->pGPIOx->OSPEEDR |= temp; //set the value to the register

	temp=0;


	//GPIO PUPDR Set

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Create a mask

	pGPIOHandle->pGPIOx ->PUPDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the register

	pGPIOHandle->pGPIOx->PUPDR |= temp; //set the value to the register

	temp=0;


	//GPIO OTYPER Set

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Create a mask

	pGPIOHandle->pGPIOx ->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the register

	pGPIOHandle->pGPIOx->OTYPER |= temp; //set the value to the register

	temp=0;


	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN  )
	{

		uint8_t temp1,temp2;

		temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/8;

		temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%8;

		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( (0xF) << 4*temp2);

		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltMode << (4*temp2));

	}
}

/************************************************************************
 * @fn             - GPIO_DeInit
 *
 * @brief          - This function is used to deinitializes a given GPIO PORT PIN
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @return         - none
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

	if(pGPIOx == GPIOA)
	{
		GPIOA_RST_EN();
		GPIOA_RST_DI();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_RST_EN();
		GPIOB_RST_DI();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_RST_EN();
		GPIOC_RST_DI();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_RST_EN();
		GPIOD_RST_DI();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_RST_EN();
		GPIOE_RST_DI();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_RST_EN();
		GPIOH_RST_DI();
	}

}

/************************************************************************
 * @fn             - GPIO_ReadFromInputPin
 *
 * @brief          - This function is used to read the value from a GPIO PIN
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @param[in]      - Pin Number
 *
 * @return         - uint8_t value (value inside the given pin )
 *
 * @Note           - Refer macros for GPIO configuration
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR>>PinNumber) & 0x00000001);
	return value;

}

/************************************************************************
 * @fn             - GPIO_ReadFromInputPort
 *
 * @brief          - This function is used to read the value from a GPIO PORT
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @return         - uint16_t value (value inside the given Port )
 *
 * @Note           - Refer macros for GPIO configuration
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{

	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;

}

/************************************************************************
 * @fn             - GPIO_WriteToOutputPin
 *
 * @brief          - This function is used to write the value to a GPIO PIN
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @param[in]      - Pin Number
 *
 * @param[in]      - Value (0 or 1)
 *
 * @return         - None
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

	if(Value==GPIO_PIN_SET  )
	{
		pGPIOx->ODR |= (1<<PinNumber);      //Write 1
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);     // Write 0
	}

}

/************************************************************************
 * @fn             - GPIO_WriteToOutputPort
 *
 * @brief          - This function is used to write the value to a GPIO PORT
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @param[in]      - Value (0 or 1)
 *
 * @return         - None
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value )
{

	pGPIOx->ODR = Value;

}

/************************************************************************
 * @fn             - GPIO_ToggleOutputPin
 *
 * @brief          - This function is used to toggle the value in a GPIO PIN
 *
 * @param[in]      - pGPIOx: Pointer to GPIO_RegDef_t structure
 *
 * @param[in]      - Pin number
 *
 * @return         - None
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

	pGPIOx->ODR ^= (1<<PinNumber);

}

/************************************************************************
 * @fn             - GPIO_IRQInterruptConfig
 *
 * @brief          - This function is used to
 *
 * @param[in]      -
 *
 * @param[in]      -
 *
 * @return         - None
 *
 * @Note           - Refer macros for GPIO configuration
 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == Enable)
	{
		if(IRQNumber <= 31)
		{
			// Program for ISER0 Register
			*NVIC_ISER0 |= (1<<IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// Program for ISER1 Register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber > 64 && IRQNumber < 96)
		{
			// Program for ISER2 Register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber < 31)
		{
			// program for ICER0 Register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// Program for ICER1 Register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber > 64 && IRQNumber <96)
		{
			// // Program for ICER2 Register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	if(EXTI -> PR & (1 << PinNumber))
	{
		EXTI -> PR |= (1 << PinNumber);
    }
}
/*
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
uint8_t iprx = IRQNumber / 4;

uint8_t iprx_section = IRQNumber % 4;

uint8_t shift_amount = (8*iprx_section)+(8 - NO_PR_BITS_IMPEMENTED);

*(NVIC_PR_BASE_ADDR + iprx)|=(IRQPriority<< shift_amount);

}
*/
