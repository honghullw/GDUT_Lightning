#ifndef __DATA_PROCESS_H_
#define __DATA_PROCESS_H_



#include "headfile.h"


#define zero_angular_speed_y_data 1.5//静态时绕y轴的角速度数据静误差
//#define change_angle_coefficient 10//角速度的角度数据转角度值系数(往加速度计的角度值去靠)
//#define complementary_coefficient 1//互补滤波系数



//#define complementary_coefficient 5//互补滤波系数


void InductanceData();
void AngularSpeedAngleCalculate();
void FuseAngleCalculate();
void ADCFilterProcess();
void InductanceProcess();
float DirectionErrorOutput1();
float DirectionErrorOutput2();

void TotalDataProcess();//数据处理总部分


#endif