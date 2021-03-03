#include "data_process.h"
double inductance_data_max[5]={1,1,1,1,1};


extern a data;
extern b speed_data;
extern c angle_data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;
//-------------------------------------------------------------------------------------------------------------------
// @brief		角度数据处理
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void AngularSpeedAngleCalculate(){
  
  angle_data.angular_speed_y_data-=zero_angular_speed_y_data;//消除角速度的角度数据静态误差
  angle_data.angularspeed_angle_value=angle_data.angularspeed_angle_value+angle_data.angular_speed_y_data*change_angle_coefficient;//积分不用单独乘时间差了，时间差已经暗含在周期中断里了

}


//-------------------------------------------------------------------------------------------------------------------
// @brief		互补滤波(融合角)
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void FuseAngleCalculate(){

angle_data.angularspeed_angle_value=angle_data.angularspeed_angle_value+(angle_data.accelerate_angle_value-angle_data.angularspeed_angle_value)*complementary_coefficient;//利用误差修复角速度的角度值
angle_data.fuse_angle_value=angle_data.angularspeed_angle_value;//修复后的角速度的角度值就是融合角的值
angle_data.fuse_angle_pid_value=angle_data.fuse_angle_value-balance_angle_value;//使得平衡位置的角度为0//用于pid计算

}




//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void ADCFilterProcess()
{
  MedianAverageFilter();//中位值平均滤波
//  TimeWeightFilter();//时间权重滤波

}



//-------------------------------------------------------------------------------------------------------------------
// @brief		电感数据归一化处理（不同电感性能是不一样的，无法直接比较，所以每个电感要各自归一化）
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void InductanceProcess(){
  uint16 i=0;
  for(;i<inductance_num;i++)
  {
     data.inductance_normalization[i]=data.filter_inductance_data[i]/inductance_data_max[i];//实时电感值/(电感最大值-电感最小值)
     if(data.inductance_normalization[i]<=0.001)
     {
      data.inductance_normalization[i]=0.001;
     }
  }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		差比和(关键是找出线性关系)
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void DirectionErrorOutput1()
{
  direction_pid.actual_value=
  ((data.inductance_normalization[0]-data.inductance_normalization[2])/(data.inductance_normalization[0]+data.inductance_normalization[2])+data.inductance_normalization[1])/2;//用误差当作当前值
      
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		比值法(关键是找出线性关系)
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void DirectionErrorOutput2()
{
  direction_pid.actual_value=
    abs((sqrt(data.inductance_normalization[0])-sqrt(data.inductance_normalization[2]))/(data.inductance_normalization[0]+data.inductance_normalization[2]));
      
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		比值法(关键是找出线性关系)
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void DirectionErrorOutput3()
{
  direction_pid.actual_value=
    //师兄方法用四个电感进行误差计算
      
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		总数据处理
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void TotalDataProcess()
{
  AngularSpeedAngleCalculate();
  FuseAngleCalculate();
  ADCFilterProcess();
  InductanceProcess();
  DirectionErrorOutput1();//差比和
//  DirectionErrorOutput2();//比值法
}