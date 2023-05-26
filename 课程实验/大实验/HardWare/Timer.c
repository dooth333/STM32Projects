#include "Timer.h" 

//定义时间片
u32 timedAD[2] = {0,500};
u32 timedEsp[2] = {0,500};
u32 timedKey[2] = {0,0};

/**
  * @brief  初始化TIM3定时器，定义1ms一次终端
  * @param  无
  * @retval None
  */
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	//避免刚初始化完就进入中断的问题，即计数从1开始
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	//使能中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
}


/**
  * @brief  TIM3中断函数，1ms进入一次
  * @param  无
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		timedAD[0]++;
		timedEsp[0]++;
		timedKey[0]++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

