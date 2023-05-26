#include "main.h"
#include "LED.h"
int main()
{
	JTAG_SWD_Config();//关闭JTAG功能，打开SWD功能
	Delay_Config();   //延时初始化
	LEDInit();
	while(1)
	{
		
	}
}


