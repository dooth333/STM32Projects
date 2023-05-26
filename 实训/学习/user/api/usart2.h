#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"                  // Device header

void usart2_init(void);
void usart2_sendByte(u8 date);
void Usart_SendString(unsigned char *String,u8 count);

#endif
