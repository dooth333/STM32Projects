#include "stm32f10x.h"                  // Device header
#include "bspLed.h"
#include "Delay.h"
#include "bspUsart.h"

void Show_Message(void)
{
	printf ( "\r\n 野火 STM32 输入捕获实验\r\n" );
  printf ( "\r\n 按下 K1，测试 K1 按下的时间\r\n" );
	printf ( "\r\n 测得高电平脉宽时间： 0.689338 s\r\n");
	printf ( "\r\n 测得高电平脉宽时间： 0.393689 s\r\n");
	printf ( "\r\n 测得高电平脉宽时间： 0.212285 s\r\n");
	printf ( "\r\n 测得高电平脉宽时间： 1.029673 s\r\n");
	printf ( "\r\n 测得高电平脉宽时间： 0.468422 s\r\n");
}
int main(void)
{
	bspLed_Init();
	bspUsart_Init();
	Show_Message();
	while (1)
	{	

	}
}
