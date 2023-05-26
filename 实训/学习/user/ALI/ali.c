#include "ali.h"
#include "hmac/utils_hmac.h"
#include "mqttpacket.h"
#include "string.h"
#include "usart2.h"
#include "delay.h"

_AliIOT_Connect Ali_Buf ;
_AliData Ali_data;

//���������ݳ�ʼ��
void AliIOT_DataConfig(void)
{
	char Temp_buf[128] = "\0";
	memset(&Ali_Buf, 0, sizeof(_AliIOT_Connect));
	//��ȡClientID
	sprintf(Ali_Buf.ClientID, "%s|securemode=3,signmethod=hmacsha1|", Ali_DeviceName);
	Ali_Buf.ClientID_len = strlen(Ali_Buf.ClientID);
	//��ȡUserName
	sprintf(Ali_Buf.UserName, "%s&%s", Ali_DeviceName, Ali_ProductKey);
	Ali_Buf.UserName_len = strlen(Ali_Buf.UserName);
	//��ȡPassWord
	sprintf(Temp_buf, "clientId%sdeviceName%sproductKey%s", Ali_DeviceName, Ali_DeviceName, Ali_ProductKey); 
	utils_hmac_sha1(Temp_buf, strlen(Temp_buf), Ali_Buf.PassWord, Ali_DeviceSecret, strlen(Ali_DeviceSecret));
	Ali_Buf.PassWord_len = strlen(Ali_Buf.PassWord); 
	//��ȡ������IP��ַ���˿ں�
	sprintf(Ali_Buf.ServerIP, "%s.iot-as-mqtt.cn-shanghai.aliyuncs.com", Ali_ProductKey);                  //��������������
	Ali_Buf.ServerPort = 1883;
	
	//Topic�б�
	sprintf(Ali_Buf.topic_post, "/sys/%s/%s/thing/event/property/post", Ali_ProductKey, Ali_DeviceName);                 
	sprintf(Ali_Buf.topic_post_reply, "/sys/%s/%s/thing/event/property/post_reply", Ali_ProductKey, Ali_DeviceName);  
	sprintf(Ali_Buf.topic_set, "/sys/%s/%s/thing/service/property/set", Ali_ProductKey, Ali_DeviceName);  
	
}


//����MQTT����
uint8_t MyMQTT_Connect(char *ClientID, char *UserName, char *PassWord)
{
   Clean_data();
	//1.����MQTT CONNECT �ṹ��
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	//2.�ṹ�帳ֵ
	data.cleansession = 1;//����Ự
	data.clientID.cstring = ClientID;//��ʼ���豸ID
	data.keepAliveInterval = 60;//���ֽ���ʱ��60s
	data.MQTTVersion = 4;//ʹ��MQTT 3.1.1
	
	data.username.cstring = UserName;//�û���
	data.password.cstring = PassWord;//�û�����
	//3.����MQTTSerialize_connect�ѽṹ���е����ݹ��ɶ�������
	Ali_data.tx_count = MQTTSerialize_connect(Ali_data.tx_buff, MAX,&data);
	if(Ali_data.tx_count == 0)
		return 1;
	Usart_SendString(Ali_data.tx_buff,Ali_data.tx_count);
}

//�Ͽ�����
uint8_t MyMQTT_DisConnect(void)
{
   Clean_data();
	//1.��DISCONNECT���Ľṹ�壬��Ϊ���������ݴ��뷢�ͻ�������
	Ali_data.tx_count = MQTTSerialize_disconnect(Ali_data.tx_buff, MAX);
	if(Ali_data.tx_count == 0)
		return 1;
	//2.���õײ����緢������
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}

//MQTT��������
uint8_t MyMQTT_Publish(char *topic, char *payload)
{
	uint32_t payload_len = 0;
	unsigned char dup = 0;
	int qos = 0;
	unsigned char retained = 0;
	unsigned short msgid = 0;
	
	Clean_data();
	
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = topic;//��������
	payload_len = strlen(payload);//��Ч���صĳ���
	//2.����Publish�Ķ�����������
	Ali_data.tx_count = MQTTSerialize_publish(Ali_data.tx_buff,MAX,dup, qos, retained, msgid,\
												topicString,(uint8_t *)payload,payload_len);
	if(Ali_data.tx_count <= 0)
		return 1;
	//3.���ͳ�ȥ
	Usart_SendString(Ali_data.tx_buff,Ali_data.tx_count);
	return 0;
}


//MQTT��������
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
	//3.���ͳ�ȥ
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}


//MQTTȡ����������
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
	//3.���ͳ�ȥ
	Usart_SendString(Ali_data.tx_buff, Ali_data.tx_count);
	return 0;
}

//�������
void Clean_data(void)
{
	memset(Ali_data.tx_buff,0,sizeof(Ali_data.tx_buff));
	Ali_data.tx_count=0;
}

