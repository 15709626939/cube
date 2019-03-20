#ifndef __AD_DEAL_H__
#define __AD_DEAL_H__
 
#include "include.h"
#include "common.h"

extern void ad_init();     //初始化
extern void ad_deal();    //ad处理
extern void AD_MAX_MIN(); //最大最小值获取
extern void ad_Element_Decision();  //AD特殊元素处理
extern void AD_0_1();   //归一化
extern void Duty_gain2();         //获取占空比



#endif