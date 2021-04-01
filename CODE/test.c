#include "test.h"

int16 Gyro_Y_Zero = 3;
float Gyro_Speed_Y_Ratio = 0.00029386;
float Car_Gyro_Y = 0,Gyro_Speed_Y = 0,Ang_Gyro = 0,Gyro_Y = 0;


void Gyro_Ang_Caculate()
{
  int i;
  for(i=0;i<10;i++)
  {     
    get_icm20602_gyro_spi();
    Gyro_Y += icm_gyro_y;
  }
  Gyro_Y = Gyro_Y / 10;
  Car_Gyro_Y = (float)(Gyro_Y*1.0 - Gyro_Y_Zero);
  Gyro_Speed_Y = (float)(Car_Gyro_Y*Gyro_Speed_Y_Ratio);
  Ang_Gyro = (float)(Ang_Gyro + (float)(Gyro_Speed_Y));
}
