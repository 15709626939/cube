#ifndef __FEATURE_H__
#define __FEATURE_H__



#include "include.h"
#include "common.h"

extern void Center_line_deal();       //中线处理
extern void Camera_Element_Decision();          //摄像头赛道元素判定
extern void Duty_gain1();         //获取占空比
extern void shizi_deal();        //十字处理
extern int16 createPoint(int type, int line);   //利用最小二乘法生成需要补全的点
extern void huaxian(int x1,int y1,int x2,int y2);  //将两个点之间连成一条线段

#endif