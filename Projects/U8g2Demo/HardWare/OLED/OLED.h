#ifndef __OLED_H
#define __OLED_H

/*引脚配置*/
#define OLED_SCL_GPIO GPIOB
#define OLED_SCL_Pin GPIO_Pin_8
#define OLED_SCL_Clock RCC_APB2Periph_GPIOB
#define OLED_W_SCL(x)		GPIO_WriteBit(OLED_SCL_GPIO, OLED_SCL_Pin, (BitAction)(x))

#define OLED_SDA_GPIO GPIOB
#define OLED_SDA_Pin GPIO_Pin_9
#define OLED_SDA_Clock RCC_APB2Periph_GPIOB
#define OLED_W_SDA(x)		GPIO_WriteBit(OLED_SDA_GPIO, OLED_SDA_Pin, (BitAction)(x))

void OLED_I2C_Init(void);

struct SENTING_LIST{
	char* srt;
	short len;
};

extern struct SENTING_LIST list[4];


extern int state;
extern short x,x_trg,y ,y_trg; //x当前位置数值,x_trg 目标坐标值
extern u8g2_t u8g2;

extern int list_len ;
extern char ui_select;//选中第几个列表
extern short frame_len,frame_len_trg;//框框的宽度
extern short frame_y,frame_y_trg;//框框的y


void u8g2Init(void);
#endif
