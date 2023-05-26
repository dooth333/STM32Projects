#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint16_t a = 666;
int main(void)
{
	OLED_Init();
	Serial_Init();
//	Serial_SendByte('A');
//	uint8_t MyArray[] = {0x42,0x43,0x44,0x45,0x46};
//	Serial_SendArray(MyArray,4);
//	Serial_SendString("\r\nHelloWorld!");
//	Serial_SendNumber(123456,6);
	
	printf("number=%d\r\n",8888);
	
	char String[100];
	sprintf(String,"number=%d\r\n",666);
	Serial_SendString(String);
	Serial_Printf("你好你好");
	while (1)
	{
		
	}
}




