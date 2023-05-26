#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdio.h>

extern char RECS[250];
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number,uint8_t Length);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag(void);
void Serial_SetRxFlag(uint8_t SetRxFlagNum);

#endif

