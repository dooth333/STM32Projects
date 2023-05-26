#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "DMA.h"
#include "Serial.h"


int main(void)
{
	uint16_t i;
	/* 初始化 USART */
	Serial_Init();
	/* 配置使用 DMA 模式 */
	USARTx_DMA_Config();
	/* 配置 RGB 彩色灯 */
	LED_Init();
//	printf("\r\n USART1 DMA TX 测试 \r\n");
	Serial_SendString("\r\n USART1 DMA TX 测试 \r\n");
 
 /*填充将要发送的数据*/
 for (i=0; i<SENDBUFF_SIZE; i++)
 {
	SendBuff[i] = 'A';
 }
 
 /*为演示 DMA 持续运行而 CPU 还能处理其它事情，持续使用 DMA 发送数据，量非常大，
 *长时间运行可能会导致电脑端串口调试助手会卡死，鼠标乱飞的情况，
 *或把 DMA 配置中的循环模式改为单次模式*/
 
 /* USART1 向 DMA 发出 TX 请求 */
 USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
 /* 此时 CPU 是空闲的，可以干其他的事情 */
 //例如同时控制 LED
 while (1)
 {
	 LED1_ON();
	 Delay_ms(500);
	 LED1_OFF();
	 Delay_ms(500);
 }
}



