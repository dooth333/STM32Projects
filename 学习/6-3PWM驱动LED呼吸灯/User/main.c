#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
uint16_t i;
int main(void)
{
	PWM_Init();
	OLED_Init();
	OLED_ShowString(1,3,"HelloWorld!");
	while (1)
	{
		for(i = 0; i<= 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i = 0; i<= 100; i++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
		
	}
}




