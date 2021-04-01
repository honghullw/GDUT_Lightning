#include "human_computer_interaction.h"

float increment=0;//方案三增量

f car_physical_condition;

extern a data;
extern b speed_data;
extern c angle_data;

extern c angle_data;
extern d  pid_data;

extern e angularspeed_pid;
extern e up_pid;
extern e speed_pid;
extern e direction_pid;
extern e current_pid;

extern PID Speed;
extern PID Angle;
extern PID Gyro;
extern PID Turn;

uint16 mode_flag;
int16 interface_flag=0;

uint16 key_up_state;
uint16 key_down_state;
uint16 key_right_state;
uint16 key_left_state;

extern first_order_low_pass_filter_parameters first_filter1;
extern float balance_angle_value;//更改小车机械零点
extern int32 speed_pulse;

extern float temp1;

extern float GyroControlOut;
extern float DirectionControlOut;

extern uint32 test_num;


extern float change_angle_coefficient;//角速度的角度数据转角度值系数(往加速度计的角度值去靠)//2000/32768
extern float complementary_coefficient;//互补滤波系数
void human_computer_interaction_init()
{

    car_physical_condition.angle=angle_data.fuse_angle_value;
    car_physical_condition.fix_angle=angle_data.fuse_angle_pid_value;
    car_physical_condition.position=angle_data.fuse_angle_value;
    car_physical_condition.speed=speed_data.car_speed;

}


//void OledViewSpecification()//告诉用户如何操作按一次按键换一个显示页面//拨码开关为0000时按键进入选择模式//说明与菜单//一级界面
//{
//    oled_p6x8str(0,0,"HELLOW");
//}
/*---------------------------------------------------------------------------oled-------------------------------------------------------------------------------------------------*/
void OledViewPhysicalCondition()//二级界面
{
//    oled_printf_float(0,0,angle_data.angular_speed_y_data,3,1);
//    oled_printf_float(0,1,angle_data.angularspeed_angle_value,3,1);
//    oled_printf_float(0,2,angle_data.accelerate_angle_value,3,1);
//
//    oled_p6x8str(0,4,"L_Enc");
//    oled_printf_float(30,4,speed_data.left_wheel_pulse_num,5,1);
//    oled_p6x8str(0,5,"R_Enc");
//    oled_printf_float(30,5,speed_data.right_wheel_pulse_num,5,1);
//    oled_printf_float(0,6,GyroControlOut,5,5);
  
    oled_printf_float(0,1,GyroControlOut,5,5);
      oled_printf_float(10,2,data.filter_inductance_data[0],5,1);//输出小车电感
    oled_printf_float(10,3,data.filter_inductance_data[1],5,1);//输出小车电感
//    oled_printf_float(10,4,data.filter_inductance_data[2],5,1);//输出小车电感
    oled_printf_float(10,5,data.filter_inductance_data[3],5,1);//输出小车电感
    oled_printf_float(10,6,data.filter_inductance_data[4],5,1);//输出小车电感
        oled_printf_float(10,7,angle_data.fuse_angle_value,3,1);
        oled_printf_float(10,4,direction_pid.actual_value,5,5);
}

//void OledViewParameters_1()//三级界面1
//{
//
////    oled_p6x8str(50,0,"Car Parameter");
//    //角速度环pid参数
//    oled_p6x8str(50,0,"Gyro Pid");
//
//    oled_p6x8str(0,1,"kp");
//    oled_printf_float(50,1,Gyro.P,5,1);//角速度P
//
//    oled_p6x8str(0,2,"ki");
//    oled_printf_float(50,2,Gyro.I,5,1);//角速度I
//
//    
//    //角度环pid参数
//    oled_p6x8str(50,4,"Angle Pid");
//
//    oled_p6x8str(0,5,"kp");
//    oled_printf_float(50,5,Angle.P,5,1);//角度P
//
//    oled_p6x8str(0,6,"kd");
//    oled_printf_float(50,6,Angle.D,5,1);//角度D
//
//}
//
//void OledViewParameters_2()//三级界面2
//{
//    
////    oled_p6x8str(50,0,"Car Parameter");
//    //速度环pid参数
//    oled_p6x8str(50,0,"Speed Pid");
//
//    oled_p6x8str(0,1,"kp");
//    oled_printf_float(50,1,Speed.P,5,1);//速度P
//
//    oled_p6x8str(0,2,"ki");
//    oled_printf_float(50,2,Speed.I,5,1);//速度I
////
////    oled_p6x8str(0,3,"kd");
////    oled_printf_float(50,3,Speed.D,5,1);//速度D
////
////    //转向环pid参数
////    oled_p6x8str(50,4,"Direction Pid");
////
////    oled_p6x8str(0,5,"kp");
////    oled_printf_float(50,5,Turn.P,5,1);//转向P
////
////    oled_p6x8str(0,6,"ki");
////    oled_printf_float(50,6,Turn.I,5,1);//转向I
////
////    oled_p6x8str(0,7,"kd");
////    oled_printf_float(50,7,Turn.D,5,1);//转向D
////
//}    

void OledViewParameters_1()//三级界面1
{

//    oled_p6x8str(50,0,"Car Parameter");
    //角速度环pid参数
    oled_p6x8str(50,0,"Gyro Pid");

    oled_p6x8str(0,1,"kp");
    oled_printf_float(50,1,angularspeed_pid.kp,5,2);//角速度P

    oled_p6x8str(0,2,"ki");
    oled_printf_float(50,2,angularspeed_pid.ki,5,2);//角速度I

    
    //角度环pid参数
    oled_p6x8str(50,4,"Angle Pid");

    oled_p6x8str(0,5,"kp");
    oled_printf_float(50,5,up_pid.kp,5,1);//角度P

    oled_p6x8str(0,6,"kd");
    oled_printf_float(50,6,up_pid.kd,5,1);//角度D

}

void OledViewParameters_2()//三级界面2
{
    
//    oled_p6x8str(50,0,"Car Parameter");
    //速度环pid参数
    oled_p6x8str(50,0,"Speed Pid");

    oled_p6x8str(0,1,"kp");
    oled_printf_float(50,1,speed_pid.kp,2,4);//速度P

    oled_p6x8str(0,2,"ki");
    oled_printf_float(50,2,speed_pid.ki,2,4);//速度I
//
//    oled_p6x8str(0,3,"kd");
//    oled_printf_float(50,3,Speed.D,5,1);//速度D
//
    //转向环pid参数
    oled_p6x8str(50,3,"Direction Pid");
//
    oled_p6x8str(0,4,"kp");
    oled_printf_float(50,4,direction_pid.kp,5,1);//转向P
//
//    oled_p6x8str(0,6,"ki");
//    oled_printf_float(50,6,Turn.I,5,1);//转向I
//
    oled_p6x8str(0,5,"kd");
    oled_printf_float(50,5,direction_pid.kd,5,1);//转向D
//
}    
    
void OledViewCoefficient()//四级页面
{
    oled_p6x8str(50,0,"Coefficient");

    oled_p6x8str(0,1,"b_angle");
    oled_printf_float(50,1,balance_angle_value,5,1);//转向P

    oled_p6x8str(0,2,"speed");
    oled_printf_int32(50,2,speed_pulse,10);//转向I
//
//    oled_p6x8str(0,3,"complementary_coefficient");
//    oled_printf_float(50,3,complementary_coefficient,5,1);//转向D

}



///*-----------------------------------------------------------------------------module------------------------------------------------------------------------------------------------*/
//void Mode()//拨码开关改变模式//方案1
//{
//    if(gpio_get(BMST) == 0 &&
//        gpio_get(BMND) == 0 &&
//        gpio_get(BMRD) == 0 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=0;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 0 &&
//            gpio_get(BMRD) == 0 &&
//            gpio_get(BMTH) == 1)
//        mode_flag=1;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 0 &&
//            gpio_get(BMRD) == 1 &&
//            gpio_get(BMTH) == 0)
//        mode_flag=2;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 0 &&
//            gpio_get(BMRD) == 1 &&
//            gpio_get(BMTH) == 1)
//        mode_flag=3;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 1 &&
//            gpio_get(BMRD) == 0 &&
//            gpio_get(BMTH) == 0)
//        mode_flag=4;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 1 &&
//            gpio_get(BMRD) == 0 &&
//            gpio_get(BMTH) == 1)
//        mode_flag=5;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 1 &&
//            gpio_get(BMRD) == 1 &&
//            gpio_get(BMTH) == 0)
//        mode_flag=6;
//    else if
//        (gpio_get(BMST) == 0 &&
//            gpio_get(BMND) == 1 &&
//            gpio_get(BMRD) == 1 &&
//            gpio_get(BMTH) == 1)
//        mode_flag=7;
//    else if
//        (gpio_get(BMST) == 1 &&
//            gpio_get(BMND) == 0 &&
//            gpio_get(BMRD) == 0 &&
//            gpio_get(BMTH) == 0)
//        mode_flag=8;
//    else if
//        (gpio_get(BMST) == 1 &&
//            gpio_get(BMND) == 0 &&
//            gpio_get(BMRD) == 0 &&
//            gpio_get(BMTH) == 1)
//        mode_flag=9;
//
//    switch(mode_flag)
//    {
//        case 0:
//            oled_fill(0x00);
//            OledViewSpecification();//一级界面
//            break;
//            
//        case 1:
//            oled_fill(0x00);
//            OledViewPhysicalCondition();//二级界面
//            break;
//            
//        case 2:
//           oled_fill(0x00);
//           OledViewParameters_f();
//           if(gpio_get(KEY_UP) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_UP) == 1)
//                Gyro.P += 5;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_DOWN) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_DOWN) == 1)
//                Gyro.P -= 5;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_LEFT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_LEFT) == 1)
//                Gyro.I += 5;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_RIGHT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_RIGHT) == 1)
//                Gyro.I -= 5;
//                OledViewParameters_f();//三级界面1
//            }
//            break;
//           
//        case 3:
//           oled_fill(0x00);
//           OledViewParameters_f();
//           if(gpio_get(KEY_UP) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_UP) == 1)
//                Angle.P += 50;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_DOWN) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_DOWN) == 1)
//                Angle.P -= 50;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_LEFT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_LEFT) == 1)
//                Angle.D += 50;
//                OledViewParameters_f();//三级界面1
//            }
//            if(gpio_get(KEY_RIGHT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_RIGHT) == 1)
//                Angle.D -= 50;
//                OledViewParameters_f();//三级界面1
//            }
//            break;
//           
//        case 4:
//           oled_fill(0x00);
//           OledViewParameters_s();
//           if(gpio_get(KEY_UP) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_UP) == 1)
//                Speed.P += 50;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_DOWN) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_DOWN) == 1)
//                Speed.P -= 50;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_LEFT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_LEFT) == 1)
//                Speed.I += 5;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_RIGHT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_RIGHT) == 1)
//                Speed.I -= 5;
//                OledViewParameters_s();//三级界面2
//            }
//            break;
//        
//        case 5:
//           oled_fill(0x00);
//           OledViewParameters_s();
//           if(gpio_get(KEY_UP) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_UP) == 1)
//                Turn.P += 50;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_DOWN) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_DOWN) == 1)
//                Turn.P -= 50;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_LEFT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_LEFT) == 1)
//                Turn.D += 50;
//                OledViewParameters_s();//三级界面2
//            }
//            if(gpio_get(KEY_RIGHT) == 1)
//            {
//                systick_delay_ms(100);
//                if(gpio_get(KEY_RIGHT) == 1)
//                Turn.D -= 50;
//                OledViewParameters_s();//三级界面2
//            }
//            break;
//
//    }
//}

//void Mode()//拨码开关改变模式//方案2
//{
//    if(gpio_get(BMST) == 0 &&
//        gpio_get(BMND) == 0 &&
//        gpio_get(BMRD) == 0 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=0;//页面切换
//    else if(gpio_get(BMST) == 1 &&
//        gpio_get(BMND) == 0 &&
//        gpio_get(BMRD) == 0 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=1;//角速度参数调整
//    else if(gpio_get(BMST) == 1 &&
//        gpio_get(BMND) == 1 &&
//        gpio_get(BMRD) == 0 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=2;//角度参数调整
//    else if(gpio_get(BMST) == 1 &&
//        gpio_get(BMND) == 1 &&
//        gpio_get(BMRD) == 1 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=3;//速度调整
//    else if(gpio_get(BMST) == 0 &&
//        gpio_get(BMND) == 0 &&
//        gpio_get(BMRD) == 1 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=4;//转向调整
//    else if(gpio_get(BMST) == 0 &&
//        gpio_get(BMND) == 1 &&
//        gpio_get(BMRD) == 0 &&
//        gpio_get(BMTH) == 0)
//        mode_flag=5;//系数调整
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 0 &&
////            gpio_get(BM3) == 1 &&
////            gpio_get(BM4) == 0)
////        mode_flag=2;
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 0 &&
////            gpio_get(BM3) == 1 &&
////            gpio_get(BM4) == 1)
////        mode_flag=3;
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 1 &&
////            gpio_get(BM3) == 0 &&
////            gpio_get(BM4) == 0)
////        mode_flag=4;
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 1 &&
////            gpio_get(BM3) == 0 &&
////            gpio_get(BM4) == 1)
////        mode_flag=5;
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 1 &&
////            gpio_get(BM3) == 1 &&
////            gpio_get(BM4) == 0)
////        mode_flag=6;
////    else if
////        (gpio_get(BM1) == 0 &&
////            gpio_get(BM2) == 1 &&
////            gpio_get(BM3) == 1 &&
////            gpio_get(BM4) == 1)
////        mode_flag=7;
////    else if
////        (gpio_get(BM1) == 1 &&
////            gpio_get(BM2) == 0 &&
////            gpio_get(BM3) == 0 &&
////            gpio_get(BM4) == 0)
////        mode_flag=8;
////    else if
////        (gpio_get(BM1) == 1 &&
////            gpio_get(BM2) == 0 &&
////            gpio_get(BM3) == 0 &&
////            gpio_get(BM4) == 1)
////        mode_flag=9;
//
//        systick_delay_ms(50);
//    key_up_state=gpio_get(KEY_UP);
//    key_down_state=gpio_get(KEY_DOWN);
//    key_right_state=gpio_get(KEY_RIGHT);
//    key_left_state=gpio_get(KEY_LEFT);
//
//    switch(mode_flag)
//    {
//        case 0:                   //切换页面
//        {if(key_up_state)
//            {
//                interface_flag--;//向上切换页面
//                if(interface_flag<0)//防止interface_flag<0;
//                {
//                    interface_flag=0;
//                }
//                oled_fill(0x00);
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                interface_flag++;//向下换页面
//                if(interface_flag>5)//防止interface_flag>3;
//                {
//                    interface_flag=5;
//                }
//                oled_fill(0x00);
//                key_down_state=0;//关掉其余页面的标志位
//            }else if(key_right_state)
//            {
//                interface_flag=5;//进入图像页面
//                oled_fill(0x00);
//                key_right_state=0;
//            }else if(key_left_state)//退出图像页面
//            {
//                interface_flag=0;//降低页面亮度页面
//                oled_fill(0x00);
//                key_left_state=0;
//            }
//        }break;
//        case 1:                  //调速度参数
//        {if(key_up_state)
//            {
//                angularspeed_pid.kp+=1;
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                angularspeed_pid.kp-=1;
//                key_down_state=0;
//            }else if(key_right_state)
//            {
//                angularspeed_pid.ki+=0.01;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                angularspeed_pid.ki-=0.01;
//                key_left_state=0;
//            }
//        }break;
//        case 2:                  //调方向参数
//        {if(key_up_state)
//            {
//                up_pid.kp+=1;
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                up_pid.kp-=1;
//                key_down_state=0;
//            }else if(key_right_state)
//            {
//                up_pid.kd+=1;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                up_pid.kd-=1;
//                key_left_state=0;
//            }
//        }break;
//        case 3:                  //调速度参数
//        {if(key_up_state)
//            {
//                speed_pid.kp+=0.005;
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                speed_pid.kp-=0.005;
//                key_down_state=0;
//            }else if(key_right_state)
//            {
//                speed_pid.ki+=0.0005;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                speed_pid.ki-=0.0005;
//                key_left_state=0;
//            }
//        }break;
//        case 4:                  //调速度参数
//        {if(key_up_state)
//            {
//                direction_pid.kp+=1;
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                direction_pid.kp-=1;
//                key_down_state=0;
//            }else if(key_right_state)
//            {
//                direction_pid.kd+=1;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                direction_pid.kd-=1;
//                key_left_state=0;
//            }
//        }break;
//        case 5:                  //调小车系数
//        {if(key_up_state)
//            {
//                balance_angle_value+=0.1;
//                key_up_state=0;
//            } else if(key_down_state)
//            {
//                balance_angle_value-=0.1;
//                key_down_state=0;
//            }
//            else if(key_right_state)
//            {
//                speed_pulse+=100;
//                key_right_state=0;
//            }else if(key_left_state)
//            {
//                speed_pulse-=100;
//                key_left_state=0;
//            }
//        }break;
//        default:
//            break;
//
//    }
//
//
//    switch(interface_flag)
//    {
//        case 0:
//            break;
//        case 1:
//            OledViewPhysicalCondition();//小车状态
//            break;
//        case 2:
//            OledViewParameters_1();//小车pid参数
//            break;
//        case 3:
//            OledViewParameters_2();//小车pid参数
//            break;    
//        case 4:
//            OledViewCoefficient();//小车系数
//            break;
//        case 5:
//            //图像页面
//            break;
//    }
//}


void Mode()//拨码开关改变模式//方案3 按键上下切换页面，拨码开关切换调参精度
{
    if(gpio_get(BMST) == 0 &&
        gpio_get(BMND) == 0 &&
        gpio_get(BMRD) == 0 &&
        gpio_get(BMTH) == 0)
        increment=0.00001;
    else if(gpio_get(BMST) == 0 &&
        gpio_get(BMND) == 0 &&
        gpio_get(BMRD) == 1 &&
        gpio_get(BMTH) == 0)
        increment=0.0001;
    else if(gpio_get(BMST) == 0 &&
        gpio_get(BMND) == 1 &&
        gpio_get(BMRD) == 0 &&
        gpio_get(BMTH) == 0)
        increment=0.001;
    else if(gpio_get(BMST) == 0 &&
        gpio_get(BMND) == 1 &&
        gpio_get(BMRD) == 1 &&
        gpio_get(BMTH) == 0)
        increment=0.01;
    else if(gpio_get(BMST) == 1 &&
        gpio_get(BMND) == 0 &&
        gpio_get(BMRD) == 0 &&
        gpio_get(BMTH) == 0)
        increment=0.1;
    else if(gpio_get(BMST) == 1 &&
        gpio_get(BMND) == 0 &&
        gpio_get(BMRD) == 1 &&
        gpio_get(BMTH) == 0)
        increment=1;
    else if(gpio_get(BMST) == 1 &&
        gpio_get(BMND) == 1 &&
        gpio_get(BMRD) == 0 &&
        gpio_get(BMTH) == 0)
        increment=10;
    else if(gpio_get(BMST) == 1 &&
        gpio_get(BMND) == 1 &&
        gpio_get(BMRD) == 1 &&
        gpio_get(BMTH) == 0)
        increment=100;


    systick_delay_ms(50);
    key_up_state=gpio_get(KEY_UP);
    key_down_state=gpio_get(KEY_DOWN);
    key_right_state=gpio_get(KEY_RIGHT);
    key_left_state=gpio_get(KEY_LEFT);


    if(key_up_state)
    {
        interface_flag--;//向上切换页面
        if(interface_flag<0)//防止interface_flag<0;
        {
            interface_flag=0;
        }
        oled_fill(0x00);

        key_up_state=0;
    } else if(key_down_state)
    {
        interface_flag++;//向下换页面
        if(interface_flag>12)//防止interface_flag>3;
        {
            interface_flag=12;
        }
        oled_fill(0x00);
        key_down_state=0;//关掉其余页面的标志位
    }

    switch(interface_flag)
    {
        case 0:
            OledViewPhysicalCondition();//小车状态
            break;
        case 1:
            oled_p6x8str(50,0,"Gyro Pid");
            oled_p6x8str(0,1,"angspeed_kp");
            oled_printf_float(70,1,angularspeed_pid.kp,5,3);//角速度P
            break;
        case 2:
            oled_p6x8str(50,0,"Gyro Pid");
            oled_p6x8str(0,1,"angspeed_ki");
            oled_printf_float(70,1,angularspeed_pid.ki,5,3);//角速度I
            break;
        case 3:
            oled_p6x8str(50,0,"Angle Pid");
            oled_p6x8str(0,1,"angle_kp");
            oled_printf_float(70,1,up_pid.kp,5,3);//角度P
            break;
        case 4:
            oled_p6x8str(50,0,"Angle Pid");
            oled_p6x8str(0,1,"angle_kd");
            oled_printf_float(70,1,up_pid.kd,5,3);//角度D
            break;
        case 5:
            oled_p6x8str(50,0,"Speed Pid");
            oled_p6x8str(0,1,"speed_kp");
            oled_printf_float(70,1,speed_pid.kp,2,5);//速度P
            break;
        case 6:
            oled_p6x8str(50,0,"Speed Pid");
            oled_p6x8str(0,1,"speed_ki");
            oled_printf_float(70,1,speed_pid.ki,2,5);//速度I
            break;
        case 7:
            oled_p6x8str(50,0,"Direction Pid");
            oled_p6x8str(0,1,"direc_kp");
            oled_printf_float(70,1,direction_pid.kp,5,3);//转向P
            break;
        case 8:
            oled_p6x8str(50,0,"Direction Pid");
            oled_p6x8str(0,1,"direc_kd");
            oled_printf_float(70,1,direction_pid.kd,5,1);//转向D
            break;
        case 9:
            oled_p6x8str(50,0,"Coefficient");
            oled_p6x8str(0,1,"bal_angle");
            oled_printf_float(70,1,balance_angle_value,5,1);//转向P
            break;
        case 10:
            oled_p6x8str(50,0,"Coefficient");
            oled_p6x8str(0,1,"speed_pulse");
            oled_printf_int32(70,1,speed_pulse,10);//转向I
            break;
        case 11:
            oled_p6x8str(50,0,"Coefficient");
            oled_p6x8str(0,1,"c_a_c");
            oled_printf_float(70,1,change_angle_coefficient,1,5);//转向I
            break;
        case 12:
            oled_p6x8str(50,0,"Coefficient");
            oled_p6x8str(0,1,"c_c");
            oled_printf_float(70,1,complementary_coefficient,1,5);//转向I    
            break;
            

    }
    switch(interface_flag)//调参
    {
        case 1:
            if(key_right_state)
            {
                angularspeed_pid.kp+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                angularspeed_pid.kp-=increment;
                key_left_state=0;
            }
            break;
        case 2:
            if(key_right_state)
            {
                angularspeed_pid.ki+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                angularspeed_pid.ki-=increment;
                key_left_state=0;
            }
            break;
        case 3:
            if(key_right_state)
            {
                up_pid.kp+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                up_pid.kp-=increment;
                key_left_state=0;
            }
            break;
        case 4:
            if(key_right_state)
            {
                up_pid.kd+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                up_pid.kd-=increment;
                key_left_state=0;
            }
            break;
        case 5:
            if(key_right_state)
            {
                speed_pid.kp+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                speed_pid.kp-=increment;
                key_left_state=0;
            }
            break;
        case 6:
            if(key_right_state)
            {
                speed_pid.ki+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                speed_pid.ki-=increment;
                key_left_state=0;
            }
            break;
        case 7:
            if(key_right_state)
            {
                direction_pid.kp+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                direction_pid.kp-=increment;
                key_left_state=0;
            }
            break;
        case 8:
            if(key_right_state)
            {
                direction_pid.kd+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                direction_pid.kd-=increment;
                key_left_state=0;
            }
            break;
        case 9:
            if(key_right_state)
            {
                balance_angle_value+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                balance_angle_value-=increment;
                key_left_state=0;
            }
            break;
        case 10:
            if(key_right_state)
            {
                speed_pulse+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                speed_pulse-=increment;
                key_left_state=0;
            }
            break;
        case 11:
            if(key_right_state)
            {
                change_angle_coefficient+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                change_angle_coefficient-=increment;
                key_left_state=0;
            }
            break;
         case 12:
            if(key_right_state)
            {
                complementary_coefficient+=increment;
                key_right_state=0;
            }else if(key_left_state)
            {
                complementary_coefficient-=increment;
                key_left_state=0;
            }
            break;


    }



}