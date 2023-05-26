#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Timer.h"
#include "Serial.h"

uint32_t CountOfToggle;
uint16_t flag=0;
int main(void)
{
	Timer_Init();
	LED_Init();
	Serial_Init();
	while (1)
	{
		if(flag)
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)  == 0)
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_2);
				CountOfToggle++;
				Serial_SendString("CountOfToggle is:");
				Serial_SendNumber(CountOfToggle,5);
				Serial_SendString("\n");
			}
			else
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			}
			flag = 0;
		}		
	}
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		flag=1;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

