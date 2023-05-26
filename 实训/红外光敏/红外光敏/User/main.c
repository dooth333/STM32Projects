#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Timer.h"
#include "LED.h"

uint16_t TEMP, IR, Num = 0;
u32 timeTemp[2] = {0, 20};

int main(void)
{
	OLED_Init();
	AD_Init();
	Timer_Init();
	LED_Init();
	
	OLED_ShowString(1, 1, "TEMP:");
	OLED_ShowString(2, 1, "  IR:");
	
	while (1)
	{
		OLED_ShowNum(1, 6, TEMP, 4);
		OLED_ShowNum(2, 6, IR, 4);
		OLED_ShowNum(3, 6, Num, 4);
		if (TEMP > 3000 & Num == 1) //光照强度低且红外触发
		{
			LED1_ON();
		}
		else
		{
			LED1_OFF();
		}
	}
}

void TIM2_IRQHandler(void) //定时器内读取AD值,定时50ms
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		timeTemp[0]++;
		
		IR = AD_GetValue(ADC_Channel_4); //50ms读取一次AD4红外数据
		if (IR > 1000) //判断进出人
		{
			Num = !Num;
		}
		if (timeTemp[0] > timeTemp[1]) //1s读取一次
		{
			TEMP = AD_GetValue(ADC_Channel_5); //读取AD5光照数据
			timeTemp[0] = 0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
