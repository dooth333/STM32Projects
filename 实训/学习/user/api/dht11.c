#include "dht11.h"                  // Device header
#include "Delay.h" 

typedef_DATA dht11_data;

void Change_DHT11_Mode(u8 mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_DHT11;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	if(mode == DHT11_Mode_OUT)
	{
			GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	if(mode == DHT11_Mode_IN)
	{
			GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(GPIOA,&GPIO_InitStructer);

}


u8 DHT11_ReadData(void)
{
	u8 data[5] = {0};
	u8 i = 0;
	Change_DHT11_Mode(DHT11_Mode_OUT);//���ģʽ
	DHT11_H;
	//��ʼ�ź�
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
	//����ģʽ����Ӧ�ź�
	Change_DHT11_Mode(DHT11_Mode_IN);//����ģʽ
	//�ȴ���Ӧ
	while(DHT11_ReadPin == 1);
	while(DHT11_ReadPin == 0);
	//��������
	for(i = 0; i<40; i++)
	{
		while(DHT11_ReadPin == 1);
		while(DHT11_ReadPin == 0);
		Delay_us(30);
		//�ж�������0��1
		if(DHT11_ReadPin == 1)//����Ϊ1
		{
			data[i/8] |= (1<<(7-i%8));
		}
		if(DHT11_ReadPin == 0)//����Ϊ0
		{
			data[i/8] &= ~(1<<(7-i%8));
		}
	}
	//У��
	if(data[4] == data[0]+data[1]+data[2]+data[3])
	{
		dht11_data.temp = data[2];
		dht11_data.huim = data[0];
		return 1;
	}
	else
	{
		return 0;
	}
}

