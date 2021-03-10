#include "my_init.h"

void AllInit(void)
{
    //小灯初始化
    gpio_init(LED_UP, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化引脚为推挽输出 默认高电平
    gpio_init(LED_DOWN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    //按键初始化
    gpio_init(KEY_UP, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为上拉输入 默认高电平
    gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_DOWN);
    gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_DOWN);
    gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_DOWN);

    //拨码开关初始胡
    gpio_init(BMST, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为上拉输入 默认高电平
    gpio_init(BMND, GPI, 0, GPI_PULL_DOWN);
    gpio_init(BMRD, GPI, 0, GPI_PULL_DOWN);
    gpio_init(BMTH, GPI, 0, GPI_PULL_DOWN);

    //三轮电机初始化
    pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);//一号电机
    gpio_init(MOTOR1_DIR, GPI, GPIO_LOW, GPI_PULL_DOWN);

    pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);//二号电机
    gpio_init(MOTOR2_DIR, GPI, GPIO_LOW, GPI_PULL_DOWN);

    //定时器中断初始化
    tim_interrupt_init_ms (TIM_3, 1,3);

    //编码器初始化
    tim_encoder_init (TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);//左编码器初始化
    tim_encoder_init (TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);//右编码器初始化

    //oled初始化
    oled_init();

    //电感adc初始化
    adc_init (ADC_1, ADC1_CH02_A02, ADC_12BIT);
    adc_init (ADC_1, ADC1_CH03_A03, ADC_12BIT);
    adc_init (ADC_1, ADC1_CH05_A05, ADC_12BIT);
    adc_init (ADC_1, ADC1_CH06_A06, ADC_12BIT);
    adc_init (ADC_1, ADC1_CH07_A07, ADC_12BIT);

    //蓝牙模块初始化
    seekfree_wireless_init();

    //电流adc初始化
    adc_init (ADC_2, ADC2_CH11_B10, ADC_12BIT);
    adc_init (ADC_2, ADC2_CH03_B13, ADC_12BIT);
}
