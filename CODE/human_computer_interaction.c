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



uint16 mode_flag;
uint16 interface_flag=0;



void human_computer_interaction_init()
{

    car_physical_condition.angle=angle_data.fuse_angle_value;
    car_physical_condition.fix_angle=angle_data.fuse_angle_pid_value;
    car_physical_condition.position=angle_data.fuse_angle_value;
    car_physical_condition.speed=speed_data.car_speed;

}


void OledViewSpecification()//告诉用户如何操作按一次按键换一个显示页面//拨码开关为0000时按键进入选择模式//说明与菜单
{
    oled_p6x8str(0,0,"Specification");

    oled_p6x8str(0,2,"interface switch");
    oled_p6x8str(50,2,"0000");

    oled_p6x8str(0,2," ");
    oled_p6x8str(50,2,"0000");


}
/*---------------------------------------------------------------------------oled-------------------------------------------------------------------------------------------------*/
void OledViewPhysicalCondition()//一级界面
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


void OledViewParameters()//二级界面
{

    oled_p6x8str(50,0,"Car Parameter");

    //直立pid参数
    oled_p6x8str(50,3,"Up Pid");

    oled_p6x8str(0,4,"kp");
    oled_printf_float(50,4,up_pid.kp,5,1);//直立P

    oled_p6x8str(0,5,"ki");
    oled_printf_float(50,5,up_pid.ki,5,1);//直立I

    oled_p6x8str(0,6,"kd");
    oled_printf_float(50,6,up_pid.kd,5,1);//直立D


    //速度pid参数
    oled_p6x8str(50, 8,"Up Pid");

    oled_p6x8str(0,8,"kp");
    oled_printf_float(50,9,speed_pid.kp,5,1);//速度P

    oled_p6x8str(0,10,"ki");
    oled_printf_float(50,10,speed_pid.ki,5,1);//速度I

    oled_p6x8str(0,11,"kd");
    oled_printf_float(50,11,speed_pid.kd,5,1);//速度D

    //转向pid参数
    oled_p6x8str(50,13,"Up Pid");

    oled_p6x8str(0,14,"kp");
    oled_printf_float(50,14,direction_pid.kp,5,1);//转向P

    oled_p6x8str(0,15,"ki");
    oled_printf_float(50,15,direction_pid.ki,5,1);//转向I

    oled_p6x8str(0,16,"kd");
    oled_printf_float(50,16,direction_pid.kd,5,1);//转向D

}

void OledViewCoefficient()//三级页面
{
    oled_p6x8str(50,0,"Coefficient");

    oled_p6x8str(0,1,"zero_angular_speed_y_data");
    oled_printf_float(50,1,zero_angular_speed_y_data,5,1);//转向P

    oled_p6x8str(0,2,"change_angle_coefficient");
    oled_printf_float(50,2,change_angle_coefficient,5,1);//转向I

    oled_p6x8str(0,3,"complementary_coefficient");
    oled_printf_float(50,3,complementary_coefficient,5,1);//转向D

}



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
    else if
        (gpio_get(BM1) == 0 &&
            gpio_get(BM2) == 1 &&
            gpio_get(BM3) == 1 &&
            gpio_get(BM4) == 1)
        mode_flag=7;
    else if
        (gpio_get(BM1) == 1 &&
            gpio_get(BM2) == 0 &&
            gpio_get(BM3) == 0 &&
            gpio_get(BM4) == 0)
        mode_flag=8;
    else if
        (gpio_get(BM1) == 1 &&
            gpio_get(BM2) == 0 &&
            gpio_get(BM3) == 0 &&
            gpio_get(BM4) == 1)
        mode_flag=9;

    switch(mode_flag)
    {
        case 0:

            if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                    interface_flag=1;//界面flag
                OledViewSpecification();//一级界面
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                    interface_flag=2;//界面flag
                OledViewPhysicalCondition();//二级界面
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                    interface_flag=3;//界面flag
                OledViewParameters();//三级界面
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                    interface_flag=4;//界面flag
                OledViewCoefficient();//四级界面
            }
            break;
        case 1:
            switch(interface_flag)
                case 1:
                    OledViewSpecification();//一级界面
                    break;
                case 2:
                    OledViewPhysicalCondition();
                    break;
                case 3:
                    OledViewParameters();//三级界面
                    break;
                case 4:
                    OledViewCoefficient();//四级界面
                    break;
            if(gpio_get(KEY1) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY1) == 1)
                  OledViewSpecification();
            }
            if(gpio_get(KEY2) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY2) == 1)
                    OledViewPhysicalCondition();//二级界面
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                    OledViewParameters();//三级界面
            }
            if(gpio_get(KEY3) == 1)
            {
                systick_delay_ms(100);
                if(gpio_get(KEY3) == 1)
                    OledViewCoefficient();//四级界面
            }
            break;

    }
}