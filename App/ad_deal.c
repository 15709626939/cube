#include "include.h"
#include "common.h"

uint16 var1,var_1,var2,var_2,var3,var_3,var4,var_4;
uint8 rightsmall_huandao_flag,leftsmall_huandao_flag,huandao_number;
float PianCha,before_PianCha;
int w,AD_var1_max=0,AD_var2_max=0,AD_var3_max=0,AD_var4_max=0,AD_var1_min=10,AD_var2_min=10,AD_var3_min=10,AD_var4_min=10;

void ad_init()     //初始化
{
    adc_init(AMP1);              
    adc_init(AMP2);
    adc_init(AMP3);              
    adc_init(AMP4);
}

void ad_deal()    //ad处理
{
    before_PianCha=PianCha;           
    AD_0_1();   //归一化
    PianCha=var_2 - var_1;
//    if(huandao_number==0)
//    {
//        ad_Element_Decision();   //环岛处理
//    }
    duoji_control();       //舵机
    dianji_control();      //电机   定速跑 94% pwm
}

void ad_Element_Decision()
{
//    if((var_1>60&&var_2==100&&var_3>80&&var_4<20)||(var_1==100&&var_2>60&&var_3<20&&var_4>80)) 
//    {
//      huandao_flag=1;
//    }
//    if(huandao_flag==1) 
//    {
//      PianCha=var_3 - var_4;w++;
//    }
//    if(w==250) 
//    {
//      PianCha=var_2 - var_1;
//      huandao_flag=0;
//      w=0;
//    }
    
    if(var_1>60&&var_2==100&&var_3>80&&var_4<20)        //右小环
    {
      rightsmall_huandao_flag=1;
      PianCha=var_3 - var_4;
      w++;
      if(w==20) 
      {
        PianCha=var_2 - var_1;
        rightsmall_huandao_flag=0;
        w=0;
        huandao_number=1;
      }
    }
    if(var_1==100&&var_2>60&&var_3<20&&var_4>80)        //左小环
    {
      leftsmall_huandao_flag=1;
      PianCha=var_3 - var_4;
      w++;
      if(w==20) 
      {
        PianCha=var_2 - var_1;
        leftsmall_huandao_flag=0;
        w=0;
        huandao_number=1;
      }
    }
}

void AD_MAX_MIN()
{
    uint16 i,sum;
    for(i=0;i<50;i++)
    {
        var1=adc_once(AMP1, ADC_8bit);
        sum+=var1;
        DELAY_MS(5);
    }
    AD_var1_min=sum/50;//最小  
    sum=0;
    
    for(i=0;i<50;i++)
    {
        var2=adc_once(AMP2, ADC_8bit); 
        sum+=var2;
        DELAY_MS(5);
    }
    AD_var2_min=sum/50;//最小  
    sum=0;
    
    for(i=0;i<50;i++)
    {
        var3=adc_once(AMP3, ADC_8bit);
        sum+=var3;
        DELAY_MS(5);
    }
    AD_var3_min=sum/50;//最小  
    sum=0;
    
    for(i=0;i<50;i++)
    {
        var4=adc_once(AMP4, ADC_8bit);
        sum+=var4;
        DELAY_MS(5);
    }
    AD_var4_min=sum/50;//最小  
    sum=0;
    
    
    for(i=0;i<1500;i++)
    {
        var1=adc_once(AMP1, ADC_8bit);
        if(var1>=AD_var1_max) AD_var1_max=var1;
        DELAY_MS(1);
        
        var2=adc_once(AMP2, ADC_8bit);
        if(var2>=AD_var2_max) AD_var2_max=var2; 
        DELAY_MS(1); 
        
        var3=adc_once(AMP3, ADC_8bit);
        if(var3>=AD_var3_max) AD_var3_max=var3; 
        DELAY_MS(1); 
        
        var4=adc_once(AMP4, ADC_8bit);
        if(var4>=AD_var4_max) AD_var4_max=var4; 
        DELAY_MS(1); 
    }
    huandao_number=0;
}

void AD_0_1()   //归一化
{
     uint16 i,sum_1,sum_2,sum_3,sum_4;
     sum_1=0;sum_2=0;sum_3=0;sum_4=0;
     for(i=0;i<=50;i++)
     {
         var1=adc_once(AMP1, ADC_8bit);
         var2=adc_once(AMP2, ADC_8bit);
         var3=adc_once(AMP3, ADC_8bit);
         var4=adc_once(AMP4, ADC_8bit);
         sum_1+=var1;
         sum_2+=var2;
         sum_3+=var3;
         sum_4+=var4;
     }
     var1=sum_1/50;
     var2=sum_2/50;
     var3=sum_3/50;
     var4=sum_4/50;
 
     //限幅
    if(var1>=AD_var1_max) var1=AD_var1_max; 
    if(var2>=AD_var2_max) var2=AD_var2_max;
    if(var3>=AD_var3_max) var3=AD_var3_max; 
    if(var4>=AD_var4_max) var4=AD_var4_max;
    
    if(var1<AD_var1_min) AD_var1_min=var1; 
    if(var2<AD_var2_min) AD_var2_min=var2;
    if(var3<AD_var3_min) AD_var3_min=var3; 
    if(var4<AD_var4_min) AD_var4_min=var4;
     //归一化
    var_1=100*(var1-AD_var1_min)/(AD_var1_max-AD_var1_min);
    var_2=100*(var2-AD_var2_min)/(AD_var2_max-AD_var2_min);
    var_3=100*(var3-AD_var3_min)/(AD_var3_max-AD_var3_min);
    var_4=100*(var4-AD_var4_min)/(AD_var4_max-AD_var4_min);   
}


void Duty_gain2()         //获取占空比
{   
    float P=0.15,D=0.7;                      //P0.15 D0.7
    if(rightsmall_huandao_flag==1||leftsmall_huandao_flag==1)
    {
        P=0.08;
    }
       
    Duty = SD5_CENTER+P*PianCha+D*(PianCha-before_PianCha);
  
//  float P=10000,I=0.02,D=0.5; 
//  Duty=SD5_CENTER+PianCha*PianCha*PianCha/P+I*PianCha+D*(PianCha-before_PianCha);
}