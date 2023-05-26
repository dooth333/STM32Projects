#include "bsp_i2c_ee.h"

//IIC初始化
void I2C_EE_Config(void)
{
	I2C_InitTypeDef 	I2C_InitStructure;
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	//打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//打开外设IIC的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		
	//将IIC SCL的GPIO配置为开漏复用模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//配置IIC的工作参数
	
	//使能应答
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	//使用7位地址模式
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	//配置SCL时钟频率
	I2C_InitStructure.I2C_ClockSpeed=400000;
	//占空1/2,9/16
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
	//模式
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	//STM32 IIC 自身设备地址，只要是总线上唯一即可
	I2C_InitStructure.I2C_OwnAddress1=I2C_ADDR;

	//把配置写到寄存器中，完成IIC的初始化配置
	I2C_Init(EEPROM_I2C,&I2C_InitStructure);
	// 使能IIC
	I2C_Cmd(EEPROM_I2C,ENABLE);	
}

//向EEPROM写一个字节
void EEPROM_Byte_Write(uint8_t addr,uint8_t data)
{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	//检测事件EV5
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	//检测事件EV6
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	
	I2C_SendData( EEPROM_I2C,addr);
	//检测EV8
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR);
	
	I2C_SendData( EEPROM_I2C,data);
	
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
	//数据传输完成
	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);
}


//向EEPROM写入多个字节（页写入），每次写入不能超过8个字节

void EEPROM_Page_Write(uint8_t addr,uint8_t *data,uint8_t numByteToWrite)
{
	//产生起始信号
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT) == ERROR);
	
	//EV5事件被检测到，发送设备地址
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	
  while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) == ERROR);

	//EV6事件被检测到，发送要操作的存储单元地址
	I2C_SendData (EEPROM_I2C,addr);
	
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING ) == ERROR);

	
	while(numByteToWrite)
	{
		//EV8事件被检测到，发送要存储的数据
		I2C_SendData (EEPROM_I2C,*data);
		
		while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED ) == ERROR);
		
		data++;
		numByteToWrite--;
			
	}
	//数据传输完成
	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);	

}


//从EEPROM读取数据
void EEPROM_Read(uint8_t addr,uint8_t *data,uint8_t numByteToRead)
{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	
	//检测事件EV5
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);

	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	//检测事件EV6
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	
	I2C_SendData( EEPROM_I2C,addr);

	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR);

	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	
	//检测事件EV5
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	//更改
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Receiver);
	
	//检测EV6
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )==ERROR);
	
	while(numByteToRead)
	{
		if(numByteToRead==1)
		{
			//最后一个字节
			I2C_AcknowledgeConfig(EEPROM_I2C,DISABLE);
		}
		//检测EV7
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)==ERROR);
		
		
		*data = I2C_ReceiveData(EEPROM_I2C);
		data++;
		
		numByteToRead--;	
	}
	
	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);
	
	I2C_AcknowledgeConfig(EEPROM_I2C,ENABLE);
}

void EEPROM_WaitForWriteEnd(void)
{
	do
	{
		I2C_GenerateSTART(EEPROM_I2C,ENABLE);
		
		//检测EV5
		while(I2C_GetFlagStatus(EEPROM_I2C,I2C_FLAG_SB)==RESET);//不要忘记分号
			
		I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	}
	while(I2C_GetFlagStatus(EEPROM_I2C,I2C_FLAG_ADDR)==RESET);

	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);
}

