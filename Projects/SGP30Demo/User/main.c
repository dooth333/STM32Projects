#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "delay.h"
#include "SGP30.h"
#include "string.h"

 int main(void)
 {		
	
	char text[100]; 
	OLED_Init(); 
	SGP30_Init(); 
   Delay_ms(800);
	OLED_ShowString(1,1,"Start!");
		while(1)
		{		
			SGP30_getValue();	
			sprintf(text,"TVOC:%d",TVOC);
			OLED_ShowString(2,1,text);
			sprintf(text,"co2:%d Ppm",Co2);
			OLED_ShowString(3,1,text);
			Delay_ms(80);
		
		}	 
}
  
