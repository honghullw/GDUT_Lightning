#ifndef __PID_H_
#define __PID_H_

#include "headfile.h"



typedef struct 
{
  //直立
  //速度
  //转向
  double inductance;
  
  double speed;
    
  double angle;
}d;


typedef struct 
{
    float kp, ki, kd;
    float error;                            //当前误差(current error)
    float error_last;                          //上次的误差(last current)
    float goal_value;                       //预期值
    float actual_value;                     //当前值
    float output;                           //pid计算后最终的输出值
    float output_max, output_min;           //输出值的最大/最小值
    float Integral_max;                     //积分项所能累加的最大值(warining:该值应该设为正值)
    float Integral;                         //积分项I
    float Differential;                     //微分项D
}e;

float PidControl();
float CasecadePidOutput(void);
float OtherPidOutput(void);

#endif