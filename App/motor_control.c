#include "include.h"
#include "common.h"


void  dianji_init()     //初始化
{
     ftm_pwm_init(FTM0, FTM_CH0,7*1000,20.0,FTM0_CH0_PIN);         // 频率为10k ，占空比为 80.0%  正转FTM_CH0  FTM0_CH0_PIN （PC1）反转FTM_CH1  FTM0_CH1_PIN （PC2）
     //ftm_pwm_init(FTM0, FTM_CH1,7*1000,20.0,FTM0_CH1_PIN);
}
  
void dianji_control()     //电机定速跑
{
    ftm_pwm_duty(FTM0,FTM_CH0,91.0);                              //占空比94%（占空比越大速度越慢）    //shexiangtou93,dianci90
    //ftm_pwm_duty(FTM0,FTM_CH1,17.0);
}
