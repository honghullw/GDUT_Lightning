#include "my_init.h"

void AllInit(void)
{
 
//²¦Âë¿ª¹Øgpio_init()
    gpio_init(B8,GPI,GPIO_LOW,GPI_PULL_DOWN);
    gpio_init(B9,GPI,GPIO_LOW,GPI_PULL_DOWN);
    gpio_init(B6,GPI,GPIO_LOW,GPI_PULL_DOWN);
    gpio_init(B7,GPI,GPIO_LOW,GPI_PULL_DOWN);
    
//°´¼ügpio_init()
gpio_init(C9,GPI,GPIO_LOW,GPI_PULL_DOWN);
gpio_init(C8,GPI,GPIO_LOW,GPI_PULL_DOWN);
gpio_init(C7,GPI,GPIO_LOW,GPI_PULL_DOWN);
gpio_init(C6,GPI,GPIO_LOW,GPI_PULL_DOWN);

//pit ?§Ø?????  
tim_interrupt_init_ms (TIM_3, 1,3);//pit?§Ø????1ms
  
  
//????????  
//????????
pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);
pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);
pwm_init (TIM_2, TIM_2_CH3_C09, 10000, 0);
pwm_init (TIM_2, TIM_2_CH4_B11, 10000, 0);

//????????????¨®????????Pwm_In??
pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);
pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);


//???????????
tim_encoder_init (TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);
tim_encoder_init (TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);

//OLED?????
oled_init();

//ICM20602?????
icm20602_init();

//adc?????
//??????adc???
adc_init (ADC_1, ADC1_CH02_A02, ADC_12BIT);
adc_init (ADC_1, ADC1_CH03_A03, ADC_12BIT);
adc_init (ADC_1, ADC1_CH05_A05, ADC_12BIT);
adc_init (ADC_1, ADC1_CH06_A06, ADC_12BIT);
adc_init (ADC_1, ADC1_CH07_A07, ADC_12BIT);

//???????adc???
adc_init (ADC_2, ADC2_CH11_B10, ADC_12BIT);
adc_init (ADC_2, ADC2_CH03_B13, ADC_12BIT);
}
