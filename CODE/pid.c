#include "pid.h"



extern a data;
extern b speed_data;
extern c angle_data;
extern first_order_low_pass_filter_parameters first_filter1;

extern float balance_angle_value;

d pid_data;

e angularspeed_pid={0};
e up_pid={0};
e speed_pid={0};
e direction_pid={0};
e current_pid={0};

//-------------------------------------------------------------------------------------------------------------------
//  @brief      各个环pid参数初始化
//  @param      pid参数指针(&pid)
//  @return     output          返回pid计算出来的输出值
//  Sample usage:   用户直接调用即可
//-------------------------------------------------------------------------------------------------------------------
void PidInit() {

    //角速度环(PD控制)
//    angularspeed_pid.kp = -130;
//    angularspeed_pid.ki = -7;
  
      angularspeed_pid.kp = -50;//-219//-100可同时增大kp和ki直道调的很硬//kp过大小误差都会变成大抖动
    angularspeed_pid.ki = -20;//-15.6//-20加i回位效果好，但好像会有延时
  
  
//      angularspeed_pid.kp = -10;
//    angularspeed_pid.ki = -0.3;
    
    angularspeed_pid.kd = 0;
    angularspeed_pid.actual_value = 0;//角速度实际值//不能这样写，这样写只初始化了一次值
    angularspeed_pid.goal_value =0;//角速度设定值
    angularspeed_pid.output_min = -50000;
    angularspeed_pid.output_max = 50000;//速度环很容易超调//单限制这里无效
//    angularspeed_pid.Integral_max=50000; //饱和区可能过大
//    angularspeed_pid.Integral_min=-50000;  
//    
    angularspeed_pid.Integral_max=30000; //饱和区可能小//积分有回位效果，以复位后的值为原点，移动后会累计误差，最后回归原点
    angularspeed_pid.Integral_min=-30000;  
    
//        angularspeed_pid.Integral_max=50000; //饱和区可能过大
//    angularspeed_pid.Integral_min=-50000;  

    //直立环(PD控制)
//    up_pid.kp = -54;
//    up_pid.ki = 0;
//    up_pid.kd = 80;
    
//        up_pid.kp = -0.81;
//    up_pid.ki = 0;
//    up_pid.kd = 0.07;
    
//    up_pid.kp = -0.007;//不一定是这个，角度环可能还没调好
//    up_pid.ki = 0;
//    up_pid.kd = 0.004;
    
        up_pid.kp = -1.68;//不一定是这个，角度环可能还没调好
    up_pid.ki = 0;
    up_pid.kd = 0.15;
    
//     up_pid.kp = -40;
//    up_pid.ki = 0;
//    up_pid.kd = 25;
    
    up_pid.actual_value = 0;//角度实际值
    up_pid.goal_value = 0;//角度设定值
    up_pid.output_min = -50000;
    up_pid.output_max = 50000;
    up_pid.Integral_max=50000; 
    up_pid.Integral_min=-50000; 

    //速度环
//    speed_pid.kp = -0.000081;
//        speed_pid.ki = 0;
    
//        speed_pid.kp = -0.00131;
//        speed_pid.ki = 0;
    
            speed_pid.kp = -0.0021;
        speed_pid.ki = 0;
    
//        speed_pid.kp = -0.000081;//2021.3.24比较好
//    speed_pid.ki = -0.000081/200.0;
    
//            speed_pid.kp = -0.00081;
//    speed_pid.ki = -0.00081/200.0;
    
//            speed_pid.kp = -0.005;
//    speed_pid.ki = -0.005/200.0;
    speed_pid.kd = 0;
    speed_pid.actual_value = 0;//脉冲数实际值
    speed_pid.goal_value = 0;//脉冲数设定值
//    speed_pid.output_max = 2;
        speed_pid.output_max = 90;
//    speed_pid.output_max=0;
    
    
//    speed_pid.output_min = -8;
    
//        speed_pid.output_min = -25;
                speed_pid.output_min = -90;

//    speed_pid.Integral_max=4000; 
//    speed_pid.Integral_min=-4000;
    speed_pid.Integral_max=4000; 
    speed_pid.Integral_min=-4000;

    //方向环
//    direction_pid.kp = -60;
//    direction_pid.ki = 0;
//    direction_pid.kd = 3;
    
        direction_pid.kp = 0;
    direction_pid.ki = 0;
    direction_pid.kd = 0;
    
    direction_pid.actual_value = 0;//direction_pid.error;
    direction_pid.goal_value = 0;//0
//    direction_pid.error;
    
    direction_pid.Integral_max = 0;
    direction_pid.output_max = 30000;
    direction_pid.output_min = -30000;


    //电流环

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pid控制框架
//  @param      pid参数指针(&pid)
//  @return     output          返回pid计算出来的输出值
//  Sample usage:   用户直接调用即可
//-------------------------------------------------------------------------------------------------------------------
//float PidControl(e pid) {
//    pid.error_last = pid.error;
//    pid.error = pid.goal_value - pid.actual_value;
//
//    /*积分项的计算*/
//    pid.Integral = pid.Integral + (float) (pid.error - pid.error_last) / (float) 2;             /*梯形积分的计算*/
//    /*抗积分饱和算法*/                                 
//    if (FastAbs(pid.Integral) > pid.Integral_max && pid.Integral > 0) {
//        pid.Integral = pid.Integral_max;
//    } else if (FastAbs(pid.Integral) > pid.Integral_max && pid.Integral < 0) {               /*积分饱和过冲时累加负项  */
//        pid.Integral = -1.0f * pid.Integral_max;                                               /*可使积分项快速退出饱和区*/
//    }
//
//    /*微分项的计算*/
//    pid.error = FirstLowFilter(first_filter1,pid.error);                                                      /*运用一阶RC低通滤波器*/
//
//    pid.Differential = pid.error - pid.error_last;
//
//    pid.output = (float) (pid.kp * pid.error + pid.ki * pid.Integral + pid.kd * pid.Differential);
//    /*对pid输出量进行限幅*/
//    if (pid.output > pid.output_max) {
//        pid.output = pid.output_max;
//    } else if (pid.output < pid.output_min) {
//        pid.output = pid.output_min;
//    }
//    return pid.output;
//}

float PidControl(e *pid) {

    pid->error = pid->goal_value - pid->actual_value;
//
//    /*积分项的计算*/
    pid->Integral = pid->Integral + (float) (pid->error + pid->error_last) / (float) 2;             /*梯形积分的计算*///感觉梯形积分写错了
//    /*抗积分饱和算法*/                                 
//    if (FastAbs(pid->Integral) > pid->Integral_max && pid->Integral > 0) {
//        pid->Integral = pid->Integral_max;
//    } else if (FastAbs(pid->Integral) > pid->Integral_max && pid->Integral < 0) {               /*积分饱和过冲时只累加负项  */
//        pid->Integral = -1.0f * pid->Integral_max;                                               /*可使积分项快速退出饱和区*/
//    }
//
//    /*微分项的计算*/
////    pid->error = FirstLowFilter(first_filter1,pid.error);                                                      /*运用一阶RC低通滤波器*/
//
//    pid->Differential = pid->error - pid->error_last;
//
//    pid->output = (float) (pid->kp * pid->error + pid->ki * pid->Integral + pid->kd * pid->Differential);
//    /*对pid输出量进行限幅*/
//    if (pid->output > pid->output_max) {
//        pid->output = pid->output_max;
//    } else if (pid->output < pid->output_min) {
//        pid->output = pid->output_min;
//    }
//    
//    pid->error_last = pid->error;
//    
//    return pid->output;
  
//      pid->error = pid->goal_value - pid->actual_value;

//    /*积分项的计算*/
//    pid->Integral +=pid->error;            /*梯形积分的计算*/
    /*抗积分饱和算法*/                                 
    if (pid->Integral> pid->Integral_max ) {
        pid->Integral = pid->Integral_max;
    } else if (pid->Integral< pid->Integral_min ) {               /*积分饱和过冲时只累加负项  */
        pid->Integral = pid->Integral_min;                                               /*可使积分项快速退出饱和区*/
    }
    

    /*微分项的计算*/
    pid->error_low = FirstLowFilter(&first_filter1,pid->error);                                                      /*运用一阶RC低通滤波器*/

    pid->Differential = pid->error_low - pid->error_last_low;

    pid->output = (float) (pid->kp * pid->error + pid->ki * pid->Integral + pid->kd * pid->Differential);
    /*对pid输出量进行限幅*/
    if (pid->output > pid->output_max) {
        pid->output = pid->output_max;
    } else if (pid->output < pid->output_min) {
        pid->output = pid->output_min;
    }
    
    pid->error_last = pid->error;
    pid->error_last_low=pid->error_low;
    
    return pid->output;
}

float CasecadePid()
{
//串级pid函数式//笔推
float casecade_pid_output=PidControl(&angularspeed_pid)+angularspeed_pid.kp*PidControl(&up_pid)+angularspeed_pid.kp*up_pid.kp*PidControl(&speed_pid);
    return casecade_pid_output;
}


float OtherPid()
{
    return PidControl(&direction_pid);
}


/*---------------------------------------------------模糊pid-----------------------------------------------------------------------*/


