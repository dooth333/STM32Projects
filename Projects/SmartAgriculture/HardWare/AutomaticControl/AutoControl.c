#include "stm32f10x.h"                  // Device header
#include "AutoControl.h"

//Ӳ������
#include "LED.h"
#include "Timer.h"
#include "buzzer.h"
#include "Servo.h"
#include "relay.h"

//0Ϊ�ر��Զ�ģʽ��1Ϊ�����Զ�ģʽ
uint8_t AutoControl_mode =1;


struct ENV_Struct tempControl;//�¶Ƚṹ��
struct ENV_Struct lightControl;//����ǿ�ȿ��ƽṹ��
struct ENV_Struct soilHumControl;//����ʪ�ȿ��ƽṹ��

void Control_Init(void)
{
	//�¶ȳ�ʼ��
	tempControl.ENV_free = 0;
	tempControl.ENV_MaxValue = 30;
	tempControl.ENV_MiniValue = 10;
	
	//ʪ�ȳ�ʼ��
	soilHumControl.ENV_free = 0;
	soilHumControl.ENV_MaxValue = 1900;
	soilHumControl.ENV_MiniValue = 1500;
	
	//����ǿ�ȳ�ʼ��
	lightControl.ENV_free = 0;
	lightControl.ENV_MaxValue = 2000;
	lightControl.ENV_MiniValue = 10;
	
}


void Control_Execute(void)
{
	//�ж��Ƿ����Զ�ģʽ
	if(AutoControl_mode == 1)
	{
		//����ǿ���ж�
		if(lightControl.ENV_free == 0)
		{
			if(lightControl.ENV_value >= lightControl.ENV_MaxValue)
			{                                                
				LED1_ON();
			}
			else
			{
				LED1_OFF();
			}
		}
		else
		{
			lightControl.ENV_free--;
		}
		
		//�¶��ж�
		if(tempControl.ENV_free == 0)
		{
			if(tempControl.ENV_value >= tempControl.ENV_MaxValue)
			{
				Buzzer_ON();
			}
			else
			{
				Buzzer_OFF();
			}
		}
		else
		{
			tempControl.ENV_free--;
		}
		
		//����ʪ��
		if(soilHumControl.ENV_free == 0)
		{
			if(soilHumControl.ENV_value >= soilHumControl.ENV_MaxValue)
			{
				LED2_ON();
			}
			else
			{
				LED2_OFF();
			}
		}
		else
		{
			soilHumControl.ENV_free--;
		}
		
		
		
	}
}