#include "stm32f10x.h"
#include "u8g2.h"
#include "OLED.h"
#include "Delay.h"
#include "Key.h"


u8g2_t u8g2;
//extern u8g2_t u8g2;
char text[30];
//main界面图片
const uint8_t LOGO[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x10,0x01,0x24,0x00,0x44,0x04,0x80,0x20,0x00,0x00,0x10,0xF2,0x3C,0x20,0xE0,0x00,
0x10,0x01,0x24,0x00,0xC4,0x04,0x80,0x20,0x00,0x00,0x10,0x11,0x24,0x30,0x10,0x01,
0x10,0x71,0x24,0x0F,0xC4,0xE2,0x99,0x3C,0x00,0x00,0x20,0x11,0x24,0x20,0x10,0x01,
0xF0,0x89,0xA4,0x10,0xA8,0x12,0x8A,0x22,0x00,0x00,0x20,0xF1,0x1C,0x20,0x10,0x01,
0x10,0xF9,0xA4,0x10,0x98,0x13,0x8A,0x22,0x00,0x00,0xA0,0x10,0x24,0x20,0x10,0x01,
0x10,0x09,0xA4,0x10,0x98,0x11,0x8A,0x22,0x00,0x00,0xA0,0x10,0x24,0x20,0x10,0x01,
0x10,0xF1,0x24,0x0F,0x10,0xE1,0x89,0x3C,0x00,0x00,0x40,0xF0,0x44,0x20,0xE2,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xE7,0xFF,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x0F,0xFE,0x99,0xFF,0xE4,0x1F,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xE7,0xFD,0xBD,0xFF,0xDE,0xDF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0xFE,
0xF7,0xFD,0x7D,0x7F,0xDF,0xDF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xDF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0x1F,0xF0,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0x1F,0xFE,0xFF,0x83,0xFF,0xE3,0xF1,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0xE3,0xF1,0xFF,0x7C,0xF8,0xF9,0xEF,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0xFD,0xEF,0x3F,0xFF,0xF3,0xFD,0xDF,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0x1E,0xDC,0xBF,0x03,0xF7,0xE3,0xE1,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0x7F,0xEF,0xB9,0xDF,0xFB,0xF0,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0x7F,0xE7,0xBB,0xDF,0xF3,0xFF,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xBF,0xF7,0x7B,0xDF,0x0F,0xFF,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xBF,0x0F,0x7C,0xBF,0xFF,0xFC,0xEF,0xFD,
0xF7,0xFD,0x7D,0x7F,0xDF,0xFF,0xF7,0xFD,0xBF,0xFF,0xBF,0x7F,0xFE,0xF3,0xEF,0xFD,
0xF7,0xFD,0xBE,0x7F,0xDF,0xFF,0xF7,0xFD,0xBF,0x07,0xC0,0xFF,0xE1,0xF7,0xEF,0xFD,
0xEF,0xFB,0xBE,0x7F,0xDF,0xFF,0xF7,0xFD,0xBF,0xEF,0xFF,0xFF,0x9F,0xEF,0xEF,0xFD,
0xEF,0x07,0xBF,0x7F,0xDF,0xFF,0xF7,0xFD,0x7F,0xEF,0xC7,0x3F,0x3E,0xEF,0xEF,0xFD,
0xDF,0xFF,0xDF,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0x1E,0xB8,0xDF,0xB9,0xF7,0xEF,0xE3,
0x9F,0xFF,0xEF,0x7F,0xDF,0xFF,0xF7,0xFD,0xFF,0xFC,0xBF,0x9F,0xC7,0xF7,0xDF,0xCF,
0x7F,0xFF,0xF3,0xFF,0xDE,0xFF,0xEF,0xFD,0xFF,0xFB,0xCF,0x3F,0xFF,0xF9,0x9F,0xEF,
0xFF,0x00,0xFC,0xFF,0xE1,0xFF,0x1F,0xFE,0xFF,0x07,0xF0,0xFF,0x00,0xFE,0x7F,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x40,0x00,0x02,0x10,0x00,0x00,
0x00,0x00,0x88,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x60,0x00,0x02,0x00,0x00,0x00,
0x00,0x00,0x88,0x9C,0x24,0xC7,0x1C,0x0F,0x68,0x22,0xA0,0xCC,0x23,0x91,0xC7,0x01,
0x00,0xFE,0x88,0xA2,0xAA,0x48,0xA2,0x08,0x98,0x14,0xB0,0x24,0x22,0x91,0x24,0x02,
0x00,0x00,0x78,0xA2,0xAB,0x4F,0xBE,0x08,0x88,0x14,0xF0,0x24,0x22,0x91,0x24,0x02,
0x00,0x00,0x08,0x22,0x9B,0x40,0x82,0x08,0x88,0x0C,0x08,0x25,0x22,0x91,0x24,0x02,
0x00,0x00,0x08,0x1C,0x11,0x4F,0x3C,0x0F,0x78,0x08,0x08,0xC5,0xE3,0x91,0xC4,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

uint8_t disappear_step=1;

float angle,angle_last;
//实时坐标
uint8_t chart_x;
bool frame_is_drawed=false;

//指向buf首地址的指针
uint8_t* buf_ptr;
uint16_t buf_len;


//选择界面变量
uint8_t x;
int16_t y,y_trg;//目标和当前
uint8_t line_y,line_y_trg;//线的位置
uint8_t box_width,box_width_trg;//框的宽度
int16_t box_y,box_y_trg;//框的当前值和目标值
int8_t ui_select;//当前选中那一栏

//pid界面变量
//int8_t pid_y,pid_y_trg;
uint8_t pid_line_y,pid_line_y_trg;//线的位置
uint8_t pid_box_width,pid_box_width_trg;//框的宽度
int16_t pid_box_y,pid_box_y_trg;//框的当前值和目标值
int8_t pid_select;//当前选中那一栏


//icon界面变量
int16_t icon_x,icon_x_trg;
int16_t app_y,app_y_trg;
int8_t icon_select;
uint8_t ui_index,ui_state;


enum//ui_index
{
  M_LOGO,//开始界面
  M_SELECT,//选择界面
  M_PID,//PID界面
  M_PID_EDIT,//pid编辑
  M_ICON,//icon界面
  M_CHART,//图表
  M_TEXT_EDIT,//文字编辑
  M_VIDEO,//视频显示
  M_ABOUT,//关于本机 
};

enum//ui_state
{
  S_NONE,
  S_DISAPPEAR,
  S_SWITCH,
  S_MENU_TO_MENU,
  S_MENU_TO_PIC,
  S_PIC_TO_MENU, 
};

//菜单结构体
typedef struct
{
  char * select;
}SELECT_LIST;

SELECT_LIST pid[] = 
{
  {"-Proportion"},
  {"-Integral"},
  {"-Derivative"},
  {"Return"},
};

uint8_t pid_num=sizeof(pid)/sizeof(SELECT_LIST);//PID选项数量

SELECT_LIST list[] = 
{
  {"MainUI"},
  {"+PID Editor"},
  {"-Icon Test"},
  {"-Chart Test"},
  {"-Text Edit"},
  {"-Play Video"},
  {"{ About }"},
};

uint8_t list_num = sizeof(list)/sizeof(SELECT_LIST);//选择界面数量
uint8_t single_line_length;//赋值在主函数中
uint8_t total_line_length;




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
	u8g2_SetFont(&u8g2,u8g2_font_wqy12_t_chinese1);
		//选择界面数量
	uint8_t single_line_length = 63 / list_num;
	uint8_t total_line_length = single_line_length*list_num+1;

	buf_ptr=u8g2_GetBufferPtr(&u8g2);//拿到buffer首地址
   buf_len=8*u8g2_GetBufferTileHeight(&u8g2)*u8g2_GetBufferTileWidth(&u8g2);
	x=4;
	y=y_trg=0;
	line_y=line_y_trg=1;
	pid_line_y=pid_line_y_trg=1;
	ui_select=pid_select=icon_select=0;
	icon_x=icon_x_trg=0;
	app_y=app_y_trg=0;
	box_width=box_width_trg=u8g2_GetStrWidth(&u8g2,list[ui_select].select)+x*2;//两边各多2
	pid_box_width=pid_box_width_trg=u8g2_GetStrWidth(&u8g2,pid[pid_select].select)+x*2;//两边各多2
	ui_index=M_LOGO;
	ui_state=S_NONE;
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

//移动函数
bool move(int16_t* a,int16_t* a_trg)
{
  if (*a < *a_trg)
  {
    *a+=SPEED;
    if (*a>*a_trg) *a=*a_trg;//加完超过
  }
  else if(*a>*a_trg)
  {
    *a-=SPEED;
    if (*a<*a_trg) *a=*a_trg;//减完不足
  }
  else
  {
    return true;//到达目标
  }
  return false;//未到达
}


//移动函数
bool move_icon(int16_t* a,int16_t* a_trg)
{
  if (*a < *a_trg)
  {
    *a+=ICON_SPEED;
    if (*a>*a_trg) *a=*a_trg;//加完超过
  }
  else if(*a>*a_trg)
  {
    *a-=ICON_SPEED;
    if (*a<*a_trg) *a=*a_trg;//减完不足
  }
  else
  {
    return true;//到达目标
  }
  return false;//未到达
}

//宽度移动函数
bool move_width(uint8_t* a,uint8_t* a_trg,uint8_t select,uint8_t id)
{
  if (*a < *a_trg)
  {
    uint8_t step=16/SPEED;//判断步数
    uint8_t len;
    if(ui_index==M_SELECT)
    {
    len=abs(u8g2_GetStrWidth(&u8g2,list[select].select)-u8g2_GetStrWidth(&u8g2,list[id==0?select+1:select-1].select));
    }
    else if(ui_index==M_PID)
    {
    len=abs(u8g2_GetStrWidth(&u8g2,pid[select].select)-u8g2_GetStrWidth(&u8g2,pid[id==0?select+1:select-1].select));
    }
    uint8_t width_speed=((len%step)==0?(len/step):(len/step+1));   //计算步长
    *a+=width_speed;
    if (*a>*a_trg) *a=*a_trg;//
  }
  else if(*a>*a_trg)
  {
    uint8_t step=16/SPEED;//判断步数
    uint8_t len;
    if(ui_index==M_SELECT)
    {
    len=abs(u8g2_GetStrWidth(&u8g2,list[select].select)-u8g2_GetStrWidth(&u8g2,list[id==0?select+1:select-1].select));
    }
    else if(ui_index==M_PID)
    {
    len=abs(u8g2_GetStrWidth(&u8g2,pid[select].select)-u8g2_GetStrWidth(&u8g2,pid[id==0?select+1:select-1].select));
    }
    uint8_t width_speed=((len%step)==0?(len/step):(len/step+1));   //计算步长
    *a-=width_speed;
    if (*a<*a_trg) *a=*a_trg;
  }
  else
  {
    return true;//到达目标
  }
  return false;//未到达
}

//进度条移动函数
bool move_bar(uint8_t* a,uint8_t* a_trg)
{
  if (*a < *a_trg)
  {
    uint8_t step=16/SPEED;//判断步数
    uint8_t width_speed=((single_line_length%step)==0?(single_line_length/step):(single_line_length/step+1));   //计算步长
    *a+=width_speed;
    if (*a>*a_trg) *a=*a_trg;//
  }
  else if(*a>*a_trg)
  {
    uint8_t step=16/SPEED;//判断步数
    uint8_t width_speed=((single_line_length%step)==0?(single_line_length/step):(single_line_length/step+1));   //计算步长
    *a-=width_speed;
    if (*a<*a_trg) *a=*a_trg;
  }
  else
  {
    return true;//到达目标
  }
  return false;//未到达
}

//消失函数
void disappear()
{
  switch(disappear_step)
  {
    case 1:
    for(uint16_t i=0;i<buf_len;++i)
    {
      if(i%2==0) buf_ptr[i]=buf_ptr[i] & 0x55;
    }
    break;
    case 2:
    for(uint16_t i=0;i<buf_len;++i)
    {
      if(i%2!=0) buf_ptr[i]=buf_ptr[i] & 0xAA;
    }
    break;
    case 3:
    for(uint16_t i=0;i<buf_len;++i)
    {
      if(i%2==0) buf_ptr[i]=buf_ptr[i] & 0x00;
    }
    break;
    case 4:
    for(uint16_t i=0;i<buf_len;++i)
    {
      if(i%2!=0) buf_ptr[i]=buf_ptr[i] & 0x00;
    }
    break;
    default:
    ui_state=S_NONE;
    disappear_step=0;
    break;
  }
  disappear_step++;
}

void logo_ui_show()//显示logo
{
  u8g2_DrawXBMP(&u8g2,0, 0, 128, 64, LOGO);
}

void select_ui_show()//选择界面
{
  move_bar(&line_y,&line_y_trg);
  move(&y,&y_trg);
  move(&box_y,&box_y_trg);
  move_width(&box_width,&box_width_trg,ui_select,key_msg.id);
  u8g2_DrawVLine(&u8g2,126,0,total_line_length);
  u8g2_DrawPixel(&u8g2,125,0);
  u8g2_DrawPixel(&u8g2,127,0);
  for(uint8_t i=0;i<list_num;++i)
  {    
    u8g2_DrawStr(&u8g2,x,16*i+y+12,list[i].select);  // 第一段输出位置 
    u8g2_DrawPixel(&u8g2,125,single_line_length*(i+1));
    u8g2_DrawPixel(&u8g2,127,single_line_length*(i+1));
  }
  u8g2_DrawVLine(&u8g2,125,line_y,single_line_length-1);
  u8g2_DrawVLine(&u8g2,127,line_y,single_line_length-1);
  u8g2_SetDrawColor(&u8g2,2);
  u8g2_DrawRBox(&u8g2,0,box_y,box_width,16,1);
  u8g2_SetDrawColor(&u8g2,1);
}


void pid_ui_show()//PID界面
{
  move_bar(&pid_line_y,&pid_line_y_trg);
  move(&pid_box_y,&pid_box_y_trg);
  move_width(&pid_box_width,&pid_box_width_trg,pid_select,key_msg.id);
  u8g2_DrawVLine(&u8g2,126,0,61);
  u8g2_DrawPixel(&u8g2,125,0);
  u8g2_DrawPixel(&u8g2,127,0);
  for(uint8_t i=0;i<pid_num;++i)
  {    
    u8g2_DrawStr(&u8g2,x,16*i+12,pid[i].select);  // 第一段输出位置 
    u8g2_DrawPixel(&u8g2,125,15*(i+1));
    u8g2_DrawPixel(&u8g2,127,15*(i+1));
  }

  u8g2_SetDrawColor(&u8g2,2);
  u8g2_DrawRBox(&u8g2,0,pid_box_y,pid_box_width,16,1);
  u8g2_SetDrawColor(&u8g2,1);
  u8g2_DrawVLine(&u8g2,125,pid_line_y,14);
  u8g2_DrawVLine(&u8g2,127,pid_line_y,14);
  u8g2_SendBuffer(&u8g2);
}


void about_ui_show()//about界面
{

  u8g2_DrawStr(&u8g2,2,12,"MCU : ESP32");
  u8g2_DrawStr(&u8g2,2,28,"FLASH : 4MB");
  u8g2_DrawStr(&u8g2,2,44,"SRAM : 520KB");
  u8g2_DrawStr(&u8g2,2,60,"RTC SRAM : 16KB");
	u8g2_SendBuffer(&u8g2);
}

void logo_proc()//logo界面处理函数
{
  if(key_msg.pressed)
  {
    key_msg.pressed=false;
    ui_state=S_DISAPPEAR;
    ui_index=M_SELECT;
  }
  logo_ui_show();
}

void select_proc(void)//选择界面处理
{
  if(key_msg.pressed)
  {
    key_msg.pressed=false;
    switch(key_msg.id)
    {
      case 0:
      if(ui_select<1) break;
      ui_select-=1;
      line_y_trg-=single_line_length;
      if(ui_select<-(y/16))
      {
        y_trg+=16;
      }
      else
      {
        box_y_trg-=16;   
      }
 
      break;
      case 1:
      if((ui_select+2)>(sizeof(list)/sizeof(SELECT_LIST))) break;
      ui_select+=1;
      line_y_trg+=single_line_length;
      if((ui_select+1)>(4-y/16))
      {
        y_trg-=16;
      }
      else
      {
        box_y_trg+=16; 
      }

      break;
      case 2:
      switch(ui_select)
      {
        case 0:     //return
        ui_state=S_DISAPPEAR;
        ui_index=M_LOGO;
        break;
        case 1:     //pid
        ui_state=S_DISAPPEAR;
        ui_index=M_PID;
        break;
        case 2:   //icon
        ui_state=S_DISAPPEAR;
        ui_index=M_ICON;
        break;
        case 3:   //chart
        ui_state=S_DISAPPEAR;
        ui_index=M_CHART;
        break;
        case 4:   //textedit
        ui_state=S_DISAPPEAR;
        ui_index=M_TEXT_EDIT;
        break;
        case 6:   //about
        ui_state=S_DISAPPEAR;
        ui_index=M_ABOUT;
        break;
        default:
        break;
      }
      default:
      break;
    }
    box_width_trg=u8g2_GetStrWidth(&u8g2,list[ui_select].select)+x*2;
  }
  select_ui_show();
}

void about_proc()//about界面处理函数
{
  if(key_msg.pressed)
  {
    key_msg.pressed=false;
    ui_state=S_DISAPPEAR;
    ui_index=M_SELECT;
  }
  about_ui_show();
}


void chart_ui_show()//chart界面
{
	sprintf(text,"RTC SRAM : %dKB",value);
	u8g2_DrawStr(&u8g2,2,12,"MCU : STM32");
	u8g2_DrawStr(&u8g2,2,28,"FLASH : 4MB");
	u8g2_DrawStr(&u8g2,2,44,"SRAM : 520KB");
	u8g2_DrawStr(&u8g2,2,60,text);
}

void chart_proc()//chart界面处理函数
{
  chart_ui_show();
  if(key_msg.pressed)
  {
    key_msg.pressed=false;
    ui_state=S_DISAPPEAR;
    ui_index=M_SELECT;
  }
}

void pid_proc()//pid界面处理函数
{
pid_ui_show();
if(key_msg.pressed)
  {  
    key_msg.pressed=false;
    switch(key_msg.id)
    {
      case 0:
      if(pid_select!=0) 
      {
      pid_select-=1;
      pid_line_y_trg-=15;
      pid_box_y_trg-=16;   
      break;
      }
      else
      {
        break;
      }
      case 1:
      if(pid_select!=3)
      { 
        pid_select+=1;
        pid_line_y_trg+=15;
        pid_box_y_trg+=16; 
      }
      else
      {
        break;
      }
      break;
      case 2:
      if(pid_select==3)
      {
        ui_index=M_SELECT;
        ui_state=S_DISAPPEAR;
        pid_select=0;
        pid_line_y=pid_line_y_trg=1;
        pid_box_y=pid_box_y_trg=0;
        pid_box_width=pid_box_width_trg=u8g2_GetStrWidth(&u8g2,pid[pid_select].select)+x*2;
      }
      else
      {
        ui_index=M_PID_EDIT;
      }
      break;
      default:
      break;
    }
    pid_box_width_trg=u8g2_GetStrWidth(&u8g2,pid[pid_select].select)+x*2;
  }
}



void ui_proc()//总的UI进程
{
  switch(ui_state)
  {
    case S_NONE:
    if(ui_index!=M_CHART) u8g2_ClearBuffer(&u8g2);
    switch(ui_index)
    {
      case M_LOGO:
      logo_proc();
      break;
      case M_SELECT:
      select_proc();
      break;
      case M_PID:
      pid_proc();
      break;
      case M_ICON:
      //icon_proc();
      break;
      case M_CHART:
      chart_proc();
      break;
      case M_TEXT_EDIT:
      //text_edit_proc();
      break;
      case M_PID_EDIT:
      //pid_edit_proc();
      break;
      case M_ABOUT:
      about_proc();
      break;
      default:
      break;
    }
    break;
    case S_DISAPPEAR:
    disappear();
    break;
    default:
    break;
  }
  u8g2_SendBuffer(&u8g2);
} 


