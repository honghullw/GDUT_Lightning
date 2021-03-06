#ifndef __OUTPUT_CONTROL_H_
#define __output_CONTROL_H_

#include "headfile.h"

void MotorControl();
void MotorDrive(uint32 motor1_duty_cycle,uint32 motor2_duty_cycle);

void TotalMotorDrive();


#endif