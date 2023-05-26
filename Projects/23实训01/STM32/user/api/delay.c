#include "delay.h"

//�δ�ʱ����ʼ��
void Delay_Config(void)
{
	if(SysTick_Config(72000) == 1)//���õδ�ʱ��Ϊ1ms��ʱ
	{
		while(1);
	}
}


u32 runtime = 0;

//��ʱ1ms�������ж�
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






