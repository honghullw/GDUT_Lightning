#include "output_control.h"

extern a data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;







void MotorInput()
{
  uint32 motor_left_duty_cycle;
  uint32 motor_right_duty_cycle;
  if(data.inductance_normalization[0]<data.inductance_normalization[4])
  {
    motor_left_duty_cycle= (uint32)(up_pid.output-speed_pid.output+direction_pid.output);
    motor_right_duty_cycle = (uint32)(up_pid.output-speed_pid.output-direction_pid.output);
  }else
  {
    motor_left_duty_cycle= (uint32)(up_pid.output-speed_pid.output-direction_pid.output);
    motor_right_duty_cycle = (uint32)(up_pid.output-speed_pid.output+direction_pid.output);
  }
  MotorDrive(motor_left_duty_cycle,motor_right_duty_cycle);

}
void MotorDrive(uint32 motor1_duty_cycle,uint32 motor2_duty_cycle)
{
  //第一个电机正转
  pwm_duty_updata(TIM_2,TIM_2_CH1_A11,motor1_duty_cycle);
  pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
  //第二个电机正转
  pwm_duty_updata(TIM_2,TIM_2_CH3_C09,motor2_duty_cycle);
  pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0);
  
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		总电机驱动
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void TotalMotorDrive()
{
  MotorInput();
}