//
// Created by 鸿鹄 on 2021-03-07.
//

#include "fuzy_pid.h"

//kp模糊控制
//1.确定基本论域
//1.1 误差基本论域
float error_basic_domain[7]={0};//误差输入基本论域//从小到大
float error_rate_basic_domain[7]={0};//误差变化率输入基本论域//从小到大
float output_basic_domain[7]={0};//kp输出基本论域
float output_basic_domain_weight[7]={0};
float error_fuzy_domain_weight[2]={0};//误差模糊论域权重
float error_rate_fuzy_domain_weight[2]={0};//误差变化率模糊论域权重

uint8 error_index;//误差索引
uint8 error_rate_index;//误差变化率索引


/*kp输出模糊论域*///将其变化到自然数便于存储对应数据//该论域值是随意取的，怎样方便怎么来，但一一对应关系不能变
#define KP_NL    0//负
#define KP_NM	 1//负
#define KP_NS	 2//负
#define KP_ZE	 3//0
#define KP_PS	 4//正
#define KP_PM	 5//正
#define KP_PL	 6//正

uint8 fuzy_rule_table_domain[7][7]={//kp模糊规则表
    KP_PL,	KP_PL,	KP_PM,	KP_PM,	KP_PS,	KP_PS,	KP_ZE,
    KP_PL,	KP_PL,	KP_PM,	KP_PM,	KP_PS,	KP_ZE,	KP_ZE,
    KP_PM,	KP_PM,	KP_PM,	KP_PS,	KP_ZE,	KP_NS,	KP_NM,
    KP_PM,	KP_PS,	KP_PS,	KP_ZE,	KP_NS,	KP_NM,	KP_NM,
    KP_PS,	KP_PS,	KP_ZE,	KP_NS,	KP_NS,	KP_NM,	KP_NM,
    KP_ZE,	KP_ZE,	KP_NS,	KP_NM,	KP_NM,	KP_NM,	KP_NL,
    KP_ZE,	KP_NS,	KP_NS,	KP_NM,	KP_NM,	KP_NL,	KP_NL
};


void FuzyPidInit()
{
//  error_basic_domain[7]={0};
//  error_rate_basic_domain[7]={0};
//  output_basic_domain[7]={0};
  uint8 a;
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		确定模糊论域元素权重(隶属度)//将基本论域映射到模糊论域上
// @param		ch				???ADC???
// @param		resolution		??????????????(????????????????????????????? ???????????????????Ч)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//?????A00?ADC???? ??????8λ
//-------------------------------------------------------------------------------------------------------------------
void FuzyDomainWeight(float error,float error_rate)
{
//    uint8 error_index,error_rate_index;
    /*误差索引*/
    if(error<=error_basic_domain[0])
    {
        error_index=0;//NS//用于之后去索引模糊规则表
        error_fuzy_domain_weight[0]=1;//暂时不确定是 error_fuzy_domain_weight[0]还是 error_fuzy_domain_weight[1]=1//确定了，是
    }else if(error<error_basic_domain[1])
    {
        error_index=0;//NS
        error_fuzy_domain_weight[0]=(error_basic_domain[1]-error)/(error_basic_domain[1]-error_basic_domain[0]);
    } else if (error<error_basic_domain[2])
    {
        error_index=1;//NM
        error_fuzy_domain_weight[0]=(error_basic_domain[2]-error)/(error_basic_domain[2]-error_basic_domain[1]);
    } else if (error<error_basic_domain[3])
    {
        error_index=2;//NB
        error_fuzy_domain_weight[0]=(error_basic_domain[3]-error)/(error_basic_domain[3]-error_basic_domain[2]);
    } else if (error<error_basic_domain[4])
    {
        error_index=3;//ZO
        error_fuzy_domain_weight[0]=(error_basic_domain[4]-error)/(error_basic_domain[4]-error_basic_domain[3]);
    } else if (error<error_basic_domain[5])
    {
        error_index=4;//PS
        error_fuzy_domain_weight[0]=(error_basic_domain[5]-error)/(error_basic_domain[5]-error_basic_domain[4]);
    } else if (error<error_basic_domain[6])
    {
        error_index=5;//PM
        error_fuzy_domain_weight[0]=(error_basic_domain[6]-error)/(error_basic_domain[6]-error_basic_domain[5]);
    } else
    {
        error_index=6;//PB
        error_fuzy_domain_weight[0]=1;
    }
    error_fuzy_domain_weight[1]=1-error_fuzy_domain_weight[0];


    /*误差变化率索引*/
    if(error_rate<=error_rate_basic_domain[0])
    {
        error_rate_index=0;//NS//用于之后去索引模糊规则表
        error_rate_fuzy_domain_weight[0]=1;//暂时不确定是 error_fuzy_domain_weight[0]还是 error_fuzy_domain_weight[1]=1//确定了，是
    }else if(error_rate<error_basic_domain[1])
    {
        error_rate_index=0;//NS
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[1]-error_rate)/(error_rate_basic_domain[1]-error_rate_basic_domain[0]);
    } else if (error_rate<error_rate_basic_domain[2])
    {
        error_rate_index=1;//NM
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[2]-error_rate)/(error_rate_basic_domain[2]-error_rate_basic_domain[1]);
    } else if (error_rate<error_rate_basic_domain[3])
    {
        error_rate_index=2;//NB
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[3]-error_rate)/(error_rate_basic_domain[3]-error_rate_basic_domain[2]);
    } else if (error_rate<error_rate_basic_domain[4])
    {
        error_rate_index=3;//ZO
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[4]-error_rate)/(error_rate_basic_domain[4]-error_rate_basic_domain[3]);
    } else if (error_rate<error_rate_basic_domain[5])
    {
        error_rate_index=4;//PS
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[5]-error_rate)/(error_rate_basic_domain[5]-error_rate_basic_domain[4]);
    } else if (error_rate<error_rate_basic_domain[6])
    {
        error_rate_index=5;//PM
        error_rate_fuzy_domain_weight[0]=(error_rate_basic_domain[6]-error_rate)/(error_rate_basic_domain[6]-error_rate_basic_domain[5]);
    } else
    {
        error_rate_index=6;//PB
        error_rate_fuzy_domain_weight[0]=1;
    }
    error_rate_fuzy_domain_weight[1]=1-error_rate_fuzy_domain_weight[0];
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		模糊论域权重合并（隶属度）
// @param		ch				???ADC???
// @param		resolution		??????????????(????????????????????????????? ???????????????????Ч)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//?????A00?ADC???? ??????8λ
//-------------------------------------------------------------------------------------------------------------------
void FuzyDomainWeightMerge()//由此可以看出输出模糊论域元素与输入模糊论域元素没有任何关系，可以随意选择，但要自己推理
{
  uint8 fuzy_element_index=0;
    fuzy_element_index=fuzy_rule_table_domain[error_index][error_rate_index];//左上
    output_basic_domain_weight[fuzy_element_index]+=error_fuzy_domain_weight[0]*error_rate_fuzy_domain_weight[0];//存储输出基本论域对应权重

    fuzy_element_index=fuzy_rule_table_domain[error_index+1][error_rate_index];//左下
    output_basic_domain_weight[fuzy_element_index]+=error_fuzy_domain_weight[1]*error_rate_fuzy_domain_weight[0];

    fuzy_element_index=fuzy_rule_table_domain[error_index][error_rate_index+1];//右上
    output_basic_domain_weight[fuzy_element_index]+=error_fuzy_domain_weight[0]*error_rate_fuzy_domain_weight[1];

    fuzy_element_index=fuzy_rule_table_domain[error_index+1][error_rate_index+1];//右下
    output_basic_domain_weight[fuzy_element_index]+=error_fuzy_domain_weight[1]*error_rate_fuzy_domain_weight[1];
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		输出基本论域加权并输出
// @param		ch				???ADC???
// @param		resolution		??????????????(????????????????????????????? ???????????????????Ч)
// @return		void
// Sample usage:				adc_init(ADC_1, ADC1_CH00_A00, ADC_8BIT);						//?????A00?ADC???? ??????8λ
//-------------------------------------------------------------------------------------------------------------------
float FuzyOutput()
{
    uint8 i;
    float fuzy_output;
    for (i=0;i<7;i++)
    {
        fuzy_output+=output_basic_domain_weight[i]*output_basic_domain[i];
    }
    return fuzy_output;
}