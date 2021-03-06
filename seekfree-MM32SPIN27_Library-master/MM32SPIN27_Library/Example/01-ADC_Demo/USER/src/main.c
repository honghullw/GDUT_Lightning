/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32SPIN2XPs
* @Taobao			https://seekfree.taobao.com/
* @date				2020-11-23
********************************************************************************************************************/

#include "headfile.h"

// *************************** 例程说明 ***************************
// 
// 测试需要准备逐飞科技MM32SPIIN27PS核心板一块
// 
// 调试下载需要准备逐飞科技CMSIS-DAP或Jlink调试下载器一个
// 
// 本例程初始化了除ADC2_CH0_A10/ADCx_CH04_A04以外的所有ADC输入引脚
// 
// 烧录本例程后 如果使用的是逐飞科技的DAP或Jlink产品
// 可以直接在串口助手中打开对应串口
// 如果使用的并不是逐飞科技的DAP或Jlink产品
// 请接上USB转TTL或其他串口调试模块等 再打开串口调试助手
// 
// 在串口助手中向单片机发送 A-L 之间的任意大写字母
// 对应0-11通道 会在串口助手上打印当前通道AD数值
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project  clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 adc_value;
uint8 adc_ch = 0;
ADCCH_enum adc1_pin[12] ={
	ADC1_CH00_A00,
	ADC1_CH01_A01,
	ADC1_CH02_A02,
	ADC1_CH03_A03,
	ADC1_CH04_A04,
	ADC1_CH05_A05,
	ADC1_CH06_A06,
	ADC1_CH07_A07,
	ADC1_CH08_B00,
	ADC1_CH09_B01,
	ADC1_CH10_B02,
	ADC1_CH11_B10,
};

ADCCH_enum adc2_pin[12] ={
	ADC2_CH00_A10,																	// A10 用作Debug_UART_RX
	ADC2_CH01_B15,
	ADC2_CH02_B14,
	ADC2_CH03_B13,
	ADC2_CH04_A04,
	ADC2_CH05_A05,
	ADC2_CH06_A06,
	ADC2_CH07_A07,
	ADC2_CH08_B00,
	ADC2_CH09_B01,
	ADC2_CH10_B02,
	ADC2_CH11_B10,
};
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	adc_init(ADC_1, ADC1_CH00_A00, ADC_12BIT);										// 初始化ADC1通道x引脚精度12bit
	for(adc_ch = 1; adc_ch < 4; adc_ch++)
	{
		adc_init(ADC_1, adc1_pin[adc_ch], ADC_12BIT);								// 初始化ADC1通道x引脚精度12bit
		adc_init(ADC_2, adc2_pin[adc_ch], ADC_12BIT);								// 初始化ADC2通道x引脚精度12bit
	}
	for(adc_ch = 5; adc_ch < 12; adc_ch++)
	{
		adc_init(ADC_1, adc1_pin[adc_ch], ADC_12BIT);								// 初始化ADC1通道x引脚精度12bit
		adc_init(ADC_2, adc2_pin[adc_ch], ADC_12BIT);								// 初始化ADC2通道x引脚精度12bit
	}

	printf("\r\n1-ADC_Demo running. Please enter A-L.\r\n");
	while(1)
	{
		uart_getchar(UART_1, &adc_ch);
		if(adc_ch >= 0x41 && adc_ch <= 0x4C)										// 串口接收字符A-L对应通道0-11
		{
			printf("\r\n");															// printf重定向至串口1 从串口1输出信息
			if(adc_ch != 0x45)														// ADC1不读取CH4
			{
				adc_value = adc_mean_filter(ADC_1, adc1_pin[(adc_ch-0x41)], 10);	// 读取对应通道数值 采集10次取平均值
				printf("ADC_1 CH%d = %d.\r\n", (adc_ch-0x41), adc_value);			// printf重定向至串口1 从串口1输出信息
			}
			if(adc_ch != 0x41 && adc_ch != 0x45)									// ADC2不读取CH0/CH4
			{
				adc_value = adc_mean_filter(ADC_2, adc2_pin[(adc_ch-0x41)], 10);	// 读取对应通道数值 采集10次取平均值
				printf("ADC_2 CH%d = %d.\r\n", (adc_ch-0x41), adc_value);			// printf重定向至串口1 从串口1输出信息
			}
			adc_ch = 0x00;
		}
	}
}
// **************************** 代码区域 ****************************
