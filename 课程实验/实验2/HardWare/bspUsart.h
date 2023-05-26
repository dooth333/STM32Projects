#ifndef _BSPUSART_H
#define _BSPUSART_H
extern uint8_t Serial_RxData;
void bspUsart_SendString(char *String);
void bspUsart_SendByte(uint8_t Byte);
void bspUsart_Init(void);


#endif
