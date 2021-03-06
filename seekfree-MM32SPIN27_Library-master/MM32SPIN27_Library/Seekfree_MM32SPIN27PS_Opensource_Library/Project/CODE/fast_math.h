//
// Created by Lao·Zhu on 2021/1/25.
//

#ifndef _ALGORITHM_FAST_MATH_H_
#define _ALGORITHM_FAST_MATH_H_

#include "headfile.h"

#define PI              3.1415926f

#define FastCos(x)      FastSin(1.57079632679f - x)
#define FastTan(x)      FastSin(x) / FastSin(1.57079632679f - x)

#define FastMax(x, y)   (((x) > (y)) ? (x) : (y))
#define FastMin(x, y)   (((x) < (y)) ? (x) : (y))
#define FastAbs(x)      (((x) >= (0)) ? (x) : (-1 * x))

float FastSin(float theta);
float FastPow(float data, unsigned char pow);
float FastSqrt(float x);
unsigned short FloatToInt16(float data0);
float Int16ToFloat(unsigned short data0);

#endif //_ALGORITHM_FAST_MATH_H_
