#include "stm32f10x.h"                  // Device header

void LED_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructer);
}

void LED_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
}


void LED_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
}
