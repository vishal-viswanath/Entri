/*
 * stm32f401xx.h
 *
 *  Created on: Jan 18, 2026
 *      Author: User
 */

#ifndef INC_STM32F401XX_H_

#include <stdio.h>
#include <stdint.h>

#define INC_STM32F401XX_H_

#define __vo  volatile
#define Enable         1
#define Disable        0

#define IRQ_NO_EXTI0         6
#define IRQ_NO_EXTI1         7
#define IRQ_NO_EXTI2         8
#define IRQ_NO_EXTI3         9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI5_9      23
#define IRQ_NO_EXTI10_15    40

/*
 * Processor definitions
 */

// ARM Cortex Mx Processor NVIC ISERx register addresses

#define NVIC_ISER0        ((__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1        ((__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2        ((__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3        ((__vo uint32_t*)0xE000E10C )

// ARM Cortex Mx Processor NVIC ICERx register addresses

#define NVIC_ICER0        ((__vo uint32_t*)0xE000E180 )
#define NVIC_ICER1        ((__vo uint32_t*)0xE000E184 )
#define NVIC_ICER2        ((__vo uint32_t*)0xE000E188 )
#define NVIC_ICER3        ((__vo uint32_t*)0xE000E18C )

// ARM Cortex Mx Processor priority register address calculation

#define NVIC_PR_BASE_ADDR ((__vo uint32_t*)0xE000E400)

// This macro returns a code (between 0 to 7) for a given GPIO base address(x)

#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA)?0:\
		                                (x == GPIOB)?1:\
		                            	(x == GPIOC)?2:\
		                            	(x == GPIOD)?3:\
		                            	(x == GPIOE)?4:\
		                            	(x == GPIOH)?7:0)

/*
 * Memory base address
 */

#define FLASH_BASEADDR        0x08000000U              // Reference manual 51st page (STM32-F401RE)
#define ROM_BASEADDR          0x1FFF0000U
#define SRAM_BASEADDR         0x20000000U

/*
 * Peripheral bus address
 */

#define APB1_PERIPH_BASEADDR         0x40000000U
#define APB2_PERIPH_BASEADDR         0x40010000U
#define AHB1_PERIPH_BASEADDR         0x40020000U
#define AHB2_PERIPH_BASEADDR         0x50000000U

/*
 * Base address of the peripherals in AHB1
 */

#define GPIOA_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x0000)
#define GPIOB_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x0400)
#define GPIOC_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x0800)
#define GPIOD_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x0C00)
#define GPIOE_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x1000)
#define GPIOH_PERIPH_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x1C00)
#define CRC_PERIPH_BASEADDR                 (AHB1_PERIPH_BASEADDR + 0x3000)
#define RCC_PERIPH_BASEADDR                 (AHB1_PERIPH_BASEADDR + 0x3800)
#define FLASH_INTERFACE_REGISTER_BASEADDR   (AHB1_PERIPH_BASEADDR + 0x3C00)
#define DMA1_PERIPH_BASEADDR                (AHB1_PERIPH_BASEADDR + 0x6000)
#define DMA2_PERIPH_BASEADDR                (AHB1_PERIPH_BASEADDR + 0x6400)


/*
 * Base address of the peripheral in AHB2
 */

#define USB_OTG_FS_BASEADDR                 (AHB2_PERIPH_BASEADDR + 0x0000)

/*
 * Base address of the peripheral in APB1
 */

#define TIM2_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x0C00)
#define RTC_BKP_REGISTERS_BASEADDR         (APB1_PERIPH_BASEADDR + 0x2800)
#define WWDG_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x2C00)
#define IWDG_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x3000)
#define I2S2ext_BASEADDR                   (APB1_PERIPH_BASEADDR + 0x3400)
#define SPI2_I2S2_BASEADDR                 (APB1_PERIPH_BASEADDR + 0x3800)
#define SPI3_I2S3_BASEADDR                 (APB1_PERIPH_BASEADDR + 0x3C00)
#define I2S3ext_BASEADDR                   (APB1_PERIPH_BASEADDR + 0x4000)
#define USART2_BASEADDR                    (APB1_PERIPH_BASEADDR + 0x4400)
#define I2C1_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR                      (APB1_PERIPH_BASEADDR + 0x5C00)
#define PWR_BASEADDR                       (APB1_PERIPH_BASEADDR + 0x7000)


/*
 * Base address of the peripheral in APB2
 */

#define TIM1_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x0000)
#define USART1_BASEADDR                   (AHB2_PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR                   (AHB2_PERIPH_BASEADDR + 0x1400)
#define ADC1_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x2000)
#define SDIO_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x2C00)
#define SPI1_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x3400)
#define SYSCFG_BASEADDR                   (AHB2_PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x3C00)
#define TIM9_BASEADDR                     (AHB2_PERIPH_BASEADDR + 0x4000)
#define TIM10_BASEADDR                    (AHB2_PERIPH_BASEADDR + 0x4400)
#define TIM11_BASEADDR                    (AHB2_PERIPH_BASEADDR + 0x4800)


/*
 * GPIO register definition
 */

typedef struct{

	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];

}GPIO_RegDef_t;

#define GPIOA        (GPIO_RegDef_t *)(GPIOA_PERIPH_BASEADDR)
#define GPIOB        (GPIO_RegDef_t *)(GPIOB_PERIPH_BASEADDR)
#define GPIOC        (GPIO_RegDef_t *)(GPIOC_PERIPH_BASEADDR)
#define GPIOD        (GPIO_RegDef_t *)(GPIOD_PERIPH_BASEADDR)
#define GPIOE        (GPIO_RegDef_t *)(GPIOE_PERIPH_BASEADDR)
#define GPIOH        (GPIO_RegDef_t *)(GPIOH_PERIPH_BASEADDR)


/*
 * I2C register definition
 */

typedef struct{

	__vo uint32_t I2C_CR1;
	__vo uint32_t I2C_CR2;
	__vo uint32_t I2C_OAR1;
	__vo uint32_t I2C_OAR2;
	__vo uint32_t I2C_DR;
	__vo uint32_t I2C_SR1;
	__vo uint32_t I2C_SR2;
	__vo uint32_t I2C_CCR;
	__vo uint32_t I2C_TRISE;
	__vo uint32_t I2C_FLTR;

}I2C_RegDef_t;

#define I2C1           ((I2C_RegDef_t *)(I2C1_BASEADDR))
#define I2C2           ((I2C_RegDef_t *)(I2C2_BASEADDR))
#define I2C3           ((I2C_RegDef_t *)(I2C3_BASEADDR))


/*
 * SPI register definition
 */

typedef struct{

	__vo uint32_t SPI_CR1;
	__vo uint32_t SPI_SR;
	__vo uint32_t SPI_DR;
	__vo uint32_t SPI_CRCPR;
	__vo uint32_t SPI_RXCRCR;
	__vo uint32_t SPI_TXCRCR;
	__vo uint32_t SPI_I2SCFGR;
	__vo uint32_t SPI_I2SPR;

}SPI_RegDef_t;

#define SPI1           ((SPI_RegDef_t *)(SPI1_BASEADDR))
#define SPI2           ((SPI_RegDef_t *)(SPI2_I2S2_BASEADDR))
#define SPI3           ((SPI_RegDef_t *)(SPI3_I2S3_BASEADDR))
#define SPI4           ((SPI_RegDef_t *)(SPI4_BASEADDR))

/*
 * USART register definition
 */

typedef struct{
	__vo uint32_t USART_SR;
	__vo uint32_t USART_DR;
	__vo uint32_t USART_BRR;
	__vo uint32_t USART_CR1;
	__vo uint32_t USART_CR2;
	__vo uint32_t USART_CR3;
	__vo uint32_t USART_GTPR;

}USART_RegDef_t;

#define USART1      (USART_RegDef_t *)(USART1_BASEADDR)
#define USART2      (USART_RegDef_t *)(USART2_BASEADDR)
#define USART6      (USART_RegDef_t *)(USART6_BASEADDR)

/*
 * RCC register definition
 */

typedef struct{
	__vo uint32_t RCC_CR;
	__vo uint32_t RCC_PLLCFGR;
	__vo uint32_t RCC_CFGR;
	__vo uint32_t RCC_CIR;
	__vo uint32_t RCC_AHB1RSTR;
	__vo uint32_t RCC_AHB2RSTS;
	uint32_t      RESERVED0;
	uint32_t      RESERVED1;
	__vo uint32_t RCC_APB1RSTR;
	__vo uint32_t RCC_APB2RSTS;
	uint32_t      RESERVED2;
	uint32_t      RESERVED3;
	__vo uint32_t RCC_AHB1ENR;
	__vo uint32_t RCC_AHB2ENR;
	uint32_t      RESERVED4;
	uint32_t      RESERVED5;
	__vo uint32_t RCC_APB1ENR;
	__vo uint32_t RCC_APB2ENR;
	uint32_t      RESERVED6;
	uint32_t      RESERVED7;
	__vo uint32_t RCC_AHB1LPENR;
	__vo uint32_t RCC_AHB2LPENR;
	uint32_t      RESERVED8;
	uint32_t      RESERVED9;
	__vo uint32_t RCC_APB1LPENR;
	__vo uint32_t RCC_APB2LPENR;
	uint32_t      RESERVED10;
	uint32_t      RESERVED11;
	__vo uint32_t RCC_BDCR;
	__vo uint32_t RCC_CSR;
	uint32_t      RESERVED12;
	uint32_t      RESERVED13;
	__vo uint32_t RCC_SSCGR;
	__vo uint32_t RCC_PLLI2SCFGR;


}RCC_RegDef_t;

#define RCC       ((RCC_RegDef_t *) (RCC_PERIPH_BASEADDR))


/*
 * Peripheral Clock enable and disable macros
 */

// GPIO peripheral clock enable macros

#define GPIOA_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<0))
#define GPIOB_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<1))
#define GPIOC_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<2))
#define GPIOD_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<3))
#define GPIOE_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<4))
#define GPIOH_PCLK_EN()    (RCC->RCC_AHB1ENR|=(1<<7))

// GPIO peripheral clock disable macros

#define GPIOA_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<0))
#define GPIOB_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<1))
#define GPIOC_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<2))
#define GPIOD_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<3))
#define GPIOE_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<4))
#define GPIOH_PCLK_DI()    (RCC->RCC_AHB1ENR &=~(1<<7))

// I2C peripheral clock enable macros

#define I2C1_PCLK_EN()      (RCC ->RCC_APB1ENR |=(1<<21))
#define I2C2_PCLK_EN()      (RCC ->RCC_APB1ENR |=(1<<22))
#define I2C3_PCLK_EN()      (RCC ->RCC_APB1ENR |=(1<<23))

// I2C peripheral clock disable macros

#define I2C3_PCLK_DI()      (RCC ->RCC_APB1ENR &=~(1<<23))
#define I2C3_PCLK_DI()      (RCC ->RCC_APB1ENR &=~(1<<23))
#define I2C3_PCLK_DI()      (RCC ->RCC_APB1ENR &=~(1<<23))

// SPI peripheral clock enable macros

#define SPI1_PCLK_EN()       (RCC->RCC_APB2ENR |=(1<<12))
#define SPI2_PCLK_EN()       (RCC->RCC_APB1ENR |=(1<<14))
#define SPI3_PCLK_EN()       (RCC->RCC_APB1ENR |=(1<<15))
#define SPI4_PCLK_EN()       (RCC->RCC_APB2ENR |=(1<<13))

// SPI peripheral clock disable macros

#define SPI1_PCLK_DI()       (RCC->RCC_APB2ENR &=~(1<<12))
#define SPI2_PCLK_DI()       (RCC->RCC_APB2ENR &=~(1<<14))
#define SPI3_PCLK_DI()       (RCC->RCC_APB2ENR &=~(1<<15))
#define SPI4_PCLK_DI()       (RCC->RCC_APB2ENR &=~(1<<13))

// USART peripheral clock Enable macros

#define USART1_PCLK_EN()     (RCC->RCC_APB2ENR |=(1<<4))
#define USART2_PCLK_EN()     (RCC->RCC_APB1ENR |=(1<<17))
#define USART6_PCLK_EN()     (RCC->RCC_APB2ENR |=(1<<5))

// USART peripheral clock disable macros

#define USART6_PCLK_DI()     (RCC->RCC_APB2ENR &=~(1<<5))
#define USART2_PCLK_DI()     (RCC->RCC_APB1ENR &=~(1<<17))
#define USART2_PCLK_DI()     (RCC->RCC_APB1ENR &=~(1<<17))

// GPIO Reset macros

#define GPIOA_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<0))
#define GPIOB_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<1))
#define GPIOC_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<2))
#define GPIOD_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<3))
#define GPIOE_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<4))
#define GPIOH_RST_EN()       (RCC->RCC_AHB1RSTR |= (1<<7))

// GPIO Disable Reset values for set default values

#define GPIOA_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<0))
#define GPIOB_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<1))
#define GPIOC_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<2))
#define GPIOD_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<3))
#define GPIOE_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<4))
#define GPIOH_RST_DI()       (RCC->RCC_AHB1RSTR &= ~(1<<7))

// Clock enable macros for SYSCFG peripheral

#define SYSCFG_PCLK_EN()    (RCC->RCC_APB2ENR |= (1<<14))


// EXTI register definition
typedef struct
{
	__vo uint32_t IMR;         // Address offset 0x00
	__vo uint32_t EMR;         // Address offset 0x04
	__vo uint32_t RTSR;        // Address offset 0x08
	__vo uint32_t FTSR;        // Address offset 0x0C
	__vo uint32_t SWIER;       // Address offset 0x10
	__vo uint32_t PR;          // Address offset 0x14
}EXTI_RegDef_t;

#define EXTI     ((EXTI_RegDef_t*) EXTI_BASEADDR)


//SYSCONFIG Register definition
typedef struct
{
	__vo uint32_t MEMRMP;       // Address offset 0x00
	__vo uint32_t PMC;          // Address offset 0x04
	__vo uint32_t EXTICR[4];    // Address offset 0x08 - 0x14
	uint32_t RESERVED[2];       // Address offset 0x18 - 0x1F
	__vo uint32_t CMPCR;        // Address offset 0x20
}SYSCFG_RegDef_t;

#define SYSCFG     ((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

#endif /* INC_STM32F401XX_H_ */
