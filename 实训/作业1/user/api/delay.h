#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

#define delay_1us() {\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
}


extern vu32 RunTime;
void SysTick_Init(uint32_t tick);
void Delay_ms(uint32_t tick);
void Delay_us(uint32_t time);
void Delay_msnop(uint32_t time);
#endif














