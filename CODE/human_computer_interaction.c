#include "human_computer_interaction.h"
//#include "test.h"

f car_physical_condition;

extern a data;
extern b speed_data;
//extern c angle_data;
//
//extern c angle_data;
extern d  pid_data;

extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;

extern first_order_low_pass_filter_parameters first_filter1;

uint16 mode_flag;
uint16 interface_flag=0;//页面标志位

//按键状态
uint16 key_up_state;
uint16 key_down_state;
uint16 key_right_state;
uint16 key_left_state;



void human_computer_interaction_init()
{

//    car_physical_condition.angle=angle_data.fuse_angle_value;
//    car_physical_condition.fix_angle=angle_data.fuse_angle_pid_value;
//    car_physical_condition.position=angle_data.fuse_angle_value;
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

    oled_p6x8str(10,0,"Physical Condition");
//
    oled_p6x8str(20,1,"Car Inductance");
    oled_printf_float(0,2,data.filter_inductance_data[0],5,1);//输出小车电感
    oled_printf_float(25,2,data.filter_inductance_data[1],5,1);//输出小车电感
    oled_printf_float(50,2,data.filter_inductance_data[2],5,1);//输出小车电感
    oled_printf_float(75,2,data.filter_inductance_data[3],5,1);//输出小车电感
    oled_printf_float(100,2,data.filter_inductance_data[4],5,1);//输出小车电感

    oled_p6x8str(30,3,"Car Error");
    oled_printf_float(0,4,data.position_error,5,1);

    oled_p6x8str(30,5,"Car Speed");
    oled_p6x8str(0,6,"L_Enc");
    oled_printf_float(30,6,speed_data.left_wheel_pulse_num,5,1);
    oled_p6x8str(0,7,"R_Enc");
    oled_printf_float(30,7,speed_data.right_wheel_pulse_num,5,1);


//    oled_p6x8str(10,0,"mode flag");
//    oled_uint16(10,1,mode_flag);

//
//    oled_p6x8str(0,2,"Car Fix Angle");
//    oled_printf_float(50,2,car_physical_condition.fix_angle,5,1);//输出小车修正俯仰角
//
//    oled_p6x8str(0,3,"Car Real Position");
//    oled_printf_float(50,3,car_physical_condition.position,5,1);//小车距离赛道中心距离
//
//
//    oled_p6x8str(0,4,"Car Speed");        //小车速度
//    oled_printf_float(50,4,car_physical_condition.speed,5,1);

}


void OledViewParameters()//二级界面
{

    oled_p6x8str(30,0,"Car Parameter");

//    //直立pid参数
//    oled_p6x8str(50,3,"Up Pid");
//
//    oled_p6x8str(0,4,"kp");
//    oled_printf_float(50,4,up_pid.kp,5,1);//直立P
//
//    oled_p6x8str(0,5,"ki");
//    oled_printf_float(50,5,up_pid.ki,5,1);//直立I
//
//    oled_p6x8str(0,6,"kd");
//    oled_printf_float(50,6,up_pid.kd,5,1);//直立D


    //速度pid参数
    oled_p6x8str(30,1,"Speed Pid");

    oled_p6x8str(0,2,"kp");
    oled_printf_float(50,2,speed_pid.kp,5,1);//速度P

    oled_p6x8str(0,3,"ki");
    oled_printf_float(50,3,speed_pid.ki,5,1);//速度I

//    oled_p6x8str(0,4,"kd");
//    oled_printf_float(50,4,speed_pid.kd,5,1);//速度D

    //转向pid参数
    oled_p6x8str(30,5,"Direction Pid");

    oled_p6x8str(0,6,"kp");
    oled_printf_float(50,6,direction_pid.kp,5,1);//转向P

//    oled_p6x8str(0,7,"ki");
//    oled_printf_float(50,7,direction_pid.ki,5,1);//转向I

    oled_p6x8str(0,7,"kd");
    oled_printf_float(50,7,direction_pid.kd,5,1);//转向D

}

void OledViewCoefficient()//三级页面
{
    oled_p6x8str(50,0,"Coefficient");

    oled_p6x8str(0,1,"firstpass_parameters");//一阶低通滤波系数
    oled_printf_float(50,1,first_filter1.low_pass_parameter,5,1);//转向P

    oled_p6x8str(0,2,"pulse_speed_coefficient");
    oled_printf_float(50,2,pulse_speed_coefficient,5,1);//转向I

    oled_p6x8str(0,3,"complementary_coefficient");
    oled_printf_float(50,3,complementary_coefficient,5,1);//转向D

}



/*-----------------------------------------------------------------------------module------------------------------------------------------------------------------------------------*/
void Mode()//拨码开关改变模式
{
    if(gpio_get(BMST) == 0 &&
        gpio_get(BMND) == 0 &&
        gpio_get(BMRD) == 0 &&
        gpio_get(BMTH) == 0)
        mode_flag=0;//页面切换
    else if(gpio_get(BMST) == 1 &&
            gpio_get(BMND) == 0 &&
            gpio_get(BMRD) == 0 &&
            gpio_get(BMTH) == 0)
        mode_flag=1;//速度参数调整
    else if(gpio_get(BMST) == 1 &&
            gpio_get(BMND) == 1 &&
            gpio_get(BMRD) == 0 &&
            gpio_get(BMTH) == 0)
        mode_flag=2;//方向参数调整
    else if(gpio_get(BMST) == 1 &&
            gpio_get(BMND) == 1 &&
            gpio_get(BMRD) == 1 &&
            gpio_get(BMTH) == 0)
        mode_flag=3;//系数调整
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 0 &&
//            gpio_get(BM3) == 1 &&
//            gpio_get(BM4) == 0)
//        mode_flag=2;
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 0 &&
//            gpio_get(BM3) == 1 &&
//            gpio_get(BM4) == 1)
//        mode_flag=3;
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 1 &&
//            gpio_get(BM3) == 0 &&
//            gpio_get(BM4) == 0)
//        mode_flag=4;
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 1 &&
//            gpio_get(BM3) == 0 &&
//            gpio_get(BM4) == 1)
//        mode_flag=5;
//    else if
//        (gpio_get(BM1) == 0 &&
//            gpio_get(BM2) == 1 &&
//            gpio_get(BM3) == 1 &&
//            gpio_get(BM4) == 0)
//        mode_flag=6;
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

    key_up_state=gpio_get(KEY_UP);
    key_down_state=gpio_get(KEY_DOWN);
    key_right_state=gpio_get(KEY_RIGHT);
    key_left_state=gpio_get(KEY_LEFT);

    switch(mode_flag)
    {
        case 0:                   //切换页面
        {if(key_up_state)
            {
                interface_flag=0;//关闭oled
                oled_fill(0x00);
                key_up_state=0;
            } else if(key_down_state)
            {
                interface_flag=1;//一级页面
                oled_fill(0x00);
                key_down_state=0;//关掉其余页面的标志位
            }else if(key_right_state)
            {
                interface_flag=2;//二级页面
                oled_fill(0x00);
                key_right_state=0;
            }else if(key_left_state)
            {
                interface_flag=3;//三级页面
                oled_fill(0x00);
                key_left_state=0;
            }
        }break;
        case 1:                  //调速度参数
        {if(key_up_state)
            {
                speed_pid.kp+=1;
                key_up_state=0;
            } else if(key_down_state)
            {
                speed_pid.kp-=1;
                key_down_state=0;
            }else if(key_right_state)
            {
                speed_pid.ki+=1;
                key_right_state=0;
            }else if(key_left_state)
            {
                speed_pid.ki+=1;
                key_left_state=0;
            }
        }break;
        case 2:                  //调方向参数
        {if(key_up_state)
            {
                direction_pid.kp+=1;
                key_up_state=0;
            } else if(key_down_state)
            {
                direction_pid.kp-=1;
                key_down_state=0;
            }else if(key_right_state)
            {
                direction_pid.kd+=1;
                key_right_state=0;
            }else if(key_left_state)
            {
                direction_pid.kd-=1;
                key_left_state=0;
            }
        }break;
        case 3:                  //调小车系数
        {if(key_up_state)
            {
                first_filter1.low_pass_parameter+=0.1;
                key_up_state=0;
            } else if(key_down_state)
            {
                first_filter1.low_pass_parameter-=0.1;
                key_down_state=0;
            }
        }break;
        default:
            break;
//            else if(key_right_state)
//            {
//                pulse_speed_coefficient+=1;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                pulse_speed_coefficient-=1;
//                key_left_state=0;
//            }break;


    }


    switch(interface_flag)
    {
        case 0:
            break;
        case 1:
            OledViewPhysicalCondition();//小车状态
            break;
        case 2:
            OledViewParameters();//小车pid参数
            break;
        case 3:
            OledViewCoefficient();//小车系数
            break;
    }

//    switch(mode_flag)
//    {
//        case 0:
//
//            if(gpio_get(KEY1) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY1) == 1)
//                    interface_flag=1;//界面flag
//                OledViewSpecification();//一级界面
//            }
//            if(gpio_get(KEY2) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY2) == 1)
//                    interface_flag=2;//界面flag
//                OledViewPhysicalCondition();//二级界面
//            }
//            if(gpio_get(KEY3) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY3) == 1)
//                    interface_flag=3;//界面flag
//                OledViewParameters();//三级界面
//            }
//            if(gpio_get(KEY3) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY3) == 1)
//                    interface_flag=4;//界面flag
//                OledViewCoefficient();//四级界面
//            }
//            break;
//        case 1:
//            switch(interface_flag)
//                case 1:
//                    OledViewSpecification();//一级界面
//                    break;
//                case 2:
//                    OledViewPhysicalCondition();
//                    break;
//                case 3:
//                    OledViewParameters();//三级界面
//                    break;
//                case 4:
//                    OledViewCoefficient();//四级界面
//                    break;
//            if(gpio_get(KEY1) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY1) == 1)
//                  OledViewSpecification();
//            }
//            if(gpio_get(KEY2) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY2) == 1)
//                    OledViewPhysicalCondition();//二级界面
//            }
//            if(gpio_get(KEY3) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY3) == 1)
//                    OledViewParameters();//三级界面
//            }
//            if(gpio_get(KEY3) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY3) == 1)
//                    OledViewCoefficient();//四级界面
//            }
//            break;

}