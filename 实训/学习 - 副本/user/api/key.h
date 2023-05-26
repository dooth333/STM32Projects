#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"                  // Device header

void Key_Init(void);
u8 Key_GetValue(void);

#define KEY1 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0))
#define KEY2 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))

#endif
