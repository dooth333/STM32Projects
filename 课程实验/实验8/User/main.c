#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "DMA.h"

uint8_t Buffercmp(const uint32_t* pBuffer,uint32_t* pBuffer1, uint16_t BufferLength)
{
	/* 数据长度递减 */
	while (BufferLength--) {
	/* 判断两个数据源是否对应相等 */
	if (*pBuffer != *pBuffer1) {
	/* 对应数据源不相等马上退出函数，并返回 0 */
	return 0;
	 }
	 /* 递增两个数据源的地址指针 */
	 pBuffer++;
	 pBuffer1++;
	 }
	 /* 完成判断并且对应数据相对 */
	 return 1;
}

int main(void)
{
	/* 定义存放比较结果变量 */
	uint8_t TransferStatus;

	/* LED 端口初始化 */
	LED_Init();

	/* 设置 RGB 彩色灯为紫色 */
	 LED1_ON();
	 
	 /* 简单延时函数 */
	 Delay_ms(100);
	 
	 /* DMA 传输配置 */
	 DMA_Config();
	 
	 /* 等待 DMA 传输完成 */
	 while (DMA_GetFlagStatus(DMA_FLAG_TC)==RESET);
	 
	 /* 比较源数据与传输后数据 */
	 TransferStatus= Buffercmp(aSRC_Const_Buffer,aDST_Buffer, BUFFER_SIZE);
	 
	 /* 判断源数据与传输后数据比较结果*/
	 if (TransferStatus==1)
	 {
			LED2_ON();
	 }
	 if (TransferStatus==2)
	 {
			LED2_OFF();
	 }
 
}



