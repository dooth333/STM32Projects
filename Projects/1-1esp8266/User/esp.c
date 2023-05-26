#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"
#include "String.h"
#include "Oled.h"

int Temperature;
int Shidu;
uint8_t Lock;
char LED;
uint8_t Switch2;
const char* WIFI ="OneThree";
const char* WIFIASSWORD="123456789";
const char* ClintID="h6t7hKWr9qO.esp826602|securemode=2\\,signmethod=hmacsha256\\,timestamp=1664873939432|";
const char* username="esp826602&h6t7hKWr9qO";
const char* passwd="b5f12175e7532d2b86a88d72e3ddd10139129d20852237aea0ddc5ac388fc5d8";
const char* Url="iot-06z00fw34djtzfc.mqtt.iothub.aliyuncs.com";
const char* pubtopic="/h6t7hKWr9qO/esp826602/user/test";
const char* subtopic="/h6t7hKWr9qO/esp826602/user/test";
const char* func1="temperature";
const char* func2="humidity";
const char* func3="powerstate_1";
const char* func4="powerstate_2";
const char* func5="LED";

char esp_Init(void)
{
	
	memset(RECS,0,sizeof(RECS));//把接收数据的数组进行清0
	printf("AT+RST\r\n");  //重启
	Delay_ms(2000);
	
	memset(RECS,0,sizeof(RECS));
	printf("ATE0\r\n");    //关闭回显
	Delay_ms(10);
	if(strcmp(RECS,"OK"))
		return 1;
	
	printf("AT+CWMODE=1\r\n"); //Station模式
	Delay_ms(1000);
	if(strcmp(RECS,"OK"))
		return 2;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	Delay_ms(2000);
	if(strcmp(RECS,"OK"))
		return 3;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	Delay_ms(10);
	if(strcmp(RECS,"OK"))
		return 4;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	Delay_ms(1000);
	if(strcmp(RECS,"OK"))
		return 5;
	
	printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	Delay_ms(500);
	if(strcmp(RECS,"OK"))
		return 5;
	memset(RECS,0,sizeof(RECS));
	return 0;
}


//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
char Esp_PUB(void)
{
	memset(RECS,0,sizeof(RECS));
//	printf("AT+MQTTPUB=0,\"%s\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d}}\",0,0\r\n",pubtopic,func1,Temperature,func2,Shidu,func3,Lock,func4,Switch2);
	//while(RECS[0]);//等待ESP返回数据
	printf("AT+MQTTPUB=0,\"%s\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d}}\",0,0\r\n",pubtopic,func1,Temperature,func2,Shidu,func3,Lock,func4,Switch2);
	Delay_ms(200);//延时等待数据接收完成
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}

void CommandAnalyse(void)
{
	if(strncmp(RECS,"+MQTTSUBRECV:",13)==0)
	{
		
		uint8_t i=0;
		while(RECS[i++] != '\0')             
		{
			if(strncmp((RECS+i),func5,3)==0)
			{
				while(RECS[i++] != ':');       
				LED=RECS[i];
			}
		}
		
//		uint8_t i=0;
//		while(RECS[i++] != '\0')             
//		{
//			OLED_ShowString(2,1,RECS);
//			if(strncmp((RECS+i),func3,12)==0)
//			{
//				while(RECS[i++] != ':');       
//				Lock=RECS[i];
//			}
//			if(strncmp((RECS+i),func4,12)==0)
//			{
//				while(RECS[i++] != ':');
//				Switch2=RECS[i];
//			}
//		}
	}
}
