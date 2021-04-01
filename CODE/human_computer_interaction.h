#ifndef __HUMAN_COMPUTER_INTERACTION_H
#define __HUMAN_COMPUTER_INTERACTION_H
#include "headfile.h"

#define BMST B6
#define BMND B7
#define BMRD B8
#define BMTH B9

#define KEY_UP B15
#define KEY_DOWN C8
#define KEY_RIGHT C7
#define KEY_LEFT C6

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
void OledViewSpecification();

#endif 