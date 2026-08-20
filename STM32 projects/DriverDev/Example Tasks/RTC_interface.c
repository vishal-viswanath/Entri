





#include <stdint.h>
#include <string.h>
#include "stm32f401xx_i2c_driver.h"
#include "stm32f401xx_gpio_driver.h"
#include "USART_Baremetal.h"
#include "TIMERs_Baremetal.h"


#define RTC_ADDRESS     0x68

void ConfigureI2c_GpioPins()
{

	// Set GPIO Configurations
	// - PB8 and PB9 are used as SCL and SDA of I2C1 instance
	// - Use alternate function AF4
	// - SCL and SDA are open drain with pull up


	GPIO_Handle_t i2c;
	i2c.pGPIOx                            = GPIOB;
	i2c.GPIO_PinConfig.GPIO_PinMode       = GPIO_MODE_ALTFN;
	i2c.GPIO_PinConfig.GPIO_PinAltFunMode = AF4;
	i2c.GPIO_PinConfig.GPIO_PinSpeed      = GPIO_SPEED_HIGH;
	i2c.GPIO_PinConfig.GPIO_PinOPType     = GPIO_OP_TYPE_OD;
	i2c.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_PIN_PU;

	// SCL
	i2c.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&i2c);
	// SDA
	i2c.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&i2c);


	GPIOA_PCLK_EN();
	GPIOA->MODER &=~(0x3<< 2*0);
	GPIOA->MODER |= (0x1<< 2*0);

}

/**********************************************************************************
 *  RTC helper functions:
 *   * For decimal to BCD
 *   * For BCD to decimal
 */
static uint8_t RTC_ConvertDecToBCD(uint8_t decimal)
{
	uint8_t bcd = ((decimal/10)<<4 ) | (decimal%10);
	return bcd;

	//Note: decimal number indicates time, so less than 60 (2 digits)//
}
static uint8_t RTC_ConvertBCDToDec(uint8_t bcd)
{
	uint8_t decimal = ((bcd>>4)*10 ) + (bcd&0xF);
	return decimal;

}
/*************************************************************************************/

int RTC_main(void)
{

	// Initialize USART2 for debugging
	USART_Configuration();

	// Initialize timer for creating delay
	Timer_Delay_Creation();

	// Initialize GPIO pins for I2C1
	ConfigureI2c_GpioPins();

	// Initialize I2C1 with required configurations
	I2C_Handle_t i2c1;
	i2c1.pI2Cx = I2C1;
	i2c1.I2C_Config.I2C_AckControl = ENABLE;
	i2c1.I2C_Config.I2C_SCLSpeed   = I2C_SCL_SPEED_SM;

	I2C_Init(&i2c1);

	// Enable peripheral
	I2C_PeripheralControl(I2C1, ENABLE);


	     //******************************* Reading time from a Real-Time Clock****************************
	     //
	     //RTC details:
	     // - Slave address of RTC - 0x68
		 // - RTC stores time in BCD format
	     // - RTC registers:
		 //                 * seconds stored at address : 0x00
		 //                 * minutes stored at address : 0x01
	     //                 * hours stored at address : 0x02
	     //
	     // - RTC control bits:
		 //                 * MSB of seconds register : controls RTC ON/OFF ( set as 0 )
	     //                                           : seconds stored in Bits6:0( Use mask 0x7F for read/write)
		 //                 * Bit_6 of hours register : controls 12/24 hour mode
	     //                                           : 0 - 24hr mode, 1- 12hr mode
	     //                                           : hour stored in Bit5:0 in 24hr mode (Use mask 0x3F for read/write)
		 //                 * Bit_5 of hours register : indicates AM/PM in 12hr mode
         //
	     //Objective:
		 // - initialize RTC with current time
		 // - read current time from registers
	     //
	     //**************************************************************************************************

	     // Setup data buffer to transmit time
	     // - stores address to which data should be send
		 // - stores seconds, minutes, hours
		 // - stored in BCD format
	     // - Note:
		 //       * MSB of seconds must be 0
		 //       * Bit_6 of hours must be 0

		 uint8_t buffer[4];

		 // Store address to which data should be sent
		 // seconds register address
		 uint8_t sec_address = 0x00;
		 buffer[0] = sec_address;

		 // seconds
		 uint8_t seconds= 00;
		 buffer[1] = (RTC_ConvertDecToBCD(seconds)& 0x7F);

		 // minutes
		 uint8_t minutes = 27;
		 buffer[2] = RTC_ConvertDecToBCD(minutes);

		 // hours
		 uint8_t hours = 22;
		 buffer[3] = ( RTC_ConvertDecToBCD(hours) & 0x3F );


		 // Initialize RTC time by transmitting buffer
		I2C_MasterSendData(&i2c1, buffer, 4, RTC_ADDRESS, I2C_DISABLE_SR);




	while(1)
	{
		// Receive data, starting from address 0x00
		I2C_MasterSendData(&i2c1, &sec_address, 1, RTC_ADDRESS, I2C_ENABLE_SR);

		// Receive RTC data into a buffer
		I2C_MasterReceiveData(&i2c1, buffer, 3, RTC_ADDRESS, I2C_DISABLE_SR );

		// convert BCD data into decimal format
		seconds = RTC_ConvertBCDToDec(buffer[0]& 0x7F);
		minutes = RTC_ConvertBCDToDec(buffer[1]);
	    hours  =  RTC_ConvertBCDToDec(buffer[2]&0x3F);

		// Print time in serial monitor

	    USART_Send_String("\n\nCurrent Time: ");
	   	USART_Send_Number(hours);
	   	USART_Send_String(": ");
	    USART_Send_Number(minutes);
	    USART_Send_String(": ");
	   	USART_Send_Number(seconds);

		delay_ms(500);
	}
}
