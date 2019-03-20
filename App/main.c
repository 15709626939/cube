#include "common.h"
#include "include.h"


uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_W*CAMERA_H];                           //����洢��ѹ���ͼ�����飨���ڶ�ȡ����ֵ��ͼ����

uint8 shexiangtou_flag = 0;         //����־λΪ1ʱ�ܸñ�־
uint8 dianci_flag = 1;

//��������
extern void PORTA_IRQHandler();
extern void DMA0_IRQHandler();


void main(void)               
{   
    led_init(LED3);                         //��ʼ��LED1
    if(shexiangtou_flag == 1) camera_init(imgbuff); //����ͷ��ʼ��
    if(dianci_flag == 1) 
    {
      ad_init(); //ad��ʼ��   
      AD_MAX_MIN(); //��ȡ�����Сֵ
    }          
    printf("system init success11\n");
    duoji_init();     //�����ʼ��
    dianji_init();    //�����ʼ��
    

    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //����LPTMR���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_DMA16_VECTORn , DMA0_IRQHandler);     //����LPTMR���жϷ�����Ϊ PORTA_IRQHandler

    while(1)
    {
        if(camera == 1)
        {
            if(ov7725_eagle_img_flag == IMG_FINISH)
            {
                Camera_img_deal();           //ͼ����
                camera_get_img();           //����ͷ��ȡͼ��
            }
            if(ov7725_eagle_img_flag == IMG_FAIL)
            {
                camera_get_img();
            }
        }
        
        if(dianci_flag == 1)
        {
            ad_deal();    //ad����
        }
        
        //luzhang_deal();      //·�ϴ���
        
    }
}

