#include "delay.h"

//滴答定时器初始化
void Delay_Config(void)
{
	if(SysTick_Config(72000) == 1)//配置滴答定时器为1ms延时
	{
		while(1);
	}
}


u32 runtime = 0;

//定时1ms发生的中断
void SysTick_Handler(void)
{

	runtime++;

}

void Delay_ms(u32 time)
{
	u32 nowtime = runtime;
	while(runtime < (nowtime+time));
}

void Delay_usnop(u32 time)
{
	while(time--)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();		
	}
}
void Delay_msnop(u32 time)
{
	while(time--)
	{
		Delay_usnop(1000);
	}
}






