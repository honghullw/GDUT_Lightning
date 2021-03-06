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
// 测试可选准备逐飞科技10245线正交迷你编码器一个
// 
// 调试下载需要准备逐飞科技CMSIS-DAP或Jlink调试下载器一个
// 
// 本例程初始化了逐飞科技MM32SPIIN27PS核心板上的TIM_1/2/3/8四个定时器作为编码器采集输入
// 将编码器接在对应的 TIM_1-A08/01  TIM_2-A05/A12  TIM_3-A06/A07  TIM_8-C00/C01
// 开启SOFT_SIM_ENCODER定义时 初始化了A2/3两个引脚作为模拟编码器波形输出
// 将A2/3接在对应的 TIM_1-A08/01  TIM_2-A05/A12  TIM_3-A06/A07  TIM_8-C00/C01
// 
// 烧录本例程后 接线完毕上电后可见从串口输出的编码器采集信息
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project  clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define SOFT_SIM_ENCODER			1												// 1-开启模拟测试 使用GPIO模拟编码器波形 0-关闭模拟测试 使用编码器实物测试
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
int16 encoder_count = 0;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
#if SOFT_SIM_ENCODER
void soft_sim_encoder_positive (uint8 loop_count)
{
	while(loop_count--)
	{
		gpio_set(A2, 1);
		systick_delay_ms(10);
		gpio_set(A3, 1);
		systick_delay_ms(10);
		gpio_set(A2, 0);
		systick_delay_ms(10);
		gpio_set(A3, 0);
		systick_delay_ms(10);
	}
}

void soft_sim_encoder_inverted (uint8 loop_count)
{
	while(loop_count--)
	{
		gpio_set(A3, 1);
		systick_delay_ms(10);
		gpio_set(A2, 1);
		systick_delay_ms(10);
		gpio_set(A3, 0);
		systick_delay_ms(10);
		gpio_set(A2, 0);
		systick_delay_ms(10);
	}
}
#endif

int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	tim_encoder_init(TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);						// 初始化 TIM_1 B005/06 正交编码器采集
	tim_encoder_init(TIM_2, TIM_2_ENC1_A05, TIM_2_ENC2_A12);						// 初始化 TIM_2 A00/A01 正交编码器采集
	tim_encoder_init(TIM_3, TIM_3_ENC1_A06, TIM_3_ENC2_A07);						// 初始化 TIM_3 A06/A07 正交编码器采集
	tim_encoder_init(TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);						// 初始化 TIM_8 C00/C01 正交编码器采集
#if SOFT_SIM_ENCODER
	gpio_init(A2, GPO, GPIO_LOW, GPO_PUSH_PULL);									// 初始化 A02 作为 GPIO 输入模拟编码器波形
	gpio_init(A3, GPO, GPIO_LOW, GPO_PUSH_PULL);									// 初始化 A03 作为 GPIO 输入模拟编码器波形
#endif

	while(1)
	{
#if SOFT_SIM_ENCODER
		soft_sim_encoder_positive(20);												// 模拟正交编码器正转波形20个 共80个边沿
		encoder_count = tim_encoder_get_count(TIM_1);								// 采集对应编码器数据
		tim_encoder_rst(TIM_1);														// 清除对应计数
		printf("\r\nTIM1 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_2);								// 采集对应编码器数据
		tim_encoder_rst(TIM_2);														// 清除对应计数
		printf("\r\nTIM2 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_3);								// 采集对应编码器数据
		tim_encoder_rst(TIM_3);														// 清除对应计数
		printf("\r\nTIM3 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_8);								// 采集对应编码器数据
		tim_encoder_rst(TIM_8);														// 清除对应计数
		printf("\r\nTIM8 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		systick_delay_ms(1000);														// 时间间隔 1000ms

		soft_sim_encoder_inverted(20);												// 模拟正交编码器反转波形20个 共80个边沿
		encoder_count = tim_encoder_get_count(TIM_1);								// 采集对应编码器数据
		tim_encoder_rst(TIM_1);														// 清除对应计数
		printf("\r\nTIM1 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_2);								// 采集对应编码器数据
		tim_encoder_rst(TIM_2);														// 清除对应计数
		printf("\r\nTIM2 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_3);								// 采集对应编码器数据
		tim_encoder_rst(TIM_3);														// 清除对应计数
		printf("\r\nTIM3 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_8);								// 采集对应编码器数据
		tim_encoder_rst(TIM_8);														// 清除对应计数
		printf("\r\nTIM8 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		systick_delay_ms(1000);														// 时间间隔 1000ms
#else
		encoder_count = tim_encoder_get_count(TIM_1);								// 采集对应编码器数据
		tim_encoder_rst(TIM_1);														// 清除对应计数
		printf("\r\nTIM1 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_2);								// 采集对应编码器数据
		tim_encoder_rst(TIM_2);														// 清除对应计数
		printf("\r\nTIM2 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_3);								// 采集对应编码器数据
		tim_encoder_rst(TIM_3);														// 清除对应计数
		printf("\r\nTIM3 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		encoder_count = tim_encoder_get_count(TIM_8);								// 采集对应编码器数据
		tim_encoder_rst(TIM_8);														// 清除对应计数
		printf("\r\nTIM8 encoder counter: %d.", encoder_count);						// 串口输出采集到数据
		systick_delay_ms(1000);														// 时间间隔 1000ms
#endif
	}
}
// **************************** 代码区域 ****************************
