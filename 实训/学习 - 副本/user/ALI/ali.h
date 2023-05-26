#ifndef __ALI_H
#define __ALI_H

#include "stm32f10x.h"
#define MAX  2048
//三元组
//替换为自己的三元组
#define Ali_ProductKey 		"h6t7nqVu7s4"
#define Ali_DeviceName 		"znwl_01"
#define Ali_DeviceSecret 	"c01db67a213fbb70896c9019918ae91f"

#define ALIBUF_SIZE 256

typedef struct{
	char ClientID[ALIBUF_SIZE];
	uint16_t ClientID_len;
	char UserName[ALIBUF_SIZE];
	uint16_t UserName_len;
	char PassWord[ALIBUF_SIZE];
	uint16_t PassWord_len;
	char ServerIP[ALIBUF_SIZE];
	uint16_t ServerPort;
	
	char topic_post[ALIBUF_SIZE];//发布Topic
	char topic_post_reply[ALIBUF_SIZE];//订阅回传响应
	char topic_set[ALIBUF_SIZE];//订阅设置信息
}_AliIOT_Connect;
extern _AliIOT_Connect Ali_Buf;

/* 阿里云通信数据封装 */
typedef struct
{
	uint16_t Tem;
	uint16_t Hum;
	uint16_t Light;
	uint8_t  LED_State;
	uint16_t 	tx_count;
	unsigned char 	tx_buff[MAX];
}_AliData;
extern _AliData Ali_data;

void AliIOT_DataConfig(void);
uint8_t MyMQTT_Connect(char *ClientID, char *UserName, char *PassWord);
uint8_t MyMQTT_Publish(char *topic, char *payload);
uint8_t MyMQTT_Subscribe(char *topic);
uint8_t MyMQTT_UnSubscribe(char *topic);
uint8_t MyMQTT_DisConnect(void);
void Clean_data(void);
#endif
