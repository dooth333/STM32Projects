#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <string.h>

//硬件驱动
#include "Key.h"

#include "Timer.h"
#include "u8g2.h"
#include "OLED.h"
#include "LED.h"

struct Keys_Struct Keys[4];
char text[30];


/**
  * @brief  按键初始化，按键一端接单片机引脚，一端接GND
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
  * @brief  根据按键按下情况实行操作，放在主函数While循环中即可
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
			//根据单击键值进行操作
			switch(j+1)
			{
				//按键1
				case 1:
				{
					
					if(ui_select < list_len - 1)
					{
						ui_select ++;
					}
					LED1_Turn();
					
				}break;
				//按键2
				case 2:
				{	
					if(ui_select > 0)
					{
						ui_select --;
					}
					
				}break;
				//按键3
				case 3:
				{
					
					
				}break;
				//按键4
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
			//根据双击键值进行操作
			switch(j+1)
			{
				//按键1
				case 1:
				{
					
				}break;
				//按键2
				case 2:
				{
					
				}break;
				//按键3
				case 3:
				{
				
				}break;
				//按键4
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
			//根据长按键值进行操作
			switch(j+1)
			{
				//按键1
				case 1:
				{
					
				}break;
				//按键2
				case 2:
				{
					
				}break;
				//按键3
				case 3:
				{
				
				}break;
				//按键4
				case 4:
				{
				
				}break;
			}
		}
	}
}

/**
  * @brief  按键操作，放在1ms的中断中
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
	{//循环4个按键判断
		if(Keys[i].Time_Count_Flag == 1)
		{//如果开始计时标志位置1，那就开始计时
			Keys[i].Press_Time_Count++;
		}
		else
		{
			Keys[i].Press_Time_Count=0;
		}
		switch(Keys[i].Step)
		{//步骤
			case 0:
			{
				if(Keys[i].Key_State ==0)
				{//当有按键按下时，进入步骤1
					Keys[i].Step = 1;
					Keys[i].Time_Count_Flag = 1;
				}
			}break;
			case 1:
			{
				if(Keys[i].Press_Time_Count>2&&Keys[i].Key_State ==0)
				{//延时20ms判断时间到了之后并且按键未松开
//					Keys[i].Time_Count_Flag = 0;先不清零，继续计时
					Keys[i].Step = 2;
//					Keys[i].Key_Single_Flag = 1;
				}
			}break;
			case 2:
			{
				if(Keys[i].Key_State ==1)
				{//松开按键
					
					//调试用:
					//sprintf(text,"Press_Time_Count%d\r\n",Keys[i].Press_Time_Count);
					//UsartPrintf(USART_DEBUG, text);
					
					if(Keys[i].Press_Time_Count<50)
					{//如果松开时时间在0.5s之前，再判断是单击还是双击
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
				{//按键又被按下同时时间小于半秒
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
  * @brief  TIM4中断函数，1ms进入一次
  * @param  无
  * @retval None
  */
void TIM4_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
	{

		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
