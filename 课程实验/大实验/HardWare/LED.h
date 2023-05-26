#ifndef __LED_H
#define __LED_H

#define GPIO_LED1 GPIO_Pin_3
#define GPIO_LED2 GPIO_Pin_4

extern u8 LED2_flag;
extern u8 LED1_flag;
extern u8 LED2_flagk1;
extern u8 LED2_flagk2;
void LED_Init(void);
void LED1_OFF(void);
void LED1_ON(void);
void LED1_Turn(void);
void LED2_Turn(void);
void LED2_OFF(void);
void LED2_ON(void);

#endif





