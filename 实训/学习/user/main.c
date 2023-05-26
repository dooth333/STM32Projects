#include "main.h"
#include "delay.h"
#include "LED.h"
#include "LCD.h"
#include "usart1.h"
#include "usart2.h"
#include "DHT11.h"
#include "ADC1.h"
#include "ALI.h"
#include "key.h"

char Send_JsonBuf[256]={0};
u8 flag1 = 0;
u8 keyVlue = 0;
void Ali_updata(void);
extern const unsigned char gImage_im_logo1[1682];
extern const unsigned char gImage_humi[1508];
extern const unsigned char gImage_light[1566];
extern const unsigned char gImage_im_temp[1682];
extern const unsigned char gImage_class[1682];
extern const unsigned char gImage_name[1682];
int main(void)
{
	char buff[30];
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	JTAG_SWD_Config();
	SysTick_Init(40000);
	LED_init();
	LCD_Init();
	ADC1_Init();
	usart1_init();
	usart2_init();
	printf("��ʼ\r\n");
	Show_Str(65,0,BLACK,WHITE,(u8*)"֣���Ṥҵ��ѧ",16,0);
	Paint_Bmp(20,40,29,29,gImage_im_logo1);
	Show_Str(80,40,BLACK,WHITE,(u8*)"��������2004",16,0);
	Paint_Bmp(20,80,29,26,gImage_name);
	Show_Str(80,80,BLACK,WHITE,(u8*)"���ĳ� 54007130418",16,0);
	Paint_Bmp(20,120,29,26,gImage_name);
	Show_Str(80,120,BLACK,WHITE,(u8*)"Т  �� 54007130419",16,0);
	Paint_Bmp(20,160,29,26,gImage_name);
	Show_Str(80,160,BLACK,WHITE,(u8*)"������ 54007130421",16,0);
	Paint_Bmp(20,200,29,26,gImage_name);
	Show_Str(80,200,BLACK,WHITE,(u8*)"��κ� 54007130422",16,0);
	Paint_Bmp(20,240,29,26,gImage_name);
	Show_Str(80,240,BLACK,WHITE,(u8*)"����˶ 54007130423",16,0);
	Paint_Bmp(20,280,29,26,gImage_name);
	Show_Str(80,280,BLACK,WHITE,(u8*)"�ŵ��e 54007130424",16,0);
	AliIOT_DataConfig();//��ʼ�����������Ӳ���
	printf("start connect\r\n");//����һ����־
	Delay_ms(500);//��ʱ500ms
	//ʹ��MQTTЭ�����Ӱ����Ʒ�����
	MyMQTT_Connect(Ali_Buf.ClientID,Ali_Buf.UserName,Ali_Buf.PassWord);
	while (1)
  {
		if(timedled[0] > timedled[1])
		{
			LED1_Toggle();
			timedled[0] = 0;
		}
		if(timedkey[0] > timedkey[1])
		{
			keyVlue = Key_GetValue();
			timedkey[0] = 0;
		}
		if(timedali[0] > timedali[1])
		{
			Ali_updata();//���ͻ������ݵ�������
			timedali[0] = 0;
		}
		if(timedht11[0] > timedht11[1])
		{
			flag1++;
			DHT11_ReadData();
			ADC1_GetValue();
			if(flag1 >= 2)
			{
				flag1 = 2;
				sprintf(buff,"temp:%d",dht11_data.temp);
				Show_Str(150,200,BLACK,WHITE,(u8*)buff,16,0);
				sprintf(buff,"huim:%d",dht11_data.huim);
				Show_Str(150,240,BLACK,WHITE,(u8*)buff,16,0);
				sprintf(buff,"light:%d",adc_data.light);
				Show_Str(150,280,BLACK,WHITE,(u8*)buff,16,0);
			}
			timedht11[0] = 0;
		}
		if(keyVlue != 0)
		{
			printf("keyVlue:%d\r\n",keyVlue);
				LED2_Toggle();
		}
		if(flag1 == 1)
		{
			LCD_Clear(WHITE);
			Paint_Bmp(20,30,29,29,gImage_im_logo1);
			Show_Str(60,30,BLACK,WHITE,(u8*)"���ܰ����ƼҾ�ϵͳ",16,0);
			Show_Str(50,100,BLACK,WHITE,(u8*)"Welcome!",16,0);
			Show_Str(80,140,BLACK,WHITE,(u8*)"���������İ��1��",16,0);
		  Paint_Bmp(20,200,29,29,gImage_im_temp);
			Paint_Bmp(20,240,29,26,gImage_humi);
			Paint_Bmp(20,280,30,28,gImage_light);
		}
  }
}
void JTAG_SWD_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//��ȫ����SWD��JTAG 
}
void Ali_updata(void)
{
      Ali_data.Hum=dht11_data.huim;
			Ali_data.Tem=dht11_data.temp;
			Ali_data.Light= adc_data.light;
			sprintf((char *)Send_JsonBuf,
					"{\"method\":\"thing.service.property.post\",\
						\"id\":\"1111\",\
						\"params\":{\
						\"Humidity\":%d,\
						\"temperature\":%d,\
						\"LightLux\":%d,\
						}\
						,\"version\":\"1.0\"}",
						Ali_data.Hum, Ali_data.Tem,Ali_data.Light);
			//ʹ��MQTTЭ�鷢��ָ��������
			MyMQTT_Publish(Ali_Buf.topic_post,Send_JsonBuf);
}
