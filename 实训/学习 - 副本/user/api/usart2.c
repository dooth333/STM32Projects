#include "usart2.h"                  // Device header

/**
  * @brief  ����usart2��ʼ��
  * @param  ��
  * @retval None
  */
void usart2_init(void)
{
	//��ʼUSART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//��ʼ��USART2�õ�������PA2(TXD����Transmit (tx) Data )��PA3(RXDReceive (rx) Data)
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	
	USART_InitTypeDef USART2_InitStructer;
	USART2_InitStructer.USART_BaudRate = 57600;
	USART2_InitStructer.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART2_InitStructer.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART2_InitStructer.USART_Parity = USART_Parity_No;
	USART2_InitStructer.USART_StopBits = USART_StopBits_1;
	USART2_InitStructer.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&USART2_InitStructer);
	
	USART_Cmd(USART2,ENABLE);
	
}

/**
  * @brief  ���͵����ֽ�
  * @param  Ҫ���͵�date
  * @retval None
  */
void usart2_sendByte(u8 date)
{
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);//�ȴ��ϴ��������
	USART_SendData(USART2,date);
	
}


/**
  * @brief �����ַ��� 
  * @param  *StringҪ���͵��ַ����׵�ַ
  * @retval None
  */
void Usart_SendString(unsigned char *String,u8 count)
{
	uint8_t i;
	for(i = 0;i<= count;i++)
	{
		usart2_sendByte(String[i]);
	}
}


