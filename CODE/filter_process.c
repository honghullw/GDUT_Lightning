#include "filter_process.h"



extern a data;
extern b speed_data;
extern c angle_data;

first_order_low_pass_filter_parameters first_filter1={0};

//-------------------------------------------------------------------------------------------------------------------
// @brief		中位值平均滤波法（又称防脉冲干扰平均滤波法）
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void MedianAverageFilter()
{
  uint16 i,j,k,n;
  double temp;
  for(i=0;i<inductance_num;i++)
  {
     for (j=0; j<inductance_num-1; j++)  //冒泡排序
    {
        for (k=0; k<inductance_num-1-j; k++) 
        {
			if (data.inductance_data[i][k] >data.inductance_data[i][k+1]) //从小到大
			{
				temp = data.inductance_data[i][k];
				data.inductance_data[i][k] = data.inductance_data[i][k+1];
				data.inductance_data[i][k+1] = temp;
			}
        }
    }
    for(n=1;n<sample_num-1;n++)//去头和尾
    {
    data.filter_inductance_data[i]+=data.inductance_data[i][n];
    }
    data.filter_inductance_data[i]/=(sample_num-2);
  }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		时间权重滤波法（不确定可不可行，可结合中位值平均滤波法（每个数据权重相同））
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
void TimeWeightFilter()
{
  uint16 i,j;
  float sum=0;
  float time_weight_array[]={10,9,8,7,6};//自己设定时间权重不要让计算机算（越后数据越新）
  for(i=0;i<sample_num;i++)
  {
    sum+=time_weight_array[i];
    
  }
  for(i=0;i<sample_num;i++)//归一化
  {
    time_weight_array[i]/=sum;
  }
  for(i=0;i<inductance_num;i++)
  {
    for(j=0;j<sample_num;j++)
    {
      data.inductance_data[i][j]*=time_weight_array[j];
    }
  }
  MedianAverageFilter();
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		一阶低通滤波(滤毛刺)
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------

float FirstLowFilter(first_order_low_pass_filter_parameters *filter,float data)
{
  filter->low_pass_parameter=0.3;
  filter->sample_data = data;
  filter->output_last = filter->output;
  
  filter->output = filter->low_pass_parameter * filter->sample_data
        + (1.0 - filter->low_pass_parameter) * filter->output_last;
  return filter->output;
    
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		角速度滤波
// @param		ch				选择ADC通道
// @param		resolution		选择选择通道分辨率(如果同一个模块初始化时设置了不同的分辨率 则第一个初始化的分辨率生效)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//初始化A00为ADC功能 分辨率为8位
//-------------------------------------------------------------------------------------------------------------------
//float AverageFilter()
//{
//  uint8 i;
//  for(i=0;i<FILTER_NUM;i++)
//  {
//    
//  }
//   
//}