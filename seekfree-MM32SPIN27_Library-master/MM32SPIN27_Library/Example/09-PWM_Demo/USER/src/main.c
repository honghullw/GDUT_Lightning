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
// 本例程初始化了逐飞科技MM32SPIIN27PS核心板上的 A11/12 B10/11 作为TIM2的PWM输出
// 请不要使用本例程来测试驱动或者驱动电机
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project  clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 duty;
bool output_dir = false;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	pwm_init(TIM_2, TIM_2_CH1_A11, 10000, 0);										// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(TIM_2, TIM_2_CH2_A12, 10000, 0);										// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(TIM_2, TIM_2_CH3_C09, 10000, 0);										// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(TIM_2, TIM_2_CH4_B11, 10000, 0);										// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%

	while(1)
	{
		if(output_dir)																// 防止接上电机跑PWM导致驱动双向导通
		{
			pwm_duty_updata(TIM_2, TIM_2_CH1_A11, duty);							// 通道 1 输出
			pwm_duty_updata(TIM_2, TIM_2_CH2_A12, 0);								// 通道 2 停止
			pwm_duty_updata(TIM_2, TIM_2_CH3_C09, duty);							// 通道 3 输出
			pwm_duty_updata(TIM_2, TIM_2_CH4_B11, 0);								// 通道 4 停止

			duty += 100;															// 更新占空比
			if(duty > PWM_DUTY_MAX/2)												// 占空比不超过 50%
			{
				duty = 0;															// 占空比清空
				output_dir = false;													// 翻转输出
			}
			systick_delay_ms(20);
		}
		else
		{
			pwm_duty_updata(TIM_2, TIM_2_CH1_A11, 0);								// 通道 1 停止
			pwm_duty_updata(TIM_2, TIM_2_CH2_A12, duty);							// 通道 2 输出
			pwm_duty_updata(TIM_2, TIM_2_CH3_C09, 0);								// 通道 3 停止
			pwm_duty_updata(TIM_2, TIM_2_CH4_B11, duty);							// 通道 4 输出

			duty += 100;															// 更新占空比
			if(duty > PWM_DUTY_MAX/2)												// 占空比不超过 50%
			{
				duty = 0;															// 占空比清空
				output_dir = true;													// 翻转输出
			}
			systick_delay_ms(20);
		}
	}
}
// **************************** 代码区域 ****************************
