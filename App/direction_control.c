#include "include.h"
#include "common.h"

float Duty=SD5_CENTER;

void duoji_init()     //��ʼ��
{
     ftm_pwm_init(SD5_FTM,SD5_CH,SD5_HZ,SD5_CENTER,SD5_PIN);      //��ʼ�� ��� PWM   FTM1��FTM_CHO��300��48(38-57)��PTA8
}

void duoji_control()    //�������
{   
    if(shexiangtou_flag == 1) 
    {
       Duty_gain1();    //��ȡռ�ձ�
    }
    if(dianci_flag == 1)
    {
        Duty_gain2();   //��ȡռ�ձ�
    }
    if(Duty>=57)
    {
        Duty=57;
    }
    if(Duty<=38)
    {
        Duty=38;
    }    
    ftm_pwm_duty(SD5_FTM,SD5_CH,Duty);        //duty��Χ24-40
}
