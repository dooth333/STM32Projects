#include "stm32f10x.h"                  // Device header

void LED_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructer);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
}


void LED1_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
}


void LED1_Toggle(void)
{
	u8 state = 0;
	state = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);
	state = !state;
	GPIO_WriteBit(GPIOC,GPIO_Pin_8,state);
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
}


void LED2_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
}


void LED2_Toggle(void)
{
	u8 state = 0;
	state = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9);
	state = !state;
	GPIO_WriteBit(GPIOC,GPIO_Pin_9,state);
}
