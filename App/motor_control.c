#include "include.h"
#include "common.h"


void  dianji_init()     //��ʼ��
{
     ftm_pwm_init(FTM0, FTM_CH0,7*1000,20.0,FTM0_CH0_PIN);         // Ƶ��Ϊ10k ��ռ�ձ�Ϊ 80.0%  ��תFTM_CH0  FTM0_CH0_PIN ��PC1����תFTM_CH1  FTM0_CH1_PIN ��PC2��
     //ftm_pwm_init(FTM0, FTM_CH1,7*1000,20.0,FTM0_CH1_PIN);
}
  
void dianji_control()     //���������
{
    ftm_pwm_duty(FTM0,FTM_CH0,91.0);                              //ռ�ձ�94%��ռ�ձ�Խ���ٶ�Խ����    //shexiangtou93,dianci90
    //ftm_pwm_duty(FTM0,FTM_CH1,17.0);
}
