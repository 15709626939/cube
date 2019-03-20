#ifndef __DEFINE_H__
#define __DEFINE_H__



#include "include.h"
#include "common.h"

/*******************ͼ�����*********************/
#define  camera_width        (160)    
#define  camera_height       (70)     
#define  GER                 (1)      //����ϵ��
#define  uart_Port           (UART0)        //uartģ���
#define  uart_frequency      (115200)       //uartƵ��
#define  white               (255)          //��ɫ
#define  black               (0)          //��ɫ


extern uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
extern uint8 img[CAMERA_W*CAMERA_H];                           //����洢��ѹ���ͼ�����飨���ڶ�ȡ����ֵ��ͼ����
extern uint8 ov7725_eagle_img_flag;


/*****************������***********************/
#define SD5_FTM FTM1         //����õĶ�ʱ��
#define SD5_CH FTM_CH0      //�����ʱ����ͨ��
#define SD5_HZ    (300)      //���Ƶ��
#define SD5_PIN   PTA8     //�������
#define SD5_CENTER 48.5 //�������ֵ

extern float Duty;       //����ռ�ձ�

/******************������*************************/
//����AD�ӿ�
#define AMP1  ADC1_SE5a         //PTE1    ����������ֱ���
#define AMP2  ADC1_SE6a        //PTE2
#define AMP3  ADC1_SE4a        //PTE0     �����������ֵ��
#define AMP4  ADC1_SE7a        //PTE3


extern uint8 shexiangtou_flag;         //����־λΪ1ʱ�ܸñ�־
extern uint8 dianci_flag;
extern uint8 zhangai_flag;

extern float timevar;


#endif
