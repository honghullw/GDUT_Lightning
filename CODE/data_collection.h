#ifndef __DATA_COLLECTION_H_
#define __DATA_COLLECTION_H_

#include "headfile.h"

#define inductance_num 5
#define sample_num 8
#define current_num 5
#define current_sample_num 5

#define pulse_speed_coefficient 5  //将脉冲数转m/s

#define Pi 3.14

#define FILTER_NUM 5

typedef struct
{
  
    float inductance_data[inductance_num][sample_num];//inductance_num个电感的数据
    float filter_inductance_data[inductance_num];//核心
    float inductance_normalization[inductance_num];
    
    float position_error;
    
    float current_loop_data[current_num][current_sample_num];
    float filter_current_loop_data[current_num];//核心
    

}a;

typedef struct 
{
  float left_wheel_pulse_num;
  float right_wheel_pulse_num;
  float wheel_pulse_num;//核心
  float car_speed;//只是看几米每秒，用不上(用于pid比较方便)
}b;

typedef struct
{
  int16 accelerate_x_data;      //加速度计的数据
  int16 accelerate_z_data;
  int16 accelarate_z_data;
  
  int16 angular_speed_x_data;    //角速度的数据     
  float angular_speed_y_data;
  int16 angular_speed_z_data;
  
  float angular_speed_y_filter_data;
  
  float accelerate_angle_value;         //加速度计的俯仰角值
  float angularspeed_angle_value;       //角速度的俯仰角值
  
  float fuse_angle_value;              //融合后的俯仰角值
  float fuse_angle_pid_value;          //用于pid的修正角度值
}c;

void InductanceData();
void SpeedData();
void AngleData();

void TotalDataCollection();


#endif