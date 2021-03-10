#include "element_process.h"

  float peak_value;
  float sum_value;
  float element_flag;//1为识别弯道，2为识别十字，3为识别弯道

  extern a data;
  
void Element()//赛道元素特征提取函数
{
  uint16 get_data_num=3;
  uint16 i,j,k;
  while(get_data_num--){//连续三次检测防止在某些非该元素的特定点也符合元素的一定特征
    
//    /*----------------环岛----------------*/
//    
//    //采集圆环ADC最大值//用手推
//    
//    
//      sum_value=inductance_normalization[0]+inductance_normalization[2]+inductance_normalization[4]//只有归一化后才能相加减
//    
//      //方案一一
//  //  peak_value=(peak_value<sum_value?sum_value:sum_value)//存储环岛峰值，用于出环岛标志消除
//      
//      //方案一二  
//      peak_value=(peak_value<?sum_value:sum_value)//存储环岛峰值，用于出环岛标志消除
//    
//    if(peak_value>MAX1)
//      element_flag=1;
//      continue
//    
//    
//    /*----------------十字----------------*/
//    
//    //竖直电感采集十字ADC最大值//用手推//需要连续数次得到数理后的数据，要求所有数据都大于一定值，防止某些特定点会使电感值过大////加上中间电感在一定范围内即可
//    
//    if(data.inductance_normalization[1]>CROSS_MAX&&data.inductance_noramlization[3]>CROSS_MAX&&CROSS_SPECIAL_SCOPE_MAX>data.filter_inductance_data[2]>CROSS_SPECIAL_SCOPE_MIN)
//      element_flag=2;
//    
//    
//    /*----------------坡道----------------*/
//    //中间水平电感检测大于坡道值，并且两竖直电感小于某坡道值
//    if(data.inductance_normalization[2]>RAMP_MAX&&data.inductance_normalization[1]<RAMP_MIN&&data.RAMP_MINinductance_normalization[2]<RAMP_MIN)
//      element_flag=3
//      
//        /*----------------三岔----------------*///先不考虑
//    
//    if(data)  
//      
//      
    
    
    
        /*----------------环岛----------------*/
    
    //采集圆环ADC最大值//用手推
    
    

      peak_value=(peak_value<data.inductance_normalization[2]?data.inductance_normalization[2]:peak_value);//存储环岛峰值，用于出环岛标志消除
    
    if(peak_value>MAX1)
      i++;
    else if(data.inductance_normalization[1]>CROSS_MAX&&data.inductance_normalization[3]>CROSS_MAX&&CROSS_SPECIAL_SCOPE_MAX>data.filter_inductance_data[2]>CROSS_SPECIAL_SCOPE_MIN)
      j++;
    else if(data.inductance_normalization[2]>RAMP_MAX&&data.inductance_normalization[1]<RAMP_MIN&&data.inductance_normalization[2]<RAMP_MIN)
      k++;
  }
  if(i==3)
    element_flag=1;
  else if(j==3)
    element_flag=2;
  else if(k==3)
    element_flag=3;
}


void RoundaboutProcess()
{ 

  //判断出两倍标志位后启动陀螺仪Z轴积分
  
  //切换两个竖直电感打角进环岛
  
  
  
  //切换三个水平电感环岛转弯


  //陀螺仪z轴积分到360度消除环岛标志


}

void CrossProcess()
{ 

  


}

void RampProcess()
{ 
  
  //方案一
  //只用三水平电感直接过

}

void  RoadJunctionProcess()
{
  //暂时没想法
}

//void Element_Mode()//实时运行
//{
//  switch(element_flag)
//    case 0:
//      
//
//
//}