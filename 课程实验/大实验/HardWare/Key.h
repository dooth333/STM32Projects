#ifndef _KEY_H_
#define _KEY_H_

void Key_Init(void);

uint8_t Key_GetNum(void);

#define KEY1 (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))
#define KEY2 (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10))
#define KEY3 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6))
#define KEY4 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5))

#endif
