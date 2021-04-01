#include "output_control.h"

extern a data;

extern c angle_data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;

extern float SpeedControlOut;
extern float DirectionControlOut;
extern float GyroControlOut;

float left_motor_out = 0;
float right_motor_out = 0;

#define MOTOR_OUT_DEAD_VAL 500*0//死区是必要的，提供较小pid输出时的pwm叠加，但如果死区过大会增大抖动情况，死去要调到较小并恰到好处的情况//2021.04.01调下这个还有速度环和角度环，关键是速度环调硬
#define MOTOR_OUT_MAX 500*70
#define MOTOR_OUT_MIN -500*70

uint32 test_num=0;

//float SmoothOutput(float input,int16 smooth_count)//（输入，总平滑次数）
//{
//  float input_last,input_increment;
//  float output;
//  input_increment=input-input_last;
//  smooth_output=input_increment*(smooth_control_period+1)/(float)smooth_count+input_last;  //smooth_control_period为全局变量
//    input_last=input;
//  return smooth_output;
//}
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


//void MotorControl()
//{
//    float casecade_pid_output=CasecadePid();
//    float other_pid_output=OtherPid();
//    float left_pwm=casecade_pid_output+other_pid_output;
//    float right_pwm=casecade_pid_output-other_pid_output;
//    MotorDrive(left_pwm,right_pwm);
//}

void SetMotorVoltage(float left_voltage, float right_voltage)
{
//    if(angle_data.fuse_angle_value>80||angle_data.fuse_angle_value<-80)//倒地保护，可注释掉
//  {
//    pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH3_C09,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0); 
//  }else
//  {
      if(left_voltage<0)
      {
        left_voltage=FastAbs(left_voltage);
        pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);
        pwm_duty_updata(TIM_2,TIM_2_CH2_A12,(int32)left_voltage);
      }else
      {
          pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(int32)left_voltage);
          pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
      }
      
      if(right_voltage<0)
      {
          right_voltage=FastAbs(right_voltage);
          pwm_duty_updata(TIM_2,TIM_2_CH3_C09,0);
          pwm_duty_updata(TIM_2,TIM_2_CH4_B11,(int32)right_voltage-1); 
      }else
      {
          pwm_duty_updata(TIM_2,TIM_2_CH3_C09,(int32)right_voltage+1);
          pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0); 
      }
//    }
  
  test_num++;
}

//void SetMotorVoltage(float left_voltage, float right_voltage)
//{
//    if(angle_data.fuse_angle_value>80||angle_data.fuse_angle_value<-80)//倒地保护，可注释掉
//  {
//    pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH3_C09,0);
//    pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0); 
//  }else
//  {
//      if(left_voltage<0)
//      {
//        left_voltage=FastAbs(left_voltage);
//          pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(int32)left_voltage);
//          pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
//      }else
//      {
//
//        pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);
//        pwm_duty_updata(TIM_2,TIM_2_CH2_A12,(int32)left_voltage);
//      }
//      
//      if(right_voltage<0)
//      {
//          right_voltage=FastAbs(right_voltage);
//          pwm_duty_updata(TIM_2,TIM_2_CH3_C09,(int32)right_voltage);
//          pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0); 
//
//      }else
//      {
//          pwm_duty_updata(TIM_2,TIM_2_CH3_C09,0);
//          pwm_duty_updata(TIM_2,TIM_2_CH4_B11,(int32)right_voltage); 
//
//      }
//    }
//  
//  test_num++;
//}

void MotorSpeedOut(void) {
    float left_val, right_val;
    left_val = left_motor_out;
    right_val = right_motor_out;
     
    if(left_val > 0) 
        left_val += MOTOR_OUT_DEAD_VAL;
    else if(left_val < 0) 
        left_val -= MOTOR_OUT_DEAD_VAL;
    if(right_val > 0) 
        right_val += MOTOR_OUT_DEAD_VAL;
    else if(right_val < 0) 
        right_val -= MOTOR_OUT_DEAD_VAL;
     
    if(left_val > MOTOR_OUT_MAX)
        left_val = MOTOR_OUT_MAX;
    if(left_val < MOTOR_OUT_MIN)
        left_val = MOTOR_OUT_MIN;
    if(right_val > MOTOR_OUT_MAX)
        right_val = MOTOR_OUT_MAX;
    if(right_val < MOTOR_OUT_MIN)
        right_val = MOTOR_OUT_MIN;
     
    SetMotorVoltage(left_val, right_val);
}

void MotorOutput(void) {
    float left, right;
    left = GyroControlOut +DirectionControlOut;
    right = GyroControlOut- DirectionControlOut;
    left_motor_out = left;
    right_motor_out = right;
    MotorSpeedOut();
}

void MotorTest()
{
    pwm_duty_updata(TIM_2,TIM_2_CH1_A11,500*20);
    pwm_duty_updata(TIM_2,TIM_2_CH2_A12,0);
    pwm_duty_updata(TIM_2,TIM_2_CH3_C09,500*20);
    pwm_duty_updata(TIM_2,TIM_2_CH4_B11,0); 

}

//-------------------------------------------------------------------------------------------------------------------
// @brief		????????
// @param		ch				???ADC???
// @param		resolution		??????????????(????????????????????????????? ???????????????????Ч)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//?????A00?ADC???? ??????8λ
//-------------------------------------------------------------------------------------------------------------------
//void TotalMotorDrive()
//{
//  MotorControl();
//}