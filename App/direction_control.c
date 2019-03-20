#include "include.h"
#include "common.h"

float Duty=SD5_CENTER;

void duoji_init()     //初始化
{
     ftm_pwm_init(SD5_FTM,SD5_CH,SD5_HZ,SD5_CENTER,SD5_PIN);      //初始化 舵机 PWM   FTM1、FTM_CHO、300、48(38-57)、PTA8
}

void duoji_control()    //舵机控制
{   
    if(shexiangtou_flag == 1) 
    {
       Duty_gain1();    //获取占空比
    }
    if(dianci_flag == 1)
    {
        Duty_gain2();   //获取占空比
    }
    if(Duty>=57)
    {
        Duty=57;
    }
    if(Duty<=38)
    {
        Duty=38;
    }    
    ftm_pwm_duty(SD5_FTM,SD5_CH,Duty);        //duty范围24-40
}
