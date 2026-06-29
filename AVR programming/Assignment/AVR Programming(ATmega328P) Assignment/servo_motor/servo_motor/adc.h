/*
 * adc.h
 *
 * Created: 28-06-2026 22:02:57
 *  Author: User
 */ 


#ifndef ADC_H_
#define ADC_H_

void Init_ADC();

uint16_t Get_ADC_value();

uint16_t Map_ADC_To_PulseWidth(uint16_t ADC_value);



#endif /* ADC_H_ */