#include "delay.h"


vu32 RunTime = 0;

/*
1ms����һ��
*/
void SysTick_Handler(void)
{
	
	RunTime++;
}

void SysTick_Init(uint32_t tick)
{
	SysTick_Config(tick);
}

//��������
void Delay_ms(uint32_t time)
{
	uint32_t Time = RunTime + time;
	while(RunTime < Time)
	{}	
}

void Delay_us(uint32_t time)
{
	while(time--)
		delay_1us();
}

void Delay_msnop(uint32_t time)
{
	while(time--)
		Delay_us(1000);
}



