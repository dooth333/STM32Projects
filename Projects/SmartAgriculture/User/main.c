//单片机头文件
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//硬件驱动
#include "OLED.h"
#include "AD.h"
#include "PWM.h"
#include "Timer.h"
#include "LED.h"
#include "Servo.h"
#include "key.h"
#include "usart.h"
#include "DHT11.h"
#include "buzzer.h"
#include "relay.h"
#include "AutoControl.h"
#include "SGP30.h"
//网络协议层
#include "onenet.h"

//网络设备
#include "esp8266.h"

//C库
#include <string.h>
#include <stdio.h> 

//与对应库里面保持一致
#define GPIO_BUZZER GPIO_Pin_12


char str[20];
uint8_t DHT_Buffer[5];
u8 OLED_Flag = 0;

uint16_t flag = 0;
u8 keyVlue1 = 0; 
u8 keyVlue2 = 0; 
uint16_t a = 0;
uint16_t humidityH,humidityL,temperatureH,temperatureL,Light,LED1_Status,LED2_Status,Buzz_Status,soilHumidity,Servo,Fan,WaterPump;

int main(void)
{
	
	const char *devSubTopics[] = {"/mysmarthome/sub"};
	const char *devPubTopics[] = {"/mysmarthome/pub"};
	
	char PUB_BUF[256];//上传数据的拼接字符串
	
	unsigned short timeCount = 0;	//发送间隔变量
	
	unsigned char *dataPtr = NULL;
	
	//初始化
	AD_Init();
	SGP30_Init();
	OLED_Init();
	LED_Init();
	Buzzer_Init();
	Timer_Init();
	Servo_Init();
	Buzzer_Init();
	relay_Init();
	Control_Init();
	Key_Init();
	Usart1_Init(115200);//debug串口
	Usart2_Init(115200);//stm32 - esp8266通讯串口
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	sprintf(str,"MQTT-Connecting");
	OLED_ShowString(1,1,str);
	ESP8266_Init();					//初始化ESP8266
	while(OneNet_DevLink())			//接入OneNET
	Delay_ms(500);
	
	OneNet_Subscribe(devSubTopics, 1);
	sprintf(str,"MQTT-Successful");
	OLED_ShowString(1,1,str);
	Delay_ms(1000);
	OLED_Clear();
	while (1)
	{
		/**
		sprintf(str,"Light:  %d LX",AD_Value[0]);
		OLED_ShowString(1,1,str);
		sprintf(str,"Temp:   %d.%d C",DHT_Buffer[2],DHT_Buffer[3]);
		OLED_ShowString(2,1,str);
		sprintf(str,"SoilHum:%d",AD_Value[1]);
		OLED_ShowString(3,1,str);
		OLED_ShowNum(4,1,lightControl.ENV_free,5);
		OLED_ShowNum(4,6,tempControl.ENV_free,5);
		OLED_ShowNum(4,11,soilHumControl.ENV_free,5);
		OLED_ShowNum(4,16,AutoControl_mode,1);
		**/
		if(timeDht11[0] > timeDht11[1])
		{
			//光照强度
			Light = AD_Value[0];
			//土壤湿度
			soilHumidity = AD_Value[1];
			//温湿度
			if(DHT_Get_Temp_Humi_Data(DHT_Buffer))
			{
				humidityH = DHT_Buffer[0];
				humidityL = DHT_Buffer[1];
				temperatureH = DHT_Buffer[2];
				temperatureL = DHT_Buffer[3];
			}
			
			//空气质量
			SGP30_getValue();

			timeDht11[0] = 0;
		}
		soilHumControl.ENV_value = soilHumidity;
		tempControl.ENV_value = temperatureH;
		lightControl.ENV_value = Light;
		//OLED切换
		if(timedSuB8266[0] > timedSuB8266[1])
		{
			OLED_Clear();
			OLED_Flag = !OLED_Flag;
			timedSuB8266[0] = 0;
		}
		
		
		if(!OLED_Flag)
		{
			sprintf(str,"Temp:   %d.%d C",DHT_Buffer[2],DHT_Buffer[3]);
			OLED_ShowString(1,1,str);
			sprintf(str,"hum:    %d.%d ",DHT_Buffer[0],DHT_Buffer[1]);
			OLED_ShowString(2,1,str);
			sprintf(str,"Light:  %d LX",AD_Value[0]);
			OLED_ShowString(3,1,str);
			sprintf(str,"SoilHum:%d",AD_Value[1]);
			OLED_ShowString(4,1,str);
		}
		else
		{
			//空气质量
			sprintf(str,"TVOC:%d",TVOC);
			OLED_ShowString(3,1,str);
			sprintf(str,"Co2:%d Ppm",Co2);
			OLED_ShowString(4,1,str);
		}
		
		if(timed8266[0] > timed8266[1])
		{
			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
			
			LED1_Status = !GPIO_ReadInputDataBit(GPIOA,GPIO_LED1);
			LED2_Status = !GPIO_ReadInputDataBit(GPIOA,GPIO_LED2);
			Buzz_Status = !GPIO_ReadInputDataBit(GPIOA,GPIO_BUZZER);
			
			Fan = !GPIO_ReadInputDataBit(GPIOC,GPIO_relay_1);
			WaterPump = !GPIO_ReadInputDataBit(GPIOC,GPIO_relay_2);
			
			sprintf(PUB_BUF,"{\"Hum\":%d.%d,\"Temp\":%d.%d,\"Light\":%d,\"LED1\":%d,\"LED2\":%d,\"BUZZ\":%d,\"SoilHum\":%d,\"Servo\":%d,\"Fan\":%d,\"WaterPump\":%d,\"Co2\":%d,\"TVOC\":%d}"
			,humidityH,humidityL,temperatureH,temperatureL,Light,LED1_Status,LED2_Status,Buzz_Status,soilHumidity,Servo_flag,Fan,WaterPump,Co2,TVOC);
			OneNet_Publish(*devPubTopics, PUB_BUF);
			
			timed8266[0] = 0;
			ESP8266_Clear();
		}
	
		dataPtr = (unsigned char *)ESP8266_GetIPD(3);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}
		
	}
} 










