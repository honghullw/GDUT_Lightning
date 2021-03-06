#ifndef __HUMAN_COMPUTER_INTERACTION_H
#define __HUMAN_COMPUTER_INTERACTION_H
#include "headfile.h"

#define BM1 B8
#define BM2 B9
#define BM3 B6
#define BM4 B7

#define KEY1 C9
#define KEY2 C8
#define KEY3 C7
#define KEY4 C6



typedef struct
{

    float angle;//小车角度
    float fix_angle;//小车修正角度
    float position;//小车离赛道中心的距离
    float speed;//小车车速

}f;



void OledViewPhysicalCondition();
void OledViewParameters();
void OledViewCoefficient();

void Mode();



#endif 