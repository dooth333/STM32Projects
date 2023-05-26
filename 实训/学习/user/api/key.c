#include "key.h"               
#include "stm32f10x.h"                  // Device header

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
}
u8 Key_GetValue(void)
{
	static u8 count1 = 0;
	static u8 count2 = 0;
	if(KEY1 == 0) count1++;
	else if(count1 > 15)
	{
		count1 = 0;
		return 1;
	}
	else
	{
		count1 = 0;
	}
	if(KEY2 == 0) count2++;
	else if(count2 > 15)
	{
		count2 = 0;
		return 2;
	}
	else
	{
		count2 = 0;
		return 0;
	}
	return 0;
}
