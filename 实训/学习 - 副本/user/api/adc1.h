#ifndef _ADC1_H
#define _ADC1_H

#include "stm32f10x.h"                  // Device header

typedef struct{
	u16 light;
}typedef_ADC;
extern typedef_ADC adc_data;

void ADC1_Init(void);
u16 ADC1_GetValue(void);

#endif
