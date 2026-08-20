




#include <stdint.h>
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_usart_driver.h"

void USART_GPIO_Configuration()
{
	// Configure GPIO pins as RX and TX lines:
	// - USART2 RX pin is mapped to PA3 (D0)
	// - USART2 TX pin is mapped to PA2 (D1)
	// - Use Alternate function AF7

	GPIO_Handle_t usart_rx;
	usart_rx.pGPIOx = GPIOA;
	usart_rx.GPIO_PinConfig.GPIO_PinNumber= GPIO_PIN_NO_3;
	usart_rx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_rx.GPIO_PinConfig.GPIO_PinAltFunMode = AF7;

	GPIO_Handle_t usart_tx;
	usart_tx.pGPIOx = GPIOA;
	usart_tx.GPIO_PinConfig.GPIO_PinNumber= GPIO_PIN_NO_2;
	usart_tx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_tx.GPIO_PinConfig.GPIO_PinAltFunMode = AF7;

	GPIO_Init(&usart_rx);
	GPIO_Init(&usart_tx);
}



int USART_main(void)
{
	// Configure GPIO pins as RX and TX lines:
	USART_GPIO_Configuration();

	// USART2 Configurations

	USART_Handle_t usart;
	usart.pUSARTx = USART2;
	usart.USART_Config.USART_Baud = USART_STD_BAUD_9600	;
	usart.USART_Config.USART_WordLength=USART_WORDLEN_8BITS ;
	usart.USART_Config.USART_Mode=USART_MODE_TXRX ;
	usart.USART_Config.USART_ParityControl= USART_PARITY_DISABLE;
	usart.USART_Config.USART_HWFlowControl= USART_HW_FLOW_CTRL_NONE;

	USART_Init(&usart);

	// Enable USART2
	USART_PeripheralControl(USART2, ENABLE);

	// Print a message
	uint8_t buffer[]= "USART Debugging\n\r";

	USART_SendData(&usart, buffer, 16);

	// Declare a variable for reception and transmission
	uint8_t character=0;


	while(1)
	{

		// Receive characters in a loop
		USART_ReceiveData(&usart, &character, 1);

		// Echo received characters
		USART_SendData(&usart, &character, 1);

	}

}
