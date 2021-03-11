#include "test.h"

extern a data;
extern b speed_data;
extern c angle_data;

uint16 state;
uint16 state1;
uint16 state2;
void KeyTestInit()
{
  	gpio_init(KEY_UP, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为下拉输入 默认低电平
	gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_DOWN);	
        gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_DOWN);	
        gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_DOWN);	
        
        gpio_init(A4, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化引脚为推挽输出 默认高电平
	gpio_init(D7, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化引脚为推挽输出 默认高电平

}

void KeyTest()
{

            state = gpio_get(KEY_UP);												// 获取输入引脚电平
		if(state)															// 高电平
			gpio_set(A4, 0);														// 输出低 亮灯
		else																		// 高电低
			gpio_set(A4, 1);														// 输出高 灭灯
        systick_delay_ms(10);


}


void BMTestInit()
{
        gpio_init(BMST, GPI, 0, GPI_PULL_DOWN);									// 初始化引脚为上拉输入 默认高电平
        gpio_init(BMND, GPI, 0, GPI_PULL_DOWN);	
        gpio_init(BMRD, GPI, 0, GPI_PULL_DOWN);	
        gpio_init(BMTH, GPI, 0, GPI_PULL_DOWN);	

        gpio_init(A4, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化引脚为推挽输出 默认高电平
	gpio_init(D7, GPO, GPIO_HIGH, GPO_PUSH_PULL);
}

void BMTest()
{
  state1 = gpio_get(BMST);//BMST有问题
  state2 = gpio_get(BMND);
  if(state1)
    gpio_set(A4, 0);
  else
    gpio_set(A4, 1);
  if(state2)
    gpio_set(D7,0);
    else
    gpio_set(D7, 1);




}



//void MotorTestInit()
//{
// pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);//一号电机
// gpio_init(MOTOR1_DIR, GPI, GPIO_LOW, GPI_PULL_DOWN);	
// 
// pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);//二号电机							
// gpio_init(MOTOR2_DIR, GPI, GPIO_LOW, GPI_PULL_DOWN);
// 
//}

void MotorTestInit(){
 pwm_init (TIM_2, TIM_2_CH2_A12, 10000, 0);//一号电机
 gpio_init(MOTOR1_DIR, GPO, 1, GPO_PUSH_PULL);	
 
 pwm_init (TIM_2, TIM_2_CH1_A11, 10000, 0);//二号电机							
 gpio_init(MOTOR2_DIR, GPO, 1, GPO_PUSH_PULL);	
 
}

void MotorTest()
{
   pwm_duty_updata(TIM_2,TIM_2_CH2_A12,500*60);
   gpio_set(MOTOR1_DIR,0);
   
   pwm_duty_updata(TIM_2,TIM_2_CH1_A11,500*60);
   gpio_set(MOTOR2_DIR,0);

}

void EncoderTestInit()
{
  tim_encoder_init (TIM_1, TIM_1_ENC1_A08, TIM_1_ENC2_A01);//左编码器初始化
  tim_encoder_init (TIM_8, TIM_8_ENC1_C00, TIM_8_ENC2_C01);//右编码器初始化
}

void EncoderTest()
{
    speed_data.left_wheel_pulse_num=tim_encoder_get_count(TIM_1);//是等号还是加等号暂时还不懂
    tim_encoder_rst(TIM_1);//清除计数值
    
    speed_data.right_wheel_pulse_num=tim_encoder_get_count(TIM_8);
    tim_encoder_rst(TIM_8);//清除计数值
    
}