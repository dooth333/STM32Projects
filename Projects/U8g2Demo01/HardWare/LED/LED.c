#include "stm32f10x.h"                  // Device header
#include "LED.h"

/*“˝Ω≈≈‰÷√*/
#define LED1_Clock RCC_APB2Periph_GPIOA
#define LED1_GPIO GPIOA
#define LED1_Pin GPIO_Pin_0
#define LED1_W(x)	GPIO_WriteBit(LED1_GPIO, LED1_Pin, (BitAction)(x))

void LED_Init(void)
{
	
	RCC_APB2PeriphClockCmd(LED1_Clock,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED1_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
	LED1_W(1);
}

void LED1_ON(void)
{
	LED1_W(0);
}

void LED1_OFF(void)
{
	LED1_W(1);
}

void LED1_Turn(void)
{
	if(GPIO_ReadInputDataBit(LED1_GPIO,LED1_Pin)  == 0)
	{
		LED1_W(1);
	}
	else
	{
		LED1_W(0);
	}
}
