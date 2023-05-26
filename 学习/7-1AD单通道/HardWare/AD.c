#include "stm32f10x.h"                  // Device header

void AD_Init()
{
	//开启ADC和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//配置GPIO，先声明结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	//GPIO模式设置模拟输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	//GPIO引脚为0引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	//GPIO速度为50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//通过结构体对GPIO进行初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//配置多路开关,把左边通道接到右边的规则组列表里
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	//配置ADC转换器,先声明ADC初始化结构体
	ADC_InitTypeDef ADC_InitStructure;
	//配置ADC对齐方式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//触发控制的触发源选择
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//配置ADC模式为
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	//关闭连续转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  //配置ADC通道数目为1
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	//扫描转换模式关闭
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//通过结构体对ADC进行初始化
	ADC_Init(ADC1,&ADC_InitStructure);
	//给ADC上电，即开关控制
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待复位校准完成，开始复位校准置1，复位校准完成后该位自动清0
	ADC_StartCalibration(ADC1);//开始校准
	while(ADC_GetCalibrationStatus(ADC1));//获取开始校准状态，开始校准置1，开始校准完成后该位自动清0
}


uint16_t AD_GetValue(void)
{
	//软件触发转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET); //转换完成置1，未完成为0（该位有软件清除，或者读取ADC_DR时自动清零，这些手册上都有）
	return ADC_GetConversionValue(ADC1);
}
