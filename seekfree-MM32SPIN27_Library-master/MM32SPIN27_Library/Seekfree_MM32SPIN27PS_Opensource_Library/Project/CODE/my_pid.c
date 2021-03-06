#include "my_pid.h"

float LeftMotorOut;
float RightMotorOut;

struct PID Speed={SPEED_P,SPEED_I,SPEED_D},Angle={ANGLE_P,ANGLE_I,ANGLE_D},Gyro={GYRO_P,GYRO_I,GYRO_D},Turn={TURN_P,TURN_I,TURN_D};

extern e direction_pid;
 
first_order_low_pass_filter_parameters Car_Data = {0,0,0,0};

//速度环——位置式PID
//Speed_L——左轮的速度
//Speed_R——右轮的速度
//Speed_m——设定的目标速度
float Speed_PID(float Speed_L,float Speed_R,float Speed_m)
{
      static float Speed_Error_Integral;
      float Speed_Error,Realize,Speed_New;

      //计算左右电机的平均速度
      Speed_New = (Speed_L + Speed_R)/2;
      
      //偏差计算
      Speed_Error = Speed_m - Speed_New;
      
      //积分的计算
      Speed_Error_Integral+= Speed_Error;
      if(Speed_Error_Integral>=4000) Speed_Error_Integral=4000;
      if(Speed_Error_Integral<=-4000) Speed_Error_Integral=-4000;
      
      Realize = Speed.P * Speed_Error + Speed_Error_Integral* Speed.I;
      
      if(Realize>30) Realize=30;
      if(Realize<-30) Realize=-30;
      
      return Realize;
}

//角度环——位置式PID
//Angle_Data——互补滤波计算出的实际角度
//Angle_m——速度环的输出，作为角度环的一个输入
//balance_angle——小车自身的机械平衡角度
float Angle_PID(float Angle_Data,float Angle_m,float balance_angle)
{
      static float Angle_Error_Least;
      float Angle_Error,Realize;
      
      //偏差计算
      Angle_Error = Angle_m - Angle_Data - balance_angle;
      
      Realize = Angle.P * Angle_Error + Angle.D * (Angle_Error - Angle_Error_Least);
      
      //更新上一次的偏差
      Angle_Error_Least = Angle_Error;
      
      return Realize;
}

//角速度环----位置式PID
//Gyro_Data——陀螺仪获取的自身实际角速度、
//Gyro_m——角度环输出的值，作为角速度环的输入
float Gyro_PID(float Gyro_Data,float Gyro_m)
{
      static float Gyro_Error_Count;
      float Realize,Gyro_Error;
      
      //偏差计算
      Gyro_Error = Gyro_m - Gyro_Data;
      
      //积分
      Gyro_Error_Count += Gyro_Error;
      
      //积分饱和限幅
      if(Gyro_Error_Count>10000) Gyro_Error_Count=10000;
      else if(Gyro_Error_Count<-10000) Gyro_Error_Count=-10000;
      
      //位置PID计算
      Realize = Gyro.P * Gyro_Error +  Gyro.I * Gyro_Error_Count;
     
      return Realize;
}

//转向环
float Turn_PID(float Speed_c,float Speed_m)
{
      float Turn_Offset,Gyro_Ratio1,Car_Gyro_Y,DireControlOutNew;
      Car_Gyro_Y = icm_gyro_y;
      Turn_Offset = direction_pid.actual_value;
      Gyro_Ratio1 = Car_Gyro_Y*Car_Gyro_Y/4000000+5.0;
      Car_Data.low_pass_parameter = 0.7;
      Car_Data.output_last = Gyro_Ratio1;
      Gyro_Ratio1 = FirstLowFilter(Car_Data,Gyro_Ratio1);
      DireControlOutNew = (Speed_c*Speed_c/(Speed_m*Speed_m)+1)*Turn_Offset*Turn.P+Gyro_Ratio1*Car_Gyro_Y*Turn.D;
      return DireControlOutNew;
}

//电机输出
void MotorOutput(float Gyro_Out,float Turn_Out) 
{
      float Left, Right;
      Left = Gyro_Out - Turn_Out;
      Right = Gyro_Out + Turn_Out;
      MotorDrive(Left,Right);
}