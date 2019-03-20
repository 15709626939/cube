#include "include.h"
#include "common.h"

#define  TRIG  PTA6    //���������Ͷ�
#define  ECHG  PTA7   //���������ն�
uint8 zhangai_flag;

float timevar;
void distance()      //���
{
    timevar=0;
    gpio_init(TRIG,GPO,0);   //��ʼ�����Ͷ�  ����͵�ƽ
    gpio_init(ECHG,GPI,0);   //��ʼ�����ն�  ����
    
    gpio_set(TRIG,1);     //������������   
    pit_delay_us(PIT2,20);       
    gpio_set(TRIG,0);           //����һ��20us�ĸߵ�ƽ����
        
        
    while(gpio_get (ECHG) == 0);             //�ȴ���ƽ��ߣ��͵�ƽһֱ�ȴ�
    pit_time_start  (PIT2);   //��ʼ��ʱ
    while(gpio_get(ECHG) == 1);              //�ȴ���ƽ��ͣ��ߵ�ƽһֱ�ȴ�
    timevar = pit_time_get(PIT2);    //ֹͣ��ʱ����ȡ��ʱʱ��
     //timevar = timevar * 340 /2/10;
     timevar = timevar*(331.4+0.607*10)/2000;  //�����¶Ȳ���
     //DELAY_MS(60); //��ʱ60MS��������ȷ�����Բ���

}

void luzhang_deal()
{
    distance();
    if((int)(timevar)/1000<=40)
    {
        zhangai_flag=1;
    }
    else zhangai_flag=0;
    if(zhangai_flag==1)
    {
        ftm_pwm_duty(SD5_FTM,SD5_CH,57);
        DELAY_MS(500);
        ftm_pwm_duty(SD5_FTM,SD5_CH,38);
        DELAY_MS(100);
        ftm_pwm_duty(SD5_FTM,SD5_CH,48);
        DELAY_MS(500);
        ftm_pwm_duty(SD5_FTM,SD5_CH,38);
        DELAY_MS(800);
        ftm_pwm_duty(SD5_FTM,SD5_CH,57);
        DELAY_MS(100);
        
    }
}

