#ifndef __DATA_COLLECTION_H_
#define __DATA_COLLECTION_H_

#include "headfile.h"

#define inductance_num 5
#define sample_num 5
#define current_num 5
#define current_sample_num 5

#define pulse_speed_coefficient 5  //将脉冲数转m/s

#define Pi 3.14

typedef struct
{
  
    double inductance_data[inductance_num][sample_num];//inductance_num个电感的数据
    double filter_inductance_data[inductance_num];//核心
    double inductance_normalization[inductance_num];
    
    double current_loop_data[current_num][current_sample_num];
    double filter_current_loop_data[current_num];//核心
    
//    double 
}a;

typedef struct 
{
  double left_wheel_pulse_num;
  double right_wheel_pulse_num;
  double wheel_pulse_num;//核心
  double car_speed;//只是看几米每秒，用不上(用于pid比较方便)
}b;

typedef struct
{
  int16 accelerate_x_data;      //加速度计的数据
  int16 accelerate_z_data;
  int16 accelarate_z_data;
  
  int16 angular_speed_x_data;    //角速度的数据     
  int16 angular_speed_y_data;
  int16 angular_speed_z_data;
  
  double accelerate_angle_value;         //加速度计的俯仰角值
  double angularspeed_angle_value;       //角速度的俯仰角值
  
  double fuse_angle_value;              //融合后的俯仰角值
  double fuse_angle_pid_value;          //用于pid的修正角度值
}c;

void InductanceData();
void SpeedData();
void AngleData();

void TotalDataCollection();


#endif