#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	//打开TIM3和GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//PA6对应TIM3的CH1
	
	GPIO_InitTypeDef  GPIO_InitTypeStructure;
	//IO设置浮空输入
	GPIO_InitTypeStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING; 
	//IO设置A6
	GPIO_InitTypeStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStructure);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	//初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// 配置输入捕获的通道，需要根据具体的 GPIO 来配置
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	// 输入捕获信号的极性配置
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// 输入通道和捕获通道的映射关系，有直连和非直连两种
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// 输入的需要被捕获的信号的分频系数
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// 输入的需要被捕获的信号的滤波系数
	TIM_ICInitStructure.TIM_ICFilter = 0;
		// 定时器输入捕获初始化
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	// 清除更新和捕获中断标志位
	TIM_ClearFlag(TIM3, TIM_FLAG_Update|TIM_IT_CC1);
		// 开启更新和捕获中断
	TIM_ITConfig (TIM3, TIM_IT_Update | TIM_IT_CC1, ENABLE );


	
	//中断优先级配置NVIC
	
   // 设置中断组为2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// 设置主优先级为 1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	// 设置抢占先级为 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
	
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}


//中断函数,名称去启动文件里找
/*
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{

		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
*/
