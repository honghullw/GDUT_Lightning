#ifndef __FIlTER_PROCESS_H_
#define __FIlTER_PROCESS_H_

#include "headfile.h"
/*一阶低通滤波参数*/

typedef struct {
    float low_pass_parameter;       //一阶低通滤波器滤波系数
    float sample_data;           //需要滤波的采样值
    float output;                   //当前滤波结果
    float output_last;              //上次滤波结果
} first_order_low_pass_filter_parameters;



void MedianAverageFilter();

void TimeWeightFilter();

float FirstLowFilter(first_order_low_pass_filter_parameters filter,float data);


#endif