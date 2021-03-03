#include "pid.h"



extern a data;
extern b speed_data;
extern c angle_data;
extern first_order_low_pass_filter_parameters first_filter1;

d pid_data;

e up_pid;
e speed_pid;
e direction_pid;
e current_pid;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      各个环pid参数初始化
//  @param      pid参数指针(&pid)
//  @return     output          返回pid计算出来的输出值
//  Sample usage:   用户直接调用即可
//-------------------------------------------------------------------------------------------------------------------
void PidInit() {
    //直立环(PD控制)
    up_pid.kp = 1;
    up_pid.ki = 0;
    up_pid.kd = 1;
    up_pid.actual_value = pid_data.angle;//角度实际值
    up_pid.goal_value = 0;//角度设定值
    up_pid.output_min = 0;
    up_pid.output_max = 0;


    //速度环
    speed_pid.kp = 1;
    speed_pid.ki = 0;
    speed_pid.kd = 1;
    speed_pid.actual_value = pid_data.speed;//脉冲数实际值
    speed_pid.goal_value = 0;//脉冲数设定值
    speed_pid.Integral_max = 0;
    speed_pid.output_max = 0;
    speed_pid.output_min = 0;

    //方向环
    direction_pid.kp = 1;
    direction_pid.ki = 0;
    direction_pid.kd = 1;
    
    direction_pid.actual_value = pid_data.inductance;//direction_pid.error;
    direction_pid.goal_value = pid_data.inductance;//0
//    direction_pid.error;
    
    direction_pid.Integral_max = 0;
    direction_pid.output_max = 0;
    direction_pid.output_min = 0;


    //电流环

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pid控制框架(输出的控制量都为正值)
//  @param      pid参数指针(&pid)
//  @return     output          返回pid计算出来的输出值
//  Sample usage:   用户直接调用即可
//-------------------------------------------------------------------------------------------------------------------
void PidControl(e pid) {
    pid.error = pid.goal_value - pid.actual_value;
    pid.error_last = pid.error;

    /*积分项的计算*/
    pid.Integral = pid.Integral + (float) (pid.error - pid.error_last) / (float) 2;             /*梯形积分的计算*/
    /*抗积分饱和算法*/                                 
    if (Ufabs(pid.Integral) > pid.Integral_max && pid.Integral > 0) {
        pid.Integral = pid.Integral_max;
    } else if (Ufabs(pid.Integral) > pid.Integral_max && pid.Integral < 0) {               /*积分饱和过冲时累加负项  */
        pid.Integral = -1.0f * pid.Integral_max;                                               /*可使积分项快速退出饱和区*/
    }

    /*微分项的计算*/
    pid.error = FirstLowFilter(first_filter1,pid.error);                                                      /*运用一阶RC低通滤波器*/

    pid.Differential = pid.error - pid.error_last;

    pid.output = (float) (pid.kp * pid.error + pid.ki * pid.Integral + pid.kd * pid.Differential);
    /*对pid输出量进行限幅*/
    if (pid.output > pid.output_max) {
        pid.output = pid.output_max;
    } else if (pid.output < pid.output_min) {
        pid.output = pid.output_min;
    }
}






