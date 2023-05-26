#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <string.h>

//Ӳ������
#include "Key.h"

#include "Timer.h"
#include "u8g2.h"
#include "OLED.h"
#include "LED.h"

struct Keys_Struct Keys[4];
char text[30];


/**
  * @brief  ������ʼ��������һ�˽ӵ�Ƭ�����ţ�һ�˽�GND
  * @param  None
  * @retval None
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	for(uint8_t j=0;j<4;j++)
	{
		Keys[j].Step = 0;
		
		Keys[j].Key_Single_Flag =0;
	
		Keys[j].Key_Double_Flag =0;
	
		Keys[j].Key_Long_Flag = 0;
		
		Keys[j].Time_Count_Flag = 0;
	
		Keys[j].Press_Time_Count = 0;
	
	}

}


/**
  * @brief  ���ݰ����������ʵ�в���������������Whileѭ���м���
  * @param  None
  * @retval None
  */
void Key_Execute(void)
{
	for(uint8_t j=0;j<4;j++)
	{
		if(Keys[j].Key_Single_Flag ==1)
		{
			Keys[j].Key_Single_Flag =0;
			//sprintf(text,"K D:%d",j+1);
			//u8g2_DrawStr(&u8g2,80,10,text);
			//u8g2_SendBuffer(&u8g2);
			//���ݵ�����ֵ���в���
			switch(j+1)
			{
				//����1
				case 1:
				{
					
					if(ui_select < list_len - 1)
					{
						ui_select ++;
					}
					LED1_Turn();
					
				}break;
				//����2
				case 2:
				{	
					if(ui_select > 0)
					{
						ui_select --;
					}
					
				}break;
				//����3
				case 3:
				{
					
					
				}break;
				//����4
				case 4:
				{
					
				}break;
			}
			
		}
		if(Keys[j].Key_Double_Flag ==1)
		{
			Keys[j].Key_Double_Flag =0;
			//sprintf(text,"KDD:%d",j+1);
			//u8g2_DrawStr(&u8g2,80,30,text);
			//u8g2_SendBuffer(&u8g2);
			//����˫����ֵ���в���
			switch(j+1)
			{
				//����1
				case 1:
				{
					
				}break;
				//����2
				case 2:
				{
					
				}break;
				//����3
				case 3:
				{
				
				}break;
				//����4
				case 4:
				{
					
				}break;
			}
			
		}
		if(Keys[j].Key_Long_Flag ==1)
		{
			Keys[j].Key_Long_Flag =0;
			//sprintf(text,"KLD:%d",j+1);
			//u8g2_DrawStr(&u8g2,80,60,text);
			//u8g2_SendBuffer(&u8g2);
			//���ݳ�����ֵ���в���
			switch(j+1)
			{
				//����1
				case 1:
				{
					
				}break;
				//����2
				case 2:
				{
					
				}break;
				//����3
				case 3:
				{
				
				}break;
				//����4
				case 4:
				{
				
				}break;
			}
		}
	}
}

/**
  * @brief  ��������������1ms���ж���
  * @param  None
  * @retval None
  */
void Key_GetVlaues(void)
{
	
	Keys[0].Key_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);
	Keys[1].Key_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	Keys[2].Key_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
	Keys[3].Key_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
	/**
	OLED_ShowNum(3,1,Keys[0].Key_State,1);
	OLED_ShowNum(3,3,Keys[1].Key_State,1);
	OLED_ShowNum(3,5,Keys[2].Key_State,1);
	OLED_ShowNum(3,7,Keys[3].Key_State,1);
	**/
	
	for(uint8_t i=0;i<4;i++)
	{//ѭ��4�������ж�
		if(Keys[i].Time_Count_Flag == 1)
		{//�����ʼ��ʱ��־λ��1���ǾͿ�ʼ��ʱ
			Keys[i].Press_Time_Count++;
		}
		else
		{
			Keys[i].Press_Time_Count=0;
		}
		switch(Keys[i].Step)
		{//����
			case 0:
			{
				if(Keys[i].Key_State ==0)
				{//���а�������ʱ�����벽��1
					Keys[i].Step = 1;
					Keys[i].Time_Count_Flag = 1;
				}
			}break;
			case 1:
			{
				if(Keys[i].Press_Time_Count>2&&Keys[i].Key_State ==0)
				{//��ʱ20ms�ж�ʱ�䵽��֮���Ұ���δ�ɿ�
//					Keys[i].Time_Count_Flag = 0;�Ȳ����㣬������ʱ
					Keys[i].Step = 2;
//					Keys[i].Key_Single_Flag = 1;
				}
			}break;
			case 2:
			{
				if(Keys[i].Key_State ==1)
				{//�ɿ�����
					
					//������:
					//sprintf(text,"Press_Time_Count%d\r\n",Keys[i].Press_Time_Count);
					//UsartPrintf(USART_DEBUG, text);
					
					if(Keys[i].Press_Time_Count<50)
					{//����ɿ�ʱʱ����0.5s֮ǰ�����ж��ǵ�������˫��
						Keys[i].Step = 3;
//						Keys[i].Time_Count_Flag = 0;
//						Keys[i].Key_Single_Flag = 1;
					}
					if(Keys[i].Press_Time_Count>100)
					{
						Keys[i].Step = 0;
						Keys[i].Time_Count_Flag = 0;
						Keys[i].Key_Long_Flag = 1;
					}
				}
			}break;
			case 3:
			{
				if(Keys[i].Key_State ==0&&Keys[i].Press_Time_Count<50)
				{//�����ֱ�����ͬʱʱ��С�ڰ���
					Keys[i].Step = 4;
					Keys[i].Time_Count_Flag = 0;
					Keys[i].Key_Double_Flag = 1;
				}
				else if(Keys[i].Key_State ==1&&Keys[i].Press_Time_Count==30)
				{
					Keys[i].Step = 4;
					Keys[i].Time_Count_Flag = 0;
					Keys[i].Key_Single_Flag = 1;
				}
			}break;
			case 4:
			{
				if(Keys[i].Key_State ==1)
				{
					Keys[i].Step = 0;
				}
			}break;
		}
	}
}


/**
  * @brief  TIM4�жϺ�����1ms����һ��
  * @param  ��
  * @retval None
  */
void TIM4_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
	{

		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
