#ifndef __DEFINE_H__
#define __DEFINE_H__



#include "include.h"
#include "common.h"

/*******************图像相关*********************/
#define  camera_width        (160)    
#define  camera_height       (70)     
#define  GER                 (1)      //比例系数
#define  uart_Port           (UART0)        //uart模块号
#define  uart_frequency      (115200)       //uart频率
#define  white               (255)          //白色
#define  black               (0)          //黑色


extern uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
extern uint8 img[CAMERA_W*CAMERA_H];                           //定义存储解压后的图像数组（用于读取像素值，图像处理）
extern uint8 ov7725_eagle_img_flag;


/*****************舵机相关***********************/
#define SD5_FTM FTM1         //舵机用的定时器
#define SD5_CH FTM_CH0      //舵机定时器的通道
#define SD5_HZ    (300)      //舵机频率
#define SD5_PIN   PTA8     //舵机引脚
#define SD5_CENTER 48.5 //舵机中心值

extern float Duty;       //定义占空比

/******************电磁相关*************************/
//定义AD接口
#define AMP1  ADC1_SE5a         //PTE1    外面两个垂直电感
#define AMP2  ADC1_SE6a        //PTE2
#define AMP3  ADC1_SE4a        //PTE0     里面两个八字电感
#define AMP4  ADC1_SE7a        //PTE3


extern uint8 shexiangtou_flag;         //当标志位为1时跑该标志
extern uint8 dianci_flag;
extern uint8 zhangai_flag;

extern float timevar;


#endif
