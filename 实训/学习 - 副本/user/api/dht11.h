#ifndef _DHT11_H
#define _DHT11_H
#include "stm32f10x.h"                  // Device header

#define DHT11_Mode_OUT 1
#define DHT11_Mode_IN 0
#define GPIO_Pin_DHT11 GPIO_Pin_11

typedef struct{
	u8 huim;
	u8 temp;
}typedef_DATA;

extern typedef_DATA dht11_data;

#define DHT11_H (GPIO_SetBits(GPIOA,GPIO_Pin_DHT11))
#define DHT11_L (GPIO_ResetBits(GPIOA,GPIO_Pin_DHT11))
#define DHT11_ReadPin (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_DHT11))

u8 DHT11_ReadData(void);
void Change_DHT11_Mode(u8 mode);
#endif

