#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "u8g2.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "Timer.h"
#include "Math.h"
#include <math.h>
char text1[30];



int ui_run(short *a,short *a_trg,u8 step ,u8 slow_cnt)
{
	u8 temp;
	temp = abs(*a_trg - *a ) > slow_cnt ? step : 1;
  if(*a < *a_trg)
  {
     *a += temp;
  }
  else if( *a > *a_trg)
  {
    *a -= temp;    
  }
  else
  {
    return 0;
  }
  return 1;
}

void ui_show(void)
{
	u8g2_ClearBuffer(&u8g2);//Çå³ý»º´æ
	//u8g2_SetFont(&u8g2,u8g2_font_t0_22_mf);
	
	frame_len = frame_len_trg = list[ui_select].len*10+2;
	frame_y_trg = ui_select*12;
	for(int i = 0; i < list_len; i++)
	{
		u8g2_DrawStr(&u8g2,x+2,y+i*12,list[i].srt);
	}
	//u8g2_DrawRFrame(&u8g2,x,frame_y,frame_len,18,3);
	u8g2_SetDrawColor(&u8g2,2);
	u8g2_DrawRBox(&u8g2,x,frame_y,frame_len,12,3);
	u8g2_SetDrawColor(&u8g2,1);
	ui_run(&y,&y_trg,5,4);
	ui_run(&frame_y,&frame_y_trg,4,3);
	u8g2_SendBuffer(&u8g2);
	
}

int main(void)
{
	LED_Init();
	Key_Init();
	Timer_Init();
	u8g2Init();
	
	while (1)
	{
		
		
		ui_show();
		
	}
}




