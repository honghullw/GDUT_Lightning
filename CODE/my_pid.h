#ifndef _MY_PID_H
#define _MY_PID_H

#include "headfile.h"

#define SPEED_P 0  //1
#define SPEED_I 0  //1
#define SPEED_D 0
#define ANGLE_P -45  //1
#define ANGLE_I 0
#define ANGLE_D 3  //1
#define GYRO_P -3 //1
#define GYRO_I -0.3   //1
#define GYRO_D 10
#define TURN_P 0
#define TURN_I 0
#define TURN_D 0

typedef struct{
  float P;
  float I;
  float D;
}PID;

float Speed_PID(float Speed_L,float Speed_R,float Speed_m);
float Angle_PID(float Angle_Data,float Angle_m,float balance_angle);
float Gyro_PID(float Gyro_Data,float Gyro_m);
float Turn_PID(float Speed_c,float Speed_m);
void SpeedControlOutput(void);
void AngleControlOutput(void);
void GyroControlOutput(void);
void DirectionControlOutput(void);

#endif