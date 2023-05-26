#include "stm32f10x.h"
#include "u8g2.h"
#include "OLED.h"
#include "Delay.h"


u8g2_t u8g2;
short x = 0,x_trg = 64; //x当前位置数值,x_trg 目标坐标值
short y = 10,y_trg = 10;
int state = 0;
char ui_select = 0;//选中第几个列表
short frame_len,frame_len_trg;//框框的宽度
short frame_y,frame_y_trg;//框框的y

struct SENTING_LIST list[4] = 
{
	{"a",1},
	{"bb",2},
	{"ccc",3},
	{"dddd",4},
};

int list_len = sizeof(list) / sizeof(struct SENTING_LIST);




//设置延时和引脚高低电平操作函数
uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_DELAY_MILLI://Function which implements a delay, arg_int contains the amount of ms
		Delay_ms(arg_int);
		break;
		
		case U8X8_MSG_DELAY_10MICRO: //Function which delays 10us
		Delay_us(10);
		break;
		
		case U8X8_MSG_DELAY_100NANO://Function which delays 100ns
		__NOP();
		break;
		
		//函数来定义时钟线的逻辑电平
		
		case U8X8_MSG_GPIO_I2C_CLOCK:
			if (arg_int) OLED_W_SCL(1);
			else OLED_W_SCL(0);
		break;
		
		case U8X8_MSG_GPIO_I2C_DATA:
			if (arg_int) OLED_W_SDA(1);
			else OLED_W_SDA(0);
		break;
		
		default:
			return 0; //A message was received which is not implemented, return 0 to indicate an error
	}

	return 1; // command processed successfully.
}


//总初始化
void u8g2Init(void)
{
   //u8g2初始化
	//U8G2_R0表示屏幕方向
	OLED_I2C_Init();
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8g2_gpio_and_delay_stm32);
	u8g2_InitDisplay(&u8g2); // 发送初始化序列到显示器，在此之后显示器处于休眠模式;
   u8g2_SetPowerSave(&u8g2, 0); // 唤醒显示wake up display
	Delay_ms(1000);
	u8g2_ClearBuffer(&u8g2);//清除缓存
	u8g2_SetFont(&u8g2,u8g2_font_wqy14_t_chinese1);
}


/*引脚初始化*/
void OLED_I2C_Init(void)
{
  RCC_APB2PeriphClockCmd(OLED_SDA_Clock, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_SCL_Pin;
 	GPIO_Init(OLED_SCL_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_SDA_Pin;
 	GPIO_Init(OLED_SDA_GPIO, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}




