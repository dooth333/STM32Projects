#include "stm32f10x.h"                  // Device header
#include "bsp_i2c_ee.h" 
#include "bspUsart.h"

uint16_t array[]={1,2,3,4,5,6,7,8,9,10};
uint8_t writeData[8]={4,5,6,7,8,9,10,11};
uint8_t readData[10]={0};
void Delay(uint32_t count)
{
	while(count--);
}	

int main(void)
{
	uint8_t i=0;
	I2C_EE_Config();
	bspUsart_Init();
	printf("这是一个IIC通讯实验\n");

//	//写入一个字节
//	EEPROM_Byte_Write(11,55);
//	
//	//等待写入操作完成
//	EEPROM_WaitForWriteEnd();
//	
//	//写入一个字节
//	EEPROM_Byte_Write(12,52);
//	
//	//等待写入操作完成
//	EEPROM_WaitForWriteEnd();
//	
//	//addr%8 == 0 ,即为地址对齐
//	EEPROM_Page_Write(16,writeData,8);
//	
//	//等待写入操作完成
//	EEPROM_WaitForWriteEnd();
//	
//	//读取数据
//	EEPROM_Read(16,readData,8);
	
	for(i=0;i<8;i++)
	{	
		printf("%d ",writeData[i]);
	}
	printf("\nIIC 读取 EEPROM 实验\n");
	
  while(1)
	{		
	}	
	
}

