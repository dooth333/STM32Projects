#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Serial.h"
#include "esp.h"
#include <String.h>

uint8_t RXData;
uint16_t keyNumber;
int main(void)
{
	OLED_Init();
	Serial_Init();
	OLED_ShowString(1,1,"Connecting....");
	char is = esp_Init();
	if(is != 0)
	{
		OLED_Clear();
		OLED_ShowString(1,1,"Fail");
		OLED_ShowNum(1,8,is,1);
		is = esp_Init();
	}
	if(is == 0)
	{
		OLED_Clear();
		OLED_ShowString(1,1,"Success");
	}
	LED_Init();
	Esp_PUB();
	while (1)
	{
		OLED_ShowString(2,1,"LED:");
		OLED_ShowChar(2,6,LED);
		if(LED == '0')
		{
			LED1_OFF();
		}
		if(LED == '1')
		{
			LED1_ON();
		}
	}
}




