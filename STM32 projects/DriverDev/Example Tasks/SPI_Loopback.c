




#include <stdint.h>
#include <string.h>
#include "stm32f401xx_spi_driver.h"

#include "TIMERs_Baremetal.h"
#include "printf.h"

void ConfigureSpi_GpioPins()
{

	// For SPI1 peripheral,
	// - SCK  - PA5
	// - MISO - PA6
	// - MOSI - PA7
	// - NSS  - PA4
	// - Select Alternate function - AF5

	GPIO_Handle_t spi;
	spi.pGPIOx                            = GPIOA;
	spi.GPIO_PinConfig.GPIO_PinMode       = GPIO_MODE_ALTFN;
	spi.GPIO_PinConfig.GPIO_PinAltFunMode = AF5;
	spi.GPIO_PinConfig.GPIO_PinSpeed      = GPIO_SPEED_HIGH;
	spi.GPIO_PinConfig.GPIO_PinOPType     = GPIO_OP_TYPE_PP;
	spi.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;

	// NSS
	spi.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&spi);
	// SCK
	spi.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&spi);
	// MISO
	spi.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&spi);
	// MOSI
	spi.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&spi);

}
int SPI_main(void)
{

	// Initialize USART2 for printf debugging
	printf_USART2_Init();

	// Initialize timer for creating delay
	Timer_Delay_Creation();

	// Initialize GPIO pins for SPI1
	ConfigureSpi_GpioPins();

	// Initialize SPI1 with required configurations
	SPI_Handle_t spi1;
	spi1.pSPIx                       = SPI1;
	spi1.SPIConfig.SPI_DeviceMode    = SPI_DEVICE_MODE_MASTER;
	spi1.SPIConfig.SPI_SclkSpeed     = SPI_SCLK_SPEED_DIV16;
	spi1.SPIConfig.SPI_BusConfig     = SPI_BUS_CONFIG_FD;
	spi1.SPIConfig.SPI_SSM           = SPI_SSM_EN;
	spi1.SPIConfig.SPI_CPHA          = SPI_CPHA_LOW;
	spi1.SPIConfig.SPI_CPOL          = SPI_CPOL_LOW;
	spi1.SPIConfig.SPI_DFF           = SPI_DFF_8BITS;

	SPI_Init(&spi1);

	// Enable SSI for preventing MODE Fault and keep SPI enabled.
	SPI_SSIConfig(SPI1, ENABLE);

	// Enable peripheral
	SPI_PeripheralControl(SPI1, ENABLE);




	//********************** SPI loopback test ********************************
	//
	// Objective:
	// - Transmit a string through MOSI
	// - Receive the transmitted string through MISO into another buffer
	// - Verify the loopback by comparing the transmitted and received strings
	//
	// Hardware setup:
	// - Connect MOSI(PA7) with MOSI(PA6)
	//
	// Note: SPI is a full duplex protocol
	// - every transmitted byte also receives a byte at same time.
	// - string is transmitted one byte at a time to read
	//   the received byte and prevent overrun issues.
	//
	//*************************************************************************



	// String to be transmitted
	uint8_t TxBuffer[]= "SPI Loopback Test";

	// Buffer to receive string
	uint8_t RxBuffer[30]={};

	uint8_t len = strlen((char*)TxBuffer);

	for(int i=0;i<len;i++)
	{
		// Send one byte (this generates a received byte)
		SPI_SendData(SPI1, &TxBuffer[i], 1);

		// Read the received byte and store in a buffer
		SPI_ReceiveData(SPI1, &RxBuffer[i], 1);
	}


	while(1)
	{
		// Compare Transmitted and received strings
		if(strcmp((char*)TxBuffer, (char*)RxBuffer) == 0)
		{
			printf("\n\r   Loopback Passed\n   ");

			printf("\n\rTransmitted string = %s", TxBuffer );
			printf("\n\rReceived string    = %s", RxBuffer );
			printf("\n\n");
		}
		else
		{
			printf("\n\rLoopback Failed\n\n");
		}

		delay_ms(500);
	}
}
