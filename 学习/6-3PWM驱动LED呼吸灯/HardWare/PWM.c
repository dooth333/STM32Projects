#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
//1、RCC开启时钟：
	//把TIM外设和GPIO外设的时钟打开
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	//重映射到PA15
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

//2、配置时基单元
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//先赋初始值就算用不到也可避免突然用的而没有值的错误
	TIM_OCStructInit(&TIM_OCInitStructure);
	//然后更改需要用的值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ; 
	TIM_OCInitStructure.TIM_Pulse = 0; //CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	


//3、配置输出比较单元
//包括：CCR的值、输出比较模式、极性选择、输出使能
	

// 4、配置GPIO
//把GPIO对应的GPIO初始化为复用推挽输出

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
}


void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}
