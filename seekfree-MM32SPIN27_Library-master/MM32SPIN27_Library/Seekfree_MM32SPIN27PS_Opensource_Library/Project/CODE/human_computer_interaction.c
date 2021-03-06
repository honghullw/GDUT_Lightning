#include "human_computer_interaction.h"

f car_physical_condition;

extern a data;
extern b speed_data;
extern c angle_data;

extern c angle_data;
extern d  pid_data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;

extern PID Speed;
extern PID Angle;
extern PID Gyro;
extern PID Turn;

uint16 mode_flag;
uint16 interface_flag=0;



void human_computer_interaction_init()
{

    car_physical_condition.angle=angle_data.fuse_angle_value;
    car_physical_condition.fix_angle=angle_data.fuse_angle_pid_value;
    car_physical_condition.position=angle_data.fuse_angle_value;
    car_physical_condition.speed=speed_data.car_speed;

}


void OledViewSpecification()//告诉用户如何操作按一次按键换一个显示页面//拨码开关为0000时按键进入选择模式//说明与菜单//一级界面
{
    oled_p6x8str(0,0,"Specification");

    oled_p6x8str(0,2,"interface switch");
    oled_p6x8str(50,2,"0000");

    oled_p6x8str(0,2," ");
    oled_p6x8str(50,2,"0000");


}
/*---------------------------------------------------------------------------oled-------------------------------------------------------------------------------------------------*/
void OledViewPhysicalCondition()//二级界面
{

    oled_p6x8str(50,0,"Oled Physical Condition");

    oled_p6x8str(0,1,"Car Angle");
    oled_printf_float(50,1,car_physical_condition.angle,5,1);//输出小车俯仰角

    oled_p6x8str(0,2,"Car Fix Angle");
    oled_printf_float(50,2,car_physical_condition.fix_angle,5,1);//输出小车修正俯仰角

    oled_p6x8str(0,3,"Car Real Position");
    oled_printf_float(50,3,car_physical_condition.position,5,1);//小车距离赛道中心距离


    oled_p6x8str(0,4,"Car Speed");        //小车速度
    oled_printf_float(50,4,car_physical_condition.speed,5,1);

}


void OledViewParameters_f()//三级界面1
{

    oled_p6x8str(50,0,"Car Parameter");

    //角速度环pid参数
    oled_p6x8str(50,3,"Gyro Pid");

    oled_p6x8str(0,4,"kp");
    oled_printf_float(50,4,Gyro.P,5,1);//角速度P

    oled_p6x8str(0,5,"ki");
    oled_printf_float(50,5,Gyro.I,5,1);//角速度I

    oled_p6x8str(0,6,"kd");
    oled_printf_float(50,6,Gyro.D,5,1);//角速度D
    
    //角度环pid参数
    oled_p6x8str(50,8,"Angle Pid");

    oled_p6x8str(0,9,"kp");
    oled_printf_float(50,9,Angle.P,5,1);//角度P

    oled_p6x8str(0,10,"ki");
    oled_printf_float(50,10,Angle.I,5,1);//角度I

    oled_p6x8str(0,11,"kd");
    oled_printf_float(50,11,Angle.D,5,1);//角度D

}

void OledViewParameters_s()//三级界面2
{
    
    oled_p6x8str(50,0,"Car Parameter");
    //速度环pid参数
    oled_p6x8str(50,3,"Speed Pid");

    oled_p6x8str(0,4,"kp");
    oled_printf_float(50,9,Speed.P,5,1);//速度P

    oled_p6x8str(0,5,"ki");
    oled_printf_float(50,10,Speed.I,5,1);//速度I

    oled_p6x8str(0,6,"kd");
    oled_printf_float(50,11,Speed.D,5,1);//速度D

    //转向环pid参数
    oled_p6x8str(50,8,"Direction Pid");

    oled_p6x8str(0,9,"kp");
    oled_printf_float(50,9,Turn.P,5,1);//转向P

    oled_p6x8str(0,10,"ki");
    oled_printf_float(50,10,Turn.I,5,1);//转向I

    oled_p6x8str(0,11,"kd");
    oled_printf_float(50,11,Turn.D,5,1);//转向D

}    
    
//void OledViewCoefficient()//四级页面
//{
//    oled_p6x8str(50,0,"Coefficient");
//
//    oled_p6x8str(0,1,"zero_angular_speed_y_data");
//    oled_printf_float(50,1,zero_angular_speed_y_data,5,1);//转向P
//
//    oled_p6x8str(0,2,"change_angle_coefficient");
//    oled_printf_float(50,2,change_angle_coefficient,5,1);//转向I
//
//    oled_p6x8str(0,3,"complementary_coefficient");
//    oled_printf_float(50,3,complementary_coefficient,5,1);//转向D
//
//}



/*-----------------------------------------------------------------------------module------------------------------------------------------------------------------------------------*/
void Mode()//拨码开关改变模式
{
    oled_fill(0x00);
    if(gpio_get(BM1) == 0 &&
        gpio_get(BM2) == 0 &&
        gpio_get(BM3) == 0 &&
        gpio_get(BM4) == 0)
        mode_flag=0;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 0 &&
            gpio_get(BM3) == 0 &&
            gpio_get(BM4) == 1)
        mode_flag=1;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 0 &&
            gpio_get(BM3) == 1 &&
            gpio_get(BM4) == 0)
        mode_flag=2;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 0 &&
            gpio_get(BM3) == 1 &&
            gpio_get(BM4) == 1)
        mode_flag=3;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 1 &&
            gpio_get(BM3) == 0 &&
            gpio_get(BM4) == 0)
        mode_flag=4;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 1 &&
            gpio_get(BM3) == 0 &&
            gpio_get(BM4) == 1)
        mode_flag=5;
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 1 &&
            gpio_get(BM3) == 1 &&
            gpio_get(BM4) == 0)
        mode_flag=6;
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 1 &&
//            gpio_get(BM3) == 1 &&
//            gpio_get(BM4) == 1)
//        mode_flag=7;
//    else if
//        (gpio_get(BM1) == 1 &&
//            gpio_get(BM2) == 0 &&
//            gpio_get(BM3) == 0 &&
//            gpio_get(BM4) == 0)
//        mode_flag=8;
//    else if
//        (gpio_get(BM1) == 1 &&
//            gpio_get(BM2) == 0 &&
//            gpio_get(BM3) == 0 &&
//            gpio_get(BM4) == 1)
//        mode_flag=9;

    switch(mode_flag)
    {
        case 0:
            oled_fill(0x00);
            OledViewSpecification();//一级界面
            break;
            
        case 1:
            oled_fill(0x00);
            OledViewParameters_s();//二级界面
            break;
            
        case 2:
           oled_fill(0x00);
           if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                Gyro.P += 50;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                Gyro.P -= 50;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                Gyro.I += 5;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY4) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY4) == 1)
                Gyro.I -= 5;
                OledViewParameters_f();//三级界面1
            }
            break;
           
        case 3:
           oled_fill(0x00);
           if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                Angle.P += 50;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                Angle.P -= 50;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                Angle.D += 50;
                OledViewParameters_f();//三级界面1
            }
            if(gpio_get(KEY4) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY4) == 1)
                Angle.D -= 50;
                OledViewParameters_f();//三级界面1
            }
            break;
           
        case 4:
           oled_fill(0x00);
           if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                Speed.P += 50;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                Speed.P -= 50;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                Speed.I += 5;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY4) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY4) == 1)
                Speed.I -= 5;
                OledViewParameters_s();//三级界面2
            }
            break;
        
        case 5:
           oled_fill(0x00);
           if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                Turn.P += 50;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                Turn.P -= 50;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                Turn.D += 50;
                OledViewParameters_s();//三级界面2
            }
            if(gpio_get(KEY4) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY4) == 1)
                Turn.D -= 50;
                OledViewParameters_s();//三级界面2
            }
            break;

    }
}