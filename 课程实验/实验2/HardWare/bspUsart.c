#include "stm32f10x.h"                  // Device header
#include <stdio.h>

uint8_t Serial_RxData;//用于存储接收到的数据

void bspUsart_Init(void)
{
	//开启用到的USART和GPIO的时钟PA9和PA10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
	
	//初始化PA9为复用输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//配置引脚PA9
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;//设置为复用输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//初始化PA10为浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//配置引脚PA10
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//设置为浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//通过结构体配置USART1
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;//波特率115200
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制不使用流
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//串口模式:接收和发送
	USART_InitStructure.USART_Parity = USART_Parity_No;//校验位：无校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;//停止位：1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长：8位
	USART_Init(USART1,&USART_InitStructure);
	
	//开启RXNE标志位到NVIC的输出
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//初始化NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//中断源配置USART1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//NVIC使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级1
	NVIC_Init(&NVIC_InitStructure);
	
	//打开USART1
	USART_Cmd(USART1,ENABLE);
}

/**
  * @brief  串口发送一个字节的函数
  * @param  Byte 要发送的字节
  * @retval None
  */
void bspUsart_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待发送完成
}

/**
  * @brief  串口发送一个字符串
  * @param  *String 要发送的字符串
  * @retval None
  */
void bspUsart_SendString(char *String)
{
	uint8_t i;
	for(i = 0; String[i] == '\0'; i++)
	{
		bspUsart_SendByte(String[i]);
	}
}

/**
  * @brief  重写fputc用于printf打印到串口
  * @param  
  * @retval None
  */
int fputc(int ch, FILE *f){
	bspUsart_SendByte(ch);
	return ch;
}

/**
  * @brief  中断函数接收数据
  * @param  
  * @retval None
  */
void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)  == SET){
		Serial_RxData = USART_ReceiveData(USART1);
		bspUsart_SendByte(Serial_RxData);
		printf("\n");
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
