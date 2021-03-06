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
// 调试下载需要准备USB转TTL模块一个
// 
// 本例程初始化了逐飞科技MM32SPIIN27PS核心板上的UART1-A9/10
// 初始化了TIM1 周期中断 优先级次高 0x01
// 初始化了C6作为外部中断输入 优先级最高  0x00
// 初始化了C7作为GPIO输入
// 初始化了A4/D7为GPIO输出 用来驱动LED作为状态演示
// 
// 烧录本例程后可见D7标识的LED闪烁 该LED在TIM1中断中控制闪烁
// 按下C6按键后触发外部中断 此时A4标识的LED亮起 D7的LED停止闪烁
// 按下C7按键后从外部中断退出 A4熄灭D7继续闪烁
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project  clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint8 uart1_get_buffer;
uint8 uart2_get_buffer;
bool uart2_interrupt_flag = false;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	gpio_init(A4, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化为GPIO功能 输出 默认高电平
	gpio_init(D7, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化为GPIO功能 输出 默认高电平
	gpio_init(C7, GPI, GPIO_HIGH, GPI_FLOATING_IN);									// 初始化为GPIO功能 输入 上拉

	exti_interrupt_init(C6, EXTI_Trigger_Rising, 0x00);								// 初始化为外部中断输入 上升沿触发 优先级0x00最高
	tim_interrupt_init(TIM_1, 1, 0x01);												// 初始化TIM为周期中断 周期1Hz 优先级0x01次高

	while(1)
	{
	}
}

void exti_interrupt_handler (void)													// 外部中断处理函数 在 EXTI4_15_IRQHandler 中调用
{
	uint8 io_state = 1;																// 用来读取C7的状态
	gpio_set(A4, GPIO_LOW);															// 点亮A4的LED
	while(io_state)																	// 判断C7是否按下
	{
		// 此时由于外部中断优先级比TIM周期定时器中断高
		// 就无法触发TIM周期中断
		// 故D7停止闪烁
		io_state = gpio_get(C7);													// 读取C7状态
	}
	gpio_set(A4, GPIO_HIGH);														// 熄灭A4
}

void tim_interrupt_handler (void)													// TIM周期中断处理函数 在 TIM1_BRK_UP_TRG_COM_IRQHandler 中调用
{
	static bool io_state = GPIO_LOW;												// D7的状态标志
	gpio_set(D7, io_state);															// 更新D7状态
	io_state = !io_state;															// 翻转D7状态标志
}
// **************************** 代码区域 ****************************
