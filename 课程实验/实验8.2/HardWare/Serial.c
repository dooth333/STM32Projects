#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

/**
  * @brief  串口初始化函数
	* 初始化的为USART1发送模式的
  * @param  None
  * @retval None
  */
void Serial_Init(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	//开启RXNE标志位到NVIC的输出
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//初始化NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);

}

/**
  * @brief  串口发送一个字节的函数
  * @param  Byte 要发送的字节
  * @retval None
  */
void Serial_SendByte(uint8_t Byte){
	
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
  * @brief  串口发送数组
  * @param  *Array 数组首地址
	* @param 	Length 长度
  * @retval None
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length){
	uint16_t i;
	for(i = 0; i< Length; i++){
		Serial_SendByte(Array[i]);
	}

}

/**
  * @brief  发送字符串
	* @param  *String 字符串名或字符串
  * @retval None
  */
void Serial_SendString(char *String){
	
	uint8_t i;
	for(i = 0; String[i] != '\0'; i++){
		Serial_SendByte(String[i]);
	}

}
/**
  * @brief  工具函数，用于计算X的Y次方
  * @param  
  * @retval X的y次方
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y){
		uint32_t reslut = 1;
		while(Y--){
			reslut *= X;
		}
		return reslut;
}

/**
  * @brief  发送数字
  * @param  
  * @retval None
  */
void Serial_SendNumber(uint32_t Number,uint8_t Length){
	uint8_t i;
	for(i = 0; i< Length; i++){
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1) % 10 + '0');
	}
}

/**
  * @brief  重写fputc用于printf打印到串口
  * @param  
  * @retval None
  */
int fputc(int ch, FILE *f){
	Serial_SendByte(ch);
	return ch;
}

/**
  * @brief  封装sprintf，用于打印到串口
	* 和java未知变量个数类似
  * @param  
  * @retval None
  */
void Serial_Printf(char *format, ...){
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(){
	if(Serial_RxFlag == 1){
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(){
	return Serial_RxData;
}

/**
  * @brief  中断函数接收数据
  * @param  
  * @retval None
  */
void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)  == SET){
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

