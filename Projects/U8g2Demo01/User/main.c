#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "u8g2.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "Timer.h"
#include "stdbool.h"
#include "Math.h"
#include <math.h>







int main(void)
{
	LED_Init();
	Key_Init();
	Timer_Init();
	u8g2Init();
	while (1)
	{
		ui_proc();
	}
}




