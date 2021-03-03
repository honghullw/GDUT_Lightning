#ifndef __HUMAN_COMPUTER_INTERACTION_H
#define __HUMAN_COMPUTER_INTERACTION_H
#include "headfile.h"

typedef struct{

  angle;//小车角度
  fixe_angle;//小车修正角度
  position;//小车离赛道中心的距离
  speed;//小车车速

}f;

void OledViewPhysicalCondition();
void OledViewParameters();
void OledViewCoefficient();

void Mode();



#endif 