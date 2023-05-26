//#include "stm32f10x.h"                  // Device header
//#include "Delay.h"
//#include "OLED.h"
//#include "Timer.h"
//#include "bspUsart.h"

//// 定时器输入捕获用户自定义变量结构体声明
//typedef struct {
//uint8_t Capture_FinishFlag; // 捕获结束标志位
//uint8_t Capture_StartFlag; // 捕获开始标志位
//uint16_t Capture_CcrValue; // 捕获寄存器的值
//uint16_t Capture_Period; // 自动重装载寄存器更新标志
//} TIM_ICUserValueTypeDef;

//TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

//int main(void)
//{
//	uint32_t time;
//	uint32_t TIM_PscCLK = 72000000 / (71+1);
//	OLED_Init();
//	OLED_ShowNum(1,1,25,3);
//	Timer_Init();
//	bspUsart_Init();
//	printf ( "\r\n 野火 STM32 输入捕获实验\r\n" );
//  printf ( "\r\n 按下 K1，测试 K1 按下的时间\r\n" );

//	while (1)
//	{
//		if (TIM_ICUserValueStructure.Capture_FinishFlag == 1) {
//		// 计算高电平时间的计数器的值
//		time = TIM_ICUserValueStructure.Capture_Period * (71+1) +
//		(TIM_ICUserValueStructure.Capture_CcrValue+1);
//		
//		// 打印高电平脉宽时间
//		printf ( "\r\n 测得高电平脉宽时间： %d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK );
//		
//		TIM_ICUserValueStructure.Capture_FinishFlag = 0;
//	}
//	}
//}


//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
//	{
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//	}
//}

//void TIM3_IRQHandler(void)
//{
//// 当要被捕获的信号的周期大于定时器的最长定时时，定时器就会溢出，产生更新中断
//// 这个时候我们需要把这个最长的定时周期加到捕获信号的时间里面去
//if ( TIM_GetITStatus ( TIM3, TIM_IT_Update) != RESET ) {
//		TIM_ICUserValueStructure.Capture_Period ++;
//		TIM_ClearITPendingBit ( TIM3, TIM_FLAG_Update );
//		}

// // 上升沿捕获中断
// if ( TIM_GetITStatus (TIM3, TIM_IT_CC1 ) != RESET) {
// // 第一次捕获
// if ( TIM_ICUserValueStructure.Capture_StartFlag == 0 ) {
// // 计数器清 0
// TIM_SetCounter ( TIM3, 0 );
// // 自动重装载寄存器更新标志清 0
// TIM_ICUserValueStructure.Capture_Period = 0;
// // 存捕获比较寄存器的值的变量的值清 0
// TIM_ICUserValueStructure.Capture_CcrValue = 0;

// // 当第一次捕获到上升沿之后，就把捕获边沿配置为下降沿
// TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Falling);
// // 开始捕获标准置 1
// TIM_ICUserValueStructure.Capture_StartFlag = 1;
// }
// // 下降沿捕获中断
// else { // 第二次捕获
// // 获取捕获比较寄存器的值，这个值就是捕获到的高电平的时间的值
// TIM_ICUserValueStructure.Capture_CcrValue =
// TIM_GetCapture1 (TIM3);

// // 当第二次捕获到下降沿之后，就把捕获边沿配置为上升沿，好开启新的一轮捕获
// TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
// // 开始捕获标志清 0
// TIM_ICUserValueStructure.Capture_StartFlag = 0;
// // 捕获完成标志置 1
// TIM_ICUserValueStructure.Capture_FinishFlag = 1;
// }

// TIM_ClearITPendingBit (TIM3,TIM_IT_CC1);
// }
//}





