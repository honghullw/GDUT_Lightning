#include "my_init.h"

void AllInit(void)
{
  
//pit 中断初始化  
tim_interrupt_init_ms (TIM_1, 5,3);//pit中断延时5ms
  
  
//电机初始化  
//直立初始化
pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);
pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);
pwm_init (TIM_2, TIM_2_CH3_C09, 10000, 0);
pwm_init (TIM_2, TIM_2_CH4_B11, 10000, 0);

//三轮初始化（只用初始化两个Pwm_In）
pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);
pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);


//编码器初始化
tim_encoder_init (TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);
tim_encoder_init (TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);

//OLED初始化
oled_init();

//ICM20602初始化
icm20602_init();

//adc初始化
//采集电感adc模块
adc_init (ADC_1, ADC1_CH02_A02, ADC_12BIT);
adc_init (ADC_1, ADC1_CH03_A03, ADC_12BIT);
adc_init (ADC_1, ADC1_CH05_A05, ADC_12BIT);
adc_init (ADC_1, ADC1_CH06_A06, ADC_12BIT);
adc_init (ADC_1, ADC1_CH07_A07, ADC_12BIT);

//采集电流adc模块
adc_init (ADC_2, ADC2_CH11_B10, ADC_12BIT);
adc_init (ADC_2, ADC2_CH03_B13, ADC_12BIT);
}
