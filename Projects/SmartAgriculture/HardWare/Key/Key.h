#ifndef __Key_H
#define __Key_H

void Key_Init(void);
void Key_GetVlaues();
void Key_Execute();
struct Keys_Struct
{
	uint8_t Step;
	uint8_t Key_State;
	uint8_t Key_Single_Flag;//������־λ
	uint8_t Key_Long_Flag;//������־λ
	uint8_t Key_Double_Flag;//������־λ
	uint8_t Time_Count_Flag;//��ʱ��־λ
	uint8_t Press_Time_Count;//����ʱ�����
};

extern struct Keys_Struct Keys[4];
#endif

