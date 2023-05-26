#include "stm32f10x.h"                  // Device header
#include "bsp_spi_flash.h" 
#include "bspUsart.h"
//读取的ID存储位置
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;

void Delay(__IO uint32_t nCount);

int main(void)
{ 	
	uint8_t cal_flag = 0;
	uint8_t k;
	
	/*存储小数和整数的数组，各7个*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};
	
//	LED_GPIO_Config();
//	LED_BLUE;//LED灯判断运行状态
	
	/* 配置串口1为：115200 8-N-1 */
//	USART_Config();
	bspUsart_Init();
  
	printf("\r\n这是一个FLASH 读写小数和长整数实验 \r\n");
	
	/* 16M串行flash W25Q128初始化 */
	SPI_FLASH_Init();
	
	/* 获取 Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	Delay( 200 );
	
	/* 获取 SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* 检验 SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
//		LED_GREEN;//LED灯判断运行状态
		
		printf("\r\n检测到SPI FLASH W25Q128 !\r\n");
		
		/*读取数据标志位*/
    SPI_FLASH_BufferRead(&cal_flag, SPI_FLASH_PageSize*0, 1);
    
		if( cal_flag == 0xCD )	/*若标志等于0xcd，表示之前已有写入数据*/
    {
			  printf("\r\n检测到数据标志\r\n");

				/*读取小数数据*/
        SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
				
				/*读取整数数据*/
        SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
	
			
				printf("\r\n从芯片读到数据：\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("小数 rx = %LF \r\n",double_buffer[k]);
					printf("整数 rx = %d \r\n",int_bufffer[k]);				
				}
    }    
    else
    {
      printf("\r\n没有检测到数据标志，FLASH没有存储数据，即将进行小数写入实验\r\n");
			cal_flag =0xCD;
			/*擦除扇区*/
      SPI_FLASH_SectorErase(0);
			
			/*写入标志到第0页*/
      SPI_FLASH_BufferWrite(&cal_flag, SPI_FLASH_PageSize*0, 1); 
      
			/*生成要写入的数据*/
      for( k=0; k<7; k++ )
			{
			   double_buffer[k] = k +0.1;
				 int_bufffer[k]=k*500+1 ;
			}

			/*写入小数数据到第一页*/
      SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
			/*写入整数数据到第二页*/
      SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
       			
			printf("向芯片写入数据：");
			/*打印到串口*/
      for( k=0; k<7; k++ )
			{
        printf("小数tx = %LF\r\n",double_buffer[k]);
				printf("整数tx = %d\r\n",int_bufffer[k]);
			}
			
			printf("\r\n请复位开发板，以读取数据进行检验\r\n");
    }
    		

	}// if (FlashID == sFLASH_ID)
	else
	{    
//		LED_RED;//LED灯判断运行状态
		printf("\r\n获取不到 W25Q64 ID!\n\r");
	}
	
	SPI_Flash_PowerDown();

	while(1);  
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

