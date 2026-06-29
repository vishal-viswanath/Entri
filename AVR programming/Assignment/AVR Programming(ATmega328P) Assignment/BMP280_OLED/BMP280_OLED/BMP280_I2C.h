/*
 * BMP280_I2C.h
 *
 * Created: 29-06-2026 08:35:06
 *  Author: User
 */ 


#ifndef BMP280_I2C_H_
#define BMP280_I2C_H_

// Define Slave Address of BMP280 sensor
// Define Slave Address of BMP280 sensor
#define BMP280_ADDR   0x76
#include "I2C.h"

uint8_t BMP_Read_Byte(uint8_t reg_addr);
void BMP_Read_Multi_Byte(uint8_t reg_addr, uint8_t *buff, uint8_t n);
void BMP_Write_Byte(uint8_t reg_addr, uint8_t byte);



#endif /* BMP280_I2C_H_ */