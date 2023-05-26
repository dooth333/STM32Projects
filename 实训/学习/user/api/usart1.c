#include "usart1.h"                  // Device header

/**
  * @brief  ����usart1��ʼ��
  * @param  ��
  * @retval None
  */
void usart1_init(void)
{
	//��ʼUSART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//��ʼ��USART1�õ�������PA9(TXD����Transmit (tx) Data )��PA10(RXDReceive (rx) Data)
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	
	USART_InitTypeDef USART1_InitStructer;
	USART1_InitStructer.USART_BaudRate = 57600;
	USART1_InitStructer.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStructer.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART1_InitStructer.USART_Parity = USART_Parity_No;
	USART1_InitStructer.USART_StopBits = USART_StopBits_1;
	USART1_InitStructer.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART1_InitStructer);
	
	USART_Cmd(USART1,ENABLE);
}

/**
  * @brief  ���͵����ֽ�
  * @param  Ҫ���͵�date
  * @retval None
  */
void usart1_sendByte(u8 date)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//�ȴ��ϴ��������
	USART_SendData(USART1,date);
	
}

/**
  * @brief  printf�ض�����
  * @retval None
  */
int fputc(int ch,FILE*stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ��ϴ��������
	USART_SendData(USART1,ch);
	return ch;
}

/**
  * @brief �����ַ��� 
  * @param  *StringҪ���͵��ַ����׵�ַ
  * @retval None
  */
void usart1_sendString(char *String)
{
	uint8_t i;
	for(i = 0;String[i] != '\0';i++)
	{
		usart1_sendByte(String[i]);
	}
}


