#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"



//�ر�JTAG���ܣ���SWD����
inline void JTAG_SWD_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
}

#endif
