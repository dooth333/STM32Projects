#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"



void Delay_Config(void);
void Delay_usnop(u32 time);
void Delay_msnop(u32 time);
void Delay_ms(u32 time);
#endif
