#include "include.h"
#include "common.h"

#define  TRIG  PTA6    //超声波发送端
#define  ECHG  PTA7   //超声波接收端
uint8 zhangai_flag;

float timevar;
void distance()      //测距
{
    timevar=0;
    gpio_init(TRIG,GPO,0);   //初始化发送端  输出低电平
    gpio_init(ECHG,GPI,0);   //初始化接收端  输入
    
    gpio_set(TRIG,1);     //产生触发脉冲   
    pit_delay_us(PIT2,20);       
    gpio_set(TRIG,0);           //产生一个20us的高电平脉冲
        
        
    while(gpio_get (ECHG) == 0);             //等待电平变高，低电平一直等待
    pit_time_start  (PIT2);   //开始计时
    while(gpio_get(ECHG) == 1);              //等待电平变低，高电平一直等待
    timevar = pit_time_get(PIT2);    //停止计时，获取计时时间
     //timevar = timevar * 340 /2/10;
     timevar = timevar*(331.4+0.607*10)/2000;  //加上温度补偿
     //DELAY_MS(60); //延时60MS，测距更精确，可以不用

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

