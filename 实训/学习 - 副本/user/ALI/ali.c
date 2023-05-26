#include "ali.h"
#include "hmac/utils_hmac.h"
#include "mqttpacket.h"
#include "string.h"
#include "usart2.h"
#include "delay.h"

_AliIOT_Connect Ali_Buf ;
_AliData Ali_data;

//阿里云数据初始化
void AliIOT_DataConfig(void)
{
	char Temp_buf[128] = "\0";
	memset(&Ali_Buf, 0, sizeof(_AliIOT_Connect));
	//获取ClientID
	sprintf(Ali_Buf.ClientID, "%s|securemode=3,signmethod=hmacsha1|", Ali_DeviceName);
	Ali_Buf.ClientID_len = strlen(Ali_Buf.ClientID);
	//获取UserName
	sprintf(Ali_Buf.UserName, "%s&%s", Ali_DeviceName, Ali_ProductKey);
	Ali_Buf.UserName_len = strlen(Ali_Buf.UserName);
	//获取PassWord
	sprintf(Temp_buf, "clientId%sdeviceName%sproductKey%s", Ali_DeviceName, Ali_DeviceName, Ali_ProductKey); 
	utils_hmac_sha1(Temp_buf, strlen(Temp_buf), Ali_Buf.PassWord, Ali_DeviceSecret, strlen(Ali_DeviceSecret));
	Ali_Buf.PassWord_len = strlen(Ali_Buf.PassWord); 
	//获取服务器IP地址、端口号
	sprintf(Ali_Buf.ServerIP, "%s.iot-as-mqtt.cn-shanghai.aliyuncs.com", Ali_ProductKey);                  //构建服务器域名
	Ali_Buf.ServerPort = 1883;
	
	//Topic列表
	sprintf(Ali_Buf.topic_post, "/sys/%s/%s/thing/event/property/post", Ali_ProductKey, Ali_DeviceName);                 
	sprintf(Ali_Buf.topic_post_reply, "/sys/%s/%s/thing/event/property/post_reply", Ali_ProductKey, Ali_DeviceName);  
	sprintf(Ali_Buf.topic_set, "/sys/%s/%s/thing/service/property/set", Ali_ProductKey, Ali_DeviceName);  
	
}


//建立MQTT链接
uint8_t MyMQTT_Connect(char *ClientID, char *UserName, char *PassWord)
{
   Clean_data();
	//1.创建MQTT CONNECT 结构体
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	//2.结构体赋值
	data.cleansession = 1;//清除会话
	data.clientID.cstring = ClientID;//初始化设备ID
	data.keepAliveInterval = 60;//保持建立时长60s
	data.MQTTVersion = 4;//使用MQTT 3.1.1
	
	data.username.cstring = UserName;//用户名
	data.password.cstring = PassWord;//用户密码
	//3.调用MQTTSerialize_connect把结构体中的数据构成二进制流
	Ali_data.tx_count = MQTTSerialize_connect(Ali_data.tx_buff, MAX,&data);
	if(Ali_data.tx_count == 0)
		return 1;
	Usart_SendString(Ali_data.tx_buff,Ali_data.tx_count);
}

//断开链接
uint8_t MyMQTT_DisConnect(void)
{
   Clean_data();
	//1.把DISCONNECT报文结构体，变为二进制数据存入发送缓冲区中
	Ali_data.tx_count = MQTTSerialize_disconnect(Ali_data.tx_buff, MAX);
	if(Ali_data.tx_count == 0)
		return 1;
	//2.调用底层网络发送数据
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}

//MQTT发布数据
uint8_t MyMQTT_Publish(char *topic, char *payload)
{
	uint32_t payload_len = 0;
	unsigned char dup = 0;
	int qos = 0;
	unsigned char retained = 0;
	unsigned short msgid = 0;
	
	Clean_data();
	
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = topic;//保存主题
	payload_len = strlen(payload);//有效荷载的长度
	//2.构成Publish的二进制数据流
	Ali_data.tx_count = MQTTSerialize_publish(Ali_data.tx_buff,MAX,dup, qos, retained, msgid,\
												topicString,(uint8_t *)payload,payload_len);
	if(Ali_data.tx_count <= 0)
		return 1;
	//3.发送出去
	Usart_SendString(Ali_data.tx_buff,Ali_data.tx_count);
	return 0;
}


//MQTT订阅主题
uint8_t MyMQTT_Subscribe(char *topic)
{
	#define TOPIC_COUNT 1
	unsigned char dup = 0;
	unsigned short msgid = 10;
	int count = TOPIC_COUNT;
	int req_qoss[TOPIC_COUNT] = {2};
	
  Clean_data();
	
	MQTTString topicStrings[TOPIC_COUNT] = { MQTTString_initializer };
	topicStrings[0].cstring = topic;
	Ali_data.tx_count = MQTTSerialize_subscribe(Ali_data.tx_buff, MAX, dup, msgid, count, topicStrings, req_qoss);
	
	if(Ali_data.tx_count <= 0)
		return 1;
	//3.发送出去
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}


//MQTT取消订阅主题
uint8_t MyMQTT_UnSubscribe(char *topic)
{
	unsigned char dup = 0;
	unsigned short msgid = 0;

   Clean_data();
	
	MQTTString topicStrings = MQTTString_initializer ;
	
	topicStrings.cstring = topic;
	Ali_data.tx_count = MQTTSerialize_unsubscribe(Ali_data.tx_buff, MAX, dup, msgid, 1, &topicStrings);
	
	if(Ali_data.tx_count <= 0)
		return 1;
	//3.发送出去
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}

//清除数据
void Clean_data(void)
{
	memset(Ali_data.tx_buff,0,sizeof(Ali_data.tx_buff));
	Ali_data.tx_count=0;
}

