#include "main.h"
#include "delay.h"
#include "LED.h"

int main(void)
{
	
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	JTAG_SWD_Config();
	SysTick_Init(40000);
	LED_init();
	
	while (1)
  {
		LED_ON();
		Delay_ms(500);
		LED_OFF();
		Delay_ms(500);
  }
	
}


void JTAG_SWD_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//完全禁用SWD及JTAG 
//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //禁用JTAG		
}

