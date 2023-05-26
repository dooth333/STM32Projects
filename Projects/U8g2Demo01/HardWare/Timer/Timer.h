#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f10x.h"                  // Device header
void Timer_Init(void);

extern u32 timedKey[2];
extern u32 timeCount;
#endif

