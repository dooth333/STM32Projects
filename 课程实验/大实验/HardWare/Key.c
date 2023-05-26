#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"

/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**
  * @brief  用于返回按键值
  * @param  None
  * @retval 被按下的按键
  */
uint8_t Key_GetNum(void)
{
	static u8 count1 = 0;
	static u8 count2 = 0;
	static u8 count3 = 0;
	static u8 count4 = 0;
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
	}
	if(KEY3 == 0) count3++;
	else if(count3 > 15)
	{
		count3 = 0;
		return 3;
	}
	else
	{
		count3 = 0;
	}
	if(KEY4 == 0) count4++;
	else if(count4 > 15)
	{
		count4 = 0;
		return 4;
	}
	else
	{
		count4 = 0;
	}
	return 0;
}
