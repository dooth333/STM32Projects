#ifndef _USART1_H
#define _USART1_H

#include "stdio.h"
#include "stm32f10x.h"                  // Device header

void usart1_init(void);
void usart1_sendByte(u8 date);
void usart1_sendString(char *String);

#endif
