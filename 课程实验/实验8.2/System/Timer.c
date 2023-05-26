#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	//开启TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//选择内部时钟
	TIM_InternalClockConfig(TIM2);
	//定义TIM2初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	//分频方式:选择不分频
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//计数方式选择:向上计数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//ARR的自动重装值设为10000-1使其可以达到500ms一次中断
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	//PSC预分频器的值设为3600-1使其可以达到500ms一次中断
	TIM_TimeBaseInitStructure.TIM_Prescaler = 3600 - 1;
	//重复计数器的值不用给0
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	//调用初始化函数进行初始化
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	//避免刚初始化完就进入中断的问题，即计数从1开始
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//使能中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//配置NVIC
	//中断分组的方式为组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//定义NVIC初始化结构体
	NVIC_InitTypeDef NVIC_InitStructure;
	//中断源配置选择TIM2
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	//NVIC使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	//响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	//使能定时器
	TIM_Cmd(TIM2,ENABLE);
}

//中断函数,名称去启动文件里找
/*
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		//自己代码
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
*/
