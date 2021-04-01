//
// Created by ºèðÀ on 2021-03-07.
//

#ifndef _FUZY_PID_H_
#define _FUZY_PID_H_

#include "headfile.h"



void FuzyPidInit();
void FuzyDomainWeight(float error,float error_rate);
void FuzyDomainWeightMerge();
float FuzyOutput();

#endif 
  