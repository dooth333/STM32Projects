#include "stm32f10x.h"                  // Device header
#include "bspLed.h"
#include "Delay.h"

int main(void)
{
	bspLed_Init();
	
	while (1)
	{	
		LED_RED();
		Delay_ms(1000);
		LED_GREEN();
		Delay_ms(1000);
		LED_BLUE();
		Delay_ms(1000);
		LED_YELLOW();
		Delay_ms(1000);
		LED_PURPLE();
		Delay_ms(1000);
		LED_CYAN();
		Delay_ms(1000);
		LED_WHITE();
		Delay_ms(1000);
		LED_RGBOFF();
		Delay_ms(1000);
	}
}
