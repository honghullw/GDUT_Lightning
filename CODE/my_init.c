#include "my_init.h"

void AllInit(void)
{
 
//拨码开关gpio_init()
gpio_init(BMST, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为上拉输入 默认高电平
gpio_init(BMND, GPI, 0, GPI_PULL_DOWN);
gpio_init(BMRD, GPI, 0, GPI_PULL_DOWN);
gpio_init(BMTH, GPI, 0, GPI_PULL_DOWN);
    
//按键gpio_init()
gpio_init(KEY_UP, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为上拉输入 默认高电平
gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_DOWN);
gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_DOWN);
gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_DOWN);
  
//电机初始化
pwm_init (TIM_2, TIM_2_CH1_A11, 13000, 0);
pwm_init (TIM_2, TIM_2_CH2_A12, 13000, 0);
pwm_init (TIM_2, TIM_2_CH3_C09, 13000, 0);
pwm_init (TIM_2, TIM_2_CH4_B11, 13000, 0);

//编码器初始化
tim_encoder_init (TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);
tim_encoder_init (TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);

//OLED初始化
oled_init();

//ICM20602初始化
icm20602_init_spi();

////电感初始化
adc_init (ADC_1, ADC1_CH02_A02, ADC_12BIT);
adc_init (ADC_1, ADC1_CH03_A03, ADC_12BIT);
adc_init (ADC_1, ADC1_CH05_A05, ADC_12BIT);
adc_init (ADC_1, ADC1_CH06_A06, ADC_12BIT);
adc_init (ADC_1, ADC1_CH07_A07, ADC_12BIT);

////电流ADC初始化
//adc_init (ADC_2, ADC2_CH11_B10, ADC_12BIT);
//adc_init (ADC_2, ADC2_CH03_B13, ADC_12BIT);

////无线串口模块初始化
//seekfree_wireless_init ();

//蓝牙
  uart_init(UART_2, 9600, UART2_TX_C04, UART2_RX_C05);							// 默认初始化 UART1 用以支持 printf 输出
  uart_rx_irq(UART_2, ENABLE);

//pit初始化
tim_interrupt_init_ms (TIM_3, 1,3);
//tim_interrupt_init_ms (TIM_14, 1,3);
}

