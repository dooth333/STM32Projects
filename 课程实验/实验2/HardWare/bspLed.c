#include "stm32f10x.h"                  // Device header

void bspLed_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStructure;//初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//初始化0、1、2引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置速度为50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);//通过配置好的结构体进行GPIO初始化
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);//初始化关闭三个LED灯
}



/**
  * @brief 红灯亮
  * @param  None
  * @retval None
  */
void bspLed0_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

/**
  * @brief 红灯关
  * @param  None
  * @retval None
  */
void bspLed0_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

/**
  * @brief 绿灯亮
  * @param  None
  * @retval None
  */
void bspLed1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

/**
  * @brief 绿灯关
  * @param  None
  * @retval None
  */
void bspLed1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

/**
  * @brief 蓝灯开
  * @param  None
  * @retval None
  */
void bspLed2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/**
  * @brief 蓝灯关
  * @param  None
  * @retval None
  */
void bspLed2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

/**
  * @brief 红
  * @param  None
  * @retval None
  */
void LED_RED(void)
{
	bspLed0_ON();
	bspLed1_OFF();
	bspLed2_OFF();
}

/**
  * @brief 绿
  * @param  None
  * @retval None
  */
void LED_GREEN(void)
{
	bspLed0_OFF();
	bspLed1_ON();
	bspLed2_OFF();
}

/**
  * @brief 蓝
  * @param  None
  * @retval None
  */
void LED_BLUE(void)
{
	bspLed0_OFF();
	bspLed1_OFF();
	bspLed2_ON();
}


/**
  * @brief 黄(红+绿)
  * @param  None
  * @retval None
  */
void LED_YELLOW(void)
{
	bspLed0_ON();
	bspLed1_ON();
	bspLed2_OFF();
}

/**
  * @brief 紫(红+蓝)
  * @param  None
  * @retval None
  */
void LED_PURPLE(void)
{
	bspLed0_ON();
	bspLed1_OFF();
	bspLed2_ON();
}

/**
  * @brief 青(绿+蓝)
  * @param  None
  * @retval None
  */
void LED_CYAN(void)
{
	bspLed0_OFF();
	bspLed1_ON();
	bspLed2_ON();
}


/**
  * @brief 白(红+绿+蓝)
  * @param  None
  * @retval None
  */
void LED_WHITE(void)
{
	bspLed0_ON();
	bspLed1_ON();
	bspLed2_ON();
}

/**
  * @brief 黑(全部关闭)
  * @param  None
  * @retval None
  */
void LED_RGBOFF(void)
{
	bspLed0_OFF();
	bspLed1_OFF();
	bspLed2_OFF();
}



