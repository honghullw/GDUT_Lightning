#include "data_collection.h"

a data = {0};
b speed_data = {0};
c angle_data = {0};
 
extern e angularspeed_pid;
extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;

//float balance_angle_value=-1.6;
float balance_angle_value=32;//加电感后机械零点//28.5

float change_angle_coefficient=0.028;//角速度的角度数据转角度值系数(往加速度计的角度值去靠)//2000/32768

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC电感数据采集
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void InductanceData()
  {
    uint16 i=0;
    for(;i<sample_num;i++)
    {
      data.inductance_data[0][i]=adc_convert(ADC_1,ADC1_CH02_A02);
      data.inductance_data[1][i]=adc_convert(ADC_1,ADC1_CH03_A03);
      data.inductance_data[2][i]=adc_convert(ADC_1,ADC1_CH05_A05);
      data.inductance_data[3][i]=adc_convert(ADC_1,ADC1_CH06_A06);
      data.inductance_data[4][i]=adc_convert(ADC_1,ADC1_CH07_A07);
    }
  }

//-------------------------------------------------------------------------------------------------------------------
// @brief		编码器数据采集（放入1ms的周期中断内）
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void SpeedData()
  {
    speed_data.left_wheel_pulse_num=tim_encoder_get_count(TIM_1);//是等号还是加等号暂时还不懂
    tim_encoder_rst(TIM_1);//清除计数值
    speed_data.right_wheel_pulse_num=-tim_encoder_get_count(TIM_8);
    tim_encoder_rst(TIM_8);//清除计数值
    speed_data.wheel_pulse_num=(speed_data.left_wheel_pulse_num+speed_data.right_wheel_pulse_num)/2;
    speed_data.car_speed=speed_data.wheel_pulse_num*pulse_speed_coefficient;
//        int32 i,i1,j,j1;
//    for(i=0,i1=0;i<3;i++){
//        i1+=tim_encoder_get_count(TIM_1);//是等号还是加等号暂时还不懂
//        tim_encoder_rst(TIM_1);//清除计数值
//    }
//    speed_data.left_wheel_pulse_num=i1/3;
//    for(j=0,j1=0;j<3;j++){
//        j1+=(-tim_encoder_get_count(TIM_8));
//        tim_encoder_rst(TIM_8);//清除计数值
//    }
//    speed_data.right_wheel_pulse_num=j1/3;
//    speed_data.wheel_pulse_num=(speed_data.left_wheel_pulse_num+speed_data.right_wheel_pulse_num)/2;
//    speed_data.car_speed=speed_data.wheel_pulse_num*pulse_speed_coefficient;
    
  }

//-------------------------------------------------------------------------------------------------------------------
// @brief		角度数据采集（使用I^2C）
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void AngleData()
  {
    uint8 i;
    get_icm20602_accdata_spi();//获取全局加速度数据

    
    //加速度处理(选取两个轴两个轴都在垂直小车轮轴平面上)（由安装方向决定）(这里规定了小车完全垂直地面时陀螺仪x轴为小车前进后退方向，z轴为垂直地面方向)
    angle_data.accelerate_x_data=icm_acc_x;
    angle_data.accelerate_z_data=icm_acc_z;
    angle_data.accelerate_angle_value=(180/Pi)*atan2(angle_data.accelerate_x_data,angle_data.accelerate_z_data);
      
      //角速度处理（陀螺仪积分仅使用一个轴（该轴平行于轮轴），小车俯仰时绕该轴的角速度（度/s））(这里规定了小车完全垂直地面时陀螺仪y轴为小车轮轴)
    
    
  for(i=0;i<FILTER_NUM;i++)
  {
        get_icm20602_gyro_spi();//获取全局陀螺仪数据
        angle_data.angular_speed_y_filter_data+=icm_gyro_y;
  }
  angle_data.angular_speed_y_filter_data/=FILTER_NUM;
  angle_data.angular_speed_y_data=angle_data.angular_speed_y_filter_data*change_angle_coefficient;
    
    

    AngularSpeedAngleCalculate();
    FuseAngleCalculate();
    
//        int32 i,i1,i2,i3;
//    for(i=0,i1=0,i2=0,i3=0;i<3;i++){
//        get_icm20602_accdata_spi();//获取全局加速度数据
//        get_icm20602_gyro_spi();//获取全局陀螺仪数据
//        i1+=icm_acc_x;
//        i2+=icm_acc_z;
//        i3+=icm_gyro_y;
//    }
//    angle_data.accelerate_x_data=i1/3;
//    angle_data.accelerate_z_data=i2/3;
//    angle_data.angular_speed_y_data=i3/3;
//    angle_data.accelerate_angle_value=(180/Pi)*atan2(angle_data.accelerate_x_data,angle_data.accelerate_z_data);   
//    AngularSpeedAngleCalculate();
//    FuseAngleCalculate();
    

    
     //角度限幅（防止一些奇奇怪怪的问题让角度值不在[-90,90]内）
//      if(angle_data.fuse_angle_value>90)
//      {
//        angle_data.fuse_angle_value=90;
//      }
//      if(angle_data.fuse_angle_value<-90)
//      {
//        angle_data.fuse_angle_value=-90;  
//      }
  }

//-------------------------------------------------------------------------------------------------------------------
// @brief		总信息采集
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void TotalDataCollection()
{
  InductanceData();
  SpeedData();
  AngleData();
}