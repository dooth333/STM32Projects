#include "main.h"
#include "LED.h"
int main()
{
	JTAG_SWD_Config();//�ر�JTAG���ܣ���SWD����
	Delay_Config();   //��ʱ��ʼ��
	LEDInit();
	while(1)
	{
		
	}
}


