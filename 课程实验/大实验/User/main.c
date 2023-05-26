#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "PWM.h"
#include "Timer.h"
#include "LED.h"
#include "Servo.h"
#include "Serial.h"
#include "esp.h"
#include "Key.h"
                                                                                                                                                                                                                                                                                   
uint16_t flag = 0;
u8 keyVlue = 0; 
int main(void)
{
	//初始化
	OLED_Init();
	Servo_Init();
	Serial_Init();
	Timer_Init();
	LED_Init();
	AD_Init();
	Servo_close();
	LED2_OFF();
	flag = esp_Init();//eap8266连接阿里云初始化，根据返回值判断连接状态
	while (1)
	{
		//显示一些标志位，用于调试
		OLED_ShowNum(1,1,flag,1);
		OLED_ShowNum(1,3,LED1_flag,1);
		OLED_ShowNum(1,5,Servo_flag,1);
		OLED_ShowChar(1,11,LED1);
		OLED_ShowChar(1,13,LED2);
	
		//判断红外和光敏控制LED2灯,光敏大于2000和有认时开灯，否者关灯
		if(InfraredSwitch == 1 && AD_Value[1] >= 2000)
		{
			LED2_ON();
		}else
		{
			LED2_OFF();
		}
		//按键值读取
		if(timedKey[0] > timedKey[1])
		{
			keyVlue = Key_GetNum();
			timedKey[0] = 0;
		}
		//ADC数据转换，然后通过OLED转换
		if(timedAD[0] > timedAD[1])
		{
			OLED_ShowString(2,1,"Temp:");
			OLED_ShowString(3,1,"Light:");
			OLED_ShowString(4,1,"Inf:");
			OLED_ShowNum(2, 8, AD_Value[0], 6);
			OLED_ShowNum(3, 8, AD_Value[1], 6);
			OLED_ShowNum(4, 8, AD_Value[2], 6);
			timedAD[0] = 0;
		}
		//esp8266往阿里云发送数据
		if(timedEsp[0] > timedEsp[1])
		{
			InfraredSwitchConvert();
			Esp_PUB();
			Esp_PUB1();
			timedEsp[0] = 0;
		}
		
		//根据不同的按键值，执行
		if(keyVlue != 0)
		{
			if(keyVlue == 1)//按键1被按下LED1灯状态转换
			{
				LED1_Turn();	
			}
			
			if(keyVlue == 2)//按键2用于开门和关门状态的转换
			{
				if(Servo_flag == 0)
				{
					Servo_open();
				}else if(Servo_flag == 1)
				{
					Servo_close();
				}
			}
			OLED_ShowNum(1,9,keyVlue,1); //显示按键值，用于调试
		}

	}
} 






