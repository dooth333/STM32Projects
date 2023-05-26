#include "adc1.h" 

typedef_ADC adc_data;

void ADC1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&	GPIO_InitStructer);
	
	ADC_InitTypeDef ADC_InitStructuer;
	ADC_InitStructuer.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructuer.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructuer.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructuer.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructuer.ADC_NbrOfChannel = 1;
	ADC_InitStructuer.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStructuer);
	
	ADC_Cmd(ADC1,ENABLE);
}

u16 ADC1_GetValue(void)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	adc_data.light =  ADC_GetConversionValue(ADC1);
	return adc_data.light;
}

