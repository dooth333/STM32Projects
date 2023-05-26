#include "stm32f10x.h"                  // Device header
#include "AutoControl.h"

//硬件驱动
#include "LED.h"
#include "Timer.h"
#include "buzzer.h"
#include "Servo.h"
#include "relay.h"

//0为关闭自动模式，1为开启自动模式
uint8_t AutoControl_mode =1;


struct ENV_Struct tempControl;//温度结构体
struct ENV_Struct lightControl;//光照强度控制结构体
struct ENV_Struct soilHumControl;//土壤湿度控制结构体

void Control_Init(void)
{
	//温度初始化
	tempControl.ENV_free = 0;
	tempControl.ENV_MaxValue = 30;
	tempControl.ENV_MiniValue = 10;
	
	//湿度初始化
	soilHumControl.ENV_free = 0;
	soilHumControl.ENV_MaxValue = 1900;
	soilHumControl.ENV_MiniValue = 1500;
	
	//光照强度初始化
	lightControl.ENV_free = 0;
	lightControl.ENV_MaxValue = 2000;
	lightControl.ENV_MiniValue = 10;
	
}


void Control_Execute(void)
{
	//判断是否开启自动模式
	if(AutoControl_mode == 1)
	{
		//光照强度判断
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
		
		//温度判断
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
		
		//土壤湿度
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