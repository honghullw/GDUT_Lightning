#include "output_control.h"

extern a data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;







//void MotorInput()
//{
//  uint32 motor_left_duty_cycle;
//  uint32 motor_right_duty_cycle;
//  if(data.inductance_normalization[0]<data.inductance_normalization[4])
//  {
//    motor_left_duty_cycle= (uint32)(up_pid.output-speed_pid.output+direction_pid.output);
//    motor_right_duty_cycle = (uint32)(up_pid.output-speed_pid.output-direction_pid.output);
//  }else
//  {
//    motor_left_duty_cycle= (uint32)(up_pid.output-speed_pid.output-direction_pid.output);
//    motor_right_duty_cycle = (uint32)(up_pid.output-speed_pid.output+direction_pid.output);
//  }
//  MotorDrive(motor_left_duty_cycle,motor_right_duty_cycle);
//
//}


void MotorControl()
{
    float casecade_pid_output=CasecadePidOutput();
    float other_pid_output=OtherPidOutput();
    uint16 left_pwm=(uint16)(casecade_pid_output+other_pid_output);
    uint16 right_pwm=(uint16)(casecade_pid_output-other_pid_output);
    MotorDrive(left_pwm,right_pwm);
}

void MotorDrive(uint32 motor1_duty_cycle,uint32 motor2_duty_cycle)
{
  //???????????
  pwm_duty_updata(TIM_2,TIM_2_CH1_A11,motor1_duty_cycle);
  pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
  //???????????
  pwm_duty_updata(TIM_2,TIM_2_CH3_C09,motor2_duty_cycle);
  pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0);
  
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		????????
// @param		ch				???ADC???
// @param		resolution		??????????????(????????????????????????????? ???????????????????งน)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//?????A00?ADC???? ??????8ฆห
//-------------------------------------------------------------------------------------------------------------------
void TotalMotorDrive()
{
  MotorControl();
}